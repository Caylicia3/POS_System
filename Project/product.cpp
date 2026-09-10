//Product cola={"cola","001",3.50};Product lollipop={"lollipop","002",0.50};Product noodles={"noodles","003",6.00};
#include<iostream>
#include<sstream>
#include<fstream>
#include"product.h"
#include<vector>
using namespace std;

vector<Product> CreateProduct(){
    vector<Product> products;
    string line;
    ifstream file("product.csv");
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
    