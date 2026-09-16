# C++ POS System

A modular command-line Point of Sale (POS) system developed in C++.

The project provides basic functions for product management, checkout, inventory management, sales recording, and administrator operations. Product and sales data are stored in CSV files, allowing the system to persist data between program runs.

## Features

### Product Management

* Load product information from CSV files
* Search products by barcode
* Display information for individual products
* Display all available products
* Add new products
* Delete products
* Modify product prices
* Check duplicate product names and barcodes

### Shopping Cart & Checkout

* Add products to the shopping cart using barcodes
* Enter multiple barcodes in a single command
* Increase or decrease item quantities
* Check current cart contents
* Clear the current cart
* Check product stock before adding items
* Automatically update inventory when items are added or removed
* Generate a final receipt during checkout
* Calculate the total purchase amount

Example:

```text
001 002 003
```

A barcode prefixed with `-` decreases the corresponding quantity:

```text
001 001 002 -001
```

Available checkout commands include:

```text
print
drop
checkout
exit
quit
```

### Inventory Management

The system maintains product stock information and provides several inventory operations:

* Restock products
* Directly modify product stock
* Check stock availability during checkout
* Restore stock when items are removed from the cart
* Display products together with current stock

### Sales Records

Completed transactions are stored in `sale.csv`.

Each record contains information including:

* Date
* Receipt number
* Transaction time
* Purchased products
* Total transaction amount

The system also provides:

* Automatic receipt number generation
* Current-day receipt numbering
* System time recording
* Sales records for a specific date
* Complete sales history
* Daily revenue calculation
* Clearing all sales history

### Administrator Mode

Administrator operations are protected by password verification.

Available administrator functions include:

```text
admin
setprice
itemadd
itemdel
restock
setstock
prices
back
```

Administrator functions include:

* Change administrator password
* Modify product prices
* Add products
* Delete products
* Restock products
* Correct product stock
* View all products and their stock

The administrator password is stored separately in `password.csv`.

### Input Validation

The system performs validation for several types of user input:

* Numeric input validation
* Barcode validation
* Duplicate barcode detection
* Duplicate product name detection
* Price validation
* Stock quantity validation
* Invalid command handling
* Password verification with limited attempts

Invalid input does not terminate the program and is handled through the corresponding error messages.

## Project Structure

```text
project1_POS/
├── LearningLog/
│   ├── g++.md
│   ├── patten
│   ├── perfect.md
│   ├── Sep_9.md
│   ├── Sep_10.md
│   ├── Sep_11.md
│   ├── Sep_12.md
│   ├── Sep_13.md
│   ├── Sep_14.md
│   ├── Sep_15.md
│   └── Sep_16.md
│
├── Project/
│   ├── admin.cpp
│   ├── admin.h
│   ├── main.cpp
│   ├── menu.cpp
│   ├── menu.h
│   ├── password.csv
│   ├── POS.exe
│   ├── product.cpp
│   ├── product.csv
│   ├── product.h
│   ├── sale.cpp
│   ├── sale.csv
│   └── sale.h
│
├── LICENSE
└── README.md
```

### Main Modules

| File                      | Responsibility                                                            |
| ------------------------- | ------------------------------------------------------------------------- |
| `main.cpp`                | Program entry point and main menu control                                 |
| `menu.cpp / menu.h`       | User interface, menu display, screen clearing and navigation              |
| `product.cpp / product.h` | Product data loading, product search and product-related operations       |
| `sale.cpp / sale.h`       | Sales records, receipt numbering, transaction time and revenue statistics |
| `admin.cpp / admin.h`     | Administrator authentication and product/inventory management             |
| `product.csv`             | Product and inventory data                                                |
| `sale.csv`                | Sales history                                                             |
| `password.csv`            | Administrator password                                                    |

## Data Format

### `product.csv`

Product information is stored using the following format:

```csv
name,barcode,price,stock
cola,001,3.50,10
lollipop,002,0.50,10
noodles,003,6.00,10
```

The fields are:

```text
name, barcode, price, stock
```

### `sale.csv`

Sales records are stored using the following format:

```csv
Date,number_of_sales/num,system_time,Receipt Items,total_sales_amount
```

A transaction may look like:

```text
1,1,14:32:10, cola 3.5*2=7,7
```

### `password.csv`

The administrator password is stored as a single line in the file.

## Program Flow

The main program starts by loading the current date and receipt number from the existing sales records.

The user can then select operations from the main menu:

```text
Main Menu
    │
    ├── Product Information
    │
    ├── Checkout
    │      ├── Add Items
    │      ├── Remove Items
    │      ├── Print Cart
    │      ├── Clear Cart
    │      └── Complete Checkout
    │
    ├── Change Date
    │
    ├── View Sales Records
    │
    ├── Clear Sales Records
    │
    └── Administrator Mode
           ├── Change Password
           ├── Modify Price
           ├── Add Product
           ├── Delete Product
           ├── Restock
           ├── Set Stock
           └── View Products
```

## Technical Implementation

The project is implemented using standard C++ features and the standard library.

Important techniques used in the project include:

* `vector` for runtime product storage
* `struct` for product data organization
* `ifstream` and `ofstream` for file operations
* CSV parsing using `stringstream`
* `getline()` for string and file input
* `stoi()` and `stod()` for string-to-number conversion
* Range-based `for` loops
* References for modifying objects in containers
* `const` references for read-only access
* String validation using `find()`
* Character validation using `isdigit()`
* Exception handling during numeric conversion
* `chrono` and `ctime` for transaction timestamps
* `iomanip` for formatted time output
* Conditional compilation for platform-dependent screen clearing
* `thread` and `chrono` for simple command-line delays

## Design Notes

### Modular Structure

The program is divided into several modules instead of placing all functionality in `main.cpp`.

The main responsibilities are separated roughly as follows:

```text
main
 └── Menu Control

product
 ├── Load Product Data
 ├── Search Products
 └── Product Data Operations

sale
 ├── Save Transactions
 ├── Read Sales History
 ├── Generate Receipt Numbers
 └── Calculate Revenue

admin
 ├── Authentication
 ├── Product Management
 └── Inventory Management

menu
 └── User Interface and Navigation
```

This structure makes the project easier to understand and maintain than a single-file implementation.

### Runtime Data and Persistent Data

The program distinguishes between data used during execution and data stored on disk.

For example, products are loaded into:

```cpp
vector<Product>
```

during program execution.

After changes are made, the updated product information can be written back to:

```text
product.csv
```

This allows modifications to remain available after restarting the program.

### Checkout Input Parsing

Checkout commands are entered as a complete line and then parsed using `stringstream`.

For example:

```text
001 002 003 -001 print checkout
```

can be processed sequentially from a single input line.

This approach allows multiple commands to be entered together while keeping the command parsing logic relatively simple.

## Build

A C++17-compatible compiler is recommended.

Using `g++`:

```bash
g++ -std=c++17 -Wall -Wextra -g *.cpp -o POS.exe
```

Run the program with:

```bash
./POS.exe
```

On Windows PowerShell:

```powershell
.\POS.exe
```

## Running the Program

The executable and CSV files should remain in the same directory.

A typical runtime directory is:

```text
Project/
├── POS.exe
├── product.csv
├── sale.csv
└── password.csv
```

The program reads and writes these files using relative paths:

```text
product.csv
sale.csv
password.csv
```

Therefore, the program does not depend on machine-specific absolute file paths.

## Default Data

The repository contains sample product data for demonstration purposes.

Example:

```text
cola      001      3.50
lollipop  002      0.50
noodles   003      6.00
```

The stock values are stored separately in the `stock` field of `product.csv`.

## Learning Log

The `LearningLog/` directory records development notes and learning progress during the implementation of the project.

The notes cover topics such as:

* C++ syntax and standard library usage
* File I/O
* CSV processing
* Input validation
* Data structures
* Git and version control
* Debugging
* Program design and refactoring

The learning log is kept separately from the actual application code so that the `Project/` directory remains focused on the runnable system.

## Known Limitations

This project is primarily designed as a command-line application and intentionally keeps the implementation relatively lightweight.

Current limitations include:

* CSV files are used instead of a database
* The command-line interface is text-based
* Product and sales data use simple CSV structures
* Password storage is not intended to provide production-level security
* Some operations could be further refactored to reduce repeated product traversal
* Financial values currently use `double`
* Error handling for malformed CSV files can be further improved

These limitations provide opportunities for future development and refactoring.

## Possible Future Improvements

Potential extensions include:

* More robust CSV parsing
* Improved exception and file error handling
* Separation of business logic from user interface logic
* Dedicated shopping cart data structures
* Improved transaction rollback handling
* Database-based data persistence
* GUI interface
* Unit testing
* Automated integration testing
* More complete cross-platform support
* Better formatting for receipts and sales reports

## License

This project is distributed under the license included in this repository.

## Project Status

The project currently provides a functional command-line POS workflow with:

* Product information management
* Shopping cart operations
* Checkout
* Inventory management
* Sales recording
* Sales history queries
* Administrator functions
* CSV-based persistence

The codebase is still suitable for continued refactoring and feature development.
