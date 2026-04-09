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
    if (!f.is_open()) return;

    static int customerCount = 1;
    string currentTime = getCurrentTime(); 

    f << "----------------------------------------------------------------------------\n";
    f << "|" << right << setw(40) << "CUSTOMER " << customerCount++ << setw(35) << " |\n";
    f << "----------------------------------------------------------------------------\n";
    
    f << "Cashier's name: " << sys.staffList[sys.currentStaff].name << "\n";
    f << "Time in:  " << dateStr << " " << currentTime << "\n";
    f << "Time out: " << dateStr << " " << currentTime << "\n\n";

    f << left << setw(35) << "| Description" 
      << "| " << setw(10) << "Quantity" 
      << "| " << setw(12) << "Unit price" 
      << "| " << setw(12) << "Into money" << "|\n";
    f << "----------------------------------------------------------------------------\n";

    long long rawTotal = 0;
    for (int i = 0; i < sys.orderCount; i++) {
        long long price = sys.orderList[i].price;
        int qty = sys.orderList[i].quantity;
        long long intoMoney = price * qty;
        rawTotal += intoMoney;

        f << "| " << left << setw(33) << sys.orderList[i].name 
          << "| " << right << setw(8) << qty << "  "
          << "| " << right << setw(10) << price << "  "
          << "| " << right << setw(10) << intoMoney << "  |\n";
    }

    f << "---------------------------------------------------------------------------\n\n";

    long long finalTotal = CalcTotal(sys);
    long long discount = rawTotal - finalTotal;

    f << "Total: " << rawTotal << " VND\n";
    f << "Discount: " << discount << " VND\n";
    f << "Total after discount: " << finalTotal << " VND\n";
    f << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\n";

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
    cout << "\n======================== BILL ===============================\n";
    cout << left << setw(5)  << "No" 
         << "| " << setw(30) << "Description" 
         << "| " << setw(10)  << "Qty" 
         << "| " << "Price" << "\n";
    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < sys.orderCount; i++) {
        long long money = (long long)sys.orderList[i].price * sys.orderList[i].quantity;
        
        cout << left << setw(5)  << i + 1
             << "| " << setw(30) << sys.orderList[i].name 
             << "| " << setw(10)  << sys.orderList[i].quantity 
             << "| " << money << " VND\n";
    }

    long long total = CalcTotal(sys);
    cout << "-------------------------------------------------------------\n";
    cout << "TOTAL: " << total << " VND\n";
    
    // Cập nhật số lượng bán và doanh thu
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

    f << "\n================= STAFF REVENUE ==================\n";
    for(int i = 0; i < sys.staffCount; i++){
        if (sys.staffList[i].revenue > 0) { 
            f << "- " << left << setw(20) << sys.staffList[i].name 
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