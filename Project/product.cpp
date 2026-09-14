#include <iostream>
#include <sstream>
#include <fstream>
#include "product.h"
#include <vector>
#include "sale.h"
#include <thread> // 暂停时间
#include <chrono>
#include "menu.h"
//#include <iomanip>
using namespace std;

vector<Product> CreateProduct(const string& filename){
    vector<Product> products;
    string line;
    ifstream file(filename);
    if (!file) {
        cout << "Failed to open file\n";
        return products;
     }
    getline(file,line);//跳过第一行表头
    while(getline(file,line)){
        stringstream ss(line);
        string name, barcode;
        double price;
        getline(ss,name,',');
        getline(ss,barcode,',');
        ss >> price;
        Product product{name, barcode, price};//注意：这个 product 每次循环结束就没了，需要用vector存储起来
        products.push_back(product);
    }
     
    file.close();
    return products;
}
   
void ShowProductInfo(const string& barcode){
    /*
    if(barcode=="001"){
        cout << "Product Name: cola" << endl;
        cout << "Barcode: 001" << endl;
        cout << "Price: 3.50" << endl;
    } else if(barcode=="002"){
        cout << "Product Name: lollipop" << endl;
        cout << "Barcode: 002" << endl;
        cout << "Price: 0.50" << endl;
    } else if(barcode=="003"){
        cout << "Product Name: noodles" << endl;
        cout << "Barcode: 003" << endl;
        cout << "Price: 6.00" << endl;
    } else if(barcode=="prices"){
        cout << "Product Name: cola" << endl;
        cout << "Barcode: 001" << endl;
        cout << "Price: 3.50" << endl << endl;
        cout << "Product Name: lollipop" << endl;
        cout << "Barcode: 002" << endl;
        cout << "Price: 0.50" << endl << endl;
        cout << "Product Name: noodles" << endl;
        cout << "Barcode: 003" << endl;
        cout << "Price: 6.00" << endl;
    }*/
    string line1, line2, line3;
    bool valid;
    if(Judge(line1, line2, line3, barcode, valid)){
        cout << "Product Name: " << line1 << endl;
        cout << "Barcode: " << line2 << endl;
        cout << "Price: " << line3 << endl;
    }else if(barcode=="prices"){
        string line;
        ifstream file("product.csv");
        getline(file,line);
        while(getline(file,line)){
            stringstream ss(line);
            getline(ss,line,',');
            cout << "Product Name: " << line << "   ";
            getline(ss,line,',');
            cout << "Barcode: " << line << "   ";
            ss >> line;
            cout << "Price: " << line << endl;
        }
    }else {
        if(valid){
            cout << "Error 0: code not found" << endl;
        }
    }
}

bool Judge(string& line1, string& line2, string& line3, const string& barcode, bool& valid){
    ifstream file("product.csv");
    if (!file) {
        cout << "Failed to open file" << endl;
        valid = 0;
        return false;
     }
    getline(file,line1);//去掉表头
    while(getline(file,line1)){
        stringstream ss(line1);//创建一个 std::stringstream 对象 ss，并用字符串 line 的内容初始化它。
        getline(ss,line1,',');
        getline(ss,line2,',');
        ss >> line3;
        if(barcode == line2){
            return true;
        }
    }
    valid = 1;
    return false;
}



void Case1(){
    cout << "Please enter the barcode of the product you want to check: " << endl;
    cout << "(Enter 'exit' or 'quit' to quit)" << endl;
    cout << "If you want to check all products, please enter 'prices'" << endl;
    string input2;
    while(cin >> input2 && input2 != "exit" && input2 != "quit"){
            ShowProductInfo(input2);
        }
    ReturnMenu();
}

void Case2(vector<Product>& products,int date,int& num){
    cout << "Enter barcodes to add items to the order. Each barcode adds 1 item (separated by spaces)." << endl;
    cout << "Enter 'exit' or 'quit' to quit." << endl;
    cout << "Enter barcode with a '-' prefix to decrease quantity by 1 (e.g., '-001').Multiple entries allowed. Separate with spaces." << endl;
    cout << "Enter 'print' to print the current receipt (items, quantities, prices, and total)." << endl;
    cout << "Enter 'drop' to clear the order and restart." << endl;
    cout << "Enter 'checkout' to finalize the order, print the receipt, and clear the order." << endl;
    cout << "Please enter your command: ";
    string input2;
    while(cin >> input2 && input2 != "exit" && input2 != "quit"){//每一个输入都循环一次
        Checkout(input2, products, date, num);             
    }   
    ReturnMenu();
};

void Checkout(string input2, vector<Product>& products, int date, int& num){
    bool found1 = false, found2 = false;
    for(Product& product : products){
        if(product.barcode == input2){
            product.quantity++;
            found1 = true;
            break;
        }
    }
    if(found1){//一个一个读入，打印目前购物车里所有商品的信息
        char input3;
        cin.get(input3);
        if(input3 == ' '){//如果输入的下一个字符是空格，就继续读入下一个条形码
            return;
        }
        else{
            cout << "----- Current order -----:" << endl;
            for(Product& product : products){
                if(product.quantity > 0){
                    cout << product.name << " " << product.price << "*" << product.quantity << "=" << product.price * product.quantity << endl;
                }
            }
        }
    }
    else if(input2[0] == '-'){//检查字符串第一个字符是不是负号
            input2 = input2.substr(1);//去掉负号(截取负号后面的部分)
            for(Product& product : products){
                if(product.barcode == input2){
                    found2 = true;
                    if(product.quantity == 0){
                        cout << "No items to remove for this product." << endl;
                    }
                    else{
                        product.quantity--;
                    }
                    break;
                }
            }
            if(found2){//一个一个读入，打印目前购物车里所有商品的信息
                        char input4;
                        bool empty = true;
                        cin.get(input4);
                        if(input4 == ' '){//如果输入的下一个字符是空格，就继续读入下一个条形码
                            return;
                        }
                        else{
                        for(Product& product : products){
                            if(product.quantity > 0){
                                empty = false;
                                break;
                            }                          
                        }
                        if(empty){
                            cout << "Cart is empty." << endl;
                            return;
                        }
                        cout << "----- Current order -----:" << endl;
                        for(Product& product : products){
                            if(product.quantity > 0){
                                cout << product.name << " " << product.price << "*" << product.quantity << "=" << product.price * product.quantity << endl;
                            }
                        }
                    }
            }else{
                cout << "Error 3:Invalid input" << endl; 
            }
    }else if(input2 == "print"){
        bool checkEmpty = true;
        cout << "----- Current order -----:" << endl;
        for(Product& product : products){
            if(product.quantity > 0){
                cout << product.name << " " << product.price << "*" << product.quantity << "=" << product.price * product.quantity << endl;
                checkEmpty = false;
            }
        }
        if(checkEmpty){
            cout << "Cart is empty." << endl;
        }
    }else if(input2 == "drop"){
        for(Product& product : products){
            product.quantity = 0;
        }
        cout << "Order cleared." << endl;
    }else if(input2 == "checkout"){
        double total = 0;
        cout << "----- Final Receipt -----:" << endl;
        for(Product& product : products){
            if(product.quantity > 0){
                cout << product.name << " " << product.price << "*" << product.quantity << "=" << product.price * product.quantity << endl;
                total += product.price * product.quantity;
            }
           }
        cout << "Total: " << total << endl;
        Record(date,num,products,total); 
        for(Product& product : products){
            product.quantity = 0;
        }
        cout << "Enter 'exit' or 'quit' to quit." << endl;
    }else{
        cout << "Error 2:Invalid input" << endl; 
    }
}
