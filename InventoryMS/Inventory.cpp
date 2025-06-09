#include "Inventory.h"
#include "Item.h"
#include <iostream>
Inventory::Inventory(): nextid(1) {}
void Inventory::addItem(const std::string &name, int quantity, double price) {
    const Item newItem(nextid++, name, quantity, price);
    items.push_back(newItem);
    std::cout<<"Item successfully added.\n"<<std::endl;
}
void Inventory::removeItemById(int id) {
    bool found = false;
    for (auto it = items.begin(); it != items.end();) {
        if (it->getId() == id) {
            it = items.erase(it);
            found = true;
            std::cout<<"Item "<<id<<" successfully removed.\n"<<std::endl;
        }
        else {
            ++it;
        }
    }
    if (found == false) {
        std::cout<<"No item found with ID: "<<id<<"\n"<<std::endl;
    }
}
void Inventory::updateItemQuantity(int id, int delta) {
    for (auto& item : items) {
        if (item.getId() == id) {
            item.updateQuantity(delta);
            return;
        }
    }
}
void Inventory::displayAllItems() const {
    if (!items.empty()) {
        for (const auto& item : items) {
            item.display();
        }
        std::cout<<"\n";
    }
    else {
        std::cout<<"No items in inventory.\n"<<std::endl;
    }
}
void Inventory::searchItemByName(const std::string& name) const {
    bool found = false;
    for (const auto& item : items) {
        if (item.getName() == name) {
            item.display();
            found = true;
        }
    }
    if (!found) {
        std::cout<<"No item found with name: "<<name<<std::endl;
    }
    std::cout<<"\n";
}
void Inventory::searchItemById(const int id) const {
    bool found = false;
    for (const auto& item : items) {
        if (item.getId() == id) {
            item.display();
            found = true;
        }
    }
    if (!found) {
        std::cout<<"No item found with id: "<<id<<std::endl;
    }
    std::cout<<"\n";
}