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
    
protected:
    bool controllerIsAwake;

    IOWorkLoop *workLoop = nullptr;
    IOCommandGate* command_gate = nullptr;
    OSArray* registered_pin_list = nullptr;
    bool isInterruptBusy;
    
    IOWorkLoop* getWorkLoop() {
        // Do we have a work loop already?, if so return it NOW.
        if ((vm_address_t) workLoop >> 1)
            return workLoop;

        if (OSCompareAndSwap(0, 1, reinterpret_cast<IOWorkLoop*>(&workLoop))) {
            // Construct the workloop and set the cntrlSync variable
            // to whatever the result is and return
            workLoop = IOWorkLoop::workLoop();
        } else {
            while (reinterpret_cast<IOWorkLoop*>(workLoop) == reinterpret_cast<IOWorkLoop*>(1)) {
                // Spin around the cntrlSync variable until the
                // initialization finishes.
                thread_block(0);
            }
        }

        return workLoop;
    }

 public:
    virtual IOReturn setInterruptTypeForPin(int pin, int type) {
        return kIOReturnNoInterrupt;
    }
};

#endif /* VoodooGPIO_h */
