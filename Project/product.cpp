//Product cola={"cola","001",3.50};Product lollipop={"lollipop","002",0.50};Product noodles={"noodles","003",6.00};
#include<iostream>
#include<sstream>
#include<fstream>
#include"product.h"
#include<vector>
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
