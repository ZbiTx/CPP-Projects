#include "Item.h"
#include <iostream>
Item::Item()
    : id(0), name(""), quantity(0), price(0.0) {}
Item::Item(int id, const std::string& name, const int quantity, double price)
    : id(id), name(name), quantity(quantity), price(price){}
void Item::display() const{
    std::cout<<"ID: "<<id<<std::endl;
    std::cout<<"Name: "<<name<<std::endl;
    std::cout<<"Quantity: "<<quantity<<std::endl;
    std::cout<<"Price: £"<<price<<"\n"<<std::endl;
}
void Item::updateQuantity(int delta) {
    std::string option;
    std::cout<<"Add or remove? ";
    std::cin>>option;

    if (option == "add") {
        if (delta < 0) {
            std::cout<<"Cannot increase by negative values.\n"<<std::endl;
        }
        else {
            quantity = quantity + delta;
            std::cout<<"Quantity updated. New quantity: "<<quantity<<"\n"<<std::endl;
        }
    }
    else if (option == "remove") {
        std::cout<<"Stock to remove: ";
        std::cin>>delta;
        if (delta > quantity) {
            std::cout<<"Cannot remove more than current stock.\n"<<std::endl;
        }
        else {
            quantity = quantity - delta;
            std::cout<<"Quantity updated. New quantity: "<<quantity<<"\n"<<std::endl;
        }
    }
    else {
        std::cout<<"Invalid Option.\n"<<std::endl;
    }
}
int Item::getId() const {
    return id;
}
std::string Item::getName() const {
    return name;
}