//
// Created by dell on 11/11/2024.
//

#ifndef LABORATORY1_H
#define LABORATORY1_H

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;


struct laboratory {
    string test_name,testname,testdate,testtime;
    int test_id,testid,testcode;
    double test_price;
};

struct customerlab {
    string name_book;
    int id_book;
    int cond_book;
};

struct medical {
    string medicine_name,customer_name;
    int medicine_quan,quantity_pur,customer_id;
    double medicine_price;
};

struct password {
    string idd,name_password,CNIC_password,passs;
};

void add_laboratory();
void lab_inventory();
void book_labtest();
void add_medicine();
void medinven();
void purchase_medicine();
void med_sale();
void customerlaboratory_dept();
void customermedical_dept() ;
void customer_dept();
void test_appointment();
void showappointment(int recursion=0);
void display_lab_sales();
void laboratory_department();
void medicine_department();
void admin_dept();
void display_title();
void prelog();
void newacc();
void login();
void mainmenu();


#endif //LABORATORY1_H
