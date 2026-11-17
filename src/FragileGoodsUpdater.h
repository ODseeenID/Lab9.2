#pragma once

#include "ItemUpdater.h"

class FragileGoodsUpdater final : public ItemUpdater
{
protected:
    void updateQuality(Item& item) const override;
    void updateExpired(Item& item) const override;
};