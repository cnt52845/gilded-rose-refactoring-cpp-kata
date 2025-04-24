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

    virtual void update_quality()
    {
        if (name != "Aged Brie" && name != "Backstage passes to a TAFKAL80ETC concert") {
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
            if (name != "Aged Brie") {
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
            else {
                if (quality < 50)
                    quality++;
            }
        }
    }

    std::string name;
    int         sell_in;
    int         quality;
};

class AgedBrie : public Item {
public:
    AgedBrie(std::string name, int sell_in, int quality) : Item(std::move(name), sell_in, quality)
    {
    }

    void update_quality() override
    {
        sell_in--;
        if (quality < 50) {
            quality++;
        }
    }
};

class GildedRose {
public:
    GildedRose() = default;

    void add_item(std::string name, int sell_in, int quality)
    {
        if (name == "Aged Brie") {
            items.emplace_back(std::make_unique<AgedBrie>(name, sell_in, quality));
            return;
        }
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
