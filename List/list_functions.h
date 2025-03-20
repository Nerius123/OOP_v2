#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../my_library.h"
#include <list>  // Naudojame std::list vietoj std::vector

// Studentų duomenys
struct Student {
    string name;
    string surname;
    list<int> grades;  // Pakeista iš vector<int> į list<int>
    int examGrade;
};

// Funkcijų prototipai
void inputStudentData(Student &s);
double calculateAverage(const Student &s);
double calculateMedian(const Student &s);
double calculateFinalGrade(const Student &s, bool useMedian);
void displayMenu();
void printStudents(const list<Student> &students, bool useMedian);
void readFromFile(list<Student> &students, const string &filename);
void saveResultsToFile(list<Student> students, const string& filename, bool showAverage, bool showMedian);
void generateStudentFiles();
void splitStudents(list<Student>& students, list<Student>& vargsiukai, bool useMedian);
void saveStudentsToFile(const list<Student>& students, const string& filename);
void testDataProcessing(const string& filename);

#endif  // Baigiame header guard (apsauga nuo pakartotinio įtraukimo)
