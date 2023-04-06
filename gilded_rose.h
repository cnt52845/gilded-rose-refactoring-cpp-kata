#include <vector>
#include <string>
#include <memory>

class Item {
public:
    Item() = delete;
    Item(std::string name, int sell_in, int quality)
        : name(std::move(name)), sell_in(sell_in), quality(quality)
    {
    }

    std::string name;
    int         sell_in;
    int         quality;
};

class GildedRose {
public:
    GildedRose() = default;

    void add_item(std::string name, int sell_in, int quality)
    {
        items.emplace_back(std::make_unique<Item>(name, sell_in, quality));
    }

    void update_quality()
    {
        for (auto& item : items) {
            if (item->name != "Aged Brie" &&
                item->name != "Backstage passes to a TAFKAL80ETC concert") {
                if (item->quality > 0) {
                    if (item->name != "Sulfuras, Hand of Ragnaros")
                        item->quality--;
                }
            }
            else {
                if (item->quality < 50) {
                    item->quality++;

                    if (item->name == "Backstage passes to a TAFKAL80ETC concert") {
                        if (item->sell_in < 11) {
                            if (item->quality < 50)
                                item->quality++;
                        }

                        if (item->sell_in < 6) {
                            if (item->quality < 50)
                                item->quality++;
                        }
                    }
                }
            }

            if (item->name != "Sulfuras, Hand of Ragnaros")
                item->sell_in--;

            if (item->sell_in < 0) {
                if (item->name != "Aged Brie") {
                    if (item->name != "Backstage passes to a TAFKAL80ETC concert") {
                        if (item->quality > 0) {
                            if (item->name != "Sulfuras, Hand of Ragnaros")
                                item->quality--;
                        }
                    }
                    else {
                        item->quality = 0;
                    }
                }
                else {
                    if (item->quality < 50)
                        item->quality++;
                }
            }
        }
    }

    std::vector<std::unique_ptr<Item>> items;
};