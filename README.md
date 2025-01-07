# Supermarket Management System

## Introduction

The **Supermarket Management System** is a console-based C++ application designed to manage a supermarket's operations efficiently. The system provides functionality for both administrators and customers, enabling them to handle inventory, process orders, and maintain records seamlessly. 

The project demonstrates the use of object-oriented programming (OOP) principles, file handling, and data structures like queues and linked lists to create a robust and user-friendly application.

---

## Features

### Admin Module
- Add, edit, and delete products in the inventory.
- View the complete list of available products with details like name, price, and stock quantity.
- Save and load product data to/from a file for persistent storage.

### Customer Module
- Place orders by selecting products and specifying quantities.
- Process customer orders, including stock updates and bill generation.
- Handle multiple customers using a queue-based system.
- Save customer order history to a file for record-keeping.

### Additional Features
- File handling for persistent storage of product data and customer orders.
- Input validation to ensure error-free user interaction.
- Real-time stock management and bill calculation.

---

## Requirements

To run this project, ensure the following:

### Software
- **Compiler**: A C++ compiler that supports C++11 or later (e.g., GCC, Clang, or MSVC).
- **Development Environment**: Any C++ IDE (e.g., Code::Blocks, Visual Studio, CLion) or a simple text editor with a terminal.

### Hardware
- Minimum system requirements:
  - 1 GHz processor
  - 512 MB RAM
  - 50 MB free disk space

### Libraries/Dependencies
- Standard C++ libraries
- #include <iostream> 
#include <string>
#include <limits>
#include <algorithm>
#include <queue>
#include <fstream>
#include<stack>
#include<windows.h>
#include <map>  
#include<conio.h>

---

## How to Run

1. Clone the repository or download the source files.
2. Open the project in your preferred IDE or compile it using a terminal:
   ```bash
   g++ -o supermarket_system main.cpp
   ./supermarket_system
