#include "functions.h"
#include "../my_library.h"
#include "Student.h"
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

void inputStudentData(Student &s) {
    try {
        std::string v, p;
        cout << "Vardas: "; 
        cin >> v;
        s.setName(v);

        cout << "Pavarde: "; 
        cin >> p;
        s.setSurname(p);

        if (s.name().empty() || s.surname().empty()) {
            throw std::invalid_argument("Vardas ir pavarde negali buti tuscias!");
        }

        // Namu darbu balu ivedimas
        cout << "Iveskite namu darbu balus (1-10). Iveskite -1, jei norite baigti.\n";
        int grade;
        std::vector<int> nd;
        while (true) {
            cin >> grade;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                throw std::runtime_error("Netinkama ivestis! Prasome ivesti skaiciu (1-10) arba -1.");
            }
            if (grade == -1) break;

            if (grade >= 1 && grade <= 10) {
                nd.push_back(grade);
            } else {
                cout << "Ivestas netinkamas balas. Prasome ivesti skaiciu tarp 1-10 arba -1." << endl;
            }
        }
        s.setGrades(nd);

        // Egzamino balo ivedimas
        int egz;
        cout << "Iveskite egzamino bala (1-10): ";
        while (true) {
            cin >> egz;
            if (egz >= 1 && egz <= 10) {
                s.setExam(egz);
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
double Student::calculateAverage() const {
    if (grades_.empty()) throw std::runtime_error("Negalima skaiciuoti vidurkio be pazymiu.");
    return std::accumulate(grades_.begin(), grades_.end(), 0.0) / grades_.size();
}

double Student::calculateMedian() const {
    if (grades_.empty()) throw std::runtime_error("Negalima skaiciuoti medianos be pazymiu.");
    std::vector<int> sortedGrades = grades_;
    std::sort(sortedGrades.begin(), sortedGrades.end());
    size_t n = sortedGrades.size();
    return (n % 2 == 0) ? (sortedGrades[n / 2 - 1] + sortedGrades[n / 2]) / 2.0 : sortedGrades[n / 2];
}

double Student::calculateFinalGrade(bool useMedian) const {
    return 0.400 * (useMedian ? calculateMedian() : calculateAverage()) + 0.600 * examGrade_;
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
        return (a.name() == b.name()) ? a.surname() < b.surname() : a.name() < b.name();
    });

    cout << "\nVardas         Pavarde          Galutinis (" << (useMedian ? "Med." : "Vid.") << ")\n";
    cout << "------------------------------------------------\n";
    for (const auto& s : sortedStudents) {
        cout << left << setw(15) << s.name() << setw(15) << s.surname() << fixed << setprecision(2) << s.calculateFinalGrade(useMedian) << endl;
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

            string vardas, pavarde;
            if (!(iss >> vardas >> pavarde)) {
                throw std::runtime_error("Klaida skaitant studento varda ir pavarde!");
            }
            s.setName(vardas);
            s.setSurname(pavarde);

            int grade;
            vector<int> tempGrades;
            while (iss >> grade) {
                tempGrades.push_back(grade);
            }

            if (tempGrades.empty()) {
                throw std::runtime_error("Studentas " + s.name() + " neturi pazymiu!");
            }

            s.setExam(tempGrades.back());
            tempGrades.pop_back();
            s.setGrades(tempGrades);

            students.push_back(s);
        }

        file.close();
        auto end_time = high_resolution_clock::now();
        duration<double> elapsed = end_time - start_time;
        // cout << "Failo nuskaitymas uztruko: " << fixed << setprecision(5) << elapsed.count() << " s\n";
    } catch (const std::exception &e) {
        cout << "Klaida: " << e.what() << endl;
    }
}


// Issaugojimas i faila su laiko matavimu
void saveResultsToFile(vector<Student> students, const string& filename, bool showAverage, bool showMedian) {
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
                break;
            } else {
                cout << "Neteisingas pasirinkimas! Bandykite dar karta.\n";
                cin.clear();
                cin.ignore(100, '\n');
            }
        }

        // Rikiavimas
        if (sortOption == '1') {
            sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.name() < b.name();
            });
        } else {
            sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.surname() < b.surname();
            });
        }

        // Antraste
        file << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
        if (showAverage) file << setw(20) << "Galutinis (Vid.)";
        if (showMedian)  file << setw(20) << "Galutinis (Med.)";
        file << endl << string(50 + (showAverage ? 20 : 0) + (showMedian ? 20 : 0), '-') << endl;

        // Duomenų įrašymas
        for (const auto& s : students) {
            file << left << setw(15) << s.name() << setw(15) << s.surname();
            if (showAverage) file << setw(20) << fixed << setprecision(2) << s.calculateFinalGrade(false);
            if (showMedian)  file << setw(20) << fixed << setprecision(2) << s.calculateFinalGrade(true);
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

void splitStudents(const vector<Student>& students, vector<Student>& vargsiukai, vector<Student>& kietiakiai, bool useMedian) {
    vargsiukai.clear();
    kietiakiai.clear();

    for (const auto& student : students) {
        double finalGrade = student.calculateFinalGrade(useMedian);

        if (finalGrade >= 5.0) {
            kietiakiai.push_back(student);
        } else {
            vargsiukai.push_back(student);
        }
    }
}


// Funkcija, kuri studentus padalina i dvi grupes (vargsiukai ir kietiakiai)
void splitStudents3(vector<Student>& students, vector<Student>& vargsiukai, bool useMedian) {
    vargsiukai.clear(); 

    auto it = remove_if(students.begin(), students.end(), [&](const Student& s) {
        if (s.calculateFinalGrade(useMedian) < 5.0) {
            vargsiukai.push_back(s);
            return true;
        }
        return false;
    });

    students.erase(it, students.end());
}


void splitStudents2(vector<Student>& students, vector<Student>& vargsiukai, bool useMedian) {
    vargsiukai.clear();

    vector<Student> kietiakiai;
    for (const auto& s : students) {
        if (s.calculateFinalGrade(useMedian) < 5.0) {
            vargsiukai.push_back(s);
        } else {
            kietiakiai.push_back(s);
        }
    }

    students.swap(kietiakiai);  // paliekame tik kietiakius
}


void splitStudents1(const vector<Student>& students, vector<Student>& vargsiukai, vector<Student>& kietiakiai, bool useMedian) {
    vargsiukai.clear();
    kietiakiai.clear();

    for (const auto& student : students) {
        double finalGrade = student.calculateFinalGrade(useMedian);

        if (finalGrade >= 5.0) {
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
    file << left << setw(15) << "Vardas"
         << setw(15) << "Pavarde"
         << setw(10) << "Galutinis\n";
    file << string(40, '-') << "\n";

    for (const auto& student : students) {
        double finalGrade = student.calculateFinalGrade(false);
        file << left << setw(15) << student.name() << setw(15) << student.surname() << fixed << setprecision(2) << finalGrade << "\n";
    }

    file.close();

    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    // cout << "Failas \"" << filename << "\" issaugotas per: " << fixed << setprecision(5) << elapsed.count() << " s\n";
}


void testDataProcessing(const string& filename, int strategy) {
    auto total_start_time = high_resolution_clock::now();

    vector<Student> students;
    vector<Student> vargsiukai, kietiakiai;

    // 1. Duomenų nuskaitymas
    auto start_time = high_resolution_clock::now();
    readFromFile(students, filename);
    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << "Failo su " << students.size() << " studentu duomenimis nuskaitymas uztruko: "
         << fixed << setprecision(5) << elapsed.count() << " sek.\n";

    // 2. Rūšiavimas
    start_time = high_resolution_clock::now();
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.calculateFinalGrade(false) < b.calculateFinalGrade(false);
    });
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << students.size() << " studentu rusiavimas konteineryje uztruko: "
         << fixed << setprecision(5) << elapsed.count() << " sek.\n";

    // 3. Skirstymas į grupes
    start_time = high_resolution_clock::now();
    size_t originalStudentCount = students.size();

    switch (strategy) {
        case 1:
            splitStudents1(students, vargsiukai, kietiakiai, false);
            break;
        case 2:
            splitStudents2(students, vargsiukai, false);
            kietiakiai = students;
            break;
        case 3:
            splitStudents3(students, vargsiukai, false);
            kietiakiai = students;
            break;
        default:
            cout << "Neteisinga strategija. Naudojama numatytoji (1 strategija)).\n";
            splitStudents1(students, vargsiukai, kietiakiai, false);
            break;
    }

    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << originalStudentCount << " studentu skirstymas i dvi grupes uztruko: "
         << fixed << setprecision(5) << elapsed.count() << " sek.\n";

    // 4. Išsaugojimas į failus
    start_time = high_resolution_clock::now();
    saveStudentsToFile(kietiakiai, "kietiakiai_test.txt");
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << kietiakiai.size() << " \"kietiakai\" studentu issaugojimas uztruko: "
         << fixed << setprecision(5) << elapsed.count() << " sek.\n";

    start_time = high_resolution_clock::now();
    saveStudentsToFile(vargsiukai, "vargsiukai_test.txt");
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << vargsiukai.size() << " \"vargsiukai\" studentu issaugojimas uztruko: "
         << fixed << setprecision(5) << elapsed.count() << " sek.\n";

    // 5. Visas laikas
    auto total_end_time = high_resolution_clock::now();
    elapsed = total_end_time - total_start_time;
    cout << "Visas studentu failo apdorojimas uztruko: "
         << fixed << setprecision(5) << elapsed.count() << " sek.\n";
}
