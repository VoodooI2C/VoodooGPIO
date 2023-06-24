//
//  VoodooGPIOAMD.cpp
//  VoodooGPIO
//
//  Created by Visual on 6/3/23.
//  Copyright © 2017 CoolStar. All rights reserved.
//  Copyright © 2023 Visual/Noot Inc/ChefKiss Inc. All rights reserved.
//

#include "VoodooGPIOAMD.hpp"

#define GPIO_LINE_DIRECTION_IN	1
#define GPIO_LINE_DIRECTION_OUT	0

OSDefineMetaClassAndStructors(VoodooGPIOAMD, VoodooGPIO);

void VoodooGPIOAMD::amd_gpio_irq_enable(unsigned pin) {
    UInt32 pin_reg = readl(this->base + pin*4);
    pin_reg |= BIT(INTERRUPT_ENABLE_OFF);
    pin_reg |= BIT(INTERRUPT_MASK_OFF);
    writel(pin_reg, this->base + pin*4);

    /*
     * When debounce logic is enabled it takes ~900 us before interrupts
     * can be enabled. During this "debounce warm up" period the
     * "INTERRUPT_ENABLE" bit will read as 0. Poll the bit here until it
     * reads back as 1, signaling that interrupts are now enabled.
     */
    UInt32 mask = BIT(INTERRUPT_ENABLE_OFF) | BIT(INTERRUPT_MASK_OFF);
    while ((readl(this->base + pin*4) & mask) != mask)
        continue;
}

void VoodooGPIOAMD::amd_gpio_irq_disable(unsigned pin) {
    UInt32 pin_reg = readl(this->base + pin*4);
    pin_reg &= ~BIT(INTERRUPT_ENABLE_OFF);
    pin_reg &= ~BIT(INTERRUPT_MASK_OFF);
    writel(pin_reg, this->base + pin*4);
}

void VoodooGPIOAMD::amd_gpio_irq_mask(unsigned pin) {
    UInt32 pin_reg = readl(this->base + pin*4);
    pin_reg &= ~BIT(INTERRUPT_MASK_OFF);
    writel(pin_reg, this->base + pin*4);
}

void VoodooGPIOAMD::amd_gpio_irq_unmask(unsigned pin) {
    UInt32 pin_reg = readl(this->base + pin*4);
    pin_reg |= BIT(INTERRUPT_MASK_OFF);
    writel(pin_reg, this->base + pin*4);
}

int VoodooGPIOAMD::amd_gpio_irq_set_wake(unsigned pin, unsigned int on) {
    UInt32 wake_mask = BIT(WAKE_CNTRL_OFF_S0I3) | BIT(WAKE_CNTRL_OFF_S3);

    UInt32 pin_reg = readl(this->base + pin*4);

    if (on)
        pin_reg |= wake_mask;
    else
        pin_reg &= ~wake_mask;

    writel(pin_reg, this->base + pin*4);

    return 0;
}

void VoodooGPIOAMD::amd_gpio_irq_eoi() {
    UInt32 reg = readl(this->base + WAKE_INT_MASTER_REG);
    reg |= EOI_MASK;
    writel(reg, this->base + WAKE_INT_MASTER_REG);
}

int VoodooGPIOAMD::amd_gpio_irq_set_type(unsigned pin, unsigned int type) {
    int ret = 0;

    UInt32 pin_reg = readl(this->base + pin*4);

    switch (type & IRQ_TYPE_SENSE_MASK) {
    case IRQ_TYPE_EDGE_RISING:
        pin_reg &= ~BIT(LEVEL_TRIG_OFF);
        pin_reg &= ~(ACTIVE_LEVEL_MASK << ACTIVE_LEVEL_OFF);
        pin_reg |= ACTIVE_HIGH << ACTIVE_LEVEL_OFF;
        break;
    case IRQ_TYPE_EDGE_FALLING:
        pin_reg &= ~BIT(LEVEL_TRIG_OFF);
        pin_reg &= ~(ACTIVE_LEVEL_MASK << ACTIVE_LEVEL_OFF);
        pin_reg |= ACTIVE_LOW << ACTIVE_LEVEL_OFF;
        break;
    case IRQ_TYPE_EDGE_BOTH:
        pin_reg &= ~BIT(LEVEL_TRIG_OFF);
        pin_reg &= ~(ACTIVE_LEVEL_MASK << ACTIVE_LEVEL_OFF);
        pin_reg |= BOTH_EADGE << ACTIVE_LEVEL_OFF;
        break;
    case IRQ_TYPE_LEVEL_HIGH:
        pin_reg |= LEVEL_TRIGGER << LEVEL_TRIG_OFF;
        pin_reg &= ~(ACTIVE_LEVEL_MASK << ACTIVE_LEVEL_OFF);
        pin_reg |= ACTIVE_HIGH << ACTIVE_LEVEL_OFF;
        break;
    case IRQ_TYPE_LEVEL_LOW:
        pin_reg |= LEVEL_TRIGGER << LEVEL_TRIG_OFF;
        pin_reg &= ~(ACTIVE_LEVEL_MASK << ACTIVE_LEVEL_OFF);
        pin_reg |= ACTIVE_LOW << ACTIVE_LEVEL_OFF;
        break;
    case IRQ_TYPE_NONE:
        break;
    default:
        TryLog("%s::VoodooGPIO Invalid type value\n", this->getName());
        ret = -1;
    }

    pin_reg |= CLR_INTR_STAT << INTERRUPT_STS_OFF;
    writel(pin_reg, this->base + pin*4);

    return ret;
}

#define PIN_IRQ_PENDING	(BIT(INTERRUPT_STS_OFF) | BIT(WAKE_STS_OFF))

bool VoodooGPIOAMD::do_amd_gpio_irq_handler(int irq) {
    UInt32 i, irqnr;
    bool ret = false;
    UInt32 regval;
    UInt64 status, mask;

    /* Read the wake status */
    status = readl(this->base + WAKE_INT_STATUS_REG1);
    status <<= 32;
    status |= readl(this->base + WAKE_INT_STATUS_REG0);

    /* Bit 0-45 contain the relevant status bits */
    status &= (1ULL << 46) - 1;
    UInt32* regs = (UInt32*)this->base;
    for (mask = 1, irqnr = 0; status; mask <<= 1, regs += 4, irqnr += 4) {
        if (!(status & mask))
            continue;

        status &= ~mask;

        /* Each status bit covers four pins */
        for (i = 0; i < 4; i++) {
            regval = readl((IOVirtualAddress)(regs + i));

            /* caused wake on resume context for shared IRQ */
            if (irq < 0 && (regval & BIT(WAKE_STS_OFF))) {
                TryLog("%s::VoodooGPIO Waking due to GPIO %d: 0x%x\n", this->getName(), irqnr + i, regval);
                return true;
            }

            if (!(regval & PIN_IRQ_PENDING) ||
                !(regval & BIT(INTERRUPT_MASK_OFF)))
                continue;

            UInt32 pin = irqnr + i;
            if (pin >= this->npins)
                break;

            if (OSObject *owner = this->pinInterruptActionOwners[pin])
                this->pinInterruptAction[pin](owner, this->pinInterruptRefcons[pin], this, pin);

            // For Level interrupts, we need to clear the interrupt status or we get too many interrupts
            if (this->interruptTypes[pin] & IRQ_TYPE_LEVEL_MASK)
                this->amd_gpio_irq_unmask(pin);

            /* Clear interrupt.
             * We must read the pin register again, in case the
             * value was changed while executing
             * generic_handle_domain_irq() above.
             * If we didn't find a mapping for the interrupt,
             * disable it in order to avoid a system hang caused
             * by an interrupt storm.
             */
            regval = readl((IOVirtualAddress)(regs + i));
            if (irq == 0) {
                regval &= ~BIT(INTERRUPT_ENABLE_OFF);
                TryLog("%s::VoodooGPIO: Disabling spurious GPIO IRQ %d\n", this->getName(), irqnr + i);
            }
            writel(regval, (IOVirtualAddress)(regs + i));

            ret = true;
        }
    }
    /* did not cause wake on resume context for shared IRQ */
    if (irq < 0)
        return false;

    this->amd_gpio_irq_eoi();

    return ret;
}

void VoodooGPIOAMD::amd_gpio_irq_init() {
    UInt32 pin_reg, mask;
    int i;

    mask = BIT(WAKE_CNTRL_OFF_S0I3) | BIT(WAKE_CNTRL_OFF_S3) |
        BIT(INTERRUPT_MASK_OFF) | BIT(INTERRUPT_ENABLE_OFF) |
        BIT(WAKE_CNTRL_OFF_S4);

    for (i = 0; i < this->npins; i++) {
        pin_reg = readl(this->base + i * 4);
        pin_reg &= ~mask;
        writel(pin_reg, this->base + i * 4);
    }
}

int VoodooGPIOAMD::amd_gpio_suspend() {
    for (size_t i = 0; i < this->npins; i++) {
        int pin = this->pins[i].number;

        this->saved_regs[i] = readl(this->base + pin * 4) & ~PIN_IRQ_PENDING;
    }

    return 0;
}

int VoodooGPIOAMD::amd_gpio_resume() {
    for (size_t i = 0; i < this->npins; i++) {
        int pin = this->pins[i].number;

        this->saved_regs[i] |= readl(this->base + pin * 4) & PIN_IRQ_PENDING;
        writel(this->saved_regs[i], this->base + pin * 4);
    }

    return 0;
}

void VoodooGPIOAMD::InterruptOccurred(void *refCon, IOService *nub, int source) {
    this->do_amd_gpio_irq_handler(source);
}

/**
 * @param pin 'Software' pin number (i.e. GpioInt)
 * @param interruptType variable to store interrupt type for specified GPIO pin.
 */
IOReturn VoodooGPIOAMD::getInterruptType(int pin, int *interruptType) {
    if (pin < 0 || pin >= this->npins)
        return kIOReturnNoInterrupt;

    return this->getProvider()->getInterruptType(0, interruptType);
}

/**
 * @param pin 'Software' pin number (i.e. GpioInt).
 */
IOReturn VoodooGPIOAMD::registerInterrupt(int pin, OSObject *target, IOInterruptAction handler, void *refcon) {
    if (pin < 0 || pin >= this->npins)
        return kIOReturnNoInterrupt;

    IOLog("%s::Registering GPIO IRQ pin 0x%02X\n", this->getName(), pin);

    if (this->pinInterruptActionOwners[pin])
        return kIOReturnNoResources;

    if (OSNumber* registered_pin = OSNumber::withNumber(pin, 32)) {
        if (!this->registered_pin_list->setObject(registered_pin)) {
            IOLog("%s::Unable to register pin into list\n", this->getName());
            registered_pin->release();
            return kIOReturnNoResources;
        }
        registered_pin->release();

        this->pinInterruptActionOwners[pin] = target;
        this->pinInterruptAction[pin] = handler;
        this->pinInterruptRefcons[pin] = refcon;
    } else {
        IOLog("%s::Unable to allocate interrupt pin", this->getName());
        return kIOReturnNoResources;
    }

    IOLog("%s::Successfully registered GPIO IRQ pin 0x%02X\n", this->getName(), pin);

    if (this->registered_pin_list->getCount() == 1)
        return this->getProvider()->registerInterrupt(0, this, OSMemberFunctionCast(IOInterruptAction, this, &VoodooGPIOAMD::InterruptOccurred));

    return kIOReturnSuccess;
}

/**
 * @param pin 'Software' pin number (i.e. GpioInt).
 */
IOReturn VoodooGPIOAMD::unregisterInterrupt(int pin) {
    if (pin < 0 || pin >= this->npins)
        return kIOReturnNoInterrupt;

    IOLog("%s::Unregistering GPIO IRQ pin 0x%02X\n", this->getName(), pin);

    this->amd_gpio_irq_mask(pin);

    this->pinInterruptActionOwners[pin] = NULL;
    this->pinInterruptAction[pin] = NULL;
    this->interruptTypes[pin] = 0;
    this->pinInterruptRefcons[pin] = NULL;

    for (int i = this->registered_pin_list->getCount() - 1; i >= 0; i--) {
        OSNumber* registered_pin = OSDynamicCast(OSNumber, this->registered_pin_list->getObject(i));
        if (registered_pin && registered_pin->unsigned32BitValue() == pin) {
            this->registered_pin_list->removeObject(i);
        }
    }

    if (this->registered_pin_list->getCount() == 0)
        return getProvider()->unregisterInterrupt(0);

    return kIOReturnSuccess;
}

/**
 * @param pin 'Software' pin number (i.e. GpioInt).
 */
IOReturn VoodooGPIOAMD::enableInterrupt(int pin) {
    if (pin < 0 || pin >= this->npins || !this->pinInterruptActionOwners[pin])
        return kIOReturnNoInterrupt;

    this->amd_gpio_irq_enable(pin);
    this->amd_gpio_irq_set_type(pin, this->interruptTypes[pin]);
    this->amd_gpio_irq_unmask(pin);
    return this->getProvider()->enableInterrupt(0);
}

/**
 * @param pin 'Software' pin number (i.e. GpioInt).
 */
IOReturn VoodooGPIOAMD::disableInterrupt(int pin) {
    if (pin < 0 || pin >= this->npins)
        return kIOReturnNoInterrupt;

    this->amd_gpio_irq_disable(pin);
    this->amd_gpio_irq_mask(pin);
    return this->getProvider()->disableInterrupt(0);
}

/**
 * @param pin 'Software' pin number (i.e. GpioInt).
 * @param type Interrupt type to set for specified pin.
 */
IOReturn VoodooGPIOAMD::setInterruptTypeForPin(int pin, int type) {
    if (pin < 0 || pin >= this->npins)
        return kIOReturnNoInterrupt;

    this->interruptTypes[pin] = type;
    return kIOReturnSuccess;
}

bool VoodooGPIOAMD::start(IOService *provider) {
    this->pins = kerncz_pins;
    this->npins = ARRAY_SIZE(kerncz_pins);
    this->groups = kerncz_groups;
    this->ngroups = ARRAY_SIZE(kerncz_groups);
    this->functions = pmx_functions;
    this->nfunctions = ARRAY_SIZE(pmx_functions);

    IOLog("%s::Loading GPIO Data for AMD\n", this->getName());

    if (!IOService::start(provider))
        return false;

    this->isInterruptBusy = true;

    this->workLoop = getWorkLoop();
    if (!this->workLoop) {
        IOLog("%s::Failed to get workloop!\n", this->getName());
        stop(provider);
        return false;
    }
    workLoop->retain();

    this->command_gate = IOCommandGate::commandGate(this);
    if (!this->command_gate || (this->workLoop->addEventSource(this->command_gate) != kIOReturnSuccess)) {
        IOLog("%s Could not open command gate\n", this->getName());
        stop(provider);
        return false;
    }

    IOLog("%s::VoodooGPIO Init!\n", this->getName());

    this->saved_regs = IONewZero(UInt32, this->npins);
    if (!this->saved_regs) {
        IOLog("%s::Failed to allocate saved_regs!\n", this->getName());
        stop(provider);
        return false;
    }

    this->mmap = provider->mapDeviceMemoryWithIndex(0);
    if (!this->mmap) {
        IOLog("%s:VoodooGPIO error mapping base 0\n", this->getName());
        return false;
    }
    this->base = this->mmap->getVirtualAddress();

    this->registered_pin_list = OSArray::withCapacity(2);
    if (!this->registered_pin_list) {
        IOLog("%s::Failed to allocate registered_pin_list!\n", this->getName());
        return false;
    }

    this->isInterruptBusy = false;
    this->controllerIsAwake = true;

    this->pinInterruptActionOwners = IONewZero(OSObject*, this->npins);
    this->pinInterruptAction = IONewZero(IOInterruptAction, this->npins);
    this->interruptTypes = IONewZero(unsigned, this->npins);
    this->pinInterruptRefcons = IONewZero(void *, this->npins);

    this->amd_gpio_irq_init();

    this->registerService();

    // Declare an array of two IOPMPowerState structures (kMyNumberOfStates = 2).

#define kMyNumberOfStates 2

    static IOPMPowerState myPowerStates[kMyNumberOfStates];
    // Zero-fill the structures.
    bzero (myPowerStates, sizeof(myPowerStates));
    // Fill in the information about your device's off state:
    myPowerStates[0].version = 1;
    myPowerStates[0].capabilityFlags = kIOPMPowerOff;
    myPowerStates[0].outputPowerCharacter = kIOPMPowerOff;
    myPowerStates[0].inputPowerRequirement = kIOPMPowerOff;
    // Fill in the information about your device's on state:
    myPowerStates[1].version = 1;
    myPowerStates[1].capabilityFlags = kIOPMPowerOn;
    myPowerStates[1].outputPowerCharacter = kIOPMPowerOn;
    myPowerStates[1].inputPowerRequirement = kIOPMPowerOn;

    this->PMinit();
    provider->joinPMtree(this);

    this->registerPowerDriver(this, myPowerStates, kMyNumberOfStates);

    return true;
}

void VoodooGPIOAMD::stop(IOService *provider) {
    IOLog("%s::VoodooGPIO stop!\n", this->getName());

    if (this->command_gate) {
        this->workLoop->removeEventSource(this->command_gate);
        OSSafeReleaseNULL(this->command_gate);
    }

    if (this->mmap) {
        OSSafeReleaseNULL(mmap);
    }

    if (this->registered_pin_list) {
        if (this->registered_pin_list->getCount() > 0) {
            IOLog("%s::Interrupt has not been unregistered by client\n", this->getName());
            this->getProvider()->unregisterInterrupt(0);
        }
        OSSafeReleaseNULL(this->registered_pin_list);
    }

    IOSafeDeleteNULL(this->pinInterruptActionOwners, OSObject*, this->npins);
    IOSafeDeleteNULL(this->pinInterruptAction, IOInterruptAction, this->npins);
    IOSafeDeleteNULL(this->interruptTypes, unsigned, this->npins);
    IOSafeDeleteNULL(this->pinInterruptRefcons, void*, this->npins);

    OSSafeReleaseNULL(this->workLoop);

    this->PMstop();

    IOService::stop(provider);
}

IOReturn VoodooGPIOAMD::setPowerState(unsigned long powerState, IOService *whatDevice) {
    if (whatDevice != this)
        return kIOPMAckImplied;

    if (powerState == 0) {
        this->controllerIsAwake = false;

        this->amd_gpio_suspend();
        IOLog("%s::Going to Sleep!\n", this->getName());
    } else {
        if (!this->controllerIsAwake) {
            this->controllerIsAwake = true;

            this->amd_gpio_resume();
            IOLog("%s::Woke up from Sleep!\n", this->getName());
        } else {
            IOLog("%s::GPIO Controller is already awake! Not reinitializing.\n", this->getName());
        }
    }
    return kIOPMAckImplied;
}
