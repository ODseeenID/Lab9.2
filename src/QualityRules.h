#pragma once

#include <algorithm>

#include "GildedRose.h"

// правила меж якості
namespace QualityRules
{
    const int MIN_QUALITY = 0;
    const int MAX_QUALITY = 50;

    inline void increase(Item& item, int amount)
    {
        if (item.quality < MAX_QUALITY)
        {
            item.quality = std::min(MAX_QUALITY, item.quality + amount);
        }
    }

    inline void decrease(Item& item, int amount)
    {
        if (item.quality > MIN_QUALITY)
        {
            item.quality = std::max(MIN_QUALITY, item.quality - amount);
        }
    }
}
