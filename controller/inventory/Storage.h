#ifndef STORAGE_H
#define STORAGE_H

#include <unordered_map>
#include <string>

class Storage
{
    std::unordered_map<std::string, int> items;

public:
    void addItem(const std::string &item, int quantity = 1);
    bool hasItem(const std::string &item) const;
    int getBuildings() const;
};

#endif
