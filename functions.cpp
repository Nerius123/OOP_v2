#include "functions.h"
#include "my_library.h"
#include <chrono>  // <== PRIDĖTA ČIA

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

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
        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Netinkama ivestis! Prasome ivesti skaiciu (1-10) arba -1, jei norite baigti: ";
            continue;
        }
        if (grade == -1) break;

        if (grade >= 1 && grade <= 10) {
            s.grades.push_back(grade);
        }
    }

    // Egzamino balu ivedimas
    cout << "Iveskite egzamino bala (1-10): ";
    while (true) {
        cin >> s.examGrade;
        if (s.examGrade >= 1 && s.examGrade <= 10) {
            break;
        } else {
            cout << "Neteisingas skaicius! Kartokite (1-10): ";
            cin.clear();
            cin.ignore(100, '\n');
        }
    }
}

// Apskaiciuojamas vidurkis 
double calculateAverage(const Student &s) {
    if (s.grades.empty()) return 0;
    return accumulate(s.grades.begin(), s.grades.end(), 0.0) / s.grades.size();
}

// Apskaiciuojamas medianas
double calculateMedian(const Student &s) {
    if (s.grades.empty()) return 0;
    
    vector<int> sortedGrades = s.grades;
    sort(sortedGrades.begin(), sortedGrades.end());
    int n = sortedGrades.size();
    
    return (n % 2 == 0) ? (sortedGrades[n / 2 - 1] + sortedGrades[n / 2]) / 2.0 : sortedGrades[n / 2];
}

// Apskaiciuojamas galutinis vertinimas
double calculateFinalGrade(const Student &s, bool useMedian) {
    return 0.4 * (useMedian ? calculateMedian(s) : calculateAverage(s)) + 0.6 * s.examGrade;
}

// Meniu atvaizdavimas
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

// Spausdinimas į ekraną su laiko matavimu
void printStudents(const vector<Student> &students, bool useMedian) {
    if (students.empty()) {
        cout << "Nera ivesta jokiu studentu." << endl;
        return;
    }

    auto start_time = high_resolution_clock::now();

    vector<Student> sortedStudents = students;
    sort(sortedStudents.begin(), sortedStudents.end(), [](const Student &a, const Student &b) {
        return (a.name == b.name) ? a.surname < b.surname : a.name < b.name;
    });

    cout << "\nVardas         Pavarde          Galutinis (" << (useMedian ? "Med." : "Vid.") << ")\n";
    cout << "------------------------------------------------\n";
    for (auto &s : sortedStudents) {
        cout << left << setw(15) << s.name << setw(15)  << s.surname << "  " << fixed << setprecision(2) << calculateFinalGrade(s, useMedian) << endl;
    }

    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << "Studentu spausdinimas i ekrana uztruko: " << elapsed.count() << " s" << endl;
}

// Nuskaitymas iš failo su laiko matavimu
void readFromFile(vector<Student> &students, const string &filename) {
    auto start_time = high_resolution_clock::now();

    ifstream file(filename);
    if (!file) {
        cout << "Klaida atidarant faila: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {  
        istringstream iss(line);
        Student s;

        if (!(iss >> s.name >> s.surname)) {
            cout << "Klaida skaitant studento varda ir pavarde!" << endl;
            continue;
        }

        int grade;
        vector<int> tempGrades;
        while (iss >> grade) {
            tempGrades.push_back(grade);
        }

        if (tempGrades.empty()) {
            cout << "Klaida: Studentas " << s.name << " " << s.surname << " neturi pazymiu!" << endl;
            continue;
        }

        s.examGrade = tempGrades.back();
        tempGrades.pop_back();
        s.grades = tempGrades;

        students.push_back(s);
    }

    file.close();
    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << "Failo nuskaitymas uztruko: " << elapsed.count() << " s" << endl;
}

// Išsaugojimas į failą su laiko matavimu
void saveResultsToFile(const vector<Student>& students, const string& filename, bool showAverage, bool showMedian) {
    auto start_time = high_resolution_clock::now();

    ofstream file(filename);
    if (!file) {
        cout << "Klaida kuriant faila!" << endl;
        return;
    }

    file << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
    
    if (showAverage) file << setw(20) << "Galutinis (Vid.)";
    if (showMedian) file << setw(20) << "Galutinis (Med.)";
    
    file << endl;
    file << string(66, '-') << endl;

    for (const auto& s : students) {
        file << left << setw(15) << s.name << setw(15) << s.surname;
        if (showAverage) file << setw(20) << fixed << setprecision(2) << calculateFinalGrade(s, false);
        if (showMedian) file << setw(20) << fixed << setprecision(2) << calculateFinalGrade(s, true);
        file << endl;
    }

    file.close();
    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << "Failo issaugojimas uztruko: " << elapsed.count() << " s" << endl;
}
