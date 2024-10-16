#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// User Class
class User
{
public:
    int id;
    string name;
    string email;

    User(int id, string name, string email) : id(id), name(name), email(email) {}
};

// Product Class
class Product
{
public:
    int id;
    string name;
    double price;

    Product(int id, string name, double price) : id(id), name(name), price(price) {}
};

// Order Class
class Order
{
public:
    int id;
    User user;
    string status;
    string order_date;
    vector<Product> products; // An order can contain multiple products

    Order(int id, User user, string status, string order_date) : id(id), user(user), status(status), order_date(order_date) {}

    // Method to add a product to the order
    void addProduct(Product product)
    {
        products.push_back(product);
    }
};

// Payment Class
class Payment
{
public:
    int id;
    Order order;
    double amount;
    string payment_date;
    string status;

    Payment(int id, Order order, double amount, string payment_date, string status)
        : id(id), order(order), amount(amount), payment_date(payment_date), status(status) {}
};

// Function to display products
void displayProducts(const vector<Product> &products)
{
    cout << "Available Products:" << endl;
    for (const auto &product : products)
    {
        cout << product.id << ". " << product.name << " - $" << product.price << endl;
    }
}

// Function for manual user interaction
void runManual(User &user, vector<Order> &orders, vector<Product> &products)
{
    // Create an order
    displayProducts(products);
    Order newOrder(orders.size() + 1, user, "Pending", "2024-10-16");

    int choice;
    cout << "Enter the product ID to add to your order (0 to finish): ";
    while (true)
    {
        cin >> choice;
        if (choice == 0)
            break;

        // Find the product and add it to the order
        bool productFound = false;
        for (const auto &product : products)
        {
            if (product.id == choice)
            {
                newOrder.addProduct(product);
                cout << "Added: " << product.name << " to the order." << endl;
                productFound = true;
                break;
            }
        }

        if (!productFound)
        {
            cout << "Invalid product ID. Please try again." << endl;
        }

        cout << "Enter the product ID to add to your order (0 to finish): ";
    }

    // Add the order to the list of orders
    orders.push_back(newOrder);

    cout << "\nOrder Created Successfully!\n";
}

// Function to display orders
void displayOrders(const vector<Order> &orders)
{
    cout << "Current Orders:" << endl;
    for (const auto &order : orders)
    {
        cout << "Order ID: " << order.id << ", Status: " << order.status << endl;
        cout << "Products:" << endl;
        for (const auto &product : order.products)
        {
            cout << "- " << product.name << " ($" << product.price << ")" << endl;
        }
        cout << "-----------" << endl;
    }
}

// Function to process payment for an order
void processPayment(vector<Order> &orders)
{
    displayOrders(orders);
    int orderId;
    cout << "Enter the Order ID for payment: ";
    cin >> orderId;

    bool orderFound = false;

    // Iterate through orders
    for (auto it = orders.begin(); it != orders.end(); ++it)
    {
        if (it->id == orderId)
        {
            if (it->status == "Pending")
            {
                // Calculate total amount
                double totalAmount = 0;
                for (const auto &product : it->products)
                {
                    totalAmount += product.price;
                }

                // Process payment
                Payment payment(orderId, *it, totalAmount, "2024-10-16", "Completed");

                // Mark order as completed
                it->status = "Completed";

                // Output success message
                cout << "\nPayment successful! Total Amount: $" << payment.amount << endl;

                // Remove the order from the vector
                // orders.erase(it);

                orderFound = true;
                break;
            }
            else if (it->status == "Completed")
            {
                // If4 the order is already paid
                cout << "Order ID: " << orderId << " has already been paid." << endl;
                orderFound = true;
                break;
            }
        }
    }

    if (!orderFound)
    {
        cout << "Invalid Order ID." << endl;
    }
}

int main()
{

    int demo;
    cout << "Enter 1 for demo, 2 for making user ,order and making payment: ";
    cin >> demo;
    // List of available products
    if (demo == 2)
    {
        vector<Product> products = {
            Product(101, "Laptop", 999.99),
            Product(102, "Smartphone", 499.99),
            Product(103, "Headphones", 199.99),
            Product(104, "Keyboard", 49.99)};

        vector<Order> orders;
        char createAnotherOrder;
        bool continueShopping = true;

        // Create a user
        cout << "Enter User ID: ";
        int userId;
        cin >> userId;

        cout << "Enter User Name: ";
        string userName;
        cin.ignore(); // To handle any leftover newline character
        getline(cin, userName);

        cout << "Enter User Email: ";
        string userEmail;
        getline(cin, userEmail);

        User user(userId, userName, userEmail);

        // Main Loop
        while (continueShopping)
        {
            runManual(user, orders, products);

            // Ask for payment after creating an order

            char payNow;
            cout << "Do you want to make a payment now? (y/n): ";
            cin >> payNow;
            if (payNow == 'y' || payNow == 'Y')
            {
                processPayment(orders);
            }

            // Display remaining orders
            cout << "\nRemaining unpaid orders: " << endl;
            for (const auto &order : orders)
            {
                if (order.status == "Pending")
                {
                    cout << "Order ID: " << order.id << " (Pending)" << endl;
                }
                else
                {
                    cout << endl;
                }
            }

            // Ask if the user wants to create another order
            cout << "Do you want to create another order? (y/n): ";
            cin >> createAnotherOrder;

            if (createAnotherOrder == 'n' || createAnotherOrder == 'N')
            {
                // Ask if the user wants to log out
                char logout;
                cout << "Do you want to log out? (y/n): ";
                cin >> logout;

                if (logout == 'y' || logout == 'Y')
                {
                    cout << "Thank you for using the system. Goodbye!" << endl;
                    continueShopping = false;
                }
            }
        }
    }
    else
    {
        User user1(1, "John Doe", "johndoe@example.com");

        // Create some products
        Product product1(101, "Laptop", 999.99);
        Product product2(102, "Smartphone", 499.99);

        // Create an order
        Order order1(1, user1, "Pending", "2024-10-16");
        order1.addProduct(product1);
        order1.addProduct(product2);

        // Create a payment
        Payment payment1(1, order1, 1499.98, "2024-10-16", "Completed");

        // Output the order details
        cout << "Order ID: " << order1.id << endl;
        cout << "User: " << order1.user.name << endl;
        cout << "Status: " << order1.status << endl;
        cout << "Products in the order:" << endl;
        for (const auto &product : order1.products)
        {
            cout << "- " << product.name << ": $" << product.price << endl;
        }

        // Output payment details
        cout << "Payment Status: " << payment1.status << endl;
        cout << "Total Amount: $" << payment1.amount << endl;
    }
    return 0;
}
