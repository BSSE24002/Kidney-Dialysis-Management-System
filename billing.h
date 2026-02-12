#ifndef BILLING_H
#define BILLING_H
#include <string>
using namespace std;
struct patientDetails {
    string id;
    string name;
    int age;
    string gender;
    string contact;
    string condition;
};
struct BillInfo {
    patientDetails info;
    string flag;
    string date;
    string time;
    int bedNumber;
    int duration;
    string service;
    double cost;
    string doctorreferral;
    string regularPatients;
};
void FinanceMenu();
void billing(string file);
void enteringDialysisInfo(const string &file1,const string &file2);
void fetchingPatientDetails(BillInfo &bill,const string &file1);
void enteringMedicineInfo(const string &file);
void enteringLabTestInfo(const string &file);
void storingBillInfo(const BillInfo &bill, string typeFlag);
void discountCheck(string doctorReferral, string regularPatients, string id, string date);
void applyDiscount(string file,const double &discount,string id, string date);
void generatingBill(string id);
string checkForRegularPatients(string id);
#endif