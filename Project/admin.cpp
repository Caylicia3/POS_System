#include <iostream>
#include <fstream>
#include "menu.h"
//#include <sstream>

using namespace std;

void Case6(){
    cout << "  Enter admin password to enter administrator mode." << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Password:" << endl;
    if(VerifyPassword()){
        Redirect();
        AdminMenu();
        ReturnMenu();
    }
    else{
    ReturnMenu();
    }
}

bool VerifyPassword(){//添加实时显示密码的功能？
    cout << "Enter 'exit' or 'quit' to quit." << endl;
    int chance = 3;
    string password, line;
    ifstream file("password.csv");
    getline(file,password);
    /*while(getline(cin, password) && password != "quit" && password != "exit"){
        if(password == line){
            file.close();
            return true;
        }
        else{
            cout << "Please enter the correct password." << endl;
            cout << "Entry cleared.Try again." << endl;//清空输入
        }
    };
    */
    for(int i = chance; i>0; i--){
        cout << "You have " << i << " chances." << endl;
        getline(cin, line);
        if(line == password){
            file.close();
            return true;
        }else if(line == "exit" || line == "quit"){
            break;
        }else{
            cout << "Please enter the correct password." << endl;
            cout << "Entry cleared.Try again." << endl;//清空输入
        }
    }
    file.close();
    return false;
}

void AdminMenu(){//const int& date, const int& num
    string input;
    while(true){
        cout << "Running as administrator :" << endl;
        ifstream file("password.csv");//验证是否为初始密码
        string line;
        getline(file,line);//line为当前存储的密码
        if(line == "admin123"){
            cout << "Current: Default password" << endl;
        }
        file.close();
        cout << "---------------------------------------------------------" << endl;
        cout << "Enter 'back' to exit Admin & return to Cashier." << endl;
        cout << "Enter '1' to change password." << endl;
        cout << "Enter '2' to " << endl;
        cin >> input;//记得检查第一次是不是"back“//检查非法输入
            if(input == "back"){
                break;
            }
            else if(input == "1"){
                Redirect();
                AdminCase1();//尽量不要嵌套递归函数(AdminMenu里套AdminMenu，而采用while循环持续等待管理员输入。)
            }
            else if(input == "2"){

            }
        }
    }

void AdminCase1(){
    cout << "Re-enter password for verification." << endl;
    if(VerifyPassword()){
        /*
        ifstream oldfile("password.csv");//储存原密码line//注意：两次操作(if/of)的file名称需要不同!一个是读取，一个是写入。file.close() 后，file 变量没有消失。
        string line;
        getline(oldfile,line);
        oldfile.close();
        修改逻辑后无需再单独储存旧密码
        */
        cout << "Please enter a new password." << endl;
        string input1, input2;
        getline(cin,input1);
        cout << "Re-enter password to confirm:" << endl;
        if(getline(cin, input2) && input2 == input1){//再次确认密码//原来是在这个if之前打开"pass.csv"文件，但是ofstream newfile("password.csv");默认模式是：ios::out 它会打开文件并且截断(truncate)原文件。只要打开，原密码就已经没了。
            cout << "Password changed successfully." << endl;
            ofstream newfile("password.csv");//如果 password.csv 不存在，ofstream 会自动帮你创建这个文件。如果存在，默认情况下它会清空（覆盖）原有内容（这也是为什么在需要追加内容时需要配合 ios::app 使用）。
            if (!newfile.is_open()) {
                cout << "Error 10:Failed to open file 'admin.csv'." << endl;
                return;
            }
            newfile << input1;
            newfile.close();
            Redirect();
        }
        else{
            cout << "Password change failed." << endl;
            Redirect();
        }
    }
}