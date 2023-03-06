//
//  VoodooGPIOAMD.cpp
//  VoodooGPIO
//
//  Created by Visual on 6/3/23.
//  Copyright © 2023 CoolStar. All rights reserved.
//  Copyright © 2023 Visual/Noot Inc/ChefKiss Inc. All rights reserved.
//

#include "VoodooGPIOAMD.hpp"

#define kIOPMPowerOff 0

bool VoodooGPIOAMD::start(IOService *provider) {
    this->pins = kerncz_pins;
    this->npins = ARRAY_SIZE(kerncz_pins);
    this->groups = kerncz_groups;
    this->ngroups = ARRAY_SIZE(kerncz_groups);
    this->functions = pmx_functions;
    this->nfunctions = ARRAY_SIZE(pmx_functions);

    IOLog("%s::Loading GPIO Data for AMD\n", getName());

    if (!IOService::start(provider))
        return false;

    isInterruptBusy = true;

    workLoop = getWorkLoop();
    if (!workLoop) {
        IOLog("%s::Failed to get workloop!\n", getName());
        stop(provider);
        return false;
    }
    workLoop->retain();

    command_gate = IOCommandGate::commandGate(this);
    if (!command_gate || (workLoop->addEventSource(command_gate) != kIOReturnSuccess)) {
        IOLog("%s Could not open command gate\n", getName());
        stop(provider);
        return false;
    }

    IOLog("%s::VoodooGPIO Init!\n", getName());

    registered_pin_list = OSArray::withCapacity(2);
    if (!registered_pin_list) {
        return false;
    }

    isInterruptBusy = false;
    controllerIsAwake = true;

    registerService();

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

    PMinit();
    provider->joinPMtree(this);

    registerPowerDriver(this, myPowerStates, kMyNumberOfStates);

    return true;
}
