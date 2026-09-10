//Product cola={"cola","001",3.50};Product lollipop={"lollipop","002",0.50};Product noodles={"noodles","003",6.00};
#include<iostream>
#include<sstream>
#include<fstream>
#include"product.h"
#include<vector>
//#include <iomanip>
using namespace std;

vector<Product> CreateProduct(const string& filename){
    vector<Product> products;
    string line;
    ifstream file(filename);
    if (!file) {
        cout << "无法打开文件\n";
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
    }else {
        cout << "ERROR: code not found" << endl;
    }
}

void Case1(){
    cout << "Please enter the barcode of the product you want to check: " << endl;
    cout << "(Enter 'exit' or 'quit' to quit)" << endl;
    cout << "If you want to check all products, please enter 'prices'" << endl;
    string input2;
    while(cin >> input2 && input2 != "exit" && input2 != "quit"){
            ShowProductInfo(input2);
        }
}

void Case2(vector<Product>& products){
    cout << "Enter barcodes to add items to the order. Each barcode adds 1 item (separated by spaces)." << endl;
    cout << "Enter 'exit' or 'quit' to quit." << endl;
    cout << "Enter barcode with a '-' prefix to decrease quantity by 1 (e.g., '-001')." << endl;
    cout << "Enter 'print' to print the current receipt (items, quantities, prices, and total)." << endl;
    cout << "Enter 'drop' to clear the order and restart." << endl;
    cout << "Enter 'checkout' to finalize the order, print the receipt, and clear the order." << endl;
    cout << "Please enter your command: ";
    string input2;
    while(cin >> input2 && input2 != "exit" && input2 != "quit"){//每一个输入都循环一次
        Checkout(input2, products);    
                    
    }
                
};

void Checkout(string input2, vector<Product>& products){
                bool found = false;
                for(Product& product : products){
                    if(product.barcode == input2){
                        product.quantity++;
                        found = true;
                        break;
                    }
                }
                if(found){//每次只读入一个商品，但打印目前购物车里所有商品的信息
                    cout << "----- Current order -----:" << endl;
                    for(Product& product : products){
                        if(product.quantity > 0){
                            cout << product.name << " " << product.price << "*" << product.quantity << "=" << product.price * product.quantity << endl;
                        }
                    }
                }
                else{
                    if(input2[0] == '-'){//检查字符串第一个字符是不是负号
                        input2 = input2.substr(1);//去掉负号(截取负号后面的部分)
                        for(Product& product : products){
                            if(product.barcode == input2){
                                product.quantity--;
                                cout << product.name << " " << product.price << "*" << product.quantity << "=" << product.price * product.quantity << endl;
                                break;
                            }
                        }
                    }else if(input2 == "print"){
                        for(Product& product : products){
                            if(product.quantity > 0){
                                cout << product.name << " " << product.price << "*" << product.quantity << "=" << product.price * product.quantity << endl;
                            }
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
                        for(Product& product : products){
                            product.quantity = 0;
                        }
                    }else{
                        cout << "Invalid input" << endl; 
                    }
                }
            }