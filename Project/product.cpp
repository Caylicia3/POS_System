#include <iostream>
#include <sstream>
#include <fstream>
#include "product.h"
#include <vector>
#include "sale.h"
#include <thread> // 暂停时间
#include <chrono>
#include "menu.h"
#include "admin.h"
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
        string name, barcode, pre_price;
        int stock;
        getline(ss,name,',');
        getline(ss,barcode,',');
        getline(ss,pre_price,',');//getline(ss, 变量, ',') 的第二个参数必须是 std::string。ss >> 变量 的 >> 对 int、double 等数字类型有重载，可以直接解析数字。
        ss >> stock;
        double price = stod(pre_price);//注意类型转换
        Product product{name, barcode, price, stock};//注意：这个 product 每次循环结束就没了，需要用vector存储起来
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
    }else if(barcode == "prices"){
        string line;
        ifstream file("product.csv");
        getline(file,line);
        while(getline(file,line)){
            stringstream ss(line);
            getline(ss,line,',');
            cout << "Product Name: " << line << "   ";
            getline(ss,line,',');
            cout << "Barcode: " << line << "   ";
            getline(ss,line,',');
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
        getline(ss,line3,',');
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

void Case2(int date, int& num){//重写版（v0.1.4以前的版本都是未重写的）重新拆分逻辑、使用stringstream修复输入bug、让运行逻辑更清晰
    cout << "Enter barcodes to add items to the order. Each barcode adds 1 item (separated by spaces)." << endl;
    cout << "Enter 'exit' or 'quit' to quit." << endl;
    cout << "Enter barcode with a '-' prefix to decrease quantity by 1 (e.g., '-001').Multiple entries allowed. Separate with spaces." << endl;
    cout << "Enter 'print' to print the current receipt (items, quantities, prices, and total)." << endl;
    cout << "Enter 'drop' to clear the order and restart." << endl;
    cout << "Enter 'checkout' to finalize the order, print the receipt, and clear the order." << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Please enter your command: ";//stringstream 支持同时处理多个输入（eg. 001 006 002 -001 print 002 drop 003 checkout)
    string input2;
    vector<Product> products = CreateProduct("product.csv");
    cin.ignore(1000,'\n');//又忘记处理回车了
    while(1){
        getline(cin, input2);
        stringstream ss(input2);
        int record = 0;//record1用于判断要不要输出目前的购物车
        while(ss >> input2 && input2 != "exit" && input2 != "quit"){//若exit在末尾，也会执行前面的内容（按顺序读取）
            //Checkout(input2, date, num);   
            if(!DuplicateCheck(input2, "barcode")){//输入的是条形码
                bool StockCheck = true;
                for(auto& product : products){
                    if(input2 == product.barcode){
                        if(product.stock == 0){
                            StockCheck = false;
                        }
                    }
                }
                if(StockCheck){
                    for(auto& product : products){
                        if(input2 == product.barcode){
                            product.stock--;
                            product.quantity++;
                        }
                    }
                    record = 1;
                }else{
                    cout << "Error 3: Insufficient stock for item with barcode " << input2 << endl;
                    //cout << "Please continue entering." << endl;
                }
            }else if(input2[0] == '-'){
                input2 = input2.substr(1);//去掉负号(截取负号后面的部分)
                if(!DuplicateCheck(input2, "barcode")){
                    bool QuantityCheck = true;
                    for(auto& product : products){
                        if(input2 == product.barcode){
                            if(product.quantity == 0){
                                QuantityCheck = false;
                            }
                        }
                    }
                    if(QuantityCheck){
                        for(auto& product : products){
                            if(input2 == product.barcode){
                                product.stock++;
                                product.quantity--;
                            }
                        }
                        record = 1;
                    }else{
                        cout << "Error 30: No " << input2 << " in cart " << endl;
                    }
                }else{
                    cout << "Error 31: Barcode does not exist" << endl;
                }
            }
            else if(input2 == "print"){
                record = 0;//处理同时输入条形码和"checkout"的情况
                bool checkEmpty1 = true;
                double total = 0;
                cout << "===== Current Order =====:" << endl;
                for(Product& product : products){
                    if(product.quantity > 0){
                        cout << product.name << " " << product.price << "*" << product.quantity << "=" << product.price * product.quantity << endl;
                        total += product.price * product.quantity;
                        checkEmpty1 = false;
                    }
                }
                if(checkEmpty1){
                    cout << "Cart is empty." << endl;
                }else{
                    cout << "Total: " << total << endl;
                }
            }
            else if(input2 == "drop"){
                record = 0;//处理同时输入条形码和"drop"的情况
                for(Product& product : products){
                    product.stock+=product.quantity;
                    product.quantity = 0;
                }
                cout << "Cart Cleared." << endl;
            }
            else if(input2 == "checkout"){
                record = 0;//处理同时输入条形码和"checkout"的情况
                bool checkEmpty2 = true;
                double total = 0;
                cout << "====== Final Receipt ======:" << endl;
                for(Product& product : products){
                    if(product.quantity > 0){
                        cout << product.name << " " << product.price << "*" << product.quantity << "=" << product.price * product.quantity << endl;
                        total += product.price * product.quantity;
                        checkEmpty2 = false;
                    }
                }
                if(checkEmpty2){
                    cout << "Cart is empty." << endl;
                }else{
                    cout << "Total: " << total << endl;
                    Record(date, num, products, total); //注意：若销售记录没有成功保存 但购物车仍然会被清空 且库存已经在加入购物车的时候减少（运行逻辑）
                    for(Product& product : products){
                        product.quantity = 0;
                    }
                }
                cout << "Continue, or enter 'exit' or 'quit' to quit." << endl;
            }
            else{
                cout << "Error 2: " << input2 << " is invalid input." << endl;
            }
        }
        //一排输入接受完毕后的再处理和输出

        if(record == 1){
            cout << "----- Current Cart -----:" << endl;
            bool checkEmpty2 = true;
            for(Product& product : products){
                if(product.quantity > 0){
                    cout << product.name << " " << product.price << "*" << product.quantity << "=" << product.price * product.quantity << endl;
                    checkEmpty2 = false;
                }
            }
            if(checkEmpty2){
                cout << "Cart is empty." << endl;
            }   
        }

        if(input2 == "quit" || input2 == "exit"){
            break;
        }
    }
    RecreateProduct(products);//回填信息   
    ReturnMenu();
};

/*bool StockCheck(const string& barcode, vector<Product>& products){此函数内容与其他部分重合度太高，所以干脆不拆成函数了
    //vector<Product> products = CreateProduct("product.csv");不能重新生成，不然数据未更新
    for(auto& product : products){
        if(barcode == product.barcode){
            if(product.stock == 0){
                return false;
            }
        }
    }
    return true;
}
    */

/*void Checkout(string input2, int date, int& num){
    vector<Product> products = CreateProduct("product.csv");
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
        Record(date, num, products, total); 
        for(Product& product : products){
            product.quantity = 0;
        }
        cout << "Enter 'exit' or 'quit' to quit." << endl;
    }else{
        cout << "Error 2:Invalid input" << endl; 
    }
}
*/