#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item {
private:
    int id;
    std::string name;
    int quantity;
    double price;
public:
    Item();
    Item(int id, const std::string& name, int quantity, double price);
    void display() const;
    void updateQuantity(int delta);
    int getId() const;
    std::string getName() const;
};

#endif //ITEM_H
