#include <iostream>
#include <string>
#include <fstream>
#include "Dialysis.h"
#include "billing.h"
using namespace std;

Dialysis d;
int hemodialysis = 50000;                                           //Initializing integers to handle cost issue
int peritonealDialysis = 100000;
int typeDialysis;
const int MAXSESSIONS = 10;
Dialysis sessions[MAXSESSIONS];

void addDialysisSession() {
    ifstream dialysisFile("Dialysis.txt");                          //Reading from file
    if(!(dialysisFile.is_open())) {
        cout << "Error opening file! " << endl;
    }
    int sessionCount = 0;
    string line;
    while(getline(dialysisFile, line)) {                            //Loop getting each line from file and incrementing count
        sessionCount = sessionCount + 1;
    }
    dialysisFile.close();
    if(sessionCount >= 10) {                                        //Condition to handle maximum sessions
        cout << "Maximum sessions reached! " << endl;
        return;
    }
    ofstream outFile("Dialysis.txt", ios::app);                     //Getting data from user and entering in file
    cout << "Enter ID of the patient: ";
    cin.ignore();
    getline(cin, d.patientID);
    cout << "Enter date for dialysis(DD/MM/YYYY): ";
    getline(cin, d.date);
    cout << "Enter a bed number: ";
    cin >> d.bedNumber;
    cout << "Enter duration of the session(hours): ";
    cin >> d.duration;
    cout << "Enter type of dialysis(1.Hemodialysis /2.Peritoneal Dialysis): ";
    cin >> typeDialysis;
    if(typeDialysis == 1) {                                         //Condition to handle cost of dialysis
        outFile << "D" << " " << d.patientID << " " << d.date << " " << d.bedNumber << " " << d.duration << " " << hemodialysis << endl;
        outFile.close();
    }
    else if(typeDialysis == 2) {                                    //Condition to handle cost of dialysis
        outFile << "D" << " " << d.patientID << " " << d.date << " " << d.bedNumber << " " << d.duration << " " << peritonealDialysis << endl;
        outFile.close();
    }
    cout << "Session added! " << endl;
}

void updateDialysisSession() {
    string id;
    cout << "Enter ID of the patient to update: ";
    cin.ignore();
    getline(cin, id);
    ifstream dialysisFile("Dialysis.txt");
    if(!(dialysisFile.is_open())) {
        cout << "Error opening file! " << endl;
    }
    ofstream temporaryFile("temporary.txt");                        //Making a temporary file to store updated data in it
    bool flag = false;
    while(dialysisFile >> d.flag >> d.patientID >> d.date >> d.bedNumber >> d.duration >> typeDialysis) {
        if(id == d.patientID) {                                     //Condition in loop to check ID to update
            cout << "New date for dialysis(DD/MM/YYYY): ";          //Getting new data from user
            getline(cin, d.date);
            cout << "Enter new bed number for dialysis: ";
            cin >> d.bedNumber;
            cout << "New duration for dialysis(hours): ";
            cin >> d.duration;
            cout << "New type of dialysis(1.Hemodialysis /2.Peritoneal Dialysis): ";
            cin >> typeDialysis;
            if(typeDialysis == 1) {
                typeDialysis = hemodialysis;
            }
            else if(typeDialysis == 2) {
                typeDialysis = peritonealDialysis;
            }
            flag = true;
        }                                                           //Storing in temporary file
        temporaryFile << "D" << " " << d.patientID << " " << d.date << " " << d.bedNumber << " " << d.duration << " " << typeDialysis << endl;
    }
    dialysisFile.close();
    temporaryFile.close();
    remove("Dialysis.txt");                                         //Removing previous file
    rename("temporary.txt", "Dialysis.txt");                        //Renaming temporary file to original name
    if(flag == true) {
        cout << "Dialysis Session Updated! " << endl;
    }
    if(flag == false) {
        cout << "Patient ID does not exist! " << endl;
    }
}

void deleteDialysisSession() {
    string id;
    cout << "Enter ID of the patient to delete: ";                  //Getting ID to delete
    cin.ignore();
    getline(cin, id);
    ifstream dialysisFile("Dialysis.txt");
    if(!(dialysisFile.is_open())) {
        cout << "Error opening file! " << endl;
    }
    ofstream temporaryFile("temporary.txt");                        //Creating a temporary file
    bool flag = false;
    while(dialysisFile >> d.flag >> d.patientID >> d.date >> d.bedNumber >> d.duration >> typeDialysis) {
        if(d.patientID != id) {                                     //Copying all data to temporary file except that of which ID matches
            temporaryFile << "D" << " " << d.patientID << " " << d.date << " " << d.bedNumber << " " << d.duration << " " << typeDialysis << endl;
        }
        else {
            flag = true;
        }
    }
    dialysisFile.close();
    temporaryFile.close();
    remove("Dialysis.txt");                                         //Removing previous file
    rename("temporary.txt", "Dialysis.txt");                        //Renaming temporary file to original file
    if(flag == true) {
        cout << "Dialysis Session Deleted! " << endl;
    }
    if(flag == false) {
        cout << "Patient ID does not exist! " << endl;
    }
}

void searchDialysisSession() {
    string id;
    cout << "Enter ID of the patient to search: ";                  //Getting ID to search
    cin.ignore();
    getline(cin, id);
    ifstream dialysisFile("Dialysis.txt");                          //Reading from file
    if(!(dialysisFile.is_open())) {
        cout << "Error opening file! " << endl;
    }
    bool flag = false;
    while(dialysisFile >> d.flag >> d.patientID >> d.date >> d.bedNumber >> d.duration >> typeDialysis) {
        if(id == d.patientID) {                                     //If ID matches, show all details
            cout << "Patient ID: " << d.patientID << endl;
            cout << "Session Date(DD/MM/YYYY): " << d.date << endl;
            cout << "Session Bed Number: " << d.bedNumber << endl;
            cout << "Session Duration(hours): " << d.duration << endl;
            if(typeDialysis == 50000) {
                cout << "Type of dialysis is Hemodialysis" << endl;
            }
            else if(typeDialysis == 100000) {
                cout << "Type of dialysis is Peritoneal Dialysis" << endl;
            }
            flag = true;
            break;
        }
    }
    dialysisFile.close();
    if(flag == false) {
        cout << "Patient ID not found " << endl;
    }
}

void displayAllSessions() {
    ifstream dialysisFile("Dialysis.txt");                          //Opening file
    if(!(dialysisFile.is_open())) {
        cout << "Error opening file! " << endl;
    }
    while(dialysisFile >> d.flag >> d.patientID >> d.date >> d.bedNumber >> d.duration >> typeDialysis) {
        cout << "Patient ID: " << d.patientID << endl;              //Displaying all data
        cout << "Session Date(DD/MM/YYYY): " << d.date << endl;
        cout << "Session Bed Number: " << d.bedNumber << endl;
        cout << "Session Duration(hours): " << d.duration << endl;
        if(typeDialysis == 50000) {                                 //Handling dialysis type issue
            cout << "Type of dialysis is Hemodialysis" << endl;
            cout << "--------------------------------" << endl;
        }
        else if(typeDialysis == 100000) {
            cout << "Type of dialysis is Peritoneal Dialysis" << endl;
            cout << "----------------------------------------" << endl;
        }
    }
    dialysisFile.close();
}

void automaticDelete(string id) {
    ifstream dialysisFile("Dialysis.txt");
    if(!(dialysisFile.is_open())) {
        cout << "Error opening file! " << endl;
    }
    ofstream temporaryFile("temporary.txt");                        //Creating a temporary file
    bool flag = false;
    while(dialysisFile >> d.flag >> d.patientID >> d.date >> d.bedNumber >> d.duration >> typeDialysis) {
        if(d.patientID != id) {                                     //Copying all data to temporary file except that of which ID matches
            temporaryFile << "D" << " " << d.patientID << " " << d.date << " " << d.bedNumber << " " << d.duration << " " << typeDialysis << endl;
        }
        else {
            flag = true;
        }
    }
    dialysisFile.close();
    temporaryFile.close();
    remove("Dialysis.txt");                                         //Removing previous file
    rename("temporary.txt", "Dialysis.txt");                        //Renaming temporary file to original file
    if(flag == true) {
        cout << "Dialysis Session Deleted! " << endl;
    }
    if(flag == false) {
        cout << "Patient ID does not exist! " << endl;
    }
}

bool loadSessions() {
    int cost;
    ifstream dialysisFile("Dialysis.txt");                          //Opening file to read
    if(!(dialysisFile.is_open())) {
        cout << "Error opening file! " << endl;
        return false;
    }
    int i = 0;
    while(dialysisFile >> sessions[i].flag >> sessions[i].patientID >> sessions[i].date >> sessions[i].bedNumber >> sessions[i].duration >> cost) {
        i++;                                                        //Loop getting all data from file into arrays
        if(i >= MAXSESSIONS) {
            cout << "Maximum sessions reached! " << endl;
            break;
        }
    }
    dialysisFile.close();
    cout << "Sessions loaded! " << endl;
    return true;
}

void listByDate() {
    loadSessions();
    string date;
    cout << "Enter date(DD/MM/YYYY) to view sessions: ";
    cin >> date;
    bool flag = false;
    cout << "Sessions on " << date << " are:" << endl;
    for(int i = 0; i < MAXSESSIONS; i++) {                          //Loop iteration over each session
        if(sessions[i].patientID.empty()) {
            break;
        }
        if(date == sessions[i].date) {                              //Condition in loop to check date
            cout << "Patient ID: " << sessions[i].patientID << endl;
            cout << "Bed Number: " << sessions[i].bedNumber << endl;
            cout << "Duration: " << sessions[i].duration << endl;
            cout << "-----------------" << endl;
            flag = true;
        }
    }
    if(flag == false) {
        cout << "No sessions found! " << endl;
    }
}

void mainMenu() {
    int choice;                                                     //Showing menu and calling functions accordingly
    cout << "======== Welcome to Dialysis Centre ========" << endl;
    cout << "1. Add Dialysis Session " << endl;
    cout << "2. Update Dialysis Session " << endl;
    cout << "3. Delete Dialysis Session " << endl;
    cout << "4. Search Dialysis Session by Patient ID " << endl;
    cout << "5. Display all Dialysis Sessions " << endl;
    cout << "6. Search Dialysis Session by Date" << endl;
    cout << "7. Generate Bill" << endl;
    cout << "8. Exit Dialysis Session " << endl;
    cout << "Choose an option: " << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            addDialysisSession();
        break;
        case 2:
            updateDialysisSession();
        break;
        case 3:
            deleteDialysisSession();
        break;
        case 4:
            searchDialysisSession();
        break;
        case 5:
            displayAllSessions();
        break;
        case 6:
            listByDate();
        break;
        case 7:
            billing("Dialysis.txt");   //Base condition
        break;
        case 8:
            cout << "Exitting program " << endl;
        return;
        default:
            cout << "You have entered invalid choice" << endl;
            break;
    }
    mainMenu();                                                     //Recursive statement
}