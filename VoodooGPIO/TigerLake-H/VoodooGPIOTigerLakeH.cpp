//
//  VoodooGPIOTigerLakeH.cpp
//  VoodooGPIO
//
//  Created by lzhoang2801 on 24/10/26.
//  Copyright © 2026 lzhoang2801. All rights reserved.
//

#include "VoodooGPIOTigerLakeH.hpp"

OSDefineMetaClassAndStructors(VoodooGPIOTigerLakeH, VoodooGPIOIntel);

bool VoodooGPIOTigerLakeH::start(IOService *provider) {
    this->pins = tglh_pins;
    this->npins = ARRAY_SIZE(tglh_pins);
    this->communities = tglh_communities;
    this->ncommunities = ARRAY_SIZE(tglh_communities);

    IOLog("%s::Loading GPIO Data for TigerLake-H\n", getName());

    return VoodooGPIOIntel::start(provider);
}
