# Task 1 
# E-Commerce System in C++

This project is a basic **e-commerce system** implemented in **C++** where users can create orders, add products, and process payments.

## Features

- **Product Listing**: View and select products.
- **Order Management**: Create orders with multiple products.
- **Payment Processing**: Process payments and check the status of each order.

## Modes

- **Demo Mode**: Predefined user, order, and payment.
- **Manual Mode**: Interactive user creation, order management, and payment.

## How to Run

### 1. **Compile the Code**
bash
Copy code
./ecommerce_system

### 2. **Choose a Mode**
Enter 1 for Demo Mode.
Enter 2 for Manual Mode (create user, orders, and process payments).
### Example Usage
Manual Mode:
Enter User ID: 123
Enter User Name: Alice Johnson
Available Products:
101. Laptop - $999.99
102. Smartphone - $499.99
Enter the product ID to add to your order: 101
Order Created Successfully!

Do you want to make a payment now? (y/n): y
Payment successful! Total Amount: $999.99


# Task 2

# Inventory management system 

*** The two main functions are process_orders() and restock_items(). ***

## process_orders() checks if products are available for the given order quantities. If stock is insufficient, it throws an error. If stock is below the threshold, an alert is triggered.
## restock_items() increases stock levels based on the restock quantities.


