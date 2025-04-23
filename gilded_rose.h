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

        if (name == "Backstage passes to a TAFKAL80ETC concert") {
            update_quality_backstage_passes();
            return;
        }

        if (name == "Sulfuras, Hand of Ragnaros") {
            update_quality_sulfuras();
            return;
        }

        if (quality > 0) {
            quality--;
        }

        sell_in--;

        if (sell_in < 0) {
            if (quality > 0) {
                quality--;
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

    void update_quality_backstage_passes()
    {
        sell_in--;
        if (sell_in < 0) {
            quality = 0;
        }
        else {
            quality++;
            if (sell_in < 10) {
                quality++;
            }
            if (sell_in < 5) {
                quality++;
            }
            if (quality > 50) {
                quality = 50;
            }
        }
    }

    void update_quality_sulfuras()
    {
        // Sulfuras does not change in quality or sell_in
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
