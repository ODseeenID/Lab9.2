#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "GildedRose.h"
#include "LegacyGildedRose.h"

namespace {

const std::vector<std::string> NAMES = {
    "+5 Dexterity Vest",
    "Aged Brie",
    "Elixir of the Mongoose",
    "Sulfuras, Hand of Ragnaros",
    "Backstage passes to a TAFKAL80ETC concert",
    "Unknown Item",
};

//допустимі вхідні дані: quality 0..50, для Sulfuras 80
std::vector<int> validQualities(const std::string& name)
{
    std::vector<int> q;
    if (name == "Sulfuras, Hand of Ragnaros") { q = {80}; return q; }
    for (int i = 0; i <= 50; ++i) q.push_back(i);
    return q;
}

}  

// 1 день: нова реалізація повинна збігатися з еталоном для всіх комбінацій
TEST(LegacyComparison, SingleDayMatchesOriginalForAllCombinations)
{
    int checked = 0;
    for (const auto& name : NAMES)
        for (int sellIn = -5; sellIn <= 20; ++sellIn)
            for (int quality : validQualities(name))
            {
                std::vector<Item> expected = {Item(name, sellIn, quality)};
                std::vector<Item> actual   = {Item(name, sellIn, quality)};
                LegacyGildedRose legacy(expected);
                GildedRose current(actual);
                legacy.updateQuality();
                current.updateQuality();

                EXPECT_EQ(actual[0].quality, expected[0].quality)
                    << name << " sellIn=" << sellIn << " quality=" << quality;
                EXPECT_EQ(actual[0].sellIn, expected[0].sellIn)
                    << name << " sellIn=" << sellIn << " quality=" << quality;
                EXPECT_EQ(actual[0].name, expected[0].name);
                ++checked;
            }
    EXPECT_TRUE(checked > 1000);
}

// 40 днів: поведінка збігається і при накопиченні змін.
TEST(LegacyComparison, FortyDaySimulationMatchesOriginal)
{
    for (const auto& name : NAMES)
        for (int sellIn = -2; sellIn <= 15; ++sellIn)
            for (int quality : validQualities(name))
            {
                std::vector<Item> expected = {Item(name, sellIn, quality)};
                std::vector<Item> actual   = {Item(name, sellIn, quality)};
                LegacyGildedRose legacy(expected);
                GildedRose current(actual);
                for (int day = 1; day <= 40; ++day)
                {
                    legacy.updateQuality();
                    current.updateQuality();
                    EXPECT_EQ(actual[0].quality, expected[0].quality)
                        << name << " start(sellIn=" << sellIn << ",quality=" << quality << ") day=" << day;
                    EXPECT_EQ(actual[0].sellIn, expected[0].sellIn)
                        << name << " start(sellIn=" << sellIn << ",quality=" << quality << ") day=" << day;
                }
            }
}

// всі товари одночасно
TEST(LegacyComparison, WholeInventoryMatchesOriginal)
{
    auto make = [] {
        return std::vector<Item>{
            Item("+5 Dexterity Vest", 10, 20), Item("Aged Brie", 2, 0),
            Item("Elixir of the Mongoose", 5, 7), Item("Sulfuras, Hand of Ragnaros", 0, 80),
            Item("Sulfuras, Hand of Ragnaros", -1, 80),
            Item("Backstage passes to a TAFKAL80ETC concert", 15, 20),
            Item("Backstage passes to a TAFKAL80ETC concert", 10, 49),
            Item("Backstage passes to a TAFKAL80ETC concert", 5, 49)};
    };
    std::vector<Item> expected = make();
    std::vector<Item> actual = make();
    LegacyGildedRose legacy(expected);
    GildedRose current(actual);
    for (int day = 0; day < 30; ++day)
    {
        legacy.updateQuality();
        current.updateQuality();
        for (size_t i = 0; i < expected.size(); ++i)
        {
            EXPECT_EQ(actual[i].quality, expected[i].quality) << "item " << i << " day " << day;
            EXPECT_EQ(actual[i].sellIn, expected[i].sellIn) << "item " << i << " day " << day;
        }
    }
}
