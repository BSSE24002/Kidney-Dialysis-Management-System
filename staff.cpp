#include <iostream>
using namespace std;
#include "staff.h"
StaffMember staff;

// Function to add a new staff member to the file
void addStaffMember() {
    ifstream readFile("kidneycenterstaff.txt");
    staff.enrollmentNumber = 0;  // Initialize enrollment number

    // Reading the last enrollment number from the file
    if (readFile.is_open()) {
        while (readFile >> staff.enrollmentNumber >> staff.age >> staff.name >>
               staff.jobType >> staff.salary >> staff.attendance) {
            // Continue to the last entry to get the highest enrollment number
        }
        readFile.close();
    }

    // Increment for the new staff member
    staff.enrollmentNumber++;

    ofstream file("kidneycenterstaff.txt", ios::out | ios::app);
    if (!file.is_open()) {
        cout << "Error: Could not open the file for writing." << endl;
        return;
    }

    // Collecting input from the user
    cout << "New Staff Enrollment Number: " << staff.enrollmentNumber << endl;
    cout << "Enter age: ";
    cin >> staff.age;
    cin.ignore();  // Clear newline left by `cin`
    cout << "Enter name: ";
    getline(cin, staff.name);
    cout << "Enter job type (Nurse, Biomedical Engineer, Pharmacist, Receptionist): ";
    getline(cin, staff.jobType);
    cout << "Enter salary: ";
    cin >> staff.salary;
    staff.attendance = 0;  // Initial attendance

    // Writing data to the file
    file << staff.enrollmentNumber << "," << staff.age << ","
         << staff.name << "," << staff.jobType << "," << staff.salary << "," << staff.attendance << endl;
    file.close();
    cout << "Staff member added successfully!" << endl;
}

// Function to display a staff member's details by enrollment number
void displayStaffMember(int roll) {
    ifstream file("kidneycenterstaff.txt");
    bool found = false;

    if (!file.is_open()) {
        cout << "Error: Could not open the file for reading." << endl;
        return;
    }

    // Reading and displaying the matching record
    while (file >> staff.enrollmentNumber >> staff.age >> staff.name >>
           staff.jobType >> staff.salary >> staff.attendance) {
        if (staff.enrollmentNumber == roll) {
            found = true;
            cout << "\nStaff Details:" << endl;
            cout << "Enrollment Number: " << staff.enrollmentNumber << endl;
            cout << "Age: " << staff.age << endl;
            cout << "Name: " << staff.name << endl;
            cout << "Job Type: " << staff.jobType << endl;
            cout << "Salary: " << staff.salary << endl;
            cout << "Attendance: " << staff.attendance << endl;
            break;
        }
    }

    if (!found) {
        cout << "Error: Enrollment number not found." << endl;
    }

    file.close();
}

// Function to update the attendance of a staff member by enrollment number
void updateStaffAttendance(int roll) {
    ifstream file("kidneycenterstaff.txt");
    ofstream tempFile("temp.txt");
    bool found = false;

    if (!file.is_open() || !tempFile.is_open()) {
        cout << "Error: Could not open files for updating." << endl;
        return;
    }

    // Reading and copying records, updating attendance when the match is found
    while (file >> staff.enrollmentNumber >> staff.age >> staff.name >>
           staff.jobType >> staff.salary >> staff.attendance) {
        if (staff.enrollmentNumber == roll) {
            found = true;
            staff.attendance++;
            cout << "Attendance updated to " << staff.attendance << " for enrollment number " << roll << "." << endl;
        }
        tempFile << staff.enrollmentNumber << "," << staff.age << ","
                 << staff.name << "," << staff.jobType << " ," << staff.salary << " ," << staff.attendance << endl;
    }

    file.close();
    tempFile.close();

    if (!found) {
        cout << "Error: Enrollment number not found." << endl;
        remove("temp.txt");  // Delete the temp file if no update was made
    } else {
        remove("kidneycenterstaff.txt");
        rename("temp.txt", "kidneycenterstaff.txt");
    }
}

// Menu function to navigate staff management options
void menuOfStaff() {
    int choice;
    do {
        cout << "\n--- Kidney Center Staff Management System ---" << endl;
        cout << "1. Add a new staff member" << endl;
        cout << "2. Display staff member information" << endl;
        cout << "3. Update attendance" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStaffMember();
                break;
            case 2:
                int roll;
                cout << "Enter enrollment number to display: ";
                cin >> roll;
                displayStaffMember(roll);
                break;
            case 3:
                int rollToUpdate;
                cout << "Enter enrollment number to update attendance: ";
                cin >> rollToUpdate;
                updateStaffAttendance(rollToUpdate);
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 4);
}

