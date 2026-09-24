#include <iostream>
#include <fstream>
#include <thread> 
#include <chrono>//读取系统时间
#include <ctime>//读取系统时间
#include "menu.h"
#include <iomanip>//输入输出格式控制，用于系统时间显示格式
#include "product.h"
#include <vector>
#include <string>
#include "sale.h"
#include <sstream>
#include "admin.h"

using namespace std;

void Record(int date,int& num,const vector<Product>& products,double total){//销售记录
    ofstream file("sale.csv",ios::app);
    if (!file.is_open()) {
    cout << "Error 4: Record Failed" << endl;
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
    file << "," << put_time(localtime(&currentTime), "%H:%M:%S") << ",";//写入数据（格式）
    //记录商品明细
    for(const Product& product : products){
        if(product.quantity > 0){
            file << "  " << product.name << " " << product.price << "*" << product.quantity << "=" << product.price * product.quantity;
        }
    }
    //记录总金额
    file << "," << total << endl;//注意！要换行

    file.close();
}

int GetTodayNum(int date){
    ifstream file("sale.csv");
    int max_num = 0;
    string all_date;//std::getline 的第二个参数必须是 std::string 类型，不能是 int。
    string num;
    string line;
    getline(file, line);// 跳过第一行表头
    while(getline(file,line)){
        stringstream ss(line);
        getline(ss,all_date,',');
        getline(ss,num,',');
        if (date == stoi(all_date))
        {
            if (stoi(num) > max_num)
            {
                max_num = stoi(num);
            }
        }
    }
    return max_num+1;
}

void Case3(int& date,int& num){
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
    /*date++;
    num = GetTodayNum(date);
    cout << "Today is : Day" << date << endl;
    */
    cout << "Enter 'newday' to start a new day (Date+1)" << endl;
    cout << "Enter 'exit' or 'quit' to quit." << endl;
    string input;
    while(cin >> input && input != "quit" && input != "exit"){
        if(input == "newday"){
            date++;
            num = GetTodayNum(date);
            cout << "Today is : Day" << date << endl;
            cout << "Refreshing in 2 seconds..." <<endl;
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
        else{
            cout << "Error 7:Invalid Input.Try again or you can quit." << endl;
        }
    }
    ReturnMenu();
}

int GetToday(){
    ifstream file("sale.csv");
    int max_date = 1;
    string date;//std::getline 的第二个参数必须是 std::string 类型，不能是 int。
    string line;
    getline(file, line);// 跳过第一行表头
    while(getline(file,line)){
        stringstream ss(line);
        getline(ss,date,',');
        if (stoi(date) > max_date)
            {
                max_date = stoi(date);
            }
        }
    return max_date;
}

void Case4(const int day){//注意：该函数内的date和day和函数外的略有区别，因为变量太多不好命名
    cout << "View All Sales Records and Total Revenue" << endl;
    //Sales Records
    //Total Sales
    cout << "Enter 'sales[day]' to view sales records for selected day and total revenue (eg.'sales 1')" << endl;
    cout << "If the day parameter is omitted, it defaults to today." << endl;
    cout << "Enter 'exit' or 'quit' to quit." << endl;
    cout << "Enter 'all' to display all records." << endl;
    string input;
    while(getline(cin, input) && input != "exit" && input != "quit"){
        if(input.size()>=5 && input.substr(0,5)=="sales"){//注意越界风险，input长度可能小5
            if(input.size()==5){
                ifstream file("sale.csv");
                string date;
                getline(file,date);
                cout << "Day: " << day << endl;
                cout << "------------------------" << endl;
                double daily_sale = 0;
                while(getline(file,date)){
                    if(date.empty()){//加入空行检测，避免因为手动修改文件导致的空行影响程序正常运行
                        continue;
                    }
                    string  No, Time, Items, Ament;//把 No, Time, Items, Amcnt 都定义在 while (getline(...)) 循环里面，每次读取新行时它们都是全新的，不会被旧数据污染。
                    stringstream ss(date);
                    getline(ss,date,',');//这会消耗 ss 中已经读过的部分
                    getline(ss,No,',');
                    getline(ss,Time,',');
                    getline(ss,Items,',');
                    ss >> Ament;
                    if(stoi(date) == day){
                        cout << "No." << No << " Time:" << Time << " Items:" << Items << " Ament:" << Ament << endl;
                        daily_sale+=stod(Ament);
                    }
                }
                cout << "------------------------" << endl;
                cout << "Daily: " << daily_sale << endl;
                file.close();
            }else{
                input.erase(0,5);
                if(input[0] == ' '){
                    input.erase(0,1);
                    if(input.empty()){
                        cout << "Error 9:Invalid input" << endl;
                    }else{
                        int tmp;
                        if(NumCheck(input)){
                            tmp = stoi(input);//为避免直接修改day,引入变量tmp
                            ifstream file("sale.csv");
                            string date, No, Time, Items, Ament;
                            getline(file,date);
                            cout << "Day: " << tmp << endl;
                            cout << "------------------------" << endl;
                            double daily_sale = 0;
                            while(getline(file,date)){
                                stringstream ss(date);
                                getline(ss,date,',');//这会消耗 ss 中已经读过的部分
                                getline(ss,No,',');
                                getline(ss,Time,',');
                                getline(ss,Items,',');
                                ss >> Ament;
                                if(stoi(date) == tmp){
                                    cout << "No." << No << " Time:" << Time << " Items:" << Items << " Ament:" << Ament << endl;
                                    daily_sale+=stod(Ament);
                                }
                            }
                            cout << "------------------------" << endl;
                            cout << "Daily: " << daily_sale << endl;
                        }else{
                            cout << "Error 35:Invalid input" << endl;
                        }

                    }
                }else{
                    cout << "Error 6:Invalid input" << endl;
                }
            }
        }
        else if(input == "all"){
            ifstream file("sale.csv");
            string date1, date2 = " ", No, Time, Items, Ament;//date1是该行的date,date2是用来判断是否是同一天的（date2为上一个date的值）
            getline(file, date1);//除表头
            double daily_sale = 0;
            if(file.peek() == EOF){//看看文件当前位置后面还有没有东西。
                cout << "No history found." << endl;
            }
            else{
                while(getline(file, date1)){
                    stringstream ss(date1);
                    getline(ss,date1,',');//这会消耗 ss 中已经读过的部分
                    getline(ss,No,',');
                    getline(ss,Time,',');
                    getline(ss,Items,',');
                    ss >> Ament;
                    if(date1 != date2){
                        if(date2 != " "){//避免最开始就打印结算部分
                            cout << "------------------------" << endl;
                            cout << "Daily: " << daily_sale << endl << endl;
                            daily_sale = 0;
                        }
                        cout << "Day: " << date1 << endl;
                        cout << "------------------------" << endl;
                    }//注意：total应该在每一天的末尾，也就是第二天的前面。
                    cout << "No." << No << " Time:" << Time << " Items:" << Items << " Ament:" << Ament << endl;
                    daily_sale+=stod(Ament);//string to double
                    date2 = date1;
                }
                if(date2 != " "){//注意：最后一次的结算还未打印循环就结束了
                    cout << "------------------------" << endl;
                    cout << "Daily: " << daily_sale << endl;
                }
                file.close();
            }
        }else{
            cout << "Error 5:Invalid input" << endl;
        }
    }
    ReturnMenu();
}

void Case5(){
    cout << "Are you sure you want to clear all history? This action cannot be undone." << endl;
    cout << "Press 1 to confirm clearing all history. Type 'quit' or 'exit' to cancel. " << endl;
    string input;
    while(cin >> input && input != "quit" && input != "exit"){
        if(input == "1"){
            ofstream file("sale.csv");
            file << "Date,number_of_sales/num,system_time,Receipt Items,total_sales_amount" << endl;
            file.close();
            cout << "Operation Successful!" << endl;
            break;
        }
        else{
            cout << "Error 8:Invalid input" << endl;
        }
    }
    ReturnMenu();
}

bool VIPcheck(){
    cout << "Are you a member of this store? Enter 1 if yes, 0 if no." << endl;
    string VIP;
    while(cin >> VIP){
        if(VIP == "1"){
            Redirect();
            return true;
        }
        else if(VIP == "0"){
            Redirect();
            return false;
        }
        else{
            cout << "Error 32 : Invalid Input.Please enter '1' or '0'." << endl;
        }
    }
    cout << "Error 33: Input Error" << endl;
    return false;
}

void Case7(){
    cout << "===== Sales Report =====" << endl;
    ifstream file("sale.csv");
    if (!file) {
        cout << "Failed to open sale.csv." << endl;
        return;
    }
    AmountReport(file);
    cout << "Enter 'quit' or 'exit' to quit." << endl;
    string input;
    while(cin >> input && input != "quit" && input != "exit"){
        cout << "Error 34: Invalid Input." << endl;
    }
    ReturnMenu();
}

void AmountReport(ifstream& file){//Date,number_of_sales/num,system_time,Receipt Items,total_sales_amount
    string line, date, num, time, item;//注意：这里day和date含义相同，用day表示int类型，用date表示string类型
    double total_amount = 0, daily_amount = 0, amount = 0, tmp2 = 0;//注意tmp2的数据类型
    int day, cnt = 0, tmp1 = 0;//cnt用来记录day的变化，tmp1用来记录单日营业额最高的天数，tmp2用来记录单日最高营业额。
    bool isEmpty = true;//检查是否有销售记录
    getline(file, line);//去掉表头
    while(getline(file, line)){
        isEmpty = false;
        stringstream ss(line);
        getline(ss, date, ',');
        getline(ss, num, ',');
        getline(ss, time, ',');
        getline(ss, item, ',');
        ss >> amount;
        day = stoi(date);
        if(cnt == day){
            daily_amount += amount;
        }
        if(cnt < day){//比较大小要用int类型，不能用stirng,因为string比较的是字典序，不是数值大小。//Record() 按销售发生时间追加,天数只能增加不能减少，所以sale.csv里的销售记录一定按照日期递增排列
            if(cnt != 0){
                cout << "Day: " << cnt << "     Daily Amount: " << daily_amount << endl;
                if(daily_amount > tmp2){//这里就没有又把每日数据单独写进csv文件了，所以没有又用csv读取
                    tmp1 = cnt;//bug:这里误写成day,但是day已经是下一天了
                    tmp2 = daily_amount;
                }
                //total_amount += daily_amount;为避免最后出现如果最后一天有两个及以上订单和只有一个订单时最后的total_amount添加daily_amount的逻辑不一样，这里统一用amount去算total_amount。因为如果最后一天只有一单，那么循环结束后total_amount还需要再加一次daily_amount；但如果不是，就不需要再加。
                daily_amount = amount;
            }
            cnt = day;
        }//因为本项目里天数只能增加，不可能减少，所以没有cnt > day的情况
        total_amount += amount;
    }
    cout << "Day: " << cnt << "     Daily Amount: " << daily_amount << endl;//如果不加的话，最后一天就不会输出这句（循环一定要注意初始和结束这两个地方）
    if(daily_amount > tmp2){
        tmp1 = cnt;
        tmp2 = daily_amount;
    }//bug:最后一天没有参与最高销售比较
    if(isEmpty){//也可以不引入bool类型，直接用cnt==0来判断。此处为加强代码可读性所以没这么写
        cout << "No sales records found." << endl;
    }
    else{
        cout << "Total Amount: " << total_amount << endl;
        cout << "Day with Highest Daily Sales: " << tmp1 << endl;
        cout << "Sales on That Day: " << tmp2 << endl;
    }
}