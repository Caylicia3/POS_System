# POS System

A simple command-line Point of Sale (POS) system written in C++.

This project is a C++ learning project focused on practicing fundamental programming concepts, file I/O, data persistence, error handling, and Git/GitHub workflows.

## Features

* Product management
* Product lookup by barcode
* Shopping cart management
* Add and remove products from the cart
* Checkout
* Receipt generation
* Sales record persistence
* Daily sales statistics
* Total revenue calculation
* CSV-based data storage
* Command-line interface

## Demo

The program runs in a command-line interface.

Typical workflow:

```text
Start POS System
      │
      ▼
  Select Function
      │
      ├── Product Management
      │
      ├── Shopping Cart
      │
      ├── Checkout
      │
      └── Sales Statistics
                │
                ▼
          Save Sales Data
                │
                ▼
             CSV Files
```

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

| File                      | Description                               |
| ------------------------- | ----------------------------------------- |
| `main.cpp`                | Program entry point and main control flow |
| `menu.cpp / menu.h`       | Command-line menu and user interaction    |
| `product.cpp / product.h` | Product-related operations                |
| `sale.cpp / sale.h`       | Sales records and sales statistics        |
| `product.csv`             | Product data                              |
| `sale.csv`                | Persistent sales records                  |
| `LearningLog/`            | Development and learning notes            |

## Data Persistence

The project uses CSV files to store data.

### `product.csv`

Stores product information such as:

* Product name
* Barcode
* Price

### `sale.csv`

Stores sales information such as:

* Sales date
* Number of sales
* Transaction time
* Purchased items
* Total transaction amount

Sales records are written to the CSV file after checkout, allowing sales data to remain available after the program is restarted.

## Requirements

### Runtime

For the released Windows version:

* Windows 10 or Windows 11
* No C++ development environment is required

### Development

If you want to build the project from source:

* C++ compiler
* C++ standard library
* A C++ development environment such as VS Code

## Running the Released Version

1. Download the latest Windows release from the [Releases](https://github.com/Caylicia3/POS_System/releases) page.
2. Extract the ZIP archive.
3. Keep the executable and required CSV files in the same directory.
4. Run `POS.exe`.

> **Important:** `product.csv` and `sale.csv` are used by the program for data storage. Do not delete or rename them unless you know how the program handles the corresponding files.

## Building from Source

Clone the repository:

```bash
git clone https://github.com/Caylicia3/POS_System.git
```

Enter the project directory:

```bash
cd POS_System/Project
```

Compile the source files with a C++ compiler.

For example, using `g++`:

```bash
g++ main.cpp menu.cpp product.cpp sale.cpp -o POS.exe
```

Then run:

```bash
POS.exe
```

Make sure the required CSV files are available in the working directory.

## Version

Current release:

**v0.1.1**

See the [Releases](https://github.com/Caylicia3/POS_System/releases) page for downloadable versions.

## Known Limitations

This is currently a small learning project, so there are several limitations:

* Data is stored using CSV files rather than a database.
* The application is primarily designed for command-line use.
* Input validation is still being improved.
* The current data model is relatively simple.
* The project has limited automated testing.
* The released version is currently focused on Windows.

## Future Improvements

Possible future improvements include:

* Improve input validation and error handling
* Refactor the shopping cart and product data models
* Improve project structure
* Add automated tests
* Improve data storage and parsing
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
