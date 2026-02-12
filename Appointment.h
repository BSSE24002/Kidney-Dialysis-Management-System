//
// Created by mwar9 on 11/17/2024.
//

#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "Patients_Functions.h"

int TimeToMinutes(const string& time);

bool isDoctorAvailable(const string& workingHours, const string& appointmentTime);

void ScheduleAppointment(const Patient* patients, int patientCount, const Doctors* doctors, int doctorCount);

void DisplayAllAppointments();

void Appointment_menu(const Patient* patients, int patientCount, Doctors*& Doctors, int& doctorCount);

#endif //APPOINTMENT_H
