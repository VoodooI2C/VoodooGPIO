//
//  VoodooGPIOAlderLakeN.cpp
//  VoodooGPIO
//
//  Created by lzhoang2801 on 24/10/26.
//  Copyright © 2026 lzhoang2801. All rights reserved.
//

#include "VoodooGPIOAlderLakeN.hpp"

OSDefineMetaClassAndStructors(VoodooGPIOAlderLakeN, VoodooGPIOIntel);

bool VoodooGPIOAlderLakeN::start(IOService *provider) {
    this->pins = adln_pins;
    this->npins = ARRAY_SIZE(adln_pins);
    this->communities = adln_communities;
    this->ncommunities = ARRAY_SIZE(adln_communities);

    IOLog("%s::Loading GPIO Data for AlderLake-N\n", getName());

    return VoodooGPIOIntel::start(provider);
}
