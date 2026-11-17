#pragma once

#include "ItemUpdater.h"

class Item;

// правило оновлення за назвою товару
class ItemUpdaterFactory
{
public:
    static const ItemUpdater& forItem(const Item& item);
};
