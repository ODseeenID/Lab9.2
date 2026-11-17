#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "GildedRose.h"

namespace {

    const std::string FRAGILE = "Fragile Goods";

    Item updateOnce(int sellIn, int quality)
    {
        std::vector<Item> items = { Item(FRAGILE, sellIn, quality) };
        GildedRose app(items);
        app.updateQuality();
        return items[0];
    }

}  

// якість - 3 щодня до завершення терміну
TEST(FragileGoods, QualityDecreasesByThreeBeforeSellDate)
{
    EXPECT_EQ(updateOnce(10, 20).quality, 17);
}

// після завершення терміну якість - 8 за день
TEST(FragileGoods, QualityDecreasesByEightAfterSellDate)
{
    EXPECT_EQ(updateOnce(0, 20).quality, 12);    
    EXPECT_EQ(updateOnce(-5, 20).quality, 12);   
}

//якість ніколи не буває від'ємною
TEST(FragileGoods, QualityNeverNegative)
{
    EXPECT_EQ(updateOnce(10, 2).quality, 0);
    EXPECT_EQ(updateOnce(-1, 7).quality, 0);
}

// SellIn зменшується на 1
TEST(FragileGoods, SellInDecreasesByOne)
{
    EXPECT_EQ(updateOnce(10, 20).sellIn, 9);
}