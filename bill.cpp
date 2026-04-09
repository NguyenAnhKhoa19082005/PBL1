#include "struct.h"
#include "bill.h"
#include "order.h"
#include "prac.h"

void SaveBill(System &sys) {
    string dateStr = getCurrentDate();
    string filename = "data/output/" + dateStr + "_" +
        sys.staffList[sys.currentStaff].id + "_" +
        sys.staffList[sys.currentStaff].name + ".dat";

    ofstream f(filename.c_str(), ios::app);
    static int customer = 1;
    f << "\nCUSTOMER " << customer++ << "\n";
    for (int i = 0; i < sys.orderCount; i++) {
        f << sys.orderList[i].name << " | "
          << sys.orderList[i].quantity << " | "
          << (long long)sys.orderList[i].price * sys.orderList[i].quantity << "\n";
    }
    f << "Total: " << CalcTotal(sys) << " VND\n";
    f << "STAFF: " << sys.staffList[sys.currentStaff].name << "\n";
    f.close();
}

void SaveEndShift(System &sys) {
    string dateStr = getCurrentDate();
    string filename = "data/output/" + dateStr + "_" +
        sys.staffList[sys.currentStaff].id + "_" +
        sys.staffList[sys.currentStaff].name + ".dat";

    ofstream f(filename.c_str(), ios::app);
    f << "\nTotal Shift: " << sys.staffList[sys.currentStaff].revenue << " VND\n";
    f.close();
}


long long CalcTotal(System &sys) {
    long long total = 0;
    for (int i = 0; i < sys.orderCount; i++)
        total += (long long)sys.orderList[i].price * sys.orderList[i].quantity;
    if (total >= 2000000) total *= 0.8;
    return total;
}


void ProcessPayment(System &sys) {
    cout << "\n=========== BILL ===========\n";
    cout << setw(25) << left << "| Name" << setw(5) << "| Qty " << "| Price\n";
    for (int i = 0; i < sys.orderCount; i++) {
        long long money = (long long)sys.orderList[i].price * sys.orderList[i].quantity;
        cout << i + 1 << ". " << setw(24) << left << sys.orderList[i].name << setw(2) << sys.orderList[i].quantity << "  " << money << " VND\n";
    }
    long long total = CalcTotal(sys);
    cout << "TOTAL: " << total << " VND\n";
    for (int i = 0; i < sys.orderCount; i++) {
        int pos = findDrink(sys, sys.orderList[i].id);
        if (pos != -1) sys.menuList[pos].sold += sys.orderList[i].quantity;
    }
    sys.staffList[sys.currentStaff].revenue += total;
    
    SaveBill(sys);
    cout << "Payment success!\n";
}



void SaveThongKe(System &sys) {
    string dateStr = getCurrentDate();
    string filename = "data/output/" + dateStr + "_ThongKe.dat";
    ofstream f(filename.c_str());
    long long totalDay = 0;


    f << "========================================= DAILY STATISTICS =========================================\n";
    f << left << setw(8)  << "| Code" 
      << "| " << setw(45) << "Description" 
      << "| " << setw(10) << "Quantity" 
      << "| " << setw(12) << "Unit price" 
      << "| " << setw(15) << "Into money" << " |\n";
    f << "----------------------------------------------------------------------------------------------------\n";


    for (int i = 0; i < sys.menuCount; i++) {
        long long money = (long long)sys.menuList[i].sold * sys.menuList[i].price;
        
        f << "| " << setw(6)  << sys.menuList[i].id
          << "| " << setw(45) << sys.menuList[i].name
          << "| " << setw(10) << sys.menuList[i].sold
          << "| " << setw(12) << sys.menuList[i].price
          << "| " << setw(15) << money << " |\n";
    }

    f << "----------------------------------------------------------------------------------------------------\n";

    f << "\n===== STAFF REVENUE =====\n";
    for(int i = 0; i < sys.staffCount; i++){
        if (sys.staffList[i].revenue > 0) { 
            f << "- " << left << setw(25) << sys.staffList[i].name 
              << ": " << sys.staffList[i].revenue << " VND\n";
            f << "  Login: " << sys.staffList[i].login 
              << " | Logout: " << sys.staffList[i].logout << "\n\n";
            
            totalDay += sys.staffList[i].revenue;
        }
    }

    f << "--------------------------------------------------\n";
    f << "TOTAL DAILY REVENUE: " << totalDay << " VND\n";
    f << "==================================================\n";

    f.close();
}