//
//  VoodooGPIO.cpp
//  VoodooGPIO
//
//  Created by Visual on 6/3/23.
//  Copyright © 2017 CoolStar. All rights reserved.
//  Copyright © 2023 Visual/Noot Inc/ChefKiss Inc. All rights reserved.
//

#include "VoodooGPIO.hpp"

OSDefineMetaClassAndAbstractStructors(VoodooGPIO, IOService);

IOWorkLoop *VoodooGPIO::getWorkLoop() {
    // Do we have a work loop already?, if so return it NOW.
    if ((vm_address_t) this->workLoop >> 1)
        return this->workLoop;

    if (OSCompareAndSwap(0, 1, reinterpret_cast<IOWorkLoop*>(&this->workLoop))) {
        // Construct the workloop and set the cntrlSync variable
        // to whatever the result is and return
        this->workLoop = IOWorkLoop::workLoop();
    } else {
        while (reinterpret_cast<IOWorkLoop*>(this->workLoop) == reinterpret_cast<IOWorkLoop*>(1)) {
            // Spin around the cntrlSync variable until the
            // initialization finishes.
            thread_block(0);
        }
    }

    return this->workLoop;
}
