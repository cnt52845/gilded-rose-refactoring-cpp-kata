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

    void update_quality()
    {
        if (name == "Aged Brie") {
            update_quality_aged_brie();
            return;
        }

        if (name != "Backstage passes to a TAFKAL80ETC concert") {
            if (quality > 0) {
                if (name != "Sulfuras, Hand of Ragnaros")
                    quality--;
            }
        }
        else {
            if (quality < 50) {
                quality++;

                if (name == "Backstage passes to a TAFKAL80ETC concert") {
                    if (sell_in < 11) {
                        if (quality < 50)
                            quality++;
                    }

                    if (sell_in < 6) {
                        if (quality < 50)
                            quality++;
                    }
                }
            }
        }

        if (name != "Sulfuras, Hand of Ragnaros")
            sell_in--;

        if (sell_in < 0) {
            if (name != "Backstage passes to a TAFKAL80ETC concert") {
                if (quality > 0) {
                    if (name != "Sulfuras, Hand of Ragnaros")
                        quality--;
                }
            }
            else {
                quality = 0;
            }
        }
    }

    void update_quality_aged_brie()
    {
        sell_in--;
        if (quality < 50) {
            quality++;
        }
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
            item->update_quality();
        }
    }

    std::vector<std::unique_ptr<Item>> items;
};
