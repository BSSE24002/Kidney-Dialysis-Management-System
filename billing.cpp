#include "billing.h"
#include "Dialysis.h"
#include <iostream>
#include<iomanip>
#include <fstream>
#include <sstream>
using namespace std;
double totalRevenue = 0.0;
static int bill_count = 0;
double discount=0.0;
bool openFIle(ifstream &file, const string &filename) {
    file.open(filename);
    if (!file) {
        cout << "Error: Could not open file " << filename << "!\n";
        return false;
    }
    return true;
}
void applyDiscount(string file,const double &discount,string id, string date){
    int is_found=0;
    BillInfo bill;
    ifstream openFile;
    if (!openFIle(openFile, file)) return;
    ofstream openFile2("temporary.txt");
    string line,ageString,costString;
    while (getline(openFile, line)) {
        stringstream ss(line);
        getline(ss,bill.flag,',');
        if(bill.flag=="D"){
            getline(ss,bill.info.id,',');
            if (id == bill.info.id) {
                getline(ss,bill.info.name,',');
                getline(ss,ageString,',');
                getline(ss,bill.info.gender,',');
                getline(ss,bill.info.contact,',');
                bill.info.age = stoi(ageString);
                getline(ss,bill.date,',');
                getline(ss,bill.doctorreferral,',');
                getline(ss,bill.service,',');
                getline(ss,costString,',');
                bill.cost=stod(costString);
                if(bill.date==date){
                    bill.cost-=bill.cost*discount;
                    is_found++;
                    openFile2<<bill.flag<<","<<bill.info.id<< "," << bill.info.name << ",";
                    openFile2<<bill.info.age<< "," << bill.info.gender<<"," <<bill.info.contact <<","<<bill.date<<",";
                    openFile2<<bill.doctorreferral<<","<<bill.service<<","<<bill.cost<<"\n";
                }
                else{
                    openFile2<<line<<"\n";
                }
            }
            else{
                openFile2<<line<<"\n";
            }
        }
        else{
            openFile2<<line<<"\n";
        }
    }
    openFile.close();
    openFile2.close();
    if(is_found!=0){
        remove(file.c_str());  
        rename("temporary.txt", file.c_str());
    }
    else if(is_found==0){
        cout<<"ID not found."<<endl;
        remove("temporary.txt");
    }
}
void discountCheck(string doctorReferral, string regularPatients, string id, string date) {
    cout << "=============================================\n";
    cout << "              Discount Section\n";
    cout << "=============================================\n";
    cout<<"Discount Options:\n";
    cout << "1. Doctor's Referral (10% off)\n";
    cout << "2. Regular Patient (15% off)\n";
    double discountPercentage=0.0;
    if(doctorReferral=="YES"&&regularPatients=="NO"){
        discountPercentage=0.10;
        cout<<"You are eligible for doctor's referral discount!\n";
        applyDiscount("BillDetail.txt",discountPercentage,id,date);
        cout<<"Your Bill is as follows:\n";
    }
    else if(doctorReferral=="NO"&&regularPatients=="YES"){
        discountPercentage=0.15;
        cout<<"You are eligible for regular Patients discount!\n";
        applyDiscount("BillDetail.txt",discountPercentage,id,date);
        cout<<"Your Bill is as follows:\n";
    }
    else if(doctorReferral=="YES"&&regularPatients=="YES"){
        discountPercentage=0.15;
        cout<<"You are eligible for both doctor's referral discount and regular Customer discount!\n";
        cout<<"According to our Policy only the discount with greater percentage (Regular Customer Discount 15%off) will be applicable!\n";
        applyDiscount("BillDetail.txt",discountPercentage,id,date);
        cout<<"Your Bill is as follows:\n";
    }
    else if(doctorReferral=="NO"&&regularPatients=="NO"){
        discountPercentage=0.0;
        cout<<"No discount applicable!\n";
        applyDiscount("BillDetail.txt",discountPercentage,id,date);
        cout<<"Your Bill is as follows:\n";
    }
    discount=discountPercentage;
}
string checkForRegularPatients(string id){
    BillInfo bill;
    int count=0;
    string line, type;
    ifstream openFile("BillDetail.txt");
    while (getline(openFile, line)) {
        stringstream ss(line);
        getline(ss, type, ',');
        if (type == "D"){
            getline(ss, bill.info.id, ',');
            if(id==bill.info.id){
                count++;
            }
        }
    }
    if(count>=3){
        return "YES";
    }
    else
        return "NO";
}
void generatingBill(string id) {
    bool found = false;
    BillInfo bill;
    ifstream openFile("BillDetail.txt");
    string line, prefix, ageString, costString;

    while (getline(openFile, line)) {
        stringstream ss(line);
        getline(ss, prefix, ',');
        if (prefix == "D") {
            getline(ss, bill.info.id, ',');
            getline(ss, bill.info.name, ',');
            getline(ss, ageString, ',');
            bill.info.age = stoi(ageString);
            getline(ss, bill.info.gender, ',');
            getline(ss, bill.info.contact, ',');
            getline(ss, bill.date, ',');
            getline(ss, bill.doctorreferral, ',');
            getline(ss, bill.service, ',');
            getline(ss, costString, ',');
            bill.cost = stod(costString);
        }
        else if (prefix == "L") {
            getline(ss, bill.info.id, ',');
            getline(ss, bill.info.name, ',');
            getline(ss, bill.date, ',');
            getline(ss, bill.time, ',');           
            getline(ss, bill.service, ',');
            getline(ss, costString, ',');
            bill.cost = stod(costString);
        } 
        else if (prefix == "M") {
            getline(ss, bill.info.id, ',');
            getline(ss, bill.info.name, ',');          
            getline(ss, bill.service, ',');
            getline(ss, costString, ',');
            bill.cost = stod(costString);
        }
        if (id == bill.info.id) {
            found = true;
            cout<<"\n";
            cout<<"\n";
            cout << "============================== KIDNEY CENTER ==============================\n";
            cout << "                             BILLING STATEMENT\n";
            cout << "==========================================================================\n";
            cout << left << setw(20) << "ID:" << bill.info.id << "\n";
            cout << left << setw(20) << "Name:" << bill.info.name << "\n";
            if (prefix == "D") {
                cout << left << setw(20) << "Age:" << bill.info.age << "\n";
                cout << left << setw(20) << "Gender:" << bill.info.gender << "\n";
                cout << left << setw(20) << "Contact:" << bill.info.contact << "\n";
                cout << "--------------------------------------------------------------------------\n";
                cout << left << setw(20) << "Service:" << bill.service << "\n";
                cout << left << setw(20) << "Date of Service:" << bill.date << "\n";
                cout << left << setw(20) << "Discount:" << discount*100 << "%" << "\n";
            } 
            if(prefix=="L"){
                cout << "--------------------------------------------------------------------------\n";
                cout << left << setw(20) << "Service:" << bill.service << "\n";
                cout << left << setw(20) << "Date of Service:" << bill.date << "\n";
                cout << left << setw(20) << "Time of Service:" << bill.time << "\n";
            }
            if(prefix=="M"){
                cout << left << setw(20) << "Name of Medicine:" << bill.service << "\n";

            }
            cout << "--------------------------------------------------------------------------\n";
            cout << fixed << setprecision(2);
            cout << right << setw(20) << "Total Cost: $" << setw(10) << bill.cost << "\n";
            totalRevenue+=bill.cost;
            cout << "==========================================================================\n";
            cout << "                         Thank you for choosing us!\n";
            cout << "==========================================================================\n";
            cout<<"\n";
            cout<<"\n";
            if(prefix=="D"){
                automaticDelete(bill.info.id);
            }
            break;
        }
    }

    if (!found) {
        cout << "ID not found!\n";
    }
}
void storingBillInfo(const BillInfo &bill, string typeFlag) {
    ofstream file("BillDetail.txt", ios::app);
    file << typeFlag << ",";
    file << bill.info.id << "," << bill.info.name << ",";
    if (typeFlag == "D") {
        file << bill.info.age << "," << bill.info.gender << "," << bill.info.contact << "," << bill.date << "," << bill.doctorreferral << ",";
    }
    else if(typeFlag=="L"){
        file << bill.date << "," << bill.time << ",";
    }
    file << bill.service << "," << bill.cost << "\n";
    file.close();
}
void fetchingPatientDetails(BillInfo &bill,const string &file1){
    patientDetails patient;
    ifstream openFile(file1);
    string line,ageString;
    while (getline(openFile, line)) {
        stringstream ss(line);
        getline(ss,patient.id,',');
        getline(ss,patient.name,',');
        getline(ss,ageString,',');
        getline(ss,patient.gender,',');
        getline(ss,patient.contact,',');
        patient.age = stoi(ageString);
        if(patient.id==bill.info.id){
            bill.info.name=patient.name;
            bill.info.age=patient.age;
            bill.info.gender=patient.gender;
            bill.info.contact=patient.contact;
            bill.flag="D";
            int doctorreferral;
            while(true){
                cout<<"Do patient have a referral letter or not?\n";
                cout<<"Press 1 for YES.\n";
                cout<<"Press 2 for NO.\n";
                cout<<"Enter your choice: ";
                cin>>doctorreferral;
                switch(doctorreferral){
                    case 1:
                        bill.doctorreferral="YES";
                        break;
                    case 2:
                        bill.doctorreferral="NO";
                        break;
                    default:
                        cout<<"You entered an invalid choice!\n";
                }
                break;
            }
            storingBillInfo(bill,bill.flag);
            bill.regularPatients=checkForRegularPatients(bill.info.id);
            discountCheck(bill.doctorreferral,bill.regularPatients,bill.info.id,bill.date);
            generatingBill(patient.id);
        }
    }
}
void enteringDialysisInfo(const string &patientFile, const string &dialysisFile) {  
    BillInfo bill;
    ifstream openFile(dialysisFile);
    string line;
    string flag, idCheck, id, date, bed, duration, costString;
    double cost;
    cout << "Enter the ID of the Patient whose bill you want to generate: ";
    cin >> idCheck;
    while (getline(openFile, line)) {
        stringstream ss(line);
        ss >> flag >> id >> date >> bed >> duration >> costString;
        cost = stod(costString);         
        if (cost == 50000) {
            bill.service = "Haemodialysis";
        } else if (cost == 100000) {
            bill.service = "Peritoneal Dialysis";
        } else {
            continue; 
        }
        bill.info.id = id;
        bill.date = date;
        bill.cost = cost;
        if (idCheck == bill.info.id) {
            fetchingPatientDetails(bill, patientFile); 
            return;
        }
    }
    cout << "Patient ID not found.\n";
}
void enteringMedicineInfo(const string &file) {
    BillInfo bill;
    ifstream openFile(file);
    string line, quantityString, costString;
    getline(openFile, line);
    stringstream ss(line);
    getline(ss, bill.flag, ',');
    getline(ss, bill.info.id, ','); 
    getline(ss, bill.service, ','); 
    getline(ss, quantityString, ','); 
    getline(ss, costString, ','); 
    getline(ss, bill.info.name, ',');     
    int quantity = stoi(quantityString);
    double costPerUnit = stod(costString);
    bill.cost = quantity * costPerUnit; 
    storingBillInfo(bill,bill.flag);
    generatingBill(bill.info.id);
    openFile.close();
}

void enteringLabTestInfo(const string &file) {
    BillInfo bill;
    ifstream openFile(file);
    string line, costString;
    getline(openFile, line);
    stringstream ss(line);
    getline(ss, bill.flag, ',');
    getline(ss, bill.info.id, ',');
    getline(ss, bill.service, ',');
    getline(ss, costString, ',');
    getline(ss, bill.info.name, ',');
    getline(ss, bill.date, ',');
    getline(ss, bill.time, ',');
    bill.cost = stod(costString);
    storingBillInfo(bill,bill.flag);
    generatingBill(bill.info.id);
    openFile.close();
}

void billing(string file) {
    int x;
    if(file=="Dialysis.txt"){
        enteringDialysisInfo("PatientRecords.txt",file);
        bill_count++;
    }
    else if(file=="med_for_reheem.txt"){
        enteringMedicineInfo(file);
        bill_count++;
    }
    else if(file=="lab_for_raheem.txt"){
        enteringLabTestInfo(file);
        bill_count++;
    }
    else
        cout << "Invalid option!\n";
}
void FinanceMenu() {
    cout << "\n=============================================\n";
    cout << "                   Finance\n";
    cout << "=============================================\n";
    cout << "1. Show Total Bills Generated\n";
    cout << "2. Show Total Revenue\n";
    cout << "3. Exit\n";
    cout << "=============================================\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice) {

        case 1:
            cout << "Total bills generated so far: " << bill_count << "\n";
            FinanceMenu();
            break;
        case 2:
            cout << "Total revenue so far: $" << totalRevenue << "\n";
            FinanceMenu();
            break;
        case 3:
            cout << "Thank you.\n";
            return;

        default:
            cout << "Invalid choice! Please try again.\n";
            FinanceMenu();
    }
}