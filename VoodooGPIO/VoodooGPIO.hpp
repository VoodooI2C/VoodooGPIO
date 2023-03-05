//
//  VoodooGPIO.h
//  VoodooGPIO
//
//  Created by CoolStar on 8/14/17.
//  Copyright © 2017 CoolStar. All rights reserved.
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

inline UInt32 readl(IOVirtualAddress addr) {
    return *(const volatile UInt32 *)addr;
}
inline void writel(UInt32 b, IOVirtualAddress addr) {
    *(volatile UInt32 *)(addr) = b;
}

class VoodooGPIO : public IOService {
    OSDeclareDefaultStructors(VoodooGPIO);

 public:
    IOReturn getInterruptType(int pin, int *interruptType) override;
    IOReturn registerInterrupt(int pin, OSObject *target, IOInterruptAction handler, void *refcon) override;
    IOReturn unregisterInterrupt(int pin) override;

    IOReturn enableInterrupt(int pin) override;
    IOReturn disableInterrupt(int pin) override;

    IOReturn setInterruptTypeForPin(int pin, int type);

    bool init(OSDictionary* properties) override;

    bool start(IOService *provider) override;
    void stop(IOService *provider) override;

    IOReturn setPowerState(unsigned long powerState, IOService *whatDevice) override;
};

#endif /* VoodooGPIO_h */
