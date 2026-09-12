#include <iostream>
#include <thread> 
#include <chrono>
using namespace std;

void ShowMenu(int date,int num){
    cout << "==============================================================" << endl;
    cout << "7-Eleven Convenience Store POS Command-Line Interactive System" << endl;
    cout << "==============================================================" << endl;
    cout << "Day:" << date << "---" << "Current Receipt Number" << num << endl << endl;
    cout << "Exit the Menu -- Please enter 0" << endl;
    cout << "Show Product Information -- Please enter 1" << endl;
    cout << "Checkout -- Please enter 2" << endl;
    cout << "Date Change (+1 Date) -- Please enter 3" << endl;
    cout << "View All Sales Records and Total Revenue -- Please enter 4" << endl;
    cout << "Clear All Sales Records -- Please enter 5" << endl;
    cout << "Enter administrator mode. -- Please enter 6" << endl;
}

void clearScreen() {
    #ifdef _WIN32 // 如果是 Windows 系统
        system("cls");
    #else         // 如果是 Linux 或 macOS 系统
        system("clear");
    #endif
}

void Redirect(){
    cout << "Redirecting in 2 seconds..." <<endl;
    this_thread::sleep_for(chrono::seconds(2));
    clearScreen();
}

void Exit(){
    cout << "Exiting in 5 seconds." << endl;
    this_thread::sleep_for(chrono::seconds(5));
    clearScreen();
}

void ReturnMenu(){
    cout << "Returning to main menu in 2 seconds..." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    clearScreen(); 
}