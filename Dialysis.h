#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>

using namespace std;
struct Dialysis {
    string patientID;                                               //Initializing struct and its attributes
    string date;
    int bedNumber;
    int duration;
    string flag;
};

void addDialysisSession();
void updateDialysisSession();
void deleteDialysisSession();
void searchDialysisSession();
void displayAllSessions();
void automaticDelete(string id);
bool loadSessions();
void listByDate();
void mainMenu();
#endif //FUNCTIONS_H