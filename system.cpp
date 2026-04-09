#include "struct.h" 
#include "system.h" 
#include "read.h"   
#include "order.h"  
#include "bill.h"   
#include "prac.h"




void Print() {
    cout << "==================================================================================================\n";
    cout << "|                                                                                                |\n";
    cout << "|                               _ PBL 1: DU AN CO SO LAP TRINH _                                 |\n";
    cout << "|                               ------------------------------------                             |\n";
    cout << "|                                            DE TAI 702                                          |\n"; 
    cout << "|                        XAY DUNG UNG DUNG DAT MON AN VA THANH TOAN DON HANG                     |\n";
    cout << "|                                             *****                                              |\n";
    cout << "|                                                                                                |\n";
    cout << "|              Giang vien huong dan: Th.S TRAN HO THUY TIEN                                      |\n";
    cout << "|              Sinh vien thuc hien:                                                              |\n";
    cout << "|                     1. NGUYEN ANH KHOA  Lop: 23PFIEV3  Ma SV: 123230154                        |\n";
    cout << "|                     2. NGUYEN VAN DUY   Lop: 23PFIEV3  Ma SV: 123230145                        |\n";
    cout << "|                     3. DOAN NGOC CUONG  Lop: 23PFIEV3  Ma SV: 123230142                        |                                                           |\n";
    cout << "==================================================================================================\n";
    

    

    cin.get(); // Dừng lại chờ người dùng nhấn Enter
    system("cls"); // Xóa màn hình để vào phần đăng nhập
}



void Login(System &sys) {
    string id, pass;
    while (true) {
        cout << "Login Staff's ID: ";
        getline(cin, id);
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
            cout << "Wrong password!\n";
            continue;
        }
        if (sys.currentStaff != -1) {
            sys.staffList[sys.currentStaff].logout = getCurrentTime();
        }
        sys.currentStaff = pos;
        sys.staffList[pos].login = getCurrentTime();
        system("cls"); 
        cout << "Welcome " << sys.staffList[pos].name << "\n";
        break;
    }
}

void Start(System &sys) {
    Read_Menu(sys);
    Read_Staff(sys);
}


void Run(System &sys) {
    Print();
    Start(sys);
    while (true) {
        if (sys.currentStaff == -1) Login(sys);
        bool NewCustomer = true;
        while (NewCustomer) {
            StartOrder(sys);
            char check;
            cout << "\nNew Customer? (Y/N): ";
            cin >> check; cin.ignore();
            if (check == 'N' || check == 'n') {
                NewCustomer = false;
            }
            system("cls"); 
        }
        while (true) {
            cout << "\n1. End Shift\n";
            cout << "2. End Day\n";
            cout << "Option: ";
            int choice; 
            cin >> choice; cin.ignore();

            if (choice == 1) {
                sys.staffList[sys.currentStaff].logout = getCurrentTime();
                
                SaveEndShift(sys); 
                
                sys.currentStaff = -1; 
                system("cls");
                break;
            } 
            else if (choice == 2) {
                sys.staffList[sys.currentStaff].logout = getCurrentTime();
                SaveEndShift(sys); 
                SaveThongKe(sys);
                return; 
            } 
            else {
                cout << "Wrong code!\n";
            }
        }
    }
}