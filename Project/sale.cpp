#include <iostream>
#include <fstream>
#include <thread> 
#include <chrono>//读取系统时间
#include <ctime>//读取系统时间
#include "menu.h"
#include <iomanip>//输入输出格式控制，用于系统时间显示格式
#include "product.h"
#include <vector>
using namespace std;

void Record(int date,int& num,const vector<Product>& products,double total){
    ofstream file("sale.csv",ios::app);
    if (!file.is_open()) {
    cout << "Error:Record failed" << endl;
    return;
    }
    //记录day
    file << date;
    //记录流水号
    file << "," << num;
    num++;
    //记录当下时间
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    file << "," << put_time(localtime(&currentTime), "%H:%M:%S");//写入数据
    //记录商品明细
    for(const Product& product : products){
        if(product.quantity > 0){
            file << "," << product.name << " " << product.price << "*" << product.quantity << "=" << product.price * product.quantity;
        }
    }
    //记录总金额
    file << "," << total << endl;

    file.close();
}

void Case3(int& date){
    /*cout << "Please enter the new day number: " << endl;
    if (!(cin >> day)) {
        cout << "Invalid input. Please enter a number.Continuing in 5 seconds." << endl;
        cin.clear();              // 清除 cin 的错误状态
        cin.ignore(10000, '\n');  // 丢掉这一行错误输入
        this_thread::sleep_for(chrono::seconds(5));
        clearScreen();
        return;
    }
    cout << "Day changed to: " << day << endl;
    cout << "Continue in 5 seconds." << endl;
    this_thread::sleep_for(chrono::seconds(5));
    clearScreen();
    */
    date++;
    cout << "Today is : Day" << date << endl;
    cout << "Refreshing in 2 seconds..." <<endl;
    this_thread::sleep_for(chrono::seconds(2));
    clearScreen();
}