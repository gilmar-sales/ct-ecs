#pragma once

#include "entities_utils.hpp"

namespace ecs {

    template<typename TSettings>
    struct Entity
    {
        using Settings = TSettings;
        using Bitset = typename Settings::Bitset;
        
        Bitset bitset;
    };
    
}