#include "FragileGoodsUpdater.h"

#include "GildedRose.h"
#include "QualityRules.h"

namespace
{
    const int DAILY_DECREASE = 3;
    const int DECREASE_AFTER_EXPIRY = 8;  
}

void FragileGoodsUpdater::updateQuality(Item& item) const
{
    QualityRules::decrease(item, DAILY_DECREASE);
}

void FragileGoodsUpdater::updateExpired(Item& item) const
{
    // updateQuality вже відняв DAILY_DECREASE, тож решта додається до 8
    QualityRules::decrease(item, DECREASE_AFTER_EXPIRY - DAILY_DECREASE);
}