#include "ItemUpdater.h"

#include "GildedRose.h"

void ItemUpdater::update(Item& item) const
{
    updateQuality(item);
    updateSellIn(item);
    if (item.sellIn < 0)
    {
        updateExpired(item);
    }
}

void ItemUpdater::updateSellIn(Item& item) const
{
    --item.sellIn;
}
