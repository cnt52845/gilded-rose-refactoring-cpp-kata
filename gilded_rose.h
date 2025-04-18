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
    AgedBrie(int sell_in, int quality) : Item("Aged Brie", sell_in, quality) {}

    void update_quality() override
    {
        sell_in--;
        if (quality < 50) {
            quality++;
        }
    }
};

class BackstagePass : public Item {
public:
    BackstagePass(std::string name, int sell_in, int quality)
        : Item(std::move(name), sell_in, quality)
    {
    }

    void update_quality() override
    {
        sell_in--;
        if (sell_in < 0) {
            quality = 0;
        }
        else if (sell_in <= 5) {
            quality += 3;
        }
        else if (sell_in <= 10) {
            quality += 2;
        }
        else {
            quality++;
        }
        if (quality > 50) {
            quality = 50;
        }
    }
};

class Sulfuras : public Item {
public:
    Sulfuras(std::string name, int sell_in) : Item(std::move(name), sell_in, 80) {}

    void update_quality() override
    {
        // Sulfuras does not change in quality or sell_in
    }
};

class ConjuredItem : public Item {
public:
    ConjuredItem(std::string name, int sell_in, int quality)
        : Item(std::move(name), sell_in, quality)
    {
    }

    void update_quality() override
    {
        sell_in--;
        quality -= 2;
    }
};

class ItemFactory {
public:
    static std::unique_ptr<Item> create_item(const std::string& name, int sell_in, int quality)
    {
        if (name == "Aged Brie") {
            return std::make_unique<AgedBrie>(sell_in, quality);
        }
        else if (name.find("Backstage passes to ") == 0) {
            return std::make_unique<BackstagePass>(name, sell_in, quality);
        }
        else if (name.find("Sulfuras") == 0) {
            return std::make_unique<Sulfuras>(name, sell_in);
        }
        else if (name.find("Conjured") == 0) {
            return std::make_unique<ConjuredItem>(name, sell_in, quality);
        }
        return std::make_unique<Item>(name, sell_in, quality);
    }
};

class GildedRose {
public:
    GildedRose() = default;

    void add_item(std::string name, int sell_in, int quality)
    {
        items.push_back(ItemFactory::create_item(name, sell_in, quality));
    }

    void update_quality()
    {
        for (auto& item : items) {
            item->update_quality();
        }
    }

    std::vector<std::unique_ptr<Item>> items;
};
