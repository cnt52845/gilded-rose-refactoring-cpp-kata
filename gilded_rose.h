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

class ItemFactory {
public:
    static std::unique_ptr<Item> create_item(const std::string& name, int sell_in, int quality)
    {
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
