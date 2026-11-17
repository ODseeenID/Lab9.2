#include "ItemUpdaterFactory.h"

#include "FragileGoodsUpdater.h" //зміна
#include "GildedRose.h"
#include "ItemNames.h"
#include "ItemUpdaters.h"

const ItemUpdater& ItemUpdaterFactory::forItem(const Item& item)
{
    static const NormalItemUpdater normal;
    static const AgedBrieUpdater agedBrie;
    static const BackstagePassesUpdater backstagePasses;
    static const SulfurasUpdater sulfuras;
    static const FragileGoodsUpdater fragileGoods; //зміна

    if (item.name == ItemNames::AGED_BRIE)
    {
        return agedBrie;
    }
    if (item.name == ItemNames::BACKSTAGE_PASSES)
    {
        return backstagePasses;
    }
    if (item.name == ItemNames::SULFURAS)
    {
        return sulfuras;
    }
    if (item.name == ItemNames::FRAGILE_GOODS) //зміна
    {
        return fragileGoods;
    }
    return normal;
}
