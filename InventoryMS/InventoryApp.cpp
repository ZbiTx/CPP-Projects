#include <iostream>
#include <limits>
#include "Item.h"
#include "Inventory.h"

int main() {
    int int_input;
    std::string option;

    std::string name;
    int quantity;
    double price;
    int id;

    Item item;
    Inventory inventory;

    while (1) {
        std::cout<<"====Inventory Management System===="<<std::endl;
        std::cout<<"1. Add item\n"<<
                    "2. View All\n"<<
                    "3. Update Quantity\n"<<
                    "4. Remove Item\n"<<
                    "5. Search item by name or id\n"<<
                    "6. Exit\n";
        std::cout<<"Enter: ";
        std::cin>>int_input;

        switch (int_input) {
            case 1:
                std::cout<<"Name: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(std::cin, name);
                std::cout<<"Quantity: ";
                std::cin>>quantity;
                std::cout<<"Price: ";
                std::cin>>price;
                inventory.addItem(name, quantity, price);
                break;
            case 2:
                inventory.displayAllItems();
                break;
            case 3:
                std::cout<<"ID: ";
                std::cin>>id;
                std::cout<<"Quantity: ";
                std::cin>>quantity;
                inventory.updateItemQuantity(id, quantity);
                break;
            case 4:
                std::cout<<"ID: ";
                std::cin>>id;
                inventory.removeItemById(id);
                break;
            case 5:
                std::cout<<"Remove by name or id? ";
                std::cin>>option;
                if (option == "name") {
                    std::cout<<"Name: ";
                    std::cin>>name;
                    inventory.searchItemByName(name);
                }
                else if (option == "id") {
                    std::cout<<"ID: ";
                    std::cin>>id;
                    inventory.searchItemById(id);
                }
                break;
            case 6:
                break;
            default:
                std::cout<<"Invalid option. Please try again."<<std::endl;
        }
        if (int_input == 6) {
            std::cout<<"Inventory App Successfully Terminated.\n";
            break;
        }
    }
}