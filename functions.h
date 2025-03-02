#ifndef FUNCTIONS_H // Patikrina, ar MY_LIBRARY_H dar nėra apibrėžtas
#define FUNCTIONS_H // Jei nėra apibrėžtas, apibrėžia MY_LIBRARY_H (kad kitą kartą būtų atpažintas)

#include "my_library.h"

// Studentų duomenys
struct Student {
    string name;
    string surname;
    vector<int> grades;
    int examGrade;
};

// Funkcijų prototipai
void inputStudentData(Student &s);
double calculateAverage(const Student &s);
double calculateMedian(const Student &s);
double calculateFinalGrade(const Student &s, bool useMedian);
void displayMenu();
void addStudent(vector<Student> &students);
void printStudents(const vector<Student> &students, bool useMedian);
void readFromFile(vector<Student> &students, const string &filename);
void saveResultsToFile(const vector<Student>& students, const string& filename);

#endif  // Baigiame header guard (apsauga nuo pakartotinio įtraukimo)