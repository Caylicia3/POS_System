# POS System

A command-line Point of Sale (POS) system implemented in C++.

This project is my first complete C++ project. It focuses on practicing fundamental programming skills, including file operations, modular design, data management, and basic software development workflow.

The system provides basic functions for product management, shopping cart operations, checkout, sales record storage, and administrator management.

## Features

### Customer Functions

- View the main menu
- Search products by barcode
- Add products to shopping cart
- Remove products from shopping cart
- Calculate total payment amount
- Generate sales records after checkout

### Administrator Functions

- Administrator password verification
- Modify product prices
- Add new products
- Check duplicate product information
- Modify product stock information
- View sales-related information

### Data Management

The project uses CSV files for simple data storage:

- `product.csv`
  - Stores product information, including name, barcode, price, and stock.

- `sale.csv`
  - Stores transaction records, including date, receipt number, purchased items, and total amount.

- `password.csv`
  - Stores administrator password information.

## Project Structure

```
project1_POS
├── LearningLog
│   ├── patten
│   ├── perfect.md
│   ├── Sep_9.md
│   ├── Sep_10.md
│   ├── Sep_11.md
│   ├── Sep_12.md
│   ├── Sep_13.md
│   ├── Sep_14.md
│   ├── Sep_15.md
│   ├── Sep_16.md
│   ├── Sep_17.md
│   ├── Sep_18.md
│   └── Sep_19.md
│
├── Project
│   ├── admin.cpp
│   ├── admin.h
│   ├── main.cpp
│   ├── menu.cpp
│   ├── menu.h
│   ├── product.cpp
│   ├── product.h
│   ├── sale.cpp
│   ├── sale.h
│   ├── product.csv
│   ├── sale.csv
│   ├── password.csv
│   └── POS.exe
│
├── LICENSE
└── README.md
```

## Implementation Details

### Programming Language

- C++

### Development Environment

- C++17
- GCC Compiler
- Visual Studio Code
- MSYS2 toolchain

### Main Concepts Practiced

Through this project, I practiced:

- C++ multi-file project organization
- Header files and source files separation
- Structure design (`struct`)
- File input and output (`fstream`)
- CSV data processing
- Vector container usage
- Function modularization
- Basic Git version control workflow
- Debugging and problem solving

## Build and Run

### Run the executable directly

The release version provides a standalone Windows executable.

Users can run the program on a Windows system without installing a C++ compiler or development environment.

Download the release package, extract all files, and run:

```
POS.exe
```

Make sure the required CSV data files remain in the same directory as the executable.

### Compile from source

Make sure a C++ compiler is installed.

Example:

```bash
g++ -std=c++17 main.cpp admin.cpp menu.cpp product.cpp sale.cpp -o POS.exe -static
```

Then run:

```bash
./POS
```

## File Storage

The program reads and writes data through CSV files.

Example:

### Product Data

```
name,barcode,price,stock
cola,001,4.00,10
lollipop,002,0.50,20
noodles,003,6.00,15
```

### Sales Record

```
Date,number_of_sales/num,system_time,Receipt Items,total_sales_amount
```

## Learning Notes

`LearningLog` contains the development records during the project.

It documents:

- Problems encountered during development
- Design decisions
- Debugging processes
- Understanding of C++ features

These records reflect the process of gradually improving programming ability through practice.

## Future Improvements

Possible improvements:

- Improve checkout input handling
- Add more robust error handling
- Optimize data storage method
- Introduce a database instead of CSV files
- Improve user interface experience

## License

This project is licensed under the MIT License.