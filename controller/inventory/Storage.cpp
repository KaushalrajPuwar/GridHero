#include "Storage.h"

void Storage::addItem(const std::string &item, int quantity)
{
    items[item] += quantity;
}

bool Storage::hasItem(const std::string &item) const
{
    return items.find(item) != items.end() && items.at(item) > 0;
}

int Storage::getBuildings() const
{
    return items.count("Building") ? items.at("Building") : 0;
}
