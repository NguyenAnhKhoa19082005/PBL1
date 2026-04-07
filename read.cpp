#include "struct.h"
#include "read.h"


void Read_Staff(System &sys) {
    ifstream f("data/input/staff.dat");
    while (getline(f, sys.staffList[sys.staffCount].id, ',')) {
        getline(f, sys.staffList[sys.staffCount].name, ',');
        getline(f, sys.staffList[sys.staffCount].pass);
        sys.staffList[sys.staffCount].revenue = 0;
        sys.staffCount++;
    }
    f.close();
}

void Read_Menu(System &sys) {
    ifstream f("data/input/menu.dat");
    while (true) {
        getline(f, sys.menuList[sys.menuCount].id, ',');
        if (sys.menuList[sys.menuCount].id == "") break;
        getline(f, sys.menuList[sys.menuCount].name, ',');
        f >> sys.menuList[sys.menuCount].price;
        f.ignore();
        sys.menuList[sys.menuCount].sold = 0;
        sys.menuCount++;
    }
    f.close();
}
