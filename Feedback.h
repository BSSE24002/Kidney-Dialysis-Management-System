#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <iostream>
#include <string>

using namespace std;
struct Feedback {
    int id;
    int rating;
    string text;
    string sentiment;
};

string sentiment(int rating);
void addFeedback();
void displaySummary();
void displayFeedbacks();
void feedbackMenu();
#endif //FEEDBACK_H