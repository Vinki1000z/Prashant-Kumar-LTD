#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Product class for inventory management
class Product {
public:
    int id;
    string name;
    int stock_level;

    Product(int id, string name, int stock_level) : id(id), name(name), stock_level(stock_level) {}
};

// Function to process sales orders and reduce stock levels
void process_orders(vector<Product>& products, unordered_map<int, int>& sales_orders, int restock_threshold) {
    for (auto& product : products) {
        if (sales_orders.find(product.id) != sales_orders.end()) {
            int order_quantity = sales_orders.at(product.id);
            if (product.stock_level >= order_quantity) {
                product.stock_level -= order_quantity;
                cout << "Processed order for product: " << product.name << ", Remaining stock: " << product.stock_level << endl;

                // Check if stock drops below the restock threshold
                if (product.stock_level < restock_threshold) {
                    cout << "Alert: Restock needed for product: " << product.name << endl;
                }
            } else {
                cout << "Error: Not enough stock for product: " << product.name << endl;
            }
        }
    }
}

// Function to restock items based on requirements
void restock_items(vector<Product>& products) {
    cout << "Enter the product ID to restock (0 to finish): ";
    while (true) {
        int product_id;
        cin >> product_id;

        if (product_id == 0) {
            break;
        }

        // Search for the product by its ID
        bool product_found = false;
        for (auto& product : products) {
            if (product.id == product_id) {
                product_found = true;

                int restock_quantity;
                cout << "Enter the quantity to restock for " << product.name << ": ";
                cin >> restock_quantity;

                // Update the stock level
                product.stock_level += restock_quantity;
                cout << "Restocked *" << product.name << "*. New stock level: " << product.stock_level << endl;
                break;
            }
        }

        if (!product_found) {
            cout << "Product ID not found. Please try again." << endl;
        }

        cout << "Enter the product ID to restock (0 to finish): ";
    }
}

void displayProducts(const vector<Product>& products) {
    cout << "Available Products:" << endl;
    for (const auto& product : products) {
        cout << product.id << ". " << product.name << " (Stock: " << product.stock_level << ")" << endl;
    }
}

int main() {
    // Example list of products
    vector<Product> products = {
        Product(1, "Laptop", 15),
        Product(2, "Phone", 8),
        Product(3, "Tablet", 12)
    };

    displayProducts(products);

    // Initialize sales_orders as an empty map
    unordered_map<int, int> sales_orders;

    // Get user input for orders
    char more_orders = 'y';
    while (more_orders == 'y' || more_orders == 'Y') {
        int product_id, quantity;
        cout << "Enter the Product ID to order: ";
        cin >> product_id;

        // Check if the product exists in the list
        bool product_found = false;
        for (const auto& product : products) {
            if (product.id == product_id) {
                product_found = true;
                break;
            }
        }

        if (product_found) {
            cout << "Enter the quantity to order: ";
            cin >> quantity;
            sales_orders[product_id] = quantity;

            cout << "Order for " << quantity << " units of Product ID " << product_id << " has been added." << endl;
        } else {
            cout << "Product ID " << product_id << " not found. Please try again." << endl;
        }

        cout << "Do you want to add another order? (y/n): ";
        cin >> more_orders;
    }

    // Set restock threshold
    int restock_threshold = 10;

    // Process sales orders
    process_orders(products, sales_orders, restock_threshold);

    // Example restock quantities (product_id -> quantity to restock)
    // unordered_map<int, int> restock_quantities = {
    //     {2, 20}, // Restock 20 phones
    // };

    // Restock items
      // Restock items (now based on user input)
    restock_items(products);

    return 0;
}
