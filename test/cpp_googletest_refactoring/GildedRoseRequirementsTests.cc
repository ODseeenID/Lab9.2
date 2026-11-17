#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "GildedRose.h"

namespace {

const std::string BRIE = "Aged Brie";
const std::string SULFURAS = "Sulfuras, Hand of Ragnaros";
const std::string PASSES = "Backstage passes to a TAFKAL80ETC concert";
const std::string NORMAL = "+5 Dexterity Vest";

// оновлює один товар на один день і повертає його стан.
Item updateOnce(const std::string& name, int sellIn, int quality)
{
    std::vector<Item> items = {Item(name, sellIn, quality)};
    GildedRose app(items);
    app.updateQuality();
    return items[0];
}

}  

// 1: звичайний товар втрачає 1 одиницю якості щодня 
TEST(NormalItem, QualityDecreasesByOneBeforeSellDate)
{
    Item item = updateOnce(NORMAL, 10, 20);
    EXPECT_EQ(item.quality, 19);
}

TEST(NormalItem, SellInDecreasesByOne)
{
    Item item = updateOnce(NORMAL, 10, 20);
    EXPECT_EQ(item.sellIn, 9);
}

//2: після терміну продажу якість падає вдвічі швидше
TEST(NormalItem, QualityDecreasesByTwoAfterSellDate)
{
    Item item = updateOnce(NORMAL, 0, 20);   
    EXPECT_EQ(item.quality, 18);
    EXPECT_EQ(item.sellIn, -1);
}

TEST(NormalItem, QualityKeepsDecreasingByTwoWhenAlreadyExpired)
{
    Item item = updateOnce(NORMAL, -5, 20);
    EXPECT_EQ(item.quality, 18);
}

// 3: якість не буває від'ємною 
TEST(NormalItem, QualityNeverNegativeBeforeSellDate)
{
    Item item = updateOnce(NORMAL, 5, 0);
    EXPECT_EQ(item.quality, 0);
}

TEST(NormalItem, QualityNeverNegativeAfterSellDate)
{
    EXPECT_EQ(updateOnce(NORMAL, 0, 1).quality, 0);   
    EXPECT_EQ(updateOnce(NORMAL, -3, 0).quality, 0);
}

//4: Aged Brie з часом покращується
TEST(AgedBrie, QualityIncreasesByOneBeforeSellDate)
{
    EXPECT_EQ(updateOnce(BRIE, 10, 20).quality, 21);
}

TEST(AgedBrie, QualityIncreasesByTwoAfterSellDate)
{
    EXPECT_EQ(updateOnce(BRIE, 0, 20).quality, 22);
}

//5: якість не перевищує 50 
TEST(QualityLimit, BrieNeverExceedsFifty)
{
    EXPECT_EQ(updateOnce(BRIE, 10, 50).quality, 50);
    EXPECT_EQ(updateOnce(BRIE, 0, 49).quality, 50);   // +2 обрізається до 50
    EXPECT_EQ(updateOnce(BRIE, -1, 50).quality, 50);
}

TEST(QualityLimit, BackstagePassesNeverExceedFifty)
{
    EXPECT_EQ(updateOnce(PASSES, 15, 50).quality, 50);
    EXPECT_EQ(updateOnce(PASSES, 10, 49).quality, 50);
    EXPECT_EQ(updateOnce(PASSES, 5, 49).quality, 50);
    EXPECT_EQ(updateOnce(PASSES, 5, 48).quality, 50);
}

//6: Sulfuras не змінюється і не має терміну продажу
TEST(Sulfuras, QualityStaysEighty)
{
    EXPECT_EQ(updateOnce(SULFURAS, 0, 80).quality, 80);
    EXPECT_EQ(updateOnce(SULFURAS, -1, 80).quality, 80);
    EXPECT_EQ(updateOnce(SULFURAS, 10, 80).quality, 80);
}

TEST(Sulfuras, SellInNeverChanges)
{
    EXPECT_EQ(updateOnce(SULFURAS, 0, 80).sellIn, 0);
    EXPECT_EQ(updateOnce(SULFURAS, -1, 80).sellIn, -1);
    EXPECT_EQ(updateOnce(SULFURAS, 10, 80).sellIn, 10);
}

//7: Backstage passes 
TEST(BackstagePasses, QualityIncreasesByOneWhenMoreThanTenDaysLeft)
{
    EXPECT_EQ(updateOnce(PASSES, 11, 20).quality, 21);
    EXPECT_EQ(updateOnce(PASSES, 15, 20).quality, 21);
}

TEST(BackstagePasses, QualityIncreasesByTwoWhenTenDaysOrLess)
{
    EXPECT_EQ(updateOnce(PASSES, 10, 20).quality, 22);
    EXPECT_EQ(updateOnce(PASSES, 6, 20).quality, 22);
}

TEST(BackstagePasses, QualityIncreasesByThreeWhenFiveDaysOrLess)
{
    EXPECT_EQ(updateOnce(PASSES, 5, 20).quality, 23);
    EXPECT_EQ(updateOnce(PASSES, 1, 20).quality, 23);
}

TEST(BackstagePasses, QualityDropsToZeroAfterConcert)
{
    EXPECT_EQ(updateOnce(PASSES, 0, 20).quality, 0);
    EXPECT_EQ(updateOnce(PASSES, -1, 20).quality, 0);
}

//загальне
TEST(General, EachItemIsUpdatedIndependently)
{
    std::vector<Item> items = {Item(NORMAL, 10, 20), Item(BRIE, 10, 20), Item(SULFURAS, 0, 80)};
    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(items[0].quality, 19);
    EXPECT_EQ(items[1].quality, 21);
    EXPECT_EQ(items[2].quality, 80);
}

TEST(General, EmptyInventoryIsHandled)
{
    std::vector<Item> items;
    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(items.size(), 0u);
}

TEST(General, ItemNameIsNotChanged)
{
    EXPECT_EQ(updateOnce(NORMAL, 5, 5).name, NORMAL);
}
