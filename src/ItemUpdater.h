#pragma once

class Item;

//абстракція правила оновлення товару за один день
//порядок кроків спільний для всіх, а правила - власні
class ItemUpdater
{
public:
    virtual ~ItemUpdater() = default;

    void update(Item& item) const;

protected:
    virtual void updateQuality(Item& item) const = 0;   // зміна якості за день
    virtual void updateSellIn(Item& item) const;        // sellIn - 1
    virtual void updateExpired(Item& item) const = 0;   // коли термін минув
};
