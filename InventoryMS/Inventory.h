#ifndef INVENTORY_H
#define INVENTORY_H
#include "Item.h"
#include <vector>
#include <string>

class Inventory {
private:
    std::vector<Item> items;
    int nextid;
public:
    Inventory();
    void addItem(const std::string& name, int quantity, double price);
    void removeItemById(int id);
    void updateItemQuantity(int id, int delta);
    void displayAllItems() const;
    void searchItemByName(const std::string &name) const;
    void searchItemById(int id) const;
};

#endif //INVENTORY_H
