#ifndef STAFF_H
#define STAFF_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Base struct for all staff members
struct StaffMember {
    int enrollmentNumber;
    int age;
    string name;
    string jobType;
    double salary;
    int attendance;
};

// Global instance of StaffMember used for reading and writing

// Function declarations
void addStaffMember();
void displayStaffMember(int roll);
void updateStaffAttendance(int roll);
void menuOfStaff();

#endif // STAFF_H
