#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Student {
    string name, surname;
    int* grades;      // Dinaminis masyvas
    int examGrade;
    int hwCount = 0;  // Kiek buvo ivesta namu darbu

    Student() {
        grades = new int[100]; // Dinaminis masyvas su pradine talpa (100)
    }

    ~Student() {
        delete[] grades; // Isvalome atminti sunaikinant objektą
    }
};

    int main() {
        Student* students = new Student[100];

    }