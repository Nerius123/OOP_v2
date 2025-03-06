#include "functions.h"
#include "my_library.h"
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

void inputStudentData(Student &s) {
    try {
        cout << "Vardas: "; 
        cin >> s.name;
        cout << "Pavarde: "; 
        cin >> s.surname;

        if (s.name.empty() || s.surname.empty()) {
            throw std::invalid_argument("Vardas ir pavarde negali buti tuscias!");
        }

        // Namu darbu balu ivedimas
        cout << "Iveskite namu darbu balus (1-10). Iveskite -1, jei norite baigti.\n";
        int grade;
        while (true) {
            cin >> grade;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                throw std::runtime_error("Netinkama ivestis! Prasome ivesti skaiciu (1-10) arba -1.");
            }
            if (grade == -1) break;

            if (grade >= 1 && grade <= 10) {
                s.grades.push_back(grade);
            } else {
                cout << "Ivestas netinkamas balas. Prasome ivesti skaiciu tarp 1-10 arba -1." << endl;
            }
        }

        // Egzamino balo ivedimas
        cout << "Iveskite egzamino bala (1-10): ";
        while (true) {
            cin >> s.examGrade;
            if (s.examGrade >= 1 && s.examGrade <= 10) {
                break;
            } else {
                throw std::out_of_range("Egzamino balas turi buti nuo 1 iki 10.");
            }
        }
    } catch (const std::exception &e) {
        cout << "Klaida: " << e.what() << endl;
    }
}

// Apskaiciuojamas vidurkis 
double calculateAverage(const Student &s) {
    if (s.grades.empty()) throw std::runtime_error("Negalima skaiciuoti vidurkio be pazymiu.");
    return accumulate(s.grades.begin(), s.grades.end(), 0.0) / s.grades.size();
}

// Apskaiciuojamas medianas
double calculateMedian(const Student &s) {
    if (s.grades.empty()) throw std::runtime_error("Negalima skaiciuoti medianos be pazymiu.");
    
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
    cout << "5. Generuoti studentu failus" << endl;
    cout << "6. Padalinti studentus i dvi kategorijas" << endl;
    cout << "7. Baigti programa" << endl;
    cout << "Pasirinkite: ";
}

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
    cout << "Studentu spausdinimas i ekrana uztruko: " << fixed << setprecision(5) << elapsed.count() << " s\n";
}

// Nuskaitymas iš failo su laiko matavimu
void readFromFile(vector<Student> &students, const string &filename) {
    try {
        auto start_time = high_resolution_clock::now();

        ifstream file(filename);
        if (!file) throw std::runtime_error("Nepavyko atidaryti failo: " + filename);

        string line;
        getline(file, line);  // Praleidžiame antraštę

        while (getline(file, line)) {  
            istringstream iss(line);
            Student s;

            if (!(iss >> s.name >> s.surname)) {
                throw std::runtime_error("Klaida skaitant studento varda ir pavarde!");
            }

            int grade;
            vector<int> tempGrades;
            while (iss >> grade) {
                tempGrades.push_back(grade);
            }

            if (tempGrades.empty()) {
                throw std::runtime_error("Studentas " + s.name + " neturi pazymiu!");
            }

            s.examGrade = tempGrades.back();
            tempGrades.pop_back();
            s.grades = tempGrades;
            students.push_back(s);
        }

        file.close();
        auto end_time = high_resolution_clock::now();
        duration<double> elapsed = end_time - start_time;
        cout << "Failo nuskaitymas uztruko: " << fixed << setprecision(5) << elapsed.count() << " s\n";
    } catch (const std::exception &e) {
        cout << "Klaida: " << e.what() << endl;
    }
}

// Išsaugojimas į failą su laiko matavimu
void saveResultsToFile(const vector<Student>& students, const string& filename, bool showAverage, bool showMedian) {
    try {
        auto start_time = high_resolution_clock::now();

        ofstream file(filename);
        if (!file) throw std::runtime_error("Nepavyko sukurti failo: " + filename);

        file << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
        if (showAverage) file << setw(20) << "Galutinis (Vid.)";
        if (showMedian) file << setw(20) << "Galutinis (Med.)";
        file << endl << string(66, '-') << endl;

        for (const auto& s : students) {
            file << left << setw(15) << s.name << setw(15) << s.surname;
            if (showAverage) file << setw(20) << fixed << setprecision(2) << calculateFinalGrade(s, false);
            if (showMedian) file << setw(20) << fixed << setprecision(2) << calculateFinalGrade(s, true);
            file << endl;
        }

        file.close();
        auto end_time = high_resolution_clock::now();
        duration<double> elapsed = end_time - start_time;
        cout << "Failo issaugojimas uztruko: " << fixed << setprecision(5) << elapsed.count() << " s\n";
    } catch (const std::exception &e) {
        cout << "Klaida: " << e.what() << endl;
    }
}

void generateStudentFile(const string& filename, int studentCount) {
    auto start_time = high_resolution_clock::now();

    ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Nepavyko sukurti failo: " + filename);
    }

    random_device rd;
    mt19937 gen(rd()); // Atsitiktinis generatorius
    uniform_int_distribution<int> gradeDist(1, 10); // Balu diapazonas

    const int numGrades = 14; // Kiek namų darbų balų bus sugeneruota

    file << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
    for (int i = 1; i <= numGrades; i++) {
        file << setw(8) << ("ND" + to_string(i));
    }
    file << setw(12) << "Egzaminas" << "\n";

    for (int i = 1; i <= studentCount; i++) {
        file << left << setw(15) << ("Vardas" + to_string(i)) << setw(15) << ("Pavarde" + to_string(i));

        // Generuojame 14 namų darbų balų
        for (int j = 0; j < numGrades; j++) {
            file << setw(8) << gradeDist(gen);
        }

        // Generuojame egzamino balą
        file << setw(12) << gradeDist(gen) << "\n";
    }

    file.close();
    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << "Failas \"" << filename << "\" sugeneruotas per: " << fixed << setprecision(5) << elapsed.count() << " s\n";
}

void splitStudentsIntoFiles(const vector<Student>& students) {
    auto start_time = high_resolution_clock::now();

    ofstream vargsiukaiFile("vargsiukai.txt");
    ofstream kietiakiaiFile("kietiakiai.txt");

    if (!vargsiukaiFile || !kietiakiaiFile) {
        throw std::runtime_error("Nepavyko sukurti vieno iš rezultatų failų.");
    }

    // Header (antraštė)
    vargsiukaiFile << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(10) << "Galutinis\n";
    vargsiukaiFile << string(40, '-') << "\n";
    
    kietiakiaiFile << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(10) << "Galutinis\n";
    kietiakiaiFile << string(40, '-') << "\n";

    for (const auto& student : students) {
        double finalGrade = calculateFinalGrade(student, false); // Galutinį skaičiuojam pagal vidurkį

        if (finalGrade < 5.0) {
            vargsiukaiFile << left << setw(15) << student.name << setw(15) << student.surname << fixed << setprecision(2) << finalGrade << "\n";
        } else {
            kietiakiaiFile << left << setw(15) << student.name << setw(15) << student.surname << fixed << setprecision(2) << finalGrade << "\n";
        }
    }

    vargsiukaiFile.close();
    kietiakiaiFile.close();

    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << "Studentai padalinti ir issaugoti per: " << fixed << setprecision(5) << elapsed.count() << " s\n";
}

