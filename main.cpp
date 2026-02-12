#include "Patients_Functions.h"
#include "Laboratory1.h"
#include "Appointment.h"
#include "Dialysis.h"
#include "Feedback.h"
#include "staff.h"
#include "billing.h"

using namespace std;

int main(){

    Patient* patients = nullptr;
    int patientCount = 0;

    Doctors* doctors = nullptr;
    int doctorCount = 0;

    int choice;

    LoadPatientFile(patients, patientCount);
    LoadDoctorFile(doctors, doctorCount);

    do {

    cout << "===================================================================================" <<endl;
    cout << "                        Kidney Centre Management System                            " << endl;
    cout << "===================================================================================" <<endl;

    cout << "1. Patients Records" << endl;
    cout << "2. Doctor Information" << endl;
    cout << "3. Staff Information" << endl;
    cout << "4. Schedule Appointment" << endl;
    cout << "5. Dialysis" << endl;
    cout << "6. Laboratory and Pharmacy" << endl;
    cout << "7. Customor Feedback" << endl;
    cout << "8. Finance admin" << endl;
    cout << "9. Exit Program" << endl;
    cout << "Enter option: ";
    cin >> choice;

    switch (choice){

        case 1:
        Patient_menu(patients, patientCount);
        break;

        case 2:
        // Work not complete
        break;
        
        case 3:
        menuOfStaff();   
        break;

        case 4:
        Appointment_menu(patients, patientCount, doctors, doctorCount);
        break;

        case 5:
        mainMenu();
        break;

        case 6:
        mainmenu();
        break;

        case 7:
        feedbackMenu();
        break;

        case 8:
        FinanceMenu();
        break;

        case 9:
        cout << "Exitting Program" << endl;
        cout << "We had a lot of fun." << endl;
        delete[] patients;
        delete[] doctors;
        return 0;

        default:
        cout << "Invalid input" << endl;
        break;

    }




    } while (choice != 8);


}