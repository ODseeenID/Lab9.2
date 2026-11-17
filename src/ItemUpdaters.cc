#include "ItemUpdaters.h"

#include "GildedRose.h"
#include "QualityRules.h"

namespace
{
    const int ONE_DAY_CHANGE = 1;
    const int TEN_DAYS_LEFT = 10;
    const int FIVE_DAYS_LEFT = 5;
}

//звичайний товар
void NormalItemUpdater::updateQuality(Item& item) const
{
    QualityRules::decrease(item, ONE_DAY_CHANGE);
}

void NormalItemUpdater::updateExpired(Item& item) const
{
    QualityRules::decrease(item, ONE_DAY_CHANGE);
}

// Aged Brie
void AgedBrieUpdater::updateQuality(Item& item) const
{
    QualityRules::increase(item, ONE_DAY_CHANGE);
}

void AgedBrieUpdater::updateExpired(Item& item) const
{
    QualityRules::increase(item, ONE_DAY_CHANGE);
}

//Backstage passes
void BackstagePassesUpdater::updateQuality(Item& item) const
{
    int amount = ONE_DAY_CHANGE;
    if (item.sellIn <= TEN_DAYS_LEFT)
    {
        ++amount;
    }
    if (item.sellIn <= FIVE_DAYS_LEFT)
    {
        ++amount;
    }
    QualityRules::increase(item, amount);
}

void BackstagePassesUpdater::updateExpired(Item& item) const
{
    item.quality = QualityRules::MIN_QUALITY;
}

// Sulfuras
void SulfurasUpdater::updateQuality(Item&) const
{
}

void SulfurasUpdater::updateSellIn(Item&) const
{
}

void SulfurasUpdater::updateExpired(Item&) const
{
}
