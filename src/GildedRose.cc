#include "GildedRose.h"

#include "ItemUpdaterFactory.h"

GildedRose::GildedRose(std::vector<Item> & items) : items(items)
{}

void GildedRose::updateQuality()
{
    for (Item& item : items)
    {
        ItemUpdaterFactory::forItem(item).update(item);
    }
}
