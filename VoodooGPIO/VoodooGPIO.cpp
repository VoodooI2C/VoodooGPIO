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

IOWorkLoop *VoodooGPIO::getWorkLoop() const {
    while (!workLoop) thread_block(0);

    return workLoop;
}
