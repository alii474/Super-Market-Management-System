#include <iostream> 
#include <string>
#include <limits>
#include <algorithm>
#include <queue>
#include <fstream>
#include<stack>
#include<windows.h>
#include <map>  // Add this line
#include<conio.h>
using namespace std;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void clearScreen() {
    system("cls"); 
}
// Product structure for linked list
struct Product {
    int id;
    string name;
    float price;
    int quantity;
    string category; 
    Product* next; // Pointer to the next product
};
// Customer structure for queue
struct Customer {
    string name;
    string phone;
    queue<pair<int, int>> orders; // Pair of product ID and quantity
};
// Global pointers for head of the linked list
Product* productHead = NULL;
int nextProductId = 1; // Unique product ID generator
// Global customer queue to manage orders
queue<Customer> customerQueue;
// Function prototypes
void addProduct();
void viewProducts();
void sortProductsByName();
void updateProduct();
void searchProduct();
void deleteProduct();
void manageCustomerOrders();
void saveProductsToFile();
void loadProductsFromFile();
Product* findProductById(int id); // Add this here
void displayProductDetails(Product* product); // Add this here
// Function to display Admin Menu
void adminMenu() {
    int choice;
    	clearScreen();
    char ch=178;
    while (true) {
        cout<<"\n\n";
        for(int i=1;i<77;i++)
        cout<<ch;
        cout<< " ADMIN MENU ";
        for(int i=1;i<80;i++)
        cout<<ch;
        cout<<"\n\n";
        
        cout<<"[1]  Add New Product" << endl;
        cout<<"[2]  View All Products"<< endl;
        cout<<"[3]  Sort Products by Name"<< endl;
        cout<<"[4]  Search Product"<< endl;
        cout<<"[5]  Update Product"<< endl; 
        cout<<"[6]  Delete Product"<< endl;
        cout<<"[7]  Save Products to File"<< endl;
        cout<<"[8]  Exit to Main Menu"<<endl;
        cout<<"  Select an option: ";
        cin>>choice;
        switch (choice) {
            case 1:	clearScreen();
                addProduct();
            clearScreen();break;
            case 2:	clearScreen();
                viewProducts();
            clearScreen(); break;
            case 3:	
                sortProductsByName();
                break;
            case 4: 	clearScreen();
                searchProduct();
               	clearScreen(); break;
            case 5:clearScreen();
          	 updateProduct();
                break;
            case 6:		clearScreen();
                deleteProduct();	
                break;
            case 7: 		
                saveProductsToFile();
                break;
            case 8:	clearScreen();
                return; 
            default:
                cout<<"Invalid option, please try again."<<endl;
        }
    }
}


// Function to display User Menu
void userMenu() {
    int choice;
    char ch=178;
    while (true) {
    	clearScreen(); 
    	cout<<"\n\n";
        for(int i=1;i<77;i++)
        cout<<ch;
        cout<< " USER MENU ";
        for(int i=1;i<80;i++)
        cout<<ch;
        cout<<"\n\n";
        cout<< "[1]  View All Products"<<endl;
        cout<< "[2]  Manage Customer Orders"<<endl;
        cout<< "[3]  Exit to Main Menu"<<endl;
        cout<< "Select an option: ";
        cin>> choice;
        switch (choice) {
            case 1: 	clearScreen();	
                viewProducts();
                break;
            case 2: 	clearScreen();
                manageCustomerOrders();
                break;
            case 3: 	clearScreen();
                return; 
            default:
                cout << "Invalid option, please try again." << endl;
        }
    }
}
void addProduct() {
    char choice;
    do {
        Product* newProduct = new Product;
        newProduct->id = nextProductId++;
        cout << "Enter Product Name: ";
        cin.ignore();
        getline(cin, newProduct->name);
        cout << "Enter Product Price: ";
        while (!(cin >> newProduct->price)) {
            cout<<"Invalid input. Please enter a valid price:";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Enter Product Quantity: ";
        while (!(cin >> newProduct->quantity)) {
            cout << "Invalid input. Please enter a valid quantity: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Enter Product Category: ";
        cin.ignore();
        getline(cin, newProduct->category);
        transform(newProduct->category.begin(), newProduct->category.end(), newProduct->category.begin(), ::tolower); // Convert to lowercase
        newProduct->next = productHead; // Insert at the beginning
        productHead = newProduct;
        cout<<"Product added successfully with ID: " << newProduct->id << endl;
        // Ask if the user wants to add another product
        cout<<"Do you want to add another product? (y/n): ";
        cin>>choice;
    } while (choice =='y'||choice == 'Y');
}

void viewProducts() {
    if (!productHead) {
        cout << "No products available." << endl;
        return;
    }

    // Create a map to categorize products by their category
    map<string, vector<Product*>> categoryMap;
    Product* current = productHead;

    // Fill the map with products categorized by their category
    while (current) {
        categoryMap[current->category].push_back(current);
        current = current->next;
    }

    // Display products by category
    for (const auto& category : categoryMap) {
        cout << "\nCategory: " << category.first << endl;

        bool firstProduct = true;  // Flag to ensure we only print the ID once per category
        for (size_t i = 0; i < category.second.size(); ++i) {
            Product* product = category.second[i];

            // Print ID and product details only once per category
            if (firstProduct) {
                cout << "    ID: " << product->id << " | Name: " << product->name
                     << " | Price: $" << product->price
                     << " | Quantity: " << product->quantity << endl;
                firstProduct = false;  // Set the flag to false after printing ID
            } else {
                // Print only product details, excluding the ID
                cout << "        Name: " << product->name
                     << " | Price: $" << product->price
                     << " | Quantity: " << product->quantity << endl;
            }
        }
    }
    cout << "\nPress Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}


// Merge function for merge sort on linked list
Product* merge(Product* left, Product* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->name < right->name) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}
// Merge sort function for linked list
Product* mergeSort(Product* head) {
    if (!head || !head->next) return head;
    Product* slow = head;
    Product* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Product* mid = slow->next;
    slow->next = NULL;
    Product* left = mergeSort(head);
    Product* right = mergeSort(mid);
    return merge(left, right);
}
// Function to sort products by name
void sortProductsByName() {
    if (!productHead) {
        cout << "No products to sort." << endl;
        return;
    }
    productHead = mergeSort(productHead);
    cout << "Products sorted successfully by name." << endl;
}
void updateProduct() {
    cout << "Enter Product ID to Update: ";
    int updateId;
    cin >> updateId;
    Product* current = productHead;
    while (current) {
        if (current->id == updateId) {
            cout << "Product Found:" << endl;
            displayProductDetails(current);
            char choice;
            do {
                cout << "What do you want to update?" << endl;
                cout << "1. Name" << endl;
                cout << "2. Price" << endl;
                cout << "3. Quantity" << endl;
                cout<< "4. Category" << endl;
                cout<<"5. Exit Update Menu" << endl;
                cout<<"Select an option: ";
                int updateChoice;
                cin>>updateChoice;
                switch (updateChoice) {
                    case 1:
                        cout<<"Enter New Name: ";
                        cin.ignore();
                        getline(cin, current->name);
                        cout<<"Name updated successfully!" << endl;
                        break;
                    case 2:
                        cout<<"Enter New Price: ";
                        while (!(cin>>current->price)) {
                            cout<<"Invalid input. Please enter a valid price: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cout << "Price updated successfully!" << endl;
                        break;
                    case 3:
                        cout<<"Enter New Quantity: ";
                        while (!(cin >> current->quantity)) {
                            cout<<"Invalid input. Please enter a valid quantity: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cout << "Quantity updated successfully!" << endl;
                        break;
                    case 4:
                        cout << "Enter New Category: ";
                        cin.ignore();
                        getline(cin, current->category);
                        transform(current->category.begin(), current->category.end(), current->category.begin(), ::tolower);
                        cout << "Category updated successfully!" << endl;
                        break;
                    case 5:
                        return; // Exit Update Menu
                    default:
                        cout<<"Invalid option, please try again."<<endl;
                }
                cout<<"Do you want to update anything else for this product? (y/n): ";
                cin>>choice;
            } while (choice == 'y' || choice == 'Y');

            return;
        }
        current=current->next;
    }
    cout<<"Product with ID "<<updateId<<" not found!"<<endl;
}
//Search function
void searchProduct() {
    char choice;
    do {
        cout<<"Enter Product Name or ID to Search: ";
        cin.ignore();
        string input;
        getline(cin, input);
        Product* current=productHead;
        bool found=false;
        while (current) {
            if (to_string(current->id) == input || current->name == input) {
                cout<< "Product Found:" <<endl;
                cout<< "ID: " <<current->id
                     << " | Name: " <<current->name
                     << " | Price: $" <<current->price
                     << " | Quantity: " <<current->quantity << endl;
                found=true;
            }
            current=current->next;
        }
        if (!found) cout<<"Product not found!"<<endl;
        // After search, ask if the user wants to search another product or go back
        cout<<"Do you want to search another product? (y/n): ";
        cin>>choice;
    } while (choice=='y'||choice=='Y');
    // Wait for user input before going back to the main menu
    cout<<"Press Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}
//Display Function
void displayProductDetails(Product* product) {
    cout<<"Product Details:"<<endl;
    cout<<"ID: "<<product->id<<endl;
    cout<<"Name:" << product->name<<endl;
    cout<<"Price: $"<< product->price<<endl;
    cout<<"Quantity:" <<product->quantity<<endl;
    cout<<"Category:"<<product->category<<endl;
}
//Delete function
void deleteProduct() {
    cout << "Enter Product ID to Delete: ";
    int deleteId;
    cin>>deleteId;
    Product* current=productHead;
    Product* previous=NULL;
    while (current) {
        if (current->id==deleteId) {
            // Ask for confirmation before deleting
            char choice;
            cout<<"Are you sure you want to delete product: "<< current->name<< "? (y/n): ";
            cin>>choice;
            if (choice=='y' || choice=='Y') {
                if (previous) {
                    previous->next=current->next; // Bypass the current node
                } else {
                    productHead=current->next; // Update head if first node
                }
                delete current; // Free memory
                cout<<"Product deleted successfully!" << endl;
            } else {
                cout<<"Product deletion canceled."<<endl;
            }
            return;
        }
        previous=current;
        current=current->next;
    }
    cout<<"Product not found!"<<endl;
}
// Function to save products to a text file in human-readable format
void saveProductsToFile() {
    ofstream file("File Upload.txt");
    if (!file) {
        cout<<"Error opening file for saving." << endl;
        return;
    }
    Product* current=productHead;
    while (current) {
        file << "Category: "<<current->category  // Write category first
             << " | ID: "<<current->id
             << " | Name: "<<current->name
             << " | Price: $"<<current->price
             << " | Quantity: "<<current->quantity<<endl;  // Then write other details
        current = current->next;
    }
    file.close();
    cout<<"Products saved successfully to file."<<endl;
}
void loadProductsFromFile() {
    ifstream file("File Upload.txt");
    if (!file) {
        cout << "Error opening file for loading." << endl;
        return;
    }
    nextProductId = 1;
    string line;
    int maxId = 0; // Variable to track the maximum ID
    while (getline(file, line)) {
        // Check if the line contains the necessary data
        if (line.find("ID: ") == string::npos || 
            line.find(" | Name: ") == string::npos || 
            line.find(" | Price: $") == string::npos || 
            line.find(" | Quantity: ") == string::npos) {
            continue; // Skip malformed lines without printing any message
        }

        Product* newProduct = new Product;
        try {
            size_t idPos = line.find("ID: ") + 4;
            size_t namePos = line.find(" | Name: ");
            size_t pricePos = line.find(" | Price: $");
            size_t quantityPos = line.find(" | Quantity: ");
            size_t categoryPos = line.find("Category: ") + 10;  // Adjust for "Category: " prefix
            
            newProduct->id = stoi(line.substr(idPos, namePos - idPos));
            maxId = max(maxId, newProduct->id); // Update the maximum ID
            newProduct->name = line.substr(namePos + 9, pricePos - (namePos + 9));
            newProduct->price = stof(line.substr(pricePos + 11, quantityPos - (pricePos + 11)));
            newProduct->quantity = stoi(line.substr(quantityPos + 13));
            newProduct->category = line.substr(categoryPos, namePos - categoryPos); 
            
            newProduct->next = productHead;
            productHead = newProduct;
        } catch (const exception&) {
            continue; // Skip this line if parsing fails without printing any error message
        }
    }

    nextProductId = maxId + 1; // Set nextProductId to one greater than the maximum ID found in the file
    file.close();
}


void saveOrderToFile(const Customer& customer) {
    std::ofstream outFile("orders.txt", std::ios::app);  // Append mode
    if (!outFile) {
        std::cerr<<"Error opening file for saving orders!"<<std::endl;
        return;
    }
    outFile<<customer.name<< "," <<customer.phone<<std::endl;
    std::queue<std::pair<int, int>> tempOrders=customer.orders;
    while (!tempOrders.empty()) {
        auto order=tempOrders.front();
        tempOrders.pop();
        outFile<<order.first <<" "<<order.second<<std::endl;
    }
    outFile << "END" << std::endl;  // Mark the end of this customer's order
    outFile.close();
}

void logProcessedOrderToFile(const Customer& customer, float totalBill) {
    std::ofstream outFile("processed_orders.txt", std::ios::app);  // Append mode
    if (!outFile) {
        std::cerr << "Error opening file for logging processed orders!" << std::endl;
        return;
    }
    outFile<< "Customer: " <<customer.name << ", Phone: "<<customer.phone<<std::endl;
    outFile<< "Total Bill: $"<<totalBill<<std::endl;
    outFile<< "Products:" <<std::endl;

    std::queue<std::pair<int, int>> tempOrders=customer.orders;  // Create a copy of the orders queue
    while (!tempOrders.empty()) {
        auto order = tempOrders.front();
        tempOrders.pop();
        Product* current = productHead;
        while (current) {
            if (current->id == order.first) {
                outFile << "Product: " << current->name 
                        << " | Quantity: " << order.second 
                        << " | Price: $" << current->price 
                        << " | Subtotal: $" << (current->price * order.second) << std::endl;
                break;
            }
            current=current->next;
        }
    }
    outFile << "---------------------" << std::endl;
    outFile.close();
}

void manageCustomerOrders() {
    char ch=178;
    while (true) {
        cout<< "\n\n";
        for(int i =1;i<70;i++)
        cout<<ch;
        cout<<" CUSTOMER ORDER MANAGEMENT SYSTEM ";
        for(int i=1;i<66; i++)
        cout << ch;
        cout<<"\n\n";
        cout<<"1. Add Customer Order" <<endl;
        cout<<"2. Process Customer Order"<<endl;
        cout<<"3. Exit to Main Menu"<<endl;
        cout<<"Select an option:";
        int choice;
        cin>>choice;
        switch (choice) {
            case 1:{
                Customer newCustomer;
                cout<<"Enter Customer Name: ";
                cin.ignore();  // Clear input buffer
                getline(cin, newCustomer.name);
                cout<<"Enter Customer Phone:";
                getline(cin, newCustomer.phone);
                bool moreOrders=true;  // Flag to check if the customer wants to order more items
                while (moreOrders) {
                    int productId, quantity;
                    cout<<"Enter Product ID (0 to stop): ";
                    cin>>productId;
                    if (productId == 0) {
                        moreOrders = false;  // Stop if product ID is 0
                    } else {
                        cout << "Enter Quantity: ";
                        cin >> quantity;
                        Product* current = productHead;
                        bool found = false;
                        while (current) {
                            if (current->id == productId) {
                                cout << "Product:" << current->name << "| Price: $" << current->price << "| Quantity:" << quantity << endl;
                                newCustomer.orders.push({productId, quantity});
                                found = true;
                                break;
                            }
                            current = current->next;
                        }
                        if (!found) {
                            cout<< "Product not found. Please try again." <<endl;
                        }
                    }
                    if (moreOrders) {
                        char choice;
                        cout<<"Do you want to add another product? (y/n):";
                        cin>>choice;
                        moreOrders=(choice=='y'||choice=='Y');  // If user wants to add more orders
                    }
                }
                customerQueue.push(newCustomer);  // Add customer to the global queue
                saveOrderToFile(newCustomer);  // Save order to file
                cout << "Customer order added successfully!" << endl;
                break;
            }
            case 2:
                if (!customerQueue.empty()) {
                    Customer frontCustomer=customerQueue.front();
                    customerQueue.pop();
                    cout<<"Processing Order for:"<<frontCustomer.name<<endl;
                    cout<<"Phone:" << frontCustomer.phone<<endl;
                    float totalOrderBill = 0.0;
                    while (!frontCustomer.orders.empty()) {
                        auto order=frontCustomer.orders.front();
                        frontCustomer.orders.pop();
                        Product* current=productHead;
                        while (current) {
                            if (current->id==order.first) {
                                if (current->quantity >= order.second) {  // Check stock
                                    cout<<"Product: "<<current->name<<" | Quantity: "<< order.second << endl;
                                    current->quantity-=order.second;  // Update stock
                                    totalOrderBill += current->price * order.second;  // Add to bill
                                } else {
                                    cout<<"Insufficient stock for product:"<<current->name<< endl;
                                }
                                break;
                            }
                            current=current->next;
                        }
                    }
                    cout<<"Total Bill for this order: $"<<totalOrderBill<<endl;
                    logProcessedOrderToFile(frontCustomer, totalOrderBill);  // Log processed order
                } else {
                    cout<<"No customer orders to process."<<endl;
                }
                break;
            case 3:
                clearScreen();
                return;
            default:
                clearScreen();
                cout<<"Invalid option, please try again."<<endl;
        }
    }
}

void processCustomerOrder() {
    if(!customerQueue.empty()) {
        Customer frontCustomer=customerQueue.front();
        customerQueue.pop();
        cout<<"Processing Order for:"<<frontCustomer.name<<endl;
        cout<<"Phone: "<< frontCustomer.phone<<endl;
        float totalOrderBill = 0.0;
        // Process each product in the customer's order
        while (!frontCustomer.orders.empty()) {
            auto order=frontCustomer.orders.front();
            frontCustomer.orders.pop();
            Product* current=productHead;
            while (current) {
                if (current->id==order.first) {
                    if (current->quantity>=order.second) { // Check if enough stock
                        cout<< "Product: "<< current->name
                             << " | Quantity: "<< order.second << endl;
                        current->quantity -= order.second; // Update stock
                        totalOrderBill +=current->price * order.second; // Calculate bill
                    }else{
                        cout<<"Insufficient stock for product:"<<current->name<<endl;
                    }
                    break;
                }
                current=current->next;
            }
        }
        cout<<"Total Bill for this order: $"<<totalOrderBill<<endl;
    } else {
        cout<<"No customer orders to process." << endl;
    }
}

// Main function
int main() { 
    loadProductsFromFile();
    char ch=178;
    setColor(14);
    while (true) {
        int choice;
        cout<<"\n";
        for(int i=1;i<70;i++)
        cout<<ch;
        cout<< " SUPER MARKET MANAGMENT SYSTEM " ;
        for(int i=1;i<68;i++)
        cout<<ch;
        cout<<"\n "<<endl;
        
        cout<< "[1] Admin Menu"<<endl;
        cout<< "[2] User Menu"<<endl;
        cout<< "[3] Exit"<<endl;
        cout<< "Select an option: ";
        cin>>choice;
        switch (choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                userMenu();
                break;
            case 3:
                saveProductsToFile(); // Save products before exiting
                cout<<"  Thank you for using the Supermarket System! Goodbye "<<endl;
                return 0;
            default:
                cout<<"Invalid option, please try again"<<endl;
        }
    }
}

