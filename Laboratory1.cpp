//
// Created by dell on 11/11/2024.
//

#include "Laboratory1.h"
#include "billing.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
laboratory * pointer3 = new laboratory[100];  //using pointer array of size 100 here
int again=0;
void add_laboratory() {  //This function will add a new lab test here only for admin
  cout<<"==================================================================================="<<endl;
  cout<<"                               ADD A LABORATORY TEST                               "<<endl;
  cout<<"==================================================================================="<<endl;
  ofstream labfile;    //Writing on file
  labfile.open("labinventory.txt",ios::app);
  if(!labfile) {
    cout<<"Error in opening file"<<endl;
    return;
  }
  cout<<"Enter Test name: ";
  cin>>pointer3[again].test_name;
  cout<<"Enter Test ID: ";
  cin>>pointer3[again].test_id;
  cout<<"Enter Test Price: $";
  cin>>pointer3[again].test_price;
  labfile<<pointer3[again].test_id<<","<<pointer3[again].test_price<<","<<pointer3[again].test_name<<endl;
  labfile.close();
  again++;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void lab_inventory() {  //Function that will show all the tests available
  cout<<"==================================================================================="<<endl;
  cout<<"                                LABORATORY INVENTORY                               "<<endl;
  cout<<"==================================================================================="<<endl;
  ifstream labfile1;   //Reading file on which wwe have added the laboratory tests
  labfile1.open("labinventory.txt");
  if(!labfile1) {
    cout<<"Error in opening file"<<endl;
    return;
  }
  cout<<endl;
  for(int i=0;i<100;i++) {  //using for loop to diplay the data on each pointer array
    while(labfile1>>pointer3[i].test_id) {
      labfile1.ignore(1, ',');
      labfile1>>pointer3[i].test_price;
      labfile1.ignore(1, ',');
      labfile1>>pointer3[i].test_name;
      cout<<"Test code: "<<pointer3[i].test_id<<" Test name: "<<pointer3[i].test_name<<" Test price: $"<<pointer3[i].test_price<<endl<<endl;
    }
  }
  cout<<endl;
  labfile1.close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void display_lab_sales() {
  ifstream sales_lab_file("labtotalsales.txt");
  if(!sales_lab_file) {
    cout<<"Error in opening file"<<endl;
    return;
  }
  cout<<"==================================================================================="<<endl;
  cout<<"                            TOTAL LABORATORY SALES                                 "<<endl;
  cout<<"==================================================================================="<<endl;
  double labtestprice[100];
  int sum=0;
  int total=0;
  for(int i=0;i<100;i++) {
    while(sales_lab_file>>labtestprice[i]) {
      cout<<endl<<"Sale No "<<total+1<<": $"<<labtestprice[i]<<endl;
      total++;
      sum=sum+labtestprice[i];
    }
  }
  cout<<endl<<"TOTAL SALES: $"<<sum<<endl<<endl;
  sales_lab_file.close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void  book_labtest() { //Function to book a lab appointment and save appointment to file
  ifstream labfile; //Reading file
  labfile.open("labinventory.txt");
  if(!labfile) {
    cout<<"Error in opening file"<<endl;
    return;
  }
  ofstream labfileappointment;  //writing file
  labfileappointment.open("labapp.txt",ios::app);
  if(!labfileappointment) {
    cout<<"Error in opening file"<<endl;
    return;
  }
  ofstream raheem2;  //writing file
  raheem2.open("lab_for_raheem.txt");
  if(!raheem2) {
    cout<<"Error in opening file"<<endl;
    return;
  }
  ofstream labtotalsales("labtotalsales.txt",ios::app);  //writing file
  if(!labtotalsales) {
    cout<<"Error in opening file"<<endl;
    return;
  }
  cout<<"==================================================================================="<<endl;
  cout<<"                             BOOK A LABORATORY TEST                                "<<endl;
  cout<<"==================================================================================="<<endl;
  int repeater2=0;
  string testname,testdate,testtime;
  int testid,testcode;
  cout<<"Enter your name: ";
  cin>>testname;
  cout<<"Enter your unique id: ";
  cin>>testid;
  cout<<"Enter the test code: ";
  cin>>testcode;
  cout<<"Enter test date (DD/MM/YYYY): ";
  cin>>testdate;
  cout<<"Enter test time (hh:mm(AM/PM)): ";
  cin>>testtime;
  for(int i=0;i<100;i++) {  //using for loop and chceking if my lab test code matches with the lab test code eneterd by the user then book an appointment against the user's id
    while(labfile>>pointer3[i].test_id) {
      labfile.ignore(1, ',');
      labfile>>pointer3[i].test_price;
      labfile.ignore(1, ',');
      labfile>>pointer3[i].test_name;
      if(testcode == pointer3[i].test_id) {
        pointer3[i].testname=testname;
        pointer3[i].testid=testid;
        pointer3[i].testdate=testdate;
        pointer3[i].testtime=testtime;
        cout<<endl<<"Test Appointment Booked suceessfully!"<<endl<<endl;
        labfileappointment<<pointer3[i].testid<<","<<pointer3[i].test_price<<","<<pointer3[i].test_id<<","<<pointer3[i].testname<<","<<pointer3[i].test_name<<","<<pointer3[i].testdate<<","<<pointer3[i].testtime<<endl;
        raheem2<<"L,"<<pointer3[i].testid<<","<<pointer3[i].test_name<<","<<pointer3[i].test_price<<","<<testname<<","<<testdate<<","<<testtime<<endl;  //Data for biiling section to prepare a bill for customer
        labtotalsales<<pointer3[i].test_price<<endl;
        //There will be fuction for billing given by raheem
        billing("lab_for_raheem.txt");
        repeater2++;
      }
      }
    }
        if(repeater2==0) {
        cout<<endl<<"Test Appointment Not booked!"<<endl<<endl;
  }
  labtotalsales.close();
  raheem2.close();
  labfileappointment.close();
  labfile.close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void display_title() {
  cout<<"==================================================================================="<<endl;
  cout<<"                           DISPLAYING ALL APPOINTMENTS                             "<<endl;
  cout<<"==================================================================================="<<endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//using recursion in this function
laboratory pointer4[100];
void showappointment(int recursion) {   //Function that will show all appointments to the admin and using recursion in this function so that it will call the function repeatidly and increment the value of recursion by 1 and read all data in the pointer array and diaplay it to user
  if(recursion>=100) {  //it shows the first 100 values otherwise it terminates
    cout<<endl<<"Maximum appointments are displayed!"<<endl<<endl;
    return;
  }
  static ifstream lab_show_app("labapp.txt",ios::in);  //using static for reading file here because here function is calling again and again to avoid initialization every time we use static
  if(!lab_show_app) {
    cout<<"Error in opening file"<<endl;
    return;
  }

    if(lab_show_app>>pointer4[recursion].testid) {  //Reading file by using if because we are incrementing the array size
      lab_show_app.ignore(1, ',');
      lab_show_app>>pointer4[recursion].test_price;
      lab_show_app.ignore(1, ',');
      lab_show_app>>pointer4[recursion].test_id;
      lab_show_app.ignore(1, ',');
      getline(lab_show_app,pointer4[recursion].testname,',');
      getline(lab_show_app,pointer4[recursion].test_name,',');
      getline(lab_show_app,pointer4[recursion].testdate,',');
      getline(lab_show_app,pointer4[recursion].testtime);
      cout<<endl<<"Appointment No "<<recursion+1<<endl<<endl;
      cout<<"Name:      "<<pointer4[recursion].testname<<endl;
      cout<<"ID:        "<<pointer4[recursion].testid<<endl;
      cout<<"Test:      "<<pointer4[recursion].test_name<<endl;
      cout<<"Test ID:   "<<pointer4[recursion].test_id<<endl;
      cout<<"Price:     $"<<pointer4[recursion].test_price<<endl;
      cout<<"Date:      "<<pointer4[recursion].testdate<<endl;
      cout<<"Time:      "<<pointer4[recursion].testtime<<endl;
      showappointment(recursion+1);  //recursion and calling the function again and again
    }
  else {
    cout<<endl;
    lab_show_app.close();
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_appointment() {  //Function allow user to search his/her appointment by his id
  cout<<"==================================================================================="<<endl;
  cout<<"                              CUSTOMER APPOINTMENTS                                "<<endl;
  cout<<"==================================================================================="<<endl;
  ifstream check_labfile_app; //Reading from file
  check_labfile_app.open("labapp.txt",ios::in);
  if(!check_labfile_app) {
    cout<<"Error in opening file"<<endl;
    return;
  }
  int repeater=0;
  int num55;
  cout<<"Enter your unique id: ";
  cin>>num55;

  for(int i=0;i<100;i++) {   //using for loop and checking if idd matches with the idd in file then shows the appointment info other wise not
    while(check_labfile_app>>pointer3[i].testid) {
      check_labfile_app.ignore(1, ',');
      check_labfile_app>>pointer3[i].test_price;
      check_labfile_app.ignore(1, ',');
      check_labfile_app>>pointer3[i].test_id;
      check_labfile_app.ignore(1, ',');
      getline(check_labfile_app,pointer3[i].testname,',');
      getline(check_labfile_app,pointer3[i].test_name,',');
      getline(check_labfile_app,pointer3[i].testdate,',');
      getline(check_labfile_app,pointer3[i].testtime);
      if(num55 == pointer3[i].testid) {
        cout<<endl<<"Test Appointment found!"<<endl;
        cout<<endl<<"Name:      "<<pointer3[i].testname<<endl;
              cout<<"ID:        "<<pointer3[i].testid<<endl;
              cout<<"Test:      "<<pointer3[i].test_name<<endl;
              cout<<"Test ID:   "<<pointer3[i].test_id<<endl;
              cout<<"Price:     $"<<pointer3[i].test_price<<endl;
              cout<<"Date:      "<<pointer3[i].testdate<<endl;
              cout<<"Time:      "<<pointer3[i].testtime<<endl<<endl;
        repeater++;
      }
    }
  }
      if (repeater == 0) {
        cout<<endl<<"Test Appointment not found!"<<endl<<endl;
      }
  check_labfile_app.close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
medical * pointer2 = new medical[100];
int rep=0;
void add_medicine(){  //Function to add a new medicine option for admin only
  cout<<"==================================================================================="<<endl;
  cout<<"                                 ADD A NEW MEDICINE                                "<<endl;
  cout<<"==================================================================================="<<endl;
  ofstream medicinefile;
  medicinefile.open("medinventory.txt",ios::app);  //Using append so that it will write new medicine at the end of file
  if(!medicinefile) {
    cout<<endl<<"Error in opening file"<<endl;
    return;
  }
  cout<<"Enter Medicine name: ";
  cin>>pointer2[rep].medicine_name;
  cout<<"Enter Medicine quantity: ";
  cin>>pointer2[rep].medicine_quan;
  cout<<"Enter Medicine price: $";
  cin>>pointer2[rep].medicine_price;
  medicinefile<<pointer2[rep].medicine_quan<<","<<pointer2[rep].medicine_price<<","<<pointer2[rep].medicine_name<<endl; //writing data on file
  medicinefile.close();
  rep++;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void medinven() {  //Function that will show all medicines in the inventory
  cout<<"==================================================================================="<<endl;
  cout<<"                                MEDICINE INVENTORY                                 "<<endl;
  cout<<"==================================================================================="<<endl;
  ifstream openfileofmedinventory;   //Reading data from file
  openfileofmedinventory.open("medinventory.txt");
  if(!openfileofmedinventory) {
    cout<<endl<<"Error in opening file"<<endl;
    return;
  }
  cout<<endl;
    for(int i=0;i<100;i++){  //using for loop so it runs untill 100 size and displays every medicine
  while(openfileofmedinventory>>pointer2[i].medicine_quan) {  //using while so that it reads data till end of file
      openfileofmedinventory.ignore(1, ',');
      openfileofmedinventory>>pointer2[i].medicine_price;
      openfileofmedinventory.ignore(1, ',');
      openfileofmedinventory>>pointer2[i].medicine_name;
      cout<<"Medicine name: "<<pointer2[i].medicine_name<<" Medicine quantity: "<<pointer2[i].medicine_quan<<" Medicine price: $"<<pointer2[i].medicine_price<<endl<<endl; //Displaying data in inventory to the terminal
    }
  }
  cout<<endl;
  openfileofmedinventory.close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void purchase_medicine() {  //Function allow user to purchase medicine and then also overwrite the quantity
  cout<<"==================================================================================="<<endl;
  cout<<"                                PURCHASE A MEDICINE                                "<<endl;
  cout<<"==================================================================================="<<endl;
  ifstream medinven;   //Reading the medinventory
  medinven.open("medinventory.txt");
  if(!medinven) {
    cout<<endl<<"Error in opening file"<<endl;
    return;
  }
  int i=0;   //initializing i so that we will read all data from the medinventory
  while(medinven>>pointer2[i].medicine_quan) {  //using while to read till end of file
       medinven.ignore(1, ',');
       medinven>>pointer2[i].medicine_price;
       medinven.ignore(1, ',');
       medinven>>pointer2[i].medicine_name;
       i++;
  }
  medinven.close();
  string medinp,name_cust;
  int id_cust;
  double medquaninp,medpriceinp;
  cout<<endl<<"*** Purchase Medicine ***"<<endl<<endl;   //taking input from customer
  cout<<"Enter your name: ";
  cin>>name_cust;
  cout<<"Enter your unique id: ";
  cin>>id_cust;
  cout<<"Purchase Medicine by name: ";
  cin>>medinp;
  cout<<"Enter the quantity: ";
  cin>>medquaninp;
  bool match = false;
  for(int j=0;j<i;j++){                              //using for loop and it will runs untill j is less than i means that i is the number of medicines in inventory it is used so that it will check every medicine
    if(pointer2[j].medicine_name == medinp){        //comparing name enetered by user with name of medicine in the file
      if(pointer2[j].medicine_quan >= medquaninp){  //checking the quantity entered by the user is available or not
        pointer2[j].medicine_quan = pointer2[j].medicine_quan - medquaninp;       //if available it minus the quantity purchased by the user
        medpriceinp = pointer2[j].medicine_price * medquaninp;                   //Then multiply the price per medicine by its quantity to calculate the price
        ofstream opensalesfile("medsales.txt",ios::app);                //writing data
        ofstream raheem("med_for_reheem.txt");                 //writing data
        if(opensalesfile && raheem) {                                           //if these both files open then it will write data on files
        opensalesfile<<medpriceinp<<endl;                                //Data for Total sales file
        raheem<<"M,"<<id_cust<<","<<pointer2[j].medicine_name<<","<<medquaninp<<","<<pointer2[j].medicine_price<<","<<name_cust<<endl; //Data for Billing section to prepare a bill for customer
        opensalesfile.close();
        raheem.close();
       }
        cout<<endl<<"Medicine found in inventory & succesfully purchased!"<<endl<<endl;  //if condition satisfy it shows this msg
        billing("med_for_reheem.txt");
        match = true; //update the match to true
         }
      else{  //else if condition is not satisfied it shows this msg
        cout<<endl<<"Sorry!!! we have Insufficient stock of medicine "<<pointer2[j].medicine_name<<" Available quantity is: "<<pointer2[j].medicine_quan<<endl<<endl;
        }
        break;
        }
      }
      if(!match){  //condition that if match is not true then it shows this msg
        cout<<endl<<"                      Medicine not found in inventory"<<endl<<endl;
      }

      ofstream mediacarefile("medinventory.txt");  //Write updated quantity on file after subtracting from the quantity purchased by the customer
      if(!mediacarefile) {
        cout<<endl<<"Error in opening file"<<endl;
        return;
        }
      for(int j=0;j<i;j++){   //using another for loop and it will run till the size of medicines in inventory and update the specific medicine quantity in file
        mediacarefile<<pointer2[j].medicine_quan<<","<<pointer2[j].medicine_price<<","<<pointer2[j].medicine_name<<endl;
        }
        mediacarefile.close();

  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void med_sale() {  //Function that shows total medicine sales
  cout<<"==================================================================================="<<endl;
  cout<<"                                TOTAL MEDICINE SALES                               "<<endl;
  cout<<"==================================================================================="<<endl;
  ifstream salesfile;    //Reading data from salesfile
  salesfile.open("medsales.txt");
  if(!salesfile) {
    cout<<endl<<"Error in opening file"<<endl;
    return;
  }
  double meddprice[100];
  double sum=0;
  int num_count=1;
  for(int i=0;i<100;i++) {          //using for loop upto 100 size of array
    while(salesfile>>meddprice[i]) {  //shows the 100 sales if exist
      cout<<endl<<"Sale No "<<num_count<<": $"<<meddprice[i]<<endl;
      num_count++;
      sum+=meddprice[i];
    }
  }
  cout<<endl<<"TOTAL SALES: $"<<sum<<endl<<endl;   //Sum of all sales
  salesfile.close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void customerlaboratory_dept() {  //This function shows customer medicine department menu
  int n7;
  do {
    cout<<"Press '1' to View all tests available."<<endl;
    cout<<"Press '2' to Book a laboratory test."<<endl;
    cout<<"Press '3' to see your test appointment."<<endl;
    cout<<"Press '0' to Exit."<<endl;
    cout<<"----------------------------------------------------------------------------------- "<<endl;
    cout<<"Enter your choice (0-3): ";
    cin>>n7;
    switch(n7){
      case 1:
        lab_inventory();  //Function that shows all inventory of laboratory tests available
      break;
      case 2:
        book_labtest();  //Function that allow user to book a laboratory test appointment
      break;
      case 3:
        test_appointment();  //Function that allow user to view his/her appointment by searching their id and then will be able to see all their previous appointments
      break;
      case 0:
        cout<<endl<<"Exiting the program....."<<endl<<endl;
      return customer_dept();
      default:
        cout<<endl<<"Invalid Choice"<<endl<<endl;
    }
  }while(n7!=3);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void customermedical_dept() { //This function shows customer medicine department menu
  int n6;
  do {
    cout<<"Press '1' to View medicines available."<<endl;
    cout<<"Press '2' to Purchase medicine."<<endl;
    cout<<"Press '0' to Exit."<<endl;
    cout<<"----------------------------------------------------------------------------------- "<<endl;
    cout<<"Enter your choice (0-3): ";
    cin>>n6;
    switch(n6){
      case 1:
        medinven();  //Function that shows all inventory of medicines available
      break;
      case 2:
        purchase_medicine();  //Function that allow user to purchase medicine
      break;
      case 0:
        cout<<endl<<"Exiting the program....."<<endl<<endl;
      return customer_dept();
      default:
        cout<<endl<<"Invalid Choice"<<endl<<endl;
    }
  }while(n6!=3);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void customer_dept() { //This function will give access to customer without any login and shows menu
  int n3;
  do {
    cout<<"Press '1' to Enter in laboratory department."<<endl;
    cout<<"Press '2' to Enter in Medicine department."<<endl;
    cout<<"Press '0' to Exit."<<endl;
    cout<<"----------------------------------------------------------------------------------- "<<endl;
    cout<<"Enter your choice (0-2): ";
    cin>>n3;
    switch(n3){
      case 1:
        customerlaboratory_dept();   //Function for laboratory department
      break;
      case 2:
        customermedical_dept();  //Function for medicine department
      break;
      case 0:
        cout<<endl<<"Exiting the program....."<<endl<<endl;
      return mainmenu();
      default:
        cout<<endl<<"Invalid Choice"<<endl<<endl;
    }
  }while(n3!=2);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void laboratory_department() {    //This function shows laboratory department menu
  int n5;
  do {
    cout<<"Press '1' to View all appointments."<<endl;
    cout<<"Press '2' to View total laboratory sales."<<endl;
    cout<<"Press '3' to View all laboratory test types."<<endl;
    cout<<"Press '4' to add a new test."<<endl;
    cout<<"Press '0' to Exit."<<endl;
    cout<<"----------------------------------------------------------------------------------- "<<endl;
    cout<<"Enter your choice (0-2): ";
    cin>>n5;
    switch(n5){
      case 1:
        display_title();
        showappointment(); //This function will display all appointments booked by customers
      break;
      case 2:
        display_lab_sales(); //This function will display all sales and their total price
      break;
      case 3:
        lab_inventory(); //Function that shows all inventory of laboratory tests available
      break;
      case 4:
        add_laboratory();  //If admin wants to add more laboratory tests then this function will be used
      break;
      case 0:
        cout<<endl<<"Exiting the program....."<<endl<<endl;
      return admin_dept();
      default:
        cout<<endl<<"Invalid Choice"<<endl<<endl;
    }
  }while(n5!=4);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void medicine_department() {   //This function shows medicine department menu
  int n6;
  do {
    cout<<"Press '1' to View all inventory."<<endl;
    cout<<"Press '2' to View Total sales."<<endl;
    cout<<"Press '3' to add new medicine."<<endl;
    cout<<"Press '0' to Exit."<<endl;
    cout<<"----------------------------------------------------------------------------------- "<<endl;
    cout<<"Enter your choice (0-3): ";
    cin>>n6;
    switch(n6){
      case 1:
        medinven();  //Function that shows all inventory of medicine available
      break;
      case 2:
        med_sale();  //This function will display all sales and their total price
      break;
      case 3:
        add_medicine();  //If admin wants to add more medicine then this function will be used
      break;
      case 0:
        cout<<endl<<"Exiting the program....."<<endl<<endl;
      return admin_dept();
      default:
        cout<<endl<<"Invalid Choice"<<endl<<endl;
    }
  }while(n6!=3);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void admin_dept() {   //Access of this function will be given after login
  int n4;
  do {
    cout<<"Press '1' to Enter in laboratory department."<<endl;
    cout<<"Press '2' to Enter in Medicine department."<<endl;
    cout<<"Press '0' to Exit."<<endl;
    cout<<"----------------------------------------------------------------------------------- "<<endl;
    cout<<"Enter your choice (0-2): ";
    cin>>n4;
    switch(n4){
      case 1:
        laboratory_department();  //Function for admin laboratory department
      break;
      case 2:
        medicine_department();  //Function for admin medicine department
      break;
      case 0:
        cout<<endl<<"Exiting the program....."<<endl<<endl;
      return login();
      default:
        cout<<endl<<"Invalid Choice"<<endl<<endl;
    }
  }while(n4!=2);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
password * pointer = new password[50];
void prelog() {   //Fuctions for login to check the user is athorize or not
  string x1,y1;
  ifstream infile;      //Reading data from file
  infile.open("Passwords.txt",ios::in);
  if(!infile) {
  cout<<"Error in opening file"<<endl;
  return;
  }
  cout<<"Enter ID: ";
  cin>>x1;
  cout<<"Enter Password: ";
  cin>>y1;
   bool access = false;
       int k=0;
  while(getline(infile,pointer[k].passs,',')) {     //using while to read data till end of file
        getline(infile,pointer[k].idd,',');
        getline(infile,pointer[k].CNIC_password,',');
        getline(infile, pointer[k].name_password);
      if(pointer[k].idd==x1 && pointer[k].passs==y1) {   //using if condition that if unique id & password matches with the unique id & password in the file then it give access
        access=true;
        break;
      }
      k=k+1;
      if(k>=50) { //as we are using an array of 50 size so the k will increment upto k otherwise it will break and exit
        break;
      }
    }
      if(access) {             //if access is given then this msg is shown to user
        cout<<endl<<"                   CONGRATULATIONS! ACCESS GRANTED SUCCESSFULLY"<<endl<<endl;
        admin_dept();
      }
      else {                 //if access not given then this msg is shown
      cout<<endl<<"                         SORRY WRONG PASS! ACCESS NOT GRANTED"<<endl<<endl;
      }
  infile.close();
 }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
int repeat=0;
void newacc() {  //Function for creating a new account of a faculty member against a unique id and password
  ofstream myfile;                        //write data on file eg;id,password,CNIC,name
  myfile.open("Passwords.txt",ios::app);
  if(!myfile) {
     cout<<"Error in opening file"<<endl;
     return;
  }
  cout<<"Enter Your name: ";
  cin>>pointer[repeat].name_password;
  cout<<"Enter your CNIC NO: ";
  cin>>pointer[repeat].CNIC_password;
  cout<<"Enter UNIQUE ID (Combination of letters & numbers): ";
  cin>>pointer[repeat].idd;
  cout<<"Enter Password: ";
  cin>>pointer[repeat].passs;
  myfile<<pointer[repeat].passs<<","<<pointer[repeat].idd<<","<<pointer[repeat].CNIC_password<<","<<pointer[repeat].name_password<<endl;
  myfile.close();
  repeat++;
  cout <<endl<< "New account created successfully!" << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void login(){  //Function for authorization of faculty memeber
      cout<<"==================================================================================="<<endl;
      cout<<"                                 ADMIN LOGIN PAGE                                  "<<endl;
      cout<<"==================================================================================="<<endl;
      int choice;
      do {
        cout<<"Press '1' to LOGIN"<<endl;
        cout<<"Press '2' to CREATE NEW LOGIN"<<endl;
        cout<<"Press '0' to Exit"<<endl;
        cout<<"----------------------------------------------------------------------------------- "<<endl;
        cout<<"Enter your choice (0-2): ";
        cin>>choice;
        switch(choice){
          case 1:
            prelog();   //This will call login function ask the user to login if he/she is a faculty member
          break;
          case 2:
            newacc();   //This will call function that allow faculty member to make a new account
          break;
          case 0:
            cout<<endl<<"Exiting the program....."<<endl<<endl;
          return mainmenu();
          default:
            cout<<endl<<"Invalid Choice"<<endl<<endl;
        }
      }while(choice!=2);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void mainmenu()  //main menu this will be called by main
    {
      int n;
      do{
        cout<<"==================================================================================="<<endl;
        cout<<"                    WELCOME TO LABORATORY & PHARMACY DEPARTMENT                    "<<endl;
        cout<<"==================================================================================="<<endl;
        cout<<"Press '1' to Enter in Admin menu"<<endl;
        cout<<"Press '2' to Enter in Customer menu"<<endl;
        cout<<"Press '0' to Exit"<<endl;
        cout<<"----------------------------------------------------------------------------------- "<<endl;
        cout<<"Enter your choice (0-2): ";
        cin>>n;
        switch(n){
          case 1:
            login();    //Function for admin
          break;
          case 2:
            customer_dept();  //Function for customer
            break;
          case 0:
            cout<<endl<<"Exiting the program....."<<endl<<endl;
          return;
          default:
            cout<<endl<<"Invalid Choice"<<endl<<endl;
            break;
        }
      }while(n!=2);
    }