//
//  VoodooGPIO.hpp
//  VoodooGPIO
//
//  Created by CoolStar on 8/14/17.
//  Copyright © 2017 CoolStar. All rights reserved.
//  Copyright © 2023 Visual/Noot Inc/ChefKiss Inc. All rights reserved.
//

#ifndef VoodooGPIO_h
#define VoodooGPIO_h
#include <IOKit/IOLib.h>
#include <IOKit/IOKitKeys.h>
#include <IOKit/acpi/IOACPIPlatformDevice.h>
#include <IOKit/IOWorkLoop.h>
#include <IOKit/IOInterruptEventSource.h>
#include <IOKit/IOLocks.h>
#include <IOKit/IOCommandGate.h>
#include "linuxirq.h"

// Exists in the macOS 10.15 SDK
#ifndef IOSafeDeleteNULL
#define IOSafeDeleteNULL(ptr, type, count)              \
    do {                                                \
        if (NULL != (ptr)) {                            \
            IODelete((ptr), type, count);               \
            (ptr) = NULL;                               \
        }                                               \
    } while (0)
#endif

inline UInt32 readl(IOVirtualAddress addr) {
    return *(const volatile UInt32 *)addr;
}

inline void writel(UInt32 b, IOVirtualAddress addr) {
    *(volatile UInt32 *)(addr) = b;
}

struct pinctrl_pin_desc {
    unsigned number;
    char *name;
    void *drv_data;
};

#define PINCTRL_PIN(a, b) {.number = a, .name = b}
#define PINCTRL_PIN_ANON(a) {.number = a}

#define kIOPMPowerOff 0

#if defined(__LP64__) && __LP64__
#define BITS_PER_LONG 64
#else
#define BITS_PER_LONG 32
#endif

#define BIT(x) 1UL << x
#define GENMASK(h, l) \
(((~0UL) << (l)) & (~0UL >> (BITS_PER_LONG - 1 - (h))))

#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

// Log only if current thread is interruptible, otherwise we will get a panic.
#define TryLog(args...) do { if (ml_get_interrupts_enabled()) IOLog(args); } while (0)

class VoodooGPIO : public IOService {
    OSDeclareAbstractStructors(VoodooGPIO);

protected:
    const struct pinctrl_pin_desc *pins = nullptr;
    size_t npins {0};
    bool controllerIsAwake = false;

    IOWorkLoop *workLoop = nullptr;
    IOCommandGate* command_gate = nullptr;
    OSArray* registered_pin_list = nullptr;
    bool isInterruptBusy = false;

    IOWorkLoop* getWorkLoop() const override;

public:
    virtual IOReturn setInterruptTypeForPin(int pin, int type) = 0;
};

#endif /* VoodooGPIO_h */
