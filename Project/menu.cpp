#include <iostream>
#include <thread> 
#include <chrono>
using namespace std;

void ShowMenu(int date,int num){
    cout << "==============================================================" << endl;
    cout << "7-Eleven Convenience Store POS Command-Line Interactive System" << endl;
    cout << "==============================================================" << endl;
    cout << "Day:" << date << "---" << "Current Receipt Number" << num << endl << endl;
    cout << "Exit the Menu -- Please Enter 0" << endl;
    cout << "Show Product Information -- Please Enter 1" << endl;
    cout << "Checkout -- Please enter 2" << endl;
    cout << "Date Change (+1 Date) -- Please Enter 3" << endl;
    cout << "View All Sales Records and Total Revenue -- Please Enter 4" << endl;
    cout << "Clear All Sales Records -- Please Enter 5" << endl;
    cout << "Enter Administrator Mode. -- Please Enter 6" << endl;
}

void clearScreen() {
    #ifdef _WIN32 // 如果是 Windows 系统
        system("cls");
    #else         // 如果是 Linux 或 macOS 系统
        system("clear");
    #endif
}

void Redirect(){
    cout << "Redirecting In 2 Seconds..." <<endl;
    this_thread::sleep_for(chrono::seconds(2));
    clearScreen();
}

void Exit(){
    cout << "Exiting In 5 Seconds." << endl;
    this_thread::sleep_for(chrono::seconds(5));
    clearScreen();
}

void ReturnMenu(){
    cout << "Returning to Main Menu In 2 Seconds..." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    clearScreen(); 
}

void Refresh(){
    cout << "Refresh In 2 Seconds..." <<endl;
    this_thread::sleep_for(chrono::seconds(2));
    clearScreen();
}