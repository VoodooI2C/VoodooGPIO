//
//  VoodooGPIOAlderLakeS.cpp
//  VoodooGPIO
//
//  Alder Lake-S PCH GPIO controller (ACPI INTC1085 / INTC1056). Raptor Lake-S
//  and the Raptor Lake-HX mobile parts use the same PCH and the same tables.
//  Pin, pad-group and community data follow Linux
//  drivers/pinctrl/intel/pinctrl-alderlake.c (adls_*).
//

#include "VoodooGPIOAlderLakeS.hpp"

OSDefineMetaClassAndStructors(VoodooGPIOAlderLakeS, VoodooGPIOIntel);

bool VoodooGPIOAlderLakeS::start(IOService *provider) {
    this->pins = adls_pins;
    this->npins = ARRAY_SIZE(adls_pins);
    this->groups = adls_groups;
    this->ngroups = ARRAY_SIZE(adls_groups);
    this->functions = adls_functions;
    this->nfunctions = ARRAY_SIZE(adls_functions);
    this->communities = adls_communities;
    this->ncommunities = ARRAY_SIZE(adls_communities);

    IOLog("%s::Loading GPIO Data for AlderLake-S\n", getName());

    return VoodooGPIOIntel::start(provider);
}
