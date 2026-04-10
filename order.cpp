#include "struct.h"
#include "order.h"
#include "bill.h"

int findInOrder(System &sys, string id) {            //tim xem mon an da co hay chua
    for (int i = 0; i < sys.orderCount; i++) {
        if (sys.orderList[i].id == id) return i;
    }
    return -1;
}

void PrintMenu(System &sys) {
    cout << "========== MENU ==========\n";
    
    int cols = 3; 
    int rows = (sys.menuCount + cols - 1) / cols; 

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int index = i + j * rows; 

            if (index < sys.menuCount) {

                cout << left << setw(2) << index + 1 << ". " 
                     << setw(30) << sys.menuList[index].name 
                     << right << setw(6) << sys.menuList[index].price 
                     << " VND | ";
            }
        }
        cout << "\n"; 
    }
    cout << "==========================\n";
}

int findDrink(System &sys, string id) {
    for (int i = 0; i < sys.menuCount; i++)
        if (sys.menuList[i].id == id) return i;
    return -1;
}

void ShowOrder(System &sys) {
    cout << "\n==================== CURRENT ORDER ==========================\n";
    cout << left << setw(5)  << "No" 
         << "| " << setw(30) << "Description" 
         << "| " << setw(10) << "Quantity" 
         << "| " << "Price" << endl;
    cout << "-------------------------------------------------------------\n";
    
    for (int i = 0; i < sys.orderCount; i++) {
        long long money = (long long)sys.orderList[i].price * sys.orderList[i].quantity;
        cout << left << setw(5)  << i + 1 
             << "| " << setw(30) << sys.orderList[i].name 
             << "| " << setw(10) << sys.orderList[i].quantity 
             << "| " << money << " " << endl;
    }
    cout << "-------------------------------------------------------------\n";
}


void AddDrink(System &sys) {
    if (sys.orderCount >= 5) {
        cout << "Order full!\n";
        return;
    }
    while (true) {
        string id;
        int qty;
        cin >> id >> qty;
        if (id == "0" && qty == 0) break;

      
        if (qty <= 0) continue; 

        int pos = findDrink(sys, id);
        if (pos == -1) { cout << "Wrong id!\n"; continue; }
        
        sys.orderList[sys.orderCount].id = sys.menuList[pos].id;
        sys.orderList[sys.orderCount].name = sys.menuList[pos].name;
        sys.orderList[sys.orderCount].price = sys.menuList[pos].price;
        sys.orderList[sys.orderCount].quantity = qty;
        sys.orderCount++;
        if (sys.orderCount >= 5) { cout << "Order full!\n"; break; }
    }
}


void ChangeDrink(System &sys) {
    ShowOrder(sys);
    int pos, qty;
    cout << "Choose item number: "; cin >> pos; pos--;
    if (pos < 0 || pos >= sys.orderCount) {
        cout << "Wrong code!\n"; return;
    }
    cout << "New quantity: "; cin >> qty;
    if (qty <= 0) cout << "Wrong code!\n";
    else sys.orderList[pos].quantity = qty;
}



void DeleteDrink(System &sys) {
    ShowOrder(sys);
    int pos;
    cout << "Choose item number: "; cin >> pos; pos--;
    if (pos < 0 || pos >= sys.orderCount) {
        cout << "Wrong code!\n"; return;
    }
    for (int i = pos; i < sys.orderCount - 1; i++)
        sys.orderList[i] = sys.orderList[i + 1];
    sys.orderCount--;
}



char OrderMenu() {
    cout << "\na.Add  b.Change  c.Delete  d.Finish  e.Cancel\n";
    cout << "Option: ";
    char option; cin >> option;
    return option;
}


void StartOrder(System &sys) {
    sys.orderCount = 0;
    PrintMenu(sys);
    cout << "\n> Enter '0 0' to finish selecting drinks!\n"; 
    
    while (true) {
        
        if (sys.orderCount >= 5) { 
            cout << "Order full!\n"; 
            break; 
        }

        string id; int qty;
        cout << "Drinking " << sys.orderCount + 1 << ": "; 
        cin >> id >> qty;

        if (id == "0" && qty == 0) break;
        if (qty <= 0) continue; 

        int pos = findDrink(sys, id);
        if (pos == -1) { 
            cout << "Wrong id!\n"; 
            continue; 
        }

        int existPos = findInOrder(sys, id);
        if (existPos != -1) {
          
            sys.orderList[existPos].quantity += qty;
        } else {
         
            sys.orderList[sys.orderCount].id = sys.menuList[pos].id;
            sys.orderList[sys.orderCount].name = sys.menuList[pos].name;
            sys.orderList[sys.orderCount].price = sys.menuList[pos].price;
            sys.orderList[sys.orderCount].quantity = qty;
            sys.orderCount++;
        }
    }

    if (sys.orderCount == 0) return;


    while (true) {
        ShowOrder(sys);
        cout << "TOTAL: " << CalcTotal(sys) << " VND\n";
        char confirm;
        cout << "Confirm Payment? (Y/N): ";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y') {
            ProcessPayment(sys);
            return;
        }
        else if (confirm == 'N' || confirm == 'n') {
            bool backToPayment = false;
            while (!backToPayment) {
                char option = OrderMenu();
                if (option == 'a') {
                    AddDrink(sys); 
                }
                else if (option == 'b') ChangeDrink(sys);
                else if (option == 'c') DeleteDrink(sys);
                else if (option == 'e') {
                    sys.orderCount = 0;
                    return;
                }
                else if (option == 'd') {
                    backToPayment = true; 
                }
                if (option != 'd') ShowOrder(sys);
            }
        }
        else {
            cout << "Wrong code!\n";
        }
    }
}