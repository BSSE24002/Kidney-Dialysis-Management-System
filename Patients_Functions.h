
#ifndef PATIENTS_FUNCTIONS_H
#define PATIENTS_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Patient{
    int ID;
    string name;
    int age;
    string gender;
    string contactInfo;
};

struct Doctors {
    string name;
    string specialty;
    string workingHours;
};

const int Max_Appointments = 20;


void AddPatientRecord(Patient*& patients , int& count);

void LoadPatientFile(Patient*& patients , int& count);

void DisplayAllPatients(const Patient* patients , int count);

void UpdatePatientRecord(Patient* patients , int count);

void SearchPatient (const Patient* patients , int count);

void LoadDoctorFile (Doctors*& Doctors , int& count);

void Patient_menu(Patient*& patients, int& patientCount);

#endif //PATIENTS_FUNCTIONS_H
