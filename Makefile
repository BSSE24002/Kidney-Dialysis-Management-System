all: run

compRun:
	g++ -std=c++17 main.cpp Appointment.cpp Dialysis.cpp Feedback.cpp Laboratory1.cpp Patients_Functions.cpp billing.cpp staff.cpp  -o r.out

run: clean compRun
	./r.out

clean:
	rm -f *.out *.o
