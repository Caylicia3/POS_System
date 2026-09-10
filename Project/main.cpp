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
    cin>>input1;
    switch(input1){
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
    }while(input1 != 0);
    cout << "Exiting the program." << endl;
    return 0;
}
   