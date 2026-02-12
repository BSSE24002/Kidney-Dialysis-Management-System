#include <iostream>
#include <string>
#include <fstream>
#include "Feedback.h"
using namespace std;

Feedback f;
string sentiment(int rating) {
    if(rating >= 4) {                                               //Returning from function according to integer values
        return "Positive";
    }
    else if(rating == 3) {
        return "Neutral";
    }
    else {
        return "Negative";
    }
}

void addFeedback() {
    cout << "Enter ID of the patient: ";                            //Getting feedback from user
    cin >> f.id;
    cout << "Enter rating(1.Very Poor - 5.Very Good)";
    cin >> f.rating;
    if(f.rating < 1 || f.rating > 5) {
        cout << "Invalid Input! " << endl;
        return;
    }
    cout << "Enter a feedback to improve our services: ";
    cin.ignore();
    getline(cin, f.text);
    f.sentiment = sentiment(f.rating);                              //Storing string from function in sentiment
    ofstream feedbackFile("Feedback.txt", ios::app);
    feedbackFile << f.id << endl;                                   //Adding all details to the file
    feedbackFile << f.rating << endl;
    feedbackFile << f.text << endl;
    feedbackFile << f.sentiment << endl;
    feedbackFile.close();
    cout << "Feedback added! " << endl;
}

void displaySummary() {
    ifstream feedbackFile("Feedback.txt");                          //Opening file
    if(!(feedbackFile.is_open())) {
        cout << "Error opening file! " << endl;
    }
    int positiveFeedback = 0;
    int negativeFeedback = 0;
    int neutralFeedback = 0;
    while(feedbackFile >> f.id >> f.rating) {                       //Loop getting all details
        feedbackFile.ignore();
        getline(feedbackFile, f.text);
        getline(feedbackFile, f.sentiment);
        if(f.sentiment == "Positive") {                             //Incrementing variables accordingly
            positiveFeedback = positiveFeedback + 1;
        }
        else if(f.sentiment == "Negative") {
            negativeFeedback = negativeFeedback + 1;
        }
        else if(f.sentiment == "Neutral") {
            neutralFeedback = neutralFeedback + 1;
        }
    }
    feedbackFile.close();
    cout << "--- Summary of Feedback ---" << endl;                  //Displaying summary
    cout << "Number of positive feedbacks: " << positiveFeedback << endl;
    cout << "Number of negative feedbacks: " << negativeFeedback << endl;
    cout << "Number of neutral feedbacks: " << neutralFeedback << endl;
}

void displayFeedbacks() {
    ifstream feedbackFile("Feedback.txt");                          //Opening file
    if(!(feedbackFile.is_open())) {
        cout << "Error opening file! " << endl;
    }
    cout << "--- Feedback Lists ---" << endl;
    while(feedbackFile >> f.id >> f.rating) {                       //Loop getting all details in variables
        feedbackFile.ignore();
        getline(feedbackFile, f.text);
        getline(feedbackFile, f.sentiment);
        cout << "Patient ID: " << f.id << endl;                     //Displaying all details
        cout << "Rating given by patient: " << f.rating << endl;
        cout << "Feedback text by patient: " << f.text << endl;
        cout << "Overall rating by patient: " << f.sentiment << endl;
    }
    feedbackFile.close();
}

void feedbackMenu() {
    int choice;
    do {                                                            //Showing menu and calling functions accordingly
        static int count = 0;
        count++;
        cout << "Feedback Menu Invoked " << count << " Times " << endl;
        cout << "======== Welcome to Feedback Menu ========" << endl;
        cout << "1. Add Feedback " << endl;
        cout << "2. Display Feedback Summary " << endl;
        cout << "3. Display all Feedback " << endl;
        cout << "4. Exit Feedback Menu " << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1:
                addFeedback();
            break;
            case 2:
                displaySummary();
            break;
            case 3:
                displayFeedbacks();
            break;
            case 4:
                cout << "Exiting Feedback Menu!" << endl;
            break;
            default:
                cout << "You entered an invalid choice! " << endl;
            break;
        }
    }while(choice != 4);
}