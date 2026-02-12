//
// Created by MPC on 11/8/2024.
//

#ifndef DOCTOR_H
#define DOCTOR_H
#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

// Maximum number of doctors the system can handle
const int MAX_DOCTORS = 100;

// Define a structure to store doctor details
struct Doctor {
    int id;
    string name;
    string specialty;
    string contact;
};

// Class to manage doctor data
struct KidneyCentreManagementSystem {

    Doctor doctors[MAX_DOCTORS]; // Array to store the list of doctors
    int numDoctors;              // Current number of doctors in the system
    const string fileName = "doctors.txt"; // File to save doctor data


    // Constructor to initialize the system and load data from file
    KidneyCentreManagementSystem() : numDoctors(0) {
        loadDoctorsFromFile();
    }

    // Function to add a new doctor
    void addDoctor() {
        if (numDoctors > MAX_DOCTORS) {//kideny centre has limited doctors
            cout << "Maximum doctor limit reached."<<endl;
            return;
        }

        int id;
        string name, specialty, contact;

        // Take input for doctor details
        cout << "Enter doctor ID: ";
        cin >> id;
        cin.ignore();  // Ignore leftover newline character
        cout << "Enter doctor name: ";
        getline(cin, name);
        cout << "Enter doctor specialty: ";
        getline(cin, specialty);
        cout << "Enter doctor contact: ";
        getline(cin, contact);

        // Add the new doctor to the array
        doctors[numDoctors] = Doctor{id, name, specialty, contact};
        numDoctors++;

        cout << "Doctor added successfully!\n";
        saveDoctorsToFile(); // Save updated data to file
    }

    // Function to display all doctors
    void displayDoctors() {
        if (numDoctors == 0) {
            cout << "No doctors available in the system.\n";
            return;
        }

        cout << "List of Doctors:\n";
        cout << "ID\tName\tSpecialty\tContact\n";
        for (int i = 0; i < numDoctors; i++) {
            cout << doctors[i].id << "\t" << doctors[i].name << "\t"
                 << doctors[i].specialty << "\t" << doctors[i].contact << endl;
        }
    }

    // Function to modify a doctor's data
    void modifyDoctor() {
        int id;
        cout << "Enter the doctor ID to modify: ";
        cin >> id;

        // Find the doctor by ID
        bool found = false;
        for (int i = 0; i < numDoctors; i++) {
            if (doctors[i].id == id) {
                found = true;

                string name, specialty, contact;
                cout << "Enter new name (current: " << doctors[i].name << "): ";
                cin.ignore();  // Clear buffer
                getline(cin, name);
                cout << "Enter new specialty (current: " << doctors[i].specialty << "): ";
                getline(cin, specialty);
                cout << "Enter new contact (current: " << doctors[i].contact << "): ";
                getline(cin, contact);

                doctors[i].name = name.empty() ? doctors[i].name : name;
                doctors[i].specialty = specialty.empty() ? doctors[i].specialty : specialty;
                doctors[i].contact = contact.empty() ? doctors[i].contact : contact;

                cout << "Doctor information updated.\n";
                saveDoctorsToFile(); // Save updated data to file
                break;
            }
        }

        if (!found) {
            cout << "Doctor not found with ID: " << id << endl;
        }
    }

    // Function to delete a doctor by ID
    void deleteDoctor() {
        int id;
        cout << "Enter the doctor ID to delete: ";
        cin >> id;

        bool found = false;
        for (int i = 0; i < numDoctors; i++) {
            if (doctors[i].id == id) {
                // Shift all doctors after the deleted one to the left
                for (int j = i; j < numDoctors - 1; j++) {
                    doctors[j] = doctors[j + 1];
                }
                numDoctors--;
                found = true;
                cout << "Doctor deleted successfully.\n";
                saveDoctorsToFile(); // Save updated data to file
                break;
            }
        }

        if (!found) {
            cout << "Doctor not found with ID: " << id << endl;
        }
    }

    // Function to search for a doctor by ID
    void searchDoctor() {
        int id;
        cout << "Enter doctor ID to search: ";
        cin >> id;

        bool found = false;
        for (int i = 0; i < numDoctors; i++) {
            if (doctors[i].id == id) {
                found = true;
                cout << "Doctor found:\n";
                cout << "ID: " << doctors[i].id << " Name: " << doctors[i].name << " Specialty: "
                     << doctors[i].specialty << " Contact: " << doctors[i].contact << endl;
                break;
            }
        }

        if (!found) {
            cout << "Doctor not found with ID: " << id << endl;
        }
    }

private:
    // Function to load doctors from the file
    void loadDoctorsFromFile() {
        ifstream file(fileName);
        if (file.is_open()) {
            int id;
            string name, specialty, contact;

            while (file >> id) {
                file.ignore();  // Ignore the newline character after the ID
                getline(file, name);
                getline(file, specialty);
                getline(file, contact);

                if (numDoctors < MAX_DOCTORS) {
                    doctors[numDoctors] = Doctor{id, name, specialty, contact};
                    numDoctors++;
                }
            }
            file.close();
        }
    }

    // Function to save doctors to the file
    void saveDoctorsToFile() {
        ofstream file(fileName);
        if (file.is_open()) {
            for (int i = 0; i < numDoctors; i++) {
                file << doctors[i].id <<","<< doctors[i].name<<"," << doctors[i].specialty<<"," << doctors[i].contact << endl;
            }
            file.close();
        }
    }
    void readDoctorFromFile() {
        ifstream file(fileName);
        if(file.is_open()) {
            Doctor currentDoctor;//temporary doctor to retrieve data and store at specific index
            string temp;//temporrary strinng to store data from file and pass to specific variable
            getline(file, temp, ',');//getline(data coming from,data going to,break condition)
            if (temp.empty()) {return;}; // Stop if there is an empty line or at the end
            currentDoctor.id = stoi(temp);//stoi means string to integer for conversion or typecasting

            // Read and store Name
            getline(file, currentDoctor.name, ',');

            // Read and store Specialty
            getline(file, currentDoctor.specialty, ',');

            // Read and store Phone Number
            getline(file, currentDoctor.contact);


            // Add the doctor to the array
            doctors[numDoctors] = currentDoctor;
            numDoctors++;
        }

        file.close();


    }
};
#endif //DOCTOR_H
