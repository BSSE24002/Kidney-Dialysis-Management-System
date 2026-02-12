//
// Created by mwar9 on 11/17/2024.
//

#include "Appointment.h"

int TimeToMinutes(const string &time) {
    int hours = stoi(time.substr(0, 2));
    int minutes = stoi(time.substr(2, 2));

    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        cout << "Invalid Input" << endl;
    }

    return hours * 60 + minutes;
}

bool isDoctorAvailable(const string &workingHours, const string &appointmentTime) {
    string appointmentTimeFormatted = appointmentTime.substr(0, 2) + ":" + appointmentTime.substr(2, 2);

    istringstream stream(workingHours);
    string startTime, endTime;

    getline(stream, startTime, '-');
    getline(stream, endTime);

    return appointmentTimeFormatted >= startTime && appointmentTimeFormatted <= endTime;
}

void ScheduleAppointment(const Patient *patients, int patientCount, const Doctors* doctors, int doctorCount) {
    int patientID;
    string doctorName, appointmentTime, appointmentDate;

    cout << "Enter patient ID: ";
    cin >> patientID;

    const Patient* selectedPatient = nullptr;
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].ID == patientID) {
            selectedPatient = &patients[i];
            break;
        }
    }

    if (!selectedPatient) {
        cout << "Patient not found." << endl;
        return;
    }

    cout << "Enter doctor name: ";
    cin.ignore();
    getline(cin, doctorName);

    const Doctors* selectedDoctor = nullptr;
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].name == doctorName) {
            selectedDoctor = &doctors[i];
            break;
        }
    }

    if (!selectedDoctor) {
        cout << "Doctor not found." << endl;
        return;
    }

    bool slotAvailable = false;
    while (!slotAvailable) {
        cout << "Enter appointment date (DDMMYYYY): ";
        cin >> appointmentDate;
        cout << "Enter appointment time (HHMM, 24-hour format): ";
        cin >> appointmentTime;

        if (!isDoctorAvailable(selectedDoctor->workingHours, appointmentTime)) {
            cout << "Doctor " << doctorName << " is not available at " << appointmentTime << ". Working hours are " << selectedDoctor->workingHours << endl;
            continue;
        }

        ifstream appointmentFile("Appointments.txt");
        bool conflictFound = false;
        if (appointmentFile.is_open()) {
            string line;
            while (getline(appointmentFile, line)) {
                if (line.find(appointmentDate) != string::npos && line.find(appointmentTime) != string::npos && line.find(selectedDoctor->name) != string::npos) {
                    cout << "An appointment already exists on " << appointmentDate << " at " << appointmentTime << ". Please choose a different date or time." << endl;
                    conflictFound = true;
                    break;
                }
            }
            appointmentFile.close();
        }

        if (!conflictFound) {
            slotAvailable = true;
        }
    }

    appointmentDate = appointmentDate.substr(0, 2) + "/" + appointmentDate.substr(2, 2) + "/" + appointmentDate.substr(4, 4);

    ofstream appointmentFile("Appointments.txt", ios::app);
    if (!appointmentFile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    appointmentFile << selectedPatient->ID << "," << selectedPatient->name << "," << selectedDoctor->name 
                    << "," << appointmentDate << "," << appointmentTime << endl;
    cout << "Appointment scheduled." << endl;

    appointmentFile.close();
}

void DisplayAllAppointments() {
    ifstream appointmentFile("Appointments.txt");

    if (!appointmentFile.is_open()) {
        cout << "Error opening Appointments file" << endl;
        return;
    }

    string line;

    cout << "List of Appointments:" << endl;
    cout << "------------------------------" << endl;

    while (getline(appointmentFile, line)) {
        stringstream ss(line);
        string patientID, patientName, doctorName, appointmentDate, appointmentTime;
        
        getline(ss, patientID, ',');
        getline(ss, patientName, ',');
        getline(ss, doctorName, ',');
        getline(ss, appointmentDate, ',');
        getline(ss, appointmentTime, ',');

        cout << "Patient ID: " << patientID << endl;
        cout << "Name: " << patientName << endl;
        cout << "Doctor Name: " << doctorName << endl;
        cout << "Appointment Date: " << appointmentDate << endl;
        cout << "Appointment Time: " << appointmentTime << endl;
        cout << "------------------------------" << endl;
    }

    appointmentFile.close();
}


void Appointment_menu(const Patient* patients, int patientCount, Doctors*& Doctors, int& doctorCount) {
   
   int choice;

    cout << endl << endl << "----- Appointment Menu -----" << endl;
    cout << "1. Schedule Appointment" << endl;
    cout << "2. Display All Appointments" << endl;
    cout << "3. Go Back to Main Menu" << endl;
    cout << "Enter your choice: ";

    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            ScheduleAppointment(patients, patientCount, Doctors, doctorCount);
            break;

        case 2:
            DisplayAllAppointments();
            break;

        case 3:
            cout << "Returning to the main menu." << endl;
            return;

        default:
            cout << "Invalid choice. Please try again." << endl;
    }

    Appointment_menu(patients, patientCount, Doctors, doctorCount);
}
