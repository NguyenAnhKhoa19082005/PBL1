#include "prac.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

string inputPassword(){
    string pass = "";
    char ch;
    while(true){
        ch = _getch();

        if(ch == 13){ // Enter
            cout << endl;
            break;
        }
        else if(ch == 8){ // Backspace
            if(pass.length() > 0){
                pass.pop_back();
                cout << "\b \b";
            }
        }
        else{
            pass += ch;
            cout << "*";
        }
    }
    return pass;
}


string getCurrentTime(){

    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << setw(2) << setfill('0') << ltm->tm_hour << ":"
       << setw(2) << setfill('0') << ltm->tm_min << ":"
       << setw(2) << setfill('0') << ltm->tm_sec;
    return ss.str();

}

string getCurrentDate(){

    time_t now = time(0);
    tm *ltm = localtime(&now);

    stringstream ss;
    ss << (1900 + ltm->tm_year) << "-"
       << setw(2) << setfill('0') << (1 + ltm->tm_mon) << "-"
       << setw(2) << setfill('0') << ltm->tm_mday;

    return ss.str();
    
}