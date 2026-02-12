#include "Patients_Functions.h"

using namespace std;

void AddPatientRecord(Patient*& patients , int& count){

    count++;
    Patient *newPatients = new Patient[count];

    for (int i = 0; i < count - 1; i++){
        newPatients[i] = patients[i];
    }

    Patient newPatient;
    newPatient.ID = count;

    cout << "Enter Patient Name: ";
    while (getline(cin , newPatient.name) , newPatient.name.empty()){
        cout << "Name cannot be empty. Please enter a valid name: ";
    }

    cout << "Enter Patient Age: ";
    while (!(cin >> newPatient.age) || newPatient.age < 0 || newPatient.age > 110){
        cout << "Invalid Input. Please enter a valid age: ";
        cin.clear();
        cin.ignore();
    }
    cin.ignore();

    cout << "Enter Patient Gender (M/F/O): ";
    while ((getline(cin , newPatient.gender) , newPatient.gender.empty()) && newPatient.gender != "M" && newPatient.gender != "F" && newPatient.gender != "O"){
        cout << "Invalid Input. Please enter a valid gender (M/F/O): ";
    }

    cout << "Enter Patient Contact Information (Phone Number): ";
    while (getline(cin , newPatient.contactInfo) , newPatient.contactInfo.empty()){
        cout << "Contact Info cannot be empty. Please enter contact info: ";
    }

    cout << "Patient record added successfully" << endl;

    newPatients[count - 1] = newPatient;

    delete[] patients;
    patients  = newPatients;

    ofstream PatientFile ("PatientRecords.txt" , ios::app);
    
    if (PatientFile.is_open()){
        PatientFile << newPatient.ID << "," << newPatient.name << "," << newPatient.age << "," << newPatient.gender << "," << newPatient.contactInfo  << endl;
        PatientFile.close();
    }
    else {
        cout << "Error occured while opening file" << endl;
    }
}


void LoadPatientFile(Patient*& patients, int& count){
    ifstream patientFile("PatientRecords.txt");

    if (!patientFile.is_open()) {
        cout << "Error opening Patient File" << endl;
        return;
    }

    count = 0;
    string line;
    while (getline(patientFile, line)) {
        count++;
    }
    patientFile.close();

    patients = new Patient[count];

    patientFile.open("PatientRecords.txt");
    int i = 0;
    while (getline(patientFile, line) && i < count) {
        istringstream Patients(line);

        string tempID, tempAge;

        getline(Patients, tempID, ',');
        getline(Patients, patients[i].name, ',');
        getline(Patients, tempAge, ',');
        getline(Patients, patients[i].gender, ',');
        getline(Patients, patients[i].contactInfo, ',');

        patients[i].ID = stoi(tempID);
        patients[i].age = stoi(tempAge);

        i++;
    }
    patientFile.close();
}


void DisplayAllPatients(const Patient *patients, int count){
    if (count == 0) {
        cout << "No patients in the system." << endl;
        return;
    }

    cout << endl << endl << "List of Patients: " << endl;
    cout << "------------------------------" << endl;
    for (int i = 0; i < count; i++) {
        cout << "Patient ID: " << patients[i].ID << endl;
        cout << "Name: " << patients[i].name << endl;
        cout << "Age: " << patients[i].age << endl;
        cout << "Gender: " << patients[i].gender << endl;
        cout << "Contact Info: " << patients[i].contactInfo << endl;
        cout << "------------------------------" << endl;
    }
}


void UpdatePatientRecord(Patient *patients, int count){

    if (count == 0) {
        cout << "No patients records in system." << endl;
        return;
    }

    int searchID;
    cout << "Enter ID of patient to update: ";
    cin >> searchID;
    cin.ignore();

    bool found = false;

    for (int i = 0; i < count; i++) {

        if (patients[i].ID == searchID){
            found = true;
            char choice;

            do {
                cout << "Updating Patient ID: " << patients[i].ID << endl;
                cout << "Press 1. Update Age" << endl;
                cout << "Press 2. Update Contact Information" << endl;
                cout << "Enter choice: ";
                cin >> choice;
                cin.ignore();

                 if (choice == '1') {
                    cout << "Enter new Age: ";
                    while (!(cin >> patients[i].age) || patients[i].age < 0 || patients[i].age > 110) {
                        cout << "Invalid age. Please enter a valid age: ";
                        cin.clear();
                        cin.ignore();
                    }
                    cin.ignore();
                    cout << "Age updated successfully." << endl;
                }
                else if (choice == '2') {
                    cout << "Enter new Contact Information: ";
                    cin.ignore();
                    while (getline(cin, patients[i].contactInfo), patients[i].contactInfo.empty()){
                        cout << "Contact Info cannot be empty. Please enter contact info: ";
                    }
                    cout << "Contact Information updated" << endl;
                }
                else {
                    cout << "Invalid choice" << endl;
                    continue;
                }

                cout << "Would you like to update additional information for this patient? (y/n): ";
                cin >> choice;
                cin.ignore();

            } while (choice == 'Y' || choice == 'y');

            ofstream PatientFile("PatientRecords.txt");
            if (PatientFile.is_open()){

                for (int j = 0; j < count; j++){

                     PatientFile << patients[j].ID << "," << patients[j].name << "," << patients[j].age << "," << patients[j].gender << "," << patients[j].contactInfo << endl;
                }
                
                PatientFile.close();
                cout << "Record updated successfully." << endl;
            }
            else {
                cout << "Error opening file" << endl;
            }
            break;
        }
    }

    if (!found) {
        cout << "Patient not found" << endl;
    }

}


void SearchPatient(const Patient *patients, int count){

    if (count == 0) {
        cout << "No patient records in system" << endl;
        return;
    }

    int searchID;

    cout << "Enter patient ID to search: ";
    cin >> searchID;

    bool found = false;
    for (int i = 0; i < count; i++) {

        if (patients[i].ID == searchID) {
            found = true;

            cout << "Patient Record Found: " << endl;
            cout << "----------------------------------" << endl;
            cout << "Patient ID: " << patients[i].ID << endl;
            cout << "Name: " << patients[i].name << endl;
            cout << "Age: " << patients[i].age << endl;
            cout << "Gender: " << patients[i].gender << endl;
            cout << "Contact Information: " << patients[i].contactInfo << endl;
            cout << "----------------------------------" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Patient not found" << endl;
    }
}


void LoadDoctorFile(Doctors *&doctors, int &count){
    ifstream DoctorFile ("DoctorFile.txt");
    if (!DoctorFile.is_open()){
        cout << "Error opening doctor file" << endl;
        return;
    }

    count = 0;

    string line;
    while (getline (DoctorFile, line)){
        count++;
    }
    DoctorFile.close();

    doctors = new Doctors[count];

    DoctorFile.open("DoctorFile.txt");

    int i= 0;
    while (getline (DoctorFile, line) && i < count){
        istringstream stream (line);

        getline(stream, doctors[i].name, ',');
        getline(stream, doctors[i].specialty, ',');
        getline(stream, doctors[i].workingHours, ',');

        i++;
    }
    DoctorFile.close();
}


void Patient_menu(Patient*& patients, int& patientCount) {

    int choice;

    cout << endl << endl << "==================================" << endl;
    cout << "           Patient Menu          " << endl;
    cout << "==================================" << endl;
    cout << "1. Add Patient Record" << endl;
    cout << "2. Display All Patients" << endl;
    cout << "3. Update Patient Record" << endl;
    cout << "4. Search Patient Record" << endl;
    cout << "5. Go Back to Main Menu" << endl;
    cout << "Enter your choice: ";

    cin >> choice;
    cin.ignore();

    switch (choice) {

        case 1:
            AddPatientRecord(patients, patientCount);
            break;

        case 2:
            DisplayAllPatients(patients, patientCount);
            break;

        case 3:
            UpdatePatientRecord(patients, patientCount);
            break;

        case 4:
            SearchPatient(patients, patientCount);
            break;

        case 5:
            cout << "Returning to the main menu." << endl;
            return;
        
        default:
        
            cout << "Invalid choice. Please try again." << endl;
    }

    Patient_menu(patients, patientCount);
}

