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
        sell_in--;
        quality--;
        if (sell_in < 0) {
            quality--;
        }
        if (quality < 0) {
            quality = 0;
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

class BackstagePasses : public Item {
public:
    BackstagePasses(std::string name, int sell_in, int quality)
        : Item(std::move(name), sell_in, quality)
    {
    }

    void update_quality() override
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
};

class Sulfuras : public Item {
public:
    Sulfuras(std::string name, int sell_in, int quality) : Item(std::move(name), sell_in, quality)
    {
    }

    void update_quality() override
    {
        // Sulfuras does not change in quality or sell_in
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
        if (name == "Backstage passes to a TAFKAL80ETC concert") {
            items.emplace_back(std::make_unique<BackstagePasses>(name, sell_in, quality));
            return;
        }
        if (name == "Sulfuras, Hand of Ragnaros") {
            items.emplace_back(std::make_unique<Sulfuras>(name, sell_in, quality));
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
