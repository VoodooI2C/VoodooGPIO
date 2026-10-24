//
//  VoodooGPIOAlderLakeS.cpp
//  VoodooGPIO
//
//  Created by lzhoang2801 on 24/10/26.
//  Copyright © 2026 lzhoang2801. All rights reserved.
//

#include "VoodooGPIOAlderLakeS.hpp"

OSDefineMetaClassAndStructors(VoodooGPIOAlderLakeS, VoodooGPIOIntel);

bool VoodooGPIOAlderLakeS::start(IOService *provider) {
    this->pins = adls_pins;
    this->npins = ARRAY_SIZE(adls_pins);
    this->communities = adls_communities;
    this->ncommunities = ARRAY_SIZE(adls_communities);

    IOLog("%s::Loading GPIO Data for AlderLake-S\n", getName());

    return VoodooGPIOIntel::start(provider);
}
