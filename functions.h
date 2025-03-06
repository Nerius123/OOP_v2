#ifndef FUNCTIONS_H // Patikrina, ar FUNCTIONS_H dar nėra apibrėžtas (kad failas nebūtų įtrauktas kelis kartus)
#define FUNCTIONS_H // Jei nėra apibrėžtas, apibrėžia FUNCTIONS_H (kad kompiliatorius kitą kartą žinotų, jog jis jau įtrauktas)

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
void printStudents(const vector<Student> &students, bool useMedian);
void readFromFile(vector<Student> &students, const string &filename);
void saveResultsToFile(const std::vector<Student>& students, const std::string& filename, bool showAverage, bool showMedian);
void generateStudentFile(const std::string& filename, int studentCount);
void splitStudentsIntoFiles(const vector<Student>& students);


#endif  // Baigiame header guard (apsauga nuo pakartotinio įtraukimo)