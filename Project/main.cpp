#include<iostream>
#include "product.h"
#include<vector>
#include "menu.h"
#include<string>
using namespace std;

int main(){
    vector<Product> products = CreateProduct("product.csv");
    int input1;
    do{
        ShowMenu();
        if (!(cin >> input1)) {//尝试把用户输入读进 input1，如果失败，就进入 if。
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();              // 清除 cin 的错误状态
            cin.ignore(10000, '\n');  // 丢掉这一行错误输入,此行代码的意思是：从输入缓冲区里丢弃（忽略）最多 10000 个字符，或者直到遇到换行符 \n 为止（换行符也会被丢弃）。
            continue;
          }
        switch(input1){
            case 0:{
                cout << "Exiting the program." << endl;
                return 0;
            }
            case 1:{
                Case1();
                break;
            }
            case 2:{
                Case2(products);
                break;
           }
           default:
                cout << "Invalid input" << endl;
            }
    }while(1);
    return 0;
}
   