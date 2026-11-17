#pragma once

#include "ItemUpdater.h"

//звичайний товар -1 щодня, після терміну -2
class NormalItemUpdater final : public ItemUpdater
{
protected:
    void updateQuality(Item& item) const override;
    void updateExpired(Item& item) const override;
};

//Aged Brie якість зростає з часом
class AgedBrieUpdater final : public ItemUpdater
{
protected:
    void updateQuality(Item& item) const override;
    void updateExpired(Item& item) const override;
};

//Backstage passes зростання прискорюється, після концерту якість 0
class BackstagePassesUpdater final : public ItemUpdater
{
protected:
    void updateQuality(Item& item) const override;
    void updateExpired(Item& item) const override;
};

//Sulfuras не змінюється і не має терміну продажу
class SulfurasUpdater final : public ItemUpdater
{
protected:
    void updateQuality(Item& item) const override;
    void updateSellIn(Item& item) const override;
    void updateExpired(Item& item) const override;
};
