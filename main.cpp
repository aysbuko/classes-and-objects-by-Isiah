#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

class Product {
private:
    int productID;
    string productName;
    int productQuantity;
    double productPrice;
    string productCategory;

public:
    Product(int id, string name, int quantity, double price, string category)
            : productID(id), productName(name), productQuantity(quantity), productPrice(price), productCategory(category) {}

    int getProductID() const { return productID; }
    string getProductName() const { return productName; }
    int getProductQuantity() const { return productQuantity; }
    double getProductPrice() const { return productPrice; }
    string getProductCategory() const { return productCategory; }

    void setProductQuantity(int quantity) { productQuantity = quantity; }
    void setProductPrice(double price) { productPrice = price; }

    void display() const {
        cout << left << setw(10) << productID << setw(20) << productName
             << setw(10) << productQuantity << setw(10) << fixed << setprecision(2) << productPrice
             << setw(15) << productCategory << endl;
    }

    bool isLowStock() const {
        return productQuantity <= 5;
    }
};

void displayAll(const vector<Product>& products) {
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity"
         << setw(10) << "Price" << setw(15) << "Category" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for (const auto& product : products) {
        product.display();
    }
}

Product* searchByID(vector<Product>& products, int id) {
    for (auto& product : products) {
        if (product.getProductID() == id) {
            return &product;
        }
    }
    return nullptr;
}

void sortProducts(vector<Product>& products, bool byPrice, bool ascending) {
    if (byPrice) {
        sort(products.begin(), products.end(), [ascending](const Product& a, const Product& b) {
            return ascending ? a.getProductPrice() < b.getProductPrice() : a.getProductPrice() > b.getProductPrice();
        });
    } else {
        sort(products.begin(), products.end(), [ascending](const Product& a, const Product& b) {
            return ascending ? a.getProductQuantity() < b.getProductQuantity() : a.getProductQuantity() > b.getProductQuantity();
        });
    }
}


void displayLowStock(const vector<Product>& products) {
    cout << "Low Stock Items (Quantity <= 5):\n";
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity"
         << setw(10) << "Price" << setw(15) << "Category" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for (const auto& product : products) {
        if (product.isLowStock()) {
            product.display();
        }
    }
}

int main() {
    vector<Product> products;
    int nextProductID = 1;
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1 - Add Item\n";
        cout << "2 - Update Item\n";
        cout << "3 - Remove Item\n";
        cout << "4 - Display All Items\n";
        cout << "5 - Search Item\n";
        cout << "6 - Sort Items\n";
        cout << "7 - Display Low Stock Items\n";
        cout << "8 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, category;
            int quantity;
            double price;
            cout << "Enter product name: ";
            cin >> ws; // To clear input buffer
            getline(cin, name);
            cout << "Enter product quantity: ";
            cin >> quantity;
            cout << "Enter product price: ";
            cin >> price;
            cout << "Enter product category: ";
            cin >> ws; // To clear input buffer
            getline(cin, category);

            Product newProduct(nextProductID++, name, quantity, price, category);
            products.push_back(newProduct);
            cout << "Item added successfully!\n";
        }
        else if (choice == 2) {
            int id;
            cout << "Enter product ID to update: ";
            cin >> id;
            Product* product = searchByID(products, id);

            if (product) {
                int updateChoice;
                cout << "1 - Update Quantity\n";
                cout << "2 - Update Price\n";
                cout << "Choose update option: ";
                cin >> updateChoice;

                if (updateChoice == 1) {
                    int newQuantity;
                    cout << "Enter new quantity: ";
                    cin >> newQuantity;
                    cout << "Updated quantity of " << product->getProductName() << " from "
                         << product->getProductQuantity() << " to " << newQuantity << endl;
                    product->setProductQuantity(newQuantity);
                }
                else if (updateChoice == 2) {
                    double newPrice;
                    cout << "Enter new price: ";
                    cin >> newPrice;
                    cout << "Updated price of " << product->getProductName() << " from "
                         << product->getProductPrice() << " to " << newPrice << endl;
                    product->setProductPrice(newPrice);
                }
            } else {
                cout << "Item not found!\n";
            }
        }
        else if (choice == 3) {
            int id;
            cout << "Enter product ID to remove: ";
            cin >> id;
            auto it = remove_if(products.begin(), products.end(), [id](const Product& product) {
                return product.getProductID() == id;
            });

            if (it != products.end()) {
                cout << "Product removed successfully.\n";
                products.erase(it, products.end());
            } else {
                cout << "Item not found!\n";
            }
        }
        else if (choice == 4) {
            displayAll(products);
        }
        else if (choice == 5) {
            int id;
            cout << "Enter product ID to search: ";
            cin >> id;
            Product* product = searchByID(products, id);

            if (product) {
                cout << "Product found:\n";
                product->display();
            } else {
                cout << "Item not found!\n";
            }
        }
        else if (choice == 6) {
            int sortBy, order;
            cout << "1 - Sort by Quantity\n";
            cout << "2 - Sort by Price\n";
            cout << "Choose sorting criteria: ";
            cin >> sortBy;
            cout << "1 - Ascending\n";
            cout << "2 - Descending\n";
            cout << "Choose order: ";
            cin >> order;

            sortProducts(products, sortBy == 2, order == 1);
            displayAll(products);
        }
        else if (choice == 7) {
            displayLowStock(products);
        }
        else if (choice == 8) {  
            break;
        }
        else {
            cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
