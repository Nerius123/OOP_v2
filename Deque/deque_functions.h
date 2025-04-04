#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../my_library.h"

// Studentų duomenys
struct Student {
    string name;
    string surname;
    deque<int> grades;
    int examGrade;
};

// Funkciju prototipai
void inputStudentData(Student &s);
double calculateAverage(const Student &s);
double calculateMedian(const Student &s);
double calculateFinalGrade(const Student &s, bool useMedian);
void displayMenu();
void printStudents(const deque<Student> &students, bool useMedian);
void readFromFile(deque<Student> &students, const string &filename);
void saveResultsToFile(deque<Student> students, const string& filename, bool showAverage, bool showMedian);
void generateStudentFiles();
void splitStudentsIntoFiles(const deque<Student>& students);
void splitStudents(const deque<Student>& students, deque<Student>& vargsiukai, deque<Student>& kietiakiai, bool useMedian);
void splitStudents3(deque<Student>& students, deque<Student>& vargsiukai, bool useMedian);
void splitStudents2(deque<Student>& students, deque<Student>& vargsiukai, bool useMedian);
void splitStudents1(const deque<Student>& students, deque<Student>& vargsiukai, deque<Student>& kietiakiai, bool useMedian);
void saveStudentsToFile(const deque<Student>& students, const string& filename);
void testDataProcessing(const string& filename, int strategy);

#endif  // Baigiame header guard (apsauga nuo pakartotinio itraukimo)
