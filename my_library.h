#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>  
#include <algorithm> 
#include <fstream>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::setw;
using std::fixed;
using std::setprecision;
using std::left;
using std::sort;
using std::accumulate;

struct Student {
    string name;
    string surname;
    vector<int> grades;
    int examGrade;
};

void inputStudentData(Student &s) {
    cout << "Vardas: "; 
    cin >> s.name;
    cout << "Pavarde: "; 
    cin >> s.surname;

    // Namu darbu balu ivedimas
    cout << "Iveskite namu darbu balus (1-10). Iveskite -1, jei norite baigti.\n";
    int grade;
    while (true) {
        cin >> grade;
        if (cin.fail()) { // Patikrina, ar ivestas ne skaicius
            cin.clear();  // Isvalo klaidos busena
            cin.ignore(100, '\n'); // Pasalina neteisingus simbolius
            cout << "Netinkama ivestis! Prasome ivesti skaiciu (1-10) arba -1, jei norite baigti: ";
            continue;
        }
        if (grade == -1) 
        break; // Jei -1, iseiname is ciklo

        if (grade >= 1 && grade <= 10) {
            s.grades.push_back(grade); // Tik jei skaicius teisingas, pridedame i vektoriu
        }
    }
    
    //Egzamino balu ivedimas ir ju tikrinimas
    cout << "Iveskite egzamino bala (1-10): ";
    while(true) {
        cin >> s.examGrade;
        if (s.examGrade >= 1 && s.examGrade <= 10) {
            break;
        }
        else {
            cout << "Neteisingas skaicius! Kartokite (1-10): ";
            cin.clear(); // Isvalo cin klaidos busena 
            cin.ignore(100, '\n'); // Pasalina visus likusius simbolius iki naujos eilutes, kad cin veiktu normaliai
        }
    }
}

    //Apskaiciuojamas vidurkis 
    double calculateAverage(const Student &s) {
        if (s.grades.empty())
            return 0;
    return accumulate(s.grades.begin(), s.grades.end(), 0.0) / s.grades.size(); // Susumuoja visus skaicius
    }

    //Apskaiciuojamas medianas
    double calculateMedian(const Student &s) {
        if (s.grades.empty()){
            return 0;}
            vector<int> sortedGrades = s.grades;
            sort(sortedGrades.begin(), sortedGrades.end()); // Surusiuoja vektoriu didejancia tvarka
            int n = sortedGrades.size();
            return (n % 2 == 0) ? (sortedGrades[n / 2 - 1] + sortedGrades[n / 2]) / 2.0 : sortedGrades[n / 2];
    }

    //Apskaiciuojamas galutinis vertinimas (Kuris skaiciuojamas nuo vartotojo pasirinkimo (ar medianu, ar vidurkiu))
    double calculateFinalGrade(const Student &s, bool useMedian) {
        return 0.4 * (useMedian ? calculateMedian(s) : calculateAverage(s)) + 0.6 * s.examGrade;
    }
         // Jei vartotojas pasirinko mediana tuomet True yra skaiciuojamas, jei vidurki tada False skaiciuojamas 

    void displayMenu() {
        cout << "========================" << endl;
        cout << "          MENIU         " << endl;
        cout << "========================" << endl;
        cout << "1. Prideti nauja studenta" << endl;
        cout << "2. Nuskaityti studentus is failo" << endl;
        cout << "3. Spausdinti studentu sarasa" << endl;
        cout << "4. Issaugoti rezultatus i faila" << endl;
        cout << "5. Baigti programa" << endl;
        cout << "Pasirinkite: ";
        }
    
    void addStudent(vector<Student> &students) {
        Student s;
        inputStudentData(s);
        students.push_back(s);
        }
    
    void printStudents(const vector<Student> &students, bool useMedian) {
        if (students.empty()) {
            cout << "Nera studentu." << endl;
            return;
        }
        vector<Student> sortedStudents = students;
        sort(sortedStudents.begin(), sortedStudents.end(), [](const Student &a, const Student &b) { // Lambda rykiavimas kuris lygina studento a ir b vardus (jei vardai vienodi pavardes) ir ziuri pagal abecele kuris pirmiau
            if (a.name == b.name)
                return a.surname < b.surname; // Jei vardai sutampa, rikiuojama pagal pavarde
            return a.name < b.name; // Pirmiausia rikiuojama pagal varda
        });
        cout << "\nVardas         Pavarde          Galutinis (" << (useMedian ? "Med." : "Vid.") << ")\n";
        cout << "------------------------------------------------\n";
        for (auto &s : sortedStudents) {
            cout << std::left << std::setw(15) << s.name << std::setw(15)  << s.surname << "  " << std::fixed << std::setprecision(2) << calculateFinalGrade(s, useMedian) << endl;
            }
        }