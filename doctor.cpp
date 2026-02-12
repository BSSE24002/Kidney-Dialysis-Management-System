//
// Created by MPC on 11/8/2024.
//
#include<iostream>
#include "doctor.h"
using namespace std;
void showMenu() {
    cout << "Kidney Centre Management System"<<endl;
    cout << "1. Add Doctor"<<endl;
    cout << "2. Display All Doctors "<<endl;
    cout << "3. Modify Doctor "<<endl;
    cout << "4. Delete Doctor"<<endl;
    cout << "5. Search Doctor by ID"<<endl;
    cout << "6. Exit"<<endl;
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addDoctor();
            break;
            case 2:
                displayDoctors();
            break;
            case 3:
                modifyDoctor();
            break;
            case 4:
                deleteDoctor();
            break;
            case 5:
                searchDoctor();
            break;
            case 6:
                cout << "Exiting program.\n";
            return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}