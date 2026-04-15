#include "struct.h"
#include "program.h"
#include "read.h"   
#include "order.h"  
#include "bill.h"   
#include "prac.h"

using namespace std;

void ShowPBL() {
    cout << "==================================================================================================\n";
    cout << "|                                                                                                |\n";
    cout << "|                               _ PBL 1: DU AN CO SO LAP TRINH _                                 |\n";
    cout << "|                               ------------------------------------                             |\n";
    cout << "|                                             DE TAI 702                                         |\n"; 
    cout << "|                        XAY DUNG UNG DUNG DAT MON AN VA THANH TOAN DON HANG                     |\n";
    cout << "|                                              *****                                             |\n";
    cout << "|                                                                                                |\n";
    cout << "|              Giang vien huong dan: Th.S TRAN HO THUY TIEN                                      |\n";
    cout << "|              Sinh vien thuc hien:                                                              |\n";
    cout << "|                     1. NGUYEN ANH KHOA  Lop: 23PFIEV3  Ma SV: 123230154                        |\n";
    cout << "|                     2. NGUYEN VAN DUY   Lop: 23PFIEV3  Ma SV: 123230145                        |\n";
    cout << "|                     3. DOAN NGOC CUONG  Lop: 23PFIEV3  Ma SV: 123230142                        |\n";
    cout << "==================================================================================================\n";
    
    cin.get(); 
    system("cls");
}

void Start(System &sys) {
    Read_Menu(sys);
    Read_Staff(sys);
}

bool Login(System &sys) {
    string id, pass;
    while (true) {
        cout << "===== LOGIN SYSTEM =====\n";
        cout << "Login Staff's ID: ";
        getline(cin, id);

        if (id == "exit") return false;

        int pos = -1;
        for (int i = 0; i < sys.staffCount; i++) {
            if (sys.staffList[i].id == id) {
                pos = i;
                break;
            }
        }

        if (pos == -1) {
            cout << "Wrong ID!\n";
            continue;
        }

        cout << "Password: ";
        pass = inputPassword(); 

        if (pass != sys.staffList[pos].pass) {
            cout << "\nWrong password!\n";
            continue;
        }

        sys.currentStaff = pos;
        sys.staffList[pos].login = getCurrentTime();
        
        system("cls"); 
        cout << "Welcome " << sys.staffList[pos].name << "!\n";
        return true;
    }
}

void Systems(System &sys) {
    bool inSession = true;
    while (inSession) {
        bool NewCustomer = true;
        while (NewCustomer){
            StartOrder(sys); 
            char check;
            while (true){
                cout << "\nNew Customer? (Y/N): ";
                cin >> check; 
                cin.ignore(1000, '\n'); 

                if (check == 'Y' || check == 'y') {
                    break; 
                }
                else if (check == 'N' || check == 'n') {
                    NewCustomer = false; 
                    break;
                }
                else {
                    cout << "Wrong code!"; 
                }
            }
            system("cls"); 
        }

        while (true) {
            cout << "================================\n";
            cout << "1. End Shift\n";
            cout << "2. End Day\n";
            cout << "Option: ";
            int choice; 
            cin >> choice; 
            if (cin.fail()) {
                cout << "Wrong code!\n";
                cin.clear();         
                cin.ignore(1000, '\n'); 
                continue;           
            }
            cin.ignore(); 

            if (choice == 1) {
                sys.staffList[sys.currentStaff].logout = getCurrentTime();
                SaveEndShift(sys); 
                sys.currentStaff = -1; 
                system("cls");
                inSession = false; 
                break;
            } 
            else if (choice == 2) {
                sys.staffList[sys.currentStaff].logout = getCurrentTime();
                SaveEndShift(sys); 
                SaveThongKe(sys);
                exit(0);
            } 
            else {
                cout << "Wrong code!\n";
            }
        }
    }
}