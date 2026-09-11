#include <iostream>
#include "product.h"
#include <vector>
#include "menu.h"
#include <string>
#include <thread> // 暂停时间
#include <chrono> // 暂停时间
#include "sale.h"

using namespace std;

int main(){
    vector<Product> products = CreateProduct("product.csv");
    int input1 , date = 1 , num = 1;
    do{
        ShowMenu(date,num);
        if (!(cin >> input1)) {//尝试把用户输入读进 input1，如果失败，就进入 if。
            cout << "Invalid input. Please enter a number.Continuing in 5 seconds." << endl;
            cin.clear();              // 清除 cin 的错误状态
            cin.ignore(10000, '\n');  // 丢掉这一行错误输入,此行代码的意思是：从输入缓冲区里丢弃（忽略）最多 10000 个字符，或者直到遇到换行符 \n 为止（换行符也会被丢弃）。
            this_thread::sleep_for(chrono::seconds(5));
            clearScreen();
            continue;
          }
        switch(input1){
            case 0:{
                cout << "Exiting in 5 seconds." << endl;
                this_thread::sleep_for(chrono::seconds(5));
                clearScreen();
                return 0;
            }
            case 1:{
                Case1();
                break;
            }
            case 2:{
                cout << "Redirecting in 2 seconds..." <<endl;
                this_thread::sleep_for(chrono::seconds(2));
                clearScreen();
                Case2(products,date,num);
                break;
           }
           case 3:{
                Case3(date);
                break;
           }
           default:
                cout << "Error 1:Invalid input" << endl;
            }
    }while(1);
    return 0;
}
   