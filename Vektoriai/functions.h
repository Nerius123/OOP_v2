#ifndef FUNCTIONS_H // Patikrina, ar FUNCTIONS_H dar nėra apibrėžtas (kad failas nebūtų įtrauktas kelis kartus)
#define FUNCTIONS_H // Jei nėra apibrėžtas, apibrėžia FUNCTIONS_H (kad kompiliatorius kitą kartą žinotų, jog jis jau įtrauktas)

#include "../my_library.h"

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
void saveResultsToFile(vector<Student> students, const string& filename, bool showAverage, bool showMedian);
void generateStudentFiles();
void splitStudents(const vector<Student>& students, vector<Student>& vargsiukai, vector<Student>& kietiakiai, bool useMedian);
void splitStudents3(vector<Student>& students, bool useMedian, std::chrono::duration<double>& irasymoTrukme);
void splitStudents2(vector<Student>& students, vector<Student>& vargsiukai, bool useMedian);
void splitStudents1(const vector<Student>& students, vector<Student>& vargsiukai, vector<Student>& kietiakiai, bool useMedian);
void saveStudentsToFile(const vector<Student>& students, const string& filename);
void testDataProcessing(const string& filename, int strategy);


#endif  // Baigiame header guard (apsauga nuo pakartotinio įtraukimo)