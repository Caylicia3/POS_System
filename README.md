# Console POS System

A small command-line point-of-sale (POS) application written in C++. I built this as my first complete project during my first year of university to practice turning basic programming concepts into a multi-file program with persistent data.

The program simulates a convenience-store checkout workflow. It stores products and sales in CSV files, so the sample data can be inspected and edited with a text editor or spreadsheet application.

## Project Highlights

- **Checkout workflow:** add products by barcode, adjust quantities, review or clear the cart, and complete a sale.
- **Pricing rules:** apply a 2-unit discount to purchases of 10 or more, followed by an optional 10% member discount.
- **Inventory management:** check product prices and stock, add or delete products, change prices, restock items, and correct stock counts.
- **Sales records and reports:** save receipts with a day number, receipt number, time, purchased items, and total; review daily or historical sales and see summary totals.
- **CSV persistence:** use plain CSV files for product, sales, and administrator data.
- **Learning record:** keep dated development notes in `LearningLog/` to document questions, debugging, and progress.

## Requirements

- A C++17-compatible compiler, such as GCC (MinGW-w64/MSYS2 on Windows)
- A terminal or command prompt

## Build and Run

The application reads and writes `product.csv`, `sale.csv`, and `password.csv` using paths relative to the current working directory. Run it from the `Project` directory so it can find the provided data files.

### Windows with GCC

Open a terminal in `Project/` and compile the source files:

```bash
g++ -std=c++17 main.cpp admin.cpp menu.cpp product.cpp sale.cpp -o POS.exe
```

Then run:

```powershell
./POS.exe
```

### Linux or macOS with GCC/Clang

Open a terminal in `Project/`, build the program, and run it:

```bash
g++ -std=c++17 main.cpp admin.cpp menu.cpp product.cpp sale.cpp -o POS
./POS
```

The checked-in `POS.exe` is a Windows build. Building from source is recommended on other platforms.

## Using the Program

The main menu provides options to:

1. View a product by barcode or list all products.
2. Start checkout. Enter barcodes separated by spaces to add items; prefix a barcode with `-` to remove one item.
3. Enter `print` to preview the cart, `drop` to clear it, or `checkout` to complete the sale.
4. Advance the simulated day with `newday`.
5. View sales for a day or all recorded sales.
6. Clear sales history after confirming the action.
7. Enter administrator mode to manage products and inventory.
8. View a sales summary, including total revenue and the highest-sales day.

The interactive menus display the accepted commands and additional instructions as the program runs.

## Data Files

All data files are located in `Project/` and are read relative to the program's current working directory.

| File | Purpose |
| --- | --- |
| `product.csv` | Product name, barcode, price, and stock quantity |
| `sale.csv` | Simulated day, receipt number, time, item summary, and transaction total |
| `password.csv` | Administrator password used by the sample application |

The CSV files are plain text and can be reset or edited manually. Keep a backup before editing or clearing data. Product names should not contain commas because the current implementation uses commas as field separators.

## Project Structure

```text
project1_POS/
├── LearningLog/       # Dated notes from the development process
├── Project/
│   ├── main.cpp       # Program entry point and main menu routing
│   ├── menu.cpp       # Menu display and console helpers
│   ├── product.cpp    # Product lookup, cart, and checkout flow
│   ├── sale.cpp       # Sales records and sales summaries
│   ├── admin.cpp      # Administrator authentication and management
│   ├── *.h            # Corresponding declarations and shared structures
│   ├── product.csv    # Sample inventory
│   ├── sale.csv       # Sales history data
│   ├── password.csv   # Local administrator password data
│   └── POS.exe        # Windows executable
├── LICENSE
└── README.md
```

## What I Practiced

This project helped me apply and connect several C++ fundamentals:

- Splitting a program across header (`.h`) and implementation (`.cpp`) files
- Defining and using a `Product` structure and `std::vector`
- Reading and writing files with `ifstream` and `ofstream`
- Parsing delimited text with `std::stringstream`
- Organizing features into functions and handling interactive input
- Tracking down bugs involving input buffers, file modes, and mutable data
- Using Git and keeping a development log while building a project

## Current Limitations

This is an educational project and uses a deliberately simple design. Data is stored in CSV files rather than a database, and the administrator password is stored as plain text. The program is intended for local learning and demonstration, not for use in a real store. Input validation and file-error handling can also be improved.

## Possible Next Steps

- Strengthen input validation and handle malformed or missing CSV data safely.
- Store currency as integer minor units to avoid floating-point rounding issues.
- Hash administrator passwords and improve access control.
- Separate business logic from console input/output to make the program easier to maintain and test.
- Add automated tests and a build configuration such as CMake.

## License

Distributed under the MIT License. See [LICENSE](LICENSE) for details.
