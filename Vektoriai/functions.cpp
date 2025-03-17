#include "functions.h"
#include "../my_library.h"
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
    
    vector<double> sortedGrades(s.grades.begin(), s.grades.end()); // Konvertuojame i double
    sort(sortedGrades.begin(), sortedGrades.end()); // Rikiuojame pries mediana
    size_t n = sortedGrades.size();
    
    return (n % 2 == 0) ? (sortedGrades[n / 2 - 1] + sortedGrades[n / 2]) / 2.0 : sortedGrades[n / 2];
}

// Apskaiciuojamas galutinis vertinimas
double calculateFinalGrade(const Student &s, bool useMedian) {
    return 0.400 * (useMedian ? calculateMedian(s) : calculateAverage(s)) + 0.600 * s.examGrade;
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
    cout << "6. Padalinti studentus i dvi kategorijas (kietiakai/vargsiukai)" << endl;
    cout << "7. Testuoti duomenu apdorojimo greiti (nuskaitymas, rusiavimas, irasymas)" << endl;
    cout << "8. Baigti programa" << endl;
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

// Nuskaitymas is failo su laiko matavimu
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

// Issaugojimas i faila su laiko matavimu
void saveResultsToFile(vector<Student> students, const string& filename, bool showAverage, bool showMedian){
    try {
        auto start_time = high_resolution_clock::now();

        ofstream file(filename);
        if (!file) throw std::runtime_error("Nepavyko sukurti failo: " + filename);

        // Vartotojo pasirinkimas rikiavimo budui
        char sortOption;
        while (true) {
            cout << "Pasirinkite rikiavima:\n"
                 << "1 - Pagal varda\n"
                 << "2 - Pagal pavarde\n"
                 << "Pasirinkimas: ";
            cin >> sortOption;
        
            if (sortOption == '1' || sortOption == '2') {
                break; // Teisinga ivestis
            } else {
                cout << "Neteisingas pasirinkimas! Bandykite dar karta.\n";
                cin.clear();            // Isvalome cin busena
                cin.ignore(100, '\n');  // Isvalome neteisinga ivedima
            }
        }

        // Rikiavimas pagal pasirinkimą
        if (sortOption == '1') {
            sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.name < b.name;
            });
        } else {
            sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.surname < b.surname;
            });
        }

        // Antraste
        file << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
        if (showAverage) file << setw(20) << "Galutinis (Vid.)";
        if (showMedian) file << setw(20) << "Galutinis (Med.)";
        file << endl << string(50 + (showAverage ? 20 : 0) + (showMedian ? 20 : 0), '-') << endl;

        // Duomenų irasymas
        for (const auto& s : students) {
            file << left << setw(15) << s.name << setw(15) << s.surname;
            if (showAverage) file << setw(20) << fixed << setprecision(2) << calculateFinalGrade(s, false);
            if (showMedian) file << setw(20) << fixed << setprecision(2) << calculateFinalGrade(s, true);
            file << endl;
        }

        file.close();
        auto end_time = high_resolution_clock::now();
        duration<double> elapsed = end_time - start_time;
        cout << "Failo \"" << filename << "\" issaugojimas uztruko: " << fixed << setprecision(5) << elapsed.count() << " s\n";
    } catch (const std::exception &e) {
        cout << "Klaida: " << e.what() << endl;
    }
}


void generateStudentFiles() {
    vector<pair<string, int>> files = {
        {"students_1000.txt", 1000},
        {"students_10000.txt", 10000},
        {"students_100000.txt", 100000},
        {"students_1000000.txt", 1000000},
        {"students_10000000.txt", 10000000}
    };

    double totalTime = 0.0;
    int fileCount = files.size();

    cout << "Generuojami studentu failai...\n";

    for (const auto& file : files) {
        auto start_time = high_resolution_clock::now();

        ofstream outputFile(file.first);
        if (!outputFile) {
            throw std::runtime_error("Nepavyko sukurti failo: " + file.first);
        }

        random_device rd;
        mt19937 gen(rd()); 
        uniform_int_distribution<int> gradeDist(1, 10);

        const int numGrades = 14;

        // Antraste
        outputFile << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
        for (int i = 1; i <= numGrades; i++) {
            outputFile << setw(8) << ("ND" + to_string(i));
        }
        outputFile << setw(12) << "Egzaminas" << "\n";

        // Duomenų generavimas
        for (int i = 1; i <= file.second; i++) {
            outputFile << left << setw(15) << ("Vardas" + to_string(i)) << setw(15) << ("Pavarde" + to_string(i));
            for (int j = 0; j < numGrades; j++) {
                outputFile << setw(8) << gradeDist(gen);
            }
            outputFile << setw(12) << gradeDist(gen) << "\n";
        }

        outputFile.close();

        auto end_time = high_resolution_clock::now();
        duration<double> elapsed = end_time - start_time;
        totalTime += elapsed.count();

        cout << "Failas \"" << file.first << "\" sugeneruotas per: " << fixed << setprecision(5) << elapsed.count() << " s\n";
    }

    // Vidutinis failo generavimo laikas
    double averageTime = totalTime / fileCount;
    cout << "Bendras failu kurimo laikas: " << fixed << setprecision(5) << totalTime << " s\n";
    cout << "Vidutinis vieno failo generavimo laikas: " << fixed << setprecision(5) << averageTime << " s\n";
}


// Funkcija, kuri studentus padalina i dvi grupes (vargsiukai ir kietiakiai)
void splitStudents(const vector<Student>& students, vector<Student>& vargsiukai, vector<Student>& kietiakiai, bool useMedian) {
    for (const auto& student : students) {
        double finalGrade = calculateFinalGrade(student, useMedian); // Pasirinkimas pagal nora

        if (finalGrade >= 5.00000) {
            kietiakiai.push_back(student);
        } else {
            vargsiukai.push_back(student);
        }
    }
}

// Funkcija, kuri issaugo studentu sarasa i faila
void saveStudentsToFile(const vector<Student>& students, const string& filename) {
    auto start_time = high_resolution_clock::now();

    ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Nepavyko sukurti failo: " + filename);
    }

    // Antraste
    file << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(10) << "Galutinis\n";
    file << string(40, '-') << "\n";

    for (const auto& student : students) {
        double finalGrade = calculateFinalGrade(student, false);
        file << left << setw(15) << student.name << setw(15) << student.surname << fixed << setprecision(2) << finalGrade << "\n";
    }

    file.close();

    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << "Failas \"" << filename << "\" issaugotas per: " << fixed << setprecision(5) << elapsed.count() << " s\n";
}

void testDataProcessing(const string& filename) {
    auto total_start_time = high_resolution_clock::now(); // Visos operacijos pradzios laikas

    vector<Student> students;
    
    // 1. Nuskaitymas is failo
    auto start_time = high_resolution_clock::now();
    readFromFile(students, filename);
    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << "Failo su " << students.size() << " studentu duomenimis nuskaitymas uztruko: " << fixed << setprecision(5) << elapsed.count() << " sek.\n";

    // 2. Skirstymas i dvi grupes
    vector<Student> vargsiukai, kietiakiai;
    start_time = high_resolution_clock::now();
    splitStudents(students, vargsiukai, kietiakiai, false); // Pagal vidurki (jei i mediana noriu reik true padaryt)
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << students.size() << " studentu failo rusiavimas i kietiakus ir vargsiukus laikas uztruko: " << fixed << setprecision(5) << elapsed.count() << " sek.\n";

    // 3. Issaugojimas i failus
    start_time = high_resolution_clock::now();
    saveStudentsToFile(kietiakiai, "kietiakiai_test.txt");
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << students.size() << " studentu su vidurkiu >=5 isvedimas i faila uztruko: " << fixed << setprecision(5) << elapsed.count() << " sek.\n";

    start_time = high_resolution_clock::now();
    saveStudentsToFile(vargsiukai, "vargsiukai_test.txt");
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << students.size() << " studentu su vidurkiu <5 isvedimas i faila uztruko: " << fixed << setprecision(5) << elapsed.count() << " sek.\n";

    // 4. Bendra testavimo trukme
    auto total_end_time = high_resolution_clock::now();
    elapsed = total_end_time - total_start_time;
    cout << students.size() << " studentu failo bendras testavimo laikas uztruko: " << fixed << setprecision(5) << elapsed.count() << " sek.\n";
}
