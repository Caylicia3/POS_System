#include <iostream>
#include <fstream>
#include "menu.h"
#include "product.h"
#include <cctype>
#include <string>
#include "admin.h"
//#include <sstream>

using namespace std;

void Case6(){
    cin.ignore(1000,'\n');
    cout << "  Enter admin password to enter administrator mode." << endl;
    cout << "          Enter 'exit' or 'quit' to quit." << endl;
    cout << "---------------------------------------------------------" << endl;
    //cout << "Password:" << endl;
    if(VerifyPassword()){
        cout << "Correct!" << endl;
        Redirect();
        AdminMenu();
        ReturnMenu();
    }
    else{
    ReturnMenu();
    }
}

bool VerifyPassword(){//添加实时显示密码的功能？
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
        cout << "-------------------------------------------------------------------------" << endl;
        cout << " Enter 'back' to exit Admin & return to Cashier." << endl;
        cout << " Enter 'admin' to change password." << endl;//AdminCase1
        cout << " Enter 'setprice' to change item price." << endl;
        cout << " Enter 'itemadd' to add new products." << endl;
        cout << " Enter 'itemdel' to delete products." << endl;
        cout << " Enter 'restock' to add stock to the specified product." << endl;
        cout << " Enter 'setstock' to directly set product stock (Stocktake Correction)." << endl;
        cout << " Enter 'prices' to view all products (with stock)." << endl;
        cin >> input;//记得检查第一次是不是"back“//检查非法输入
        cin.ignore(1000,'\n');
            if(input == "back"){
                break;
            }else if(input == "admin"){
                Redirect();
                AdminCase1();//尽量不要嵌套递归函数(AdminMenu里套AdminMenu，而采用while循环持续等待管理员输入。)
            }else if(input == "setprice"){
                Redirect();
                AdminCase2();
            }else if(input == "itemadd"){
                Redirect();
                AdminCase3();
            }else if(input == "itemdel"){
                Redirect();
                AdminCase4();
            }else if(input == "restock"){
                Redirect();
                AdminCase5();
            }else if(input == "setstock"){
                Redirect();
                AdminCase6();
            }else if(input == "prices"){
                Redirect();
                AdminCase7();
            }else{
                cout << "Error 15:Invalid input. Please Try Again." << endl;
                Refresh();
            }
        }
    }

void AdminCase1(){
    cout << "Re-enter Password For Verification." << endl;
    if(VerifyPassword()){
        /*
        ifstream oldfile("password.csv");//储存原密码line//注意：两次操作(if/of)的file名称需要不同!一个是读取，一个是写入。file.close() 后，file 变量没有消失。
        string line;
        getline(oldfile,line);
        oldfile.close();
        修改逻辑后无需再单独储存旧密码
        */
        cout << "Please Enter a New Password." << endl;//现阶段认为"back"可以是密码
        string input1, input2;
        //getline(cin,input1);//坑：如果VerifyPassword() 里面使用：cin >> password;那么直接：getline(cin,input1);会吃掉换行。此处不用getline原因：可能会产生密码为空格的情况
        cin >> input1;// \n不会成为密码
        if(!PasswordDuplicateCheck(input1)){
            cout << "New Password Cannot Be the Same As the Old One." << endl;
        }else{
            cout << "Re-enter password to confirm:" << endl;
            cin.ignore(1000,'\n');
            if(getline(cin, input2) && input2 == input1){//再次确认密码//原来是在这个if之前打开"pass.csv"文件，但是ofstream newfile("password.csv");默认模式是：ios::out 它会打开文件并且截断(truncate)原文件。只要打开，原密码就已经没了。
                ofstream newfile("password.csv");//如果 password.csv 不存在，ofstream 会自动帮你创建这个文件。如果存在，默认情况下它会清空（覆盖）原有内容（这也是为什么在需要追加内容时需要配合 ios::app 使用）。
                if (!newfile.is_open()) {
                    cout << "Error 10:Failed to open file 'password.csv'." << endl;
                    Redirect();
                    return;
                }
                newfile << input1;
                newfile.close();
                cout << "Password changed successfully." << endl;
            }else{
                cout << "Password Change Failed." << endl;
            }
        }
    }
    else{
        cout << "Password Is Incorrect." << endl;
    }
    Redirect();
}

void AdminCase2(){//setprice
    string input;
    cout << "Enter Product Barcode to Change Price (eg.001) (Numbers only)."<< endl;
    cout << "Enter 'back' to Return." << endl;
    vector<Product> products = CreateProduct("product.csv");//想要检验并找到条形码对应的商品，直接用之前写的函数，不再手写代码去从.csv文件里找 //注意：这部分本来在循环内，但是建议改到循环外，避免程序重复
    while(cin >> input && input != "back"){
        if(NumCheck(input)){//检查是否是数字
            cout << "The Barcode Is : " << input << endl;
            bool judge = false;//判断是否找到条形码
            for(const auto& product : products){
                if(product.barcode == input){
                    cout << "Product Name: " << product.name << endl;
                    cout << "Barcode: " << product.barcode << endl;
                    cout << "OldPrice: " << product.price << endl;
                    judge = true;
                    break;//可以提前结束循环，因为条形码唯一
                }
            }
            if(!judge){
                cout << "Error 11:Cant't Find the Product!" << endl;
            }
            else{//找到商品了
                string New;
                cout << "Please Enter the New Price." << endl;
                cout << "Note : Commas(',') Are Not Allowed.Numbers Only." << endl;
                while(cin >> New && New != "back"){//不会输入空白
                    if(New.find(',') == string::npos){//未发现逗号
                        if(PriceCheck(New)){//检测价格是否合理
                            for(auto& product : products){
                                if(product.barcode == input){
                                    product.price = stod(New);//注意：类型转换——price是double  New是string  PriceCheck函数并未改变New的类型
                                    break;
                                }
                            }
                            RecreateProduct(products);//把更改后的商品信息填回去
                            cout << "Product Price Updated Successfully." << endl;
                            Redirect();
                            cout << "Enter Barcode to Continue Editing (Numbers only)." << endl;
                            cout << "Enter 'back' to Return." << endl;
                            break;
                            }else{
                                cout << "Error 14: Price Must Be a Number! Enter price again." << endl;
                        }
                    }
                    else{
                        cout << "Error 13 : Commas(',') are not allowed! Enter price again." << endl;
                    }
                }
                break;
            }
        }
        else{
            cout << "Error 18:Invalid input!" << endl; 
            cout << "Try Again." << endl;
        }
    }
    Redirect();
}

bool NumCheck(string input){//检验数字（不可以包含小数点，0-9的数字——不包含负数）//负数return false;
    if(input.empty())
        return false;
    for(char c : input){
        if(!isdigit(c))
            return false;
    }
    return true;
}

void RecreateProduct(const vector<Product>& products){//回填商品信息
    ofstream file("product.csv");
    file << "name,barcode,price,stock\n";//不要忘记写表头
    for(const Product& product : products){
        file << product.name << "," << product.barcode << "," << product.price << "," << product.stock << endl;
    }
}

bool PriceCheck(string input){//检验数字（含小数）
    try{
        size_t pos;
        stod(input, &pos);
        return pos == input.size();
    }
    catch(...){
        return false;
    }
}

void AdminCase3(){
    cout << "Only One Item Can Be Added At a Time." << endl;
    cout << "Enter the Barcode of the New Product.Numbers Only.(eg.001)" << endl;
    cout << "Enter 'back' to Exit." << endl;
    Check();
    Redirect();
}

bool DuplicateCheck(const string& add, const string& data_member){//条形码和名称都需要查重//注意：使用时data_member只能是name或barcode
    vector<Product> products = CreateProduct("product.csv");
    for(const Product& product : products){
        //if(product.data_member == add);不能这样写，因为Product没有data_member这个成员
        if(data_member == "barcode" && product.barcode == add){
            return false;//发现重复返回false
        }else if(data_member == "name" && product.name == add){
            return false;
        }
    }
    return true;//未发现重复返回true
}

void Check(){//单独写一个Check()让逻辑更清晰
    BarcodeCheck();
}

void BarcodeCheck(){
    string Barcode;
    while(cin >> Barcode && Barcode != "back"){
        if(NumCheck(Barcode)){
            if(DuplicateCheck(Barcode, "barcode")){
                cout << "Valid Input "<< endl;
                NameCheck(Barcode);
                break;
            }else{
                cout << "Error 17: Barcode Already Exists.Please Try Again.";
            }
        }else{
            cout << "Error 16: Numbers Only!" << endl;
        }
    }
    return;
}

void NameCheck(const string& Barcode){
    cout << "Enter the Name of the New Product.No Spaces Or Commas Allowed." << endl;
    cout << "Enter 'back' to Exit." << endl;
    string Name;
    while(cin >> Name && Name != "back"){
        if(Name.find(',') == string::npos){//逗号检测，比较简单就没写成函数
            if(DuplicateCheck(Name, "name")){
                cout << "Valid Input "<< endl;
                NewPriceCheck(Barcode, Name);
                break;
            }else{
                cout << "Error 20: Name Already Exists.Please Try Again.";
            }
        }else{
            cout << "Error 19 : Commas(',') Are Not Allowed.Numbers Only." << endl;
            cout << "Enter 'back' to Exit,or enter name again" << endl;
        }
    }
    return;
}

void NewPriceCheck(const string& Barcode, const string& Name){
    cout << "Enter the Price of the New Product.Numbers Only(eg.3.50)." << endl;
    cout << "Enter 'back' to Exit." << endl;
    string Price;
    while(cin >> Price && Price != "back"){
        if(PriceCheck(Price)){
            cout << "Valid Input "<< endl;
            StockCheck(Barcode, Name, Price);
            break;
        }else{
            cout << "Error 21:Invalid input!Numbers Only(eg.3.50)." << endl;
            cout << "Please Try Again." << endl;
            cout << "Enter 'back' to Exit." << endl;
        }   
    }
    return;
}

void StockCheck(const string& Barcode, const string& Name, const string& Price){
    cout << "Enter the Stock of the New Product.Numbers Only(eg.10)." << endl;
    cout << "or You Can Enter 'back' to Exit." << endl;
    string Stock;
    while(cin >> Stock && Stock != "back"){
        if(NumCheck(Stock)){
            cout << "Valid Input "<< endl;
            cout << "The New Product :" << endl;
            cout << "name :" << Name << "  " << "barcode:" << Barcode << "  " << "price:" << Price << "  " << "stock:" << Stock << endl;
            ofstream file("product.csv",ios::app);
            if (!file.is_open()) {
            cout << "Error 22: Record Failed" << endl;
            break;
            }
            file << Name << ',' << Barcode << ',' << Price << ',' << Stock << '\n';//注意，在CreateProduct函数里有类型转换，所以填入的可以都用string类型
            break;
        }else{
            cout << "Error 23:Invalid input." << endl;
            cout << "Please Try Again." << endl;
            cout << "or You Can Enter 'back' to Exit." << endl;
        }
    }
    return;
}

void AdminCase4(){
    cout << "Enter 'back' to Exit." << endl;
    cout << "Enter Barcode to Delete a Product." << endl;
    string Barcode;
    while(cin >> Barcode && Barcode != "back"){
        vector<Product> products = CreateProduct("product.csv");
        bool Valid = false;
        for(const auto& product : products){//无需检验是不是数字，因为如果不是数字根本不会匹配得上
            if(product.barcode == Barcode){
                Valid = true;
            }
        }
        if(Valid){
            ofstream file("product.csv");
            file << "name" << ',' << "barcode" << ',' << "price" << ',' << "stock" << endl;
            for(const auto& product : products){//
                if(product.barcode != Barcode){
                    file << product.name << ',' << product.barcode << ',' << product.price << ',' << product.stock << endl;
                }
            }
            cout << "Product Deleted Successfully." << endl;
            cout << "Enter 'back' to Exit, or Enter Barcode to Delete a Product." << endl << endl;
        }else{
            cout << "Error 15:Invalid input. Product Not Found.Please Try Again." << endl;
            cout << endl;
        }
    }
    Redirect();
}

bool PasswordDuplicateCheck(const string& input){
    ifstream oldfile("password.csv");//储存原密码line //新增检验：密码查重
    string line;
    getline(oldfile,line);
    oldfile.close();
    if(input == line){
        return false;
    }
    return true;
}

void AdminCase5(){//双层while嵌套，依次检验两次输入
    cout << "Enter the barcode of the product you want to restock." << endl;
    cout << "Enter 'back' to exit." << endl;
    string input;
    while(cin >> input && input != "back"){
        if(!DuplicateCheck(input, "barcode")){
            cout << "Enter quantity to restock:" << endl;
            cout << "Enter 'back' to exit." << endl;
            string num;//restock
            while(cin >> num && num != "back"){
                if(NumCheck(num)){
                    vector<Product> products = CreateProduct("product.csv");
                    for(auto& product : products){//必须加&，不然只改变了复制出的副本，没有改变实际的值
                        if(product.barcode == input){
                            int add = stoi(num);//类型转换！总是写错变量：是num 不是input!
                            product.stock += add;
                            cout << "The stock of " << product.name << " is " << product.stock << " now." << endl;
                            break;//及时break,跳出循环
                        }
                    }
                    RecreateProduct(products);
                    break;
                }else{
                    cout << "Error 25: Numbers Only.Negative quantities are not allowed." << endl;
                    cout << "Try Again or Enter 'back' to Exit." << endl;
                }
            }
            break;   
        }else{
            cout << "Error 24: Invalid Barcode. Product Not Found.You can try again or exit." << endl;
            cout << "Enter 'back' to exit." << endl;
        }
    }
    Redirect();
}

void AdminCase6(){
    cout << "Enter the Barcode to Set Product Stock (Stocktake Correction)." << endl;
    cout << "Enter 'back' to exit." << endl;
    string input;
    while(cin >> input && input != "back"){
        if(!DuplicateCheck(input, "barcode")){
            cout << "Enter the updated stock quantity for this product:" << endl;
            cout << "Enter 'back' to exit." << endl;
            string num;//update
            while(cin >> num && num != "back"){
                if(NumCheck(num)){
                    vector<Product> products = CreateProduct("product.csv");
                    for(auto& product : products){
                        if(product.barcode == input){
                            int add = stoi(num);//注意：类型转换
                            product.stock = add;
                            cout << "The stock of " << product.name << " is " << product.stock << " now." << endl;
                            break;
                        }
                    }
                    RecreateProduct(products);
                    break;
                }else{
                    cout << "Error 27: Numbers Only.Negative quantities are not allowed." << endl;
                    cout << "Try Again or Enter 'back' to Exit." << endl;
                }
            }
            break;   
        }else{
            cout << "Error 26: Invalid Barcode. Product Not Found.You can try again or enter 'back' to exit." << endl;
        }
    }
    Redirect();
}

void AdminCase7(){
    vector<Product> products = CreateProduct("product.csv");
    for(const Product& product : products){
        cout << "Name:" << product.name << "  " << "Barcode:" << product.barcode << "  " <<  "Price:" << product.price << "  " << "Stock:" << product.stock << endl;
    }
    cout << "-----------------------------------------------" << endl;
    cout << " Enter 'back' to exit." << endl;
    string input;
    while(cin >> input && input != "back"){//本来想实现“按任意键继续”功能，但是比较简单的写法会用到_getch()(无法跨平台使用的函数)，所以没有实现这个功能
        cout << "Error 28: Invalid Input" << endl;
    }
    Redirect();
}