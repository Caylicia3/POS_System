# POS System

A simple command-line Point of Sale (POS) system written in C++.

This project is a C++ learning project focused on practicing fundamental programming concepts, file I/O, data persistence, error handling, and Git/GitHub workflows.

## Features

* Product lookup by barcode
* View all product information
* Add products to the shopping cart
* Remove products from the shopping cart
* View the current order
* Clear the current order
* Checkout and receipt generation
* Persistent sales records
* Daily sales statistics
* View all sales records
* Total revenue calculation
* Change the current business day
* Clear all sales history
* CSV-based data storage
* Windows executable release

## Demo

The program is a command-line interactive POS system.

```text
Start POS System
      │
      ▼
  Main Menu
      │
      ├── 1. Show Product Information
      │
      ├── 2. Checkout
      │
      ├── 3. Change Date
      │
      ├── 4. View Sales Records
      │
      ├── 5. Clear Sales Records
      │
      └── 0. Exit
```

## Main Menu

When the program starts, the following options are available:

| Input | Function                             |
| ----- | ------------------------------------ |
| `0`   | Exit the program                     |
| `1`   | Show product information             |
| `2`   | Checkout                             |
| `3`   | Change the current business day      |
| `4`   | View sales records and total revenue |
| `5`   | Clear all sales records              |

## Usage

### 1. Show Product Information

Select:

```text
1
```

You can then enter a product barcode to view its information.

For example:

```text
001
```

The program displays:

```text
Product Name
Barcode
Price
```

To display all available products:

```text
prices
```

To return to the main menu:

```text
exit
```

or:

```text
quit
```

---

### 2. Checkout

Select:

```text
2
```

The checkout interface accepts product barcodes.

Each barcode adds **one item** to the current order.

For example:

```text
001
001
002
```

This adds two units of product `001` and one unit of product `002`.

#### Remove an item

Add `-` before the barcode:

```text
-001
```

This decreases the quantity of product `001` by one.

#### Print the current order

```text
print
```

This displays the current items, quantities, prices, and total amount.

#### Clear the current order

```text
drop
```

This clears the current order without recording a sale.

#### Complete the transaction

```text
checkout
```

The program will:

1. Display the final receipt.
2. Calculate the total amount.
3. Save the transaction to `sale.csv`.
4. Clear the current order.

#### Exit checkout

```text
exit
```

or:

```text
quit
```

---

### 3. Change the Business Day

Select:

```text
3
```

Then enter:

```text
newday
```

The current day will increase by one.

The receipt number for the new day is calculated from the existing sales records.

To return to the main menu:

```text
exit
```

or:

```text
quit
```

---

### 4. View Sales Records

Select:

```text
4
```

#### View today's sales

Enter:

```text
sales
```

The program displays the sales records for the current day and calculates the daily revenue.

#### View sales from a specific day

For example:

```text
sales 1
```

This displays the sales records and total revenue for Day 1.

#### View all sales records

```text
all
```

The program displays the sales history grouped by day and calculates the total revenue for each day.

To return to the main menu:

```text
exit
```

or:

```text
quit
```

---

### 5. Clear Sales History

Select:

```text
5
```

The program will ask for confirmation.

Enter:

```text
1
```

to clear all sales records.

This operation cannot be undone.

You can also enter:

```text
exit
```

or:

```text
quit
```

to cancel.

> **Warning:** Clearing sales history overwrites `sale.csv` and removes the existing sales records.

## Data Persistence

The project uses CSV files for persistent data storage.

### `product.csv`

Stores product information:

```text
Product Name
Barcode
Price
```

Example:

```text
cola,001,3.5
lollipop,002,0.5
noodles,003,6
```

### `sale.csv`

Stores transaction information including:

* Business day
* Receipt number
* Transaction time
* Purchased items
* Total transaction amount

Sales records are written to `sale.csv` after a successful checkout.

This allows sales information to remain available after the program is restarted.

## Project Structure

```text
POS_System/
│
├── Project/
│   ├── main.cpp
│   ├── menu.cpp
│   ├── menu.h
│   ├── product.cpp
│   ├── product.h
│   ├── sale.cpp
│   ├── sale.h
│   ├── product.csv
│   └── sale.csv
│
├── LearningLog/
│   └── ...
│
└── README.md
```

### Main Components

| File                      | Description                                            |
| ------------------------- | ------------------------------------------------------ |
| `main.cpp`                | Program entry point and main control flow              |
| `menu.cpp / menu.h`       | Command-line menu and screen management                |
| `product.cpp / product.h` | Product loading, lookup, and checkout operations       |
| `sale.cpp / sale.h`       | Sales recording, sales statistics, and date management |
| `product.csv`             | Product data                                           |
| `sale.csv`                | Persistent sales records                               |
| `LearningLog/`            | Development and learning notes                         |

## Requirements

### Released Version

The released Windows version requires:

* Windows 10 or Windows 11
* No C++ development environment
* No compiler installation

The program can be run directly using the provided executable.

### Building from Source

To build the project from source, you need:

* A C++ compiler
* C++ standard library
* A development environment such as VS Code

## Running the Released Version

1. Go to the [Releases](https://github.com/Caylicia3/POS_System/releases) page.
2. Download the latest Windows release ZIP file.
3. Extract the ZIP archive.
4. Make sure `POS.exe`, `product.csv`, and `sale.csv` are in the same directory.
5. Run `POS.exe`.

The current release is:

**v0.1.1**

> **Important:** The program uses relative paths to access `product.csv` and `sale.csv`. Keep these files in the same working directory as the executable.

## Building from Source

Clone the repository:

```bash
git clone https://github.com/Caylicia3/POS_System.git
```

Enter the project directory:

```bash
cd POS_System/Project
```

Compile the source files using `g++`:

```bash
g++ main.cpp menu.cpp product.cpp sale.cpp -o POS.exe
```

Run the program:

```bash
POS.exe
```

Make sure `product.csv` and `sale.csv` are available in the working directory when running the program.

## Error Messages

The current version uses several error codes for invalid operations.

| Error Code | Meaning                         |
| ---------- | ------------------------------- |
| `Error 0`  | Product barcode not found       |
| `Error 2`  | Invalid checkout command        |
| `Error 3`  | Invalid product removal command |
| `Error 4`  | Failed to record the sale       |
| `Error 5`  | Invalid sales query             |
| `Error 6`  | Invalid `sales` command format  |
| `Error 7`  | Invalid date-change command     |
| `Error 8`  | Invalid day parameter           |

These error codes are currently part of the command-line interface and may be redesigned in future versions.

## Version

Current release:

**v0.1.1**

This is the second official release of the project.

See the [Releases](https://github.com/Caylicia3/POS_System/releases) page for available versions and release notes.

## Known Limitations

This is currently a small C++ learning project.

Current limitations include:

* Data is stored using CSV files rather than a database.
* The application is primarily designed for command-line use.
* Input validation is still being improved.
* The current data model is relatively simple.
* Automated testing is limited.
* The released version currently focuses on Windows.
* The program currently depends on the CSV files being available in the expected working directory.

## Future Improvements

Possible future improvements include:

* Improve input validation and error handling
* Refactor the shopping cart and product data models
* Improve the project structure
* Add automated tests
* Improve CSV parsing and data validation
* Improve file path handling
* Improve cross-platform compatibility
* Add a build system such as CMake
* Add continuous integration with GitHub Actions
* Consider using SQLite for persistent data storage
* Improve the command-line user interface

## Learning Goals

This project is mainly intended as a practical C++ learning project.

Through this project, I am practicing:

* C++ fundamentals
* Functions and structures
* STL containers
* Header and source file organization
* File input/output
* CSV data processing
* Error handling
* Data persistence
* Git and GitHub
* GitHub Releases
* Software packaging and distribution

## License

This project is released under the MIT License.

See [LICENSE](LICENSE) for details.
