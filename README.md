# POS_System

A lightweight command-line Point of Sale (POS) system implemented in C++.

This project simulates a basic retail checkout workflow, including product management, checkout, sales recording, and administrator operations.

The project is developed with standard C++ features and uses CSV files for persistent data storage.

---

## Project Overview

POS_System is a command-line interactive application designed to simulate a small retail management system.

The system provides:

- Product information management
- Product searching
- Shopping cart and checkout functions
- Sales record management
- Administrator mode
- Persistent data storage through CSV files

The main purpose of this project is to practice C++ programming, file operations, modular program design, and basic software engineering concepts.

---

## Features

### Product Management

The system stores product information in CSV format.

Example:

```csv
name,barcode,price
cola,001,3.50
lollipop,002,0.50
noodles,003,6.00
```

Supported operations:

- Load product information from CSV files
- Search products by barcode
- Display all products
- Add new products
- Delete products
- Modify product prices

---

### Checkout System

The cashier module supports interactive order management.

Features:

- Add products by entering product barcodes
- Remove products using `-barcode`
- View current order information
- Clear current order
- Complete checkout and generate transaction records

Example commands:

Add product:

```
001
```

Remove product:

```
-001
```

View current order:

```
print
```

Clear current order:

```
drop
```

Complete checkout:

```
checkout
```

During checkout, the system will:

1. Generate the final receipt
2. Calculate the total price
3. Save the transaction record
4. Reset the shopping cart

---

### Sales Record System

Completed transactions are stored in:

```
sale.csv
```

Each transaction contains:

- Date
- Receipt number
- Transaction time
- Purchased items
- Total amount

Example:

```csv
Date,number_of_sales/num,system_time,Receipt Items,total_sales_amount
1,1,12:30:15,cola 3.5*2=7,7
```

Supported commands:

View today's sales:

```
sales
```

View sales of a specific day:

```
sales 3
```

View all sales history:

```
all
```

The system also supports clearing historical sales records after confirmation.

---

### Administrator Mode

Administrator mode provides additional management functions.

Functions include:

- Administrator authentication
- Change administrator configuration
- Modify product price
- Add products
- Delete products

When adding new products, the system checks:

- Barcode validity
- Duplicate barcode
- Duplicate product name
- Price validity

When deleting products, the system reloads product information and rewrites the CSV file.

---

## Project Structure

```
POS_System
│
├── main.cpp
│
├── menu.cpp
├── menu.h
│
├── product.cpp
├── product.h
│
├── sale.cpp
├── sale.h
│
├── admin.cpp
├── admin.h
│
├── product.csv
├── sale.csv
└── password.csv
```

---

## Implementation Details

### CSV Data Storage

This project uses CSV files instead of a database because the project scale is relatively small.

CSV files are used for:

- Product information
- Sales records
- Administrator authentication data

The program uses:

- `fstream`
- `stringstream`
- File input/output operations

to read and write structured data.

---

### Modular Design

The project separates different responsibilities into independent modules.

Structure:

```
main.cpp
    |
    ├── menu module
    |
    ├── product module
    |
    ├── sale module
    |
    └── admin module
```

This reduces coupling and improves code organization and maintainability.

---

### Input Validation

The program includes multiple input validation mechanisms:

- Invalid numeric input detection
- Barcode checking
- Price format checking
- Duplicate data checking
- Command validation

The project also handles common C++ input stream issues caused by mixing:

```cpp
cin >>
```

and:

```cpp
getline()
```

---

## Development Challenges

During development, several problems were encountered and solved.

### 1. File Overwriting Issue

When modifying files using:

```cpp
ofstream
```

the default behavior may truncate existing files.

The solution was:

- Complete input validation before opening output files
- Carefully control file writing operations

---

### 2. CSV Parsing

Initially, CSV files were treated as simple text files.

Later, the project introduced:

```cpp
stringstream
```

to parse structured data:

```
name,barcode,price
```

into C++ objects.

---

### 3. Input Buffer Problems

Mixing:

```cpp
cin >>
```

with:

```cpp
getline()
```

can leave newline characters in the input buffer.

The project handles this by clearing remaining input when necessary.

---

## Build and Run

### Requirements

- C++ compiler supporting C++17
- Standard library support

Recommended:

- GCC
- MinGW
- Visual Studio C++ Compiler

---

### Compile

Example:

```bash
g++ -std=c++17 *.cpp -o POS.exe
```

---

### Run from Source

Make sure the executable and CSV files are located in the same directory:

```
POS.exe
product.csv
sale.csv
password.csv
```

Then run:

```bash
./POS.exe
```

---

## Release Version

Pre-built executable files are available through GitHub Releases.

Users can run the program directly without installing a C++ development environment.

To run the release version:

1. Download the latest release package
2. Extract all files into the same directory
3. Run `POS.exe`

The CSV files should remain in the same directory as the executable because the program uses relative paths to access data files.

---

## Future Improvements

Possible future improvements include:

- Replace CSV storage with a database
- Add graphical user interface
- Improve user permission management
- Add automated testing
- Improve error handling
- Support more advanced inventory management

---

## License

This project is licensed under the MIT License.