#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Product {
private:
    int id;
    std::string name;
    std::string category;
    std::string manufacturer;
    int quantity;
    double price;

public:
    Product() : id(-1), name("Undefined"), category("Undefined"), manufacturer("Undefined"), quantity(0), price(0.0) {}

    Product(int id, const std::string& name, const std::string& category, const std::string& manufacturer, int quantity, double price)
        : id(id), name(name), category(category), manufacturer(manufacturer), quantity(quantity), price(price) {}

    void display() const {
        std::cout << "ID: " << id << "\n"
                  << "Name: " << name << "\n"
                  << "Category: " << category << "\n"
                  << "Manufacturer: " << manufacturer << "\n"
                  << "Quantity: " << quantity << "\n"
                  << "Price: " << price << "\n";
    }

    void edit(int id, const std::string& name, const std::string& category, const std::string& manufacturer, int quantity, double price) {
        this->id = id;
        this->name = name;
        this->category = category;
        this->manufacturer = manufacturer;
        this->quantity = quantity;
        this->price = price;
    }

    int getId() const { return id; }
    double getTotalCost() const { return quantity * price; }
};

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void createArray(std::vector<Product>& products, int size) {
    for (int i = 0; i < size; ++i) {
        int id, quantity;
        double price;
        std::string name, category, manufacturer;

        std::cout << "Enter the data for the product " << i + 1 << " (id, name, category, manufacturer, quantity, price): \n";
        if (!(std::cin >> id >> name >> category >> manufacturer >> quantity >> price)) {
            std::cout << "Invalid input. Skipping this product.\n";
            clearInput();
            continue;
        }

        products.emplace_back(id, name, category, manufacturer, quantity, price);
    }
}

void displayArray(const std::vector<Product>& products) {
    for (const auto& product : products) {
        product.display();
        std::cout << "--------------------\n";
    }
}

void editProduct(std::vector<Product>& products) {
    int id;
    std::cout << "Enter the product ID to edit: ";
    if (!(std::cin >> id)) {
        std::cout << "Invalid input.\n";
        clearInput();
        return;
    }

    for (auto& product : products) {
        if (product.getId() == id) {
            int newId, quantity;
            double price;
            std::string name, category, manufacturer;

            std::cout << "Enter new data (id, name, category, manufacturer, quantity, price): \n";
            if (!(std::cin >> newId >> name >> category >> manufacturer >> quantity >> price)) {
                std::cout << "Invalid input. Edit aborted.\n";
                clearInput();
                return;
            }
            product.edit(newId, name, category, manufacturer, quantity, price);
            std::cout << "The product has been updated!\n";
            return;
        }
    }
    std::cout << "Product with this ID was not found.\n";
}

void calculateTotalCost(const std::vector<Product>& products) {
    double totalCost = 0;
    for (const auto& product : products) {
        totalCost += product.getTotalCost();
    }
    std::cout << "Total value of all goods: " << totalCost << "\n";
}

int main() {
    std::vector<Product> products;
    int choice;

    do {
        std::cout << "\nMenu:\n"
                  << "1. Create an object with a default constructor\n"
                  << "2. Create an object with a constructor with parameters\n"
                  << "3. Create an array of objects\n"
                  << "4. Edit object properties\n"
                  << "5. View all objects\n"
                  << "6. Calculate the total cost of goods\n"
                  << "0. Exit\n"
                  << "Your choice: ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Try again.\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: {
                Product product;
                products.push_back(product);
                std::cout << "The object is created using the default constructor.\n";
                break;
            }
            case 2: {
                int id, quantity;
                double price;
                std::string name, category, manufacturer;
                std::cout << "Enter data (id, name, category, manufacturer, quantity, price): \n";
                if (!(std::cin >> id >> name >> category >> manufacturer >> quantity >> price)) {
                    std::cout << "Invalid input. Try again.\n";
                    clearInput();
                    break;
                }
                products.emplace_back(id, name, category, manufacturer, quantity, price);
                std::cout << "The object was created using the constructor with parameters.\n";
                break;
            }
            case 3: {
                int size;
                std::cout << "Enter the number of objects: ";
                if (!(std::cin >> size) || size <= 0) {
                    std::cout << "Invalid input. Try again.\n";
                    clearInput();
                    break;
                }
                createArray(products, size);
                break;
            }
            case 4:
                editProduct(products);
                break;
            case 5:
                displayArray(products);
                break;
            case 6:
                calculateTotalCost(products);
                break;
            case 0:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Wrong choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
