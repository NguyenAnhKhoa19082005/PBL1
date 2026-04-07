#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

struct Drink {
    string id;
    string name;
    int price;
    int sold;
};

struct Staff {
    string id;
    string name;
    string pass;
    long long revenue;
    string login;
    string logout;
};

struct Order {
    string id;
    string name;
    int price;
    int quantity;
};

struct System {
    Drink menuList[50];
    Staff staffList[3];
    Order orderList[5];

    int menuCount = 0;
    int staffCount = 0;
    int orderCount = 0;
    int currentStaff = -1;

    string todayid;
};