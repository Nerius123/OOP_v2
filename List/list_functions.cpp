#include "list_functions.h"
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
                s.grades.push_back(grade);  // ✅ List naudoja push_back() 
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
    if (s.grades.empty()) 
        throw std::runtime_error("Negalima skaiciuoti vidurkio be pazymiu.");
    return accumulate(s.grades.begin(), s.grades.end(), 0.0) / s.grades.size();
}


// Apskaiciuojamas medianas
double calculateMedian(const Student &s) {
    if (s.grades.empty()) 
        throw std::runtime_error("Negalima skaiciuoti medianos be pazymiu.");

    list<double> sortedGrades(s.grades.begin(), s.grades.end()); // Konvertuojame i double
    sortedGrades.sort(); // Rikiuojame pries medianos paieska

    size_t n = sortedGrades.size();
    auto it = sortedGrades.begin();
    advance(it, n / 2); // Pereiname iki vidurinio elemento

    return (n % 2 == 0) ? (*prev(it) + *it) / 2.0 : *it;
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

void printStudents(const list<Student> &students, bool useMedian) {
    if (students.empty()) {
        cout << "Nera ivesta jokiu studentu." << endl;
        return;
    }

    auto start_time = high_resolution_clock::now();

    list<Student> sortedStudents(students); // Kopijuojame studentų sąrašą
    sortedStudents.sort([](const Student &a, const Student &b) {
        return (a.name == b.name) ? a.surname < b.surname : a.name < b.name;
    });

    cout << "\nVardas         Pavarde          Galutinis (" << (useMedian ? "Med." : "Vid.") << ")\n";
    cout << "------------------------------------------------\n";
    for (const auto &s : sortedStudents) {
        cout << left << setw(15) << s.name << setw(15) << s.surname << "  " << fixed << setprecision(2) << calculateFinalGrade(s, useMedian) << endl;
    }

    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << "Studentu spausdinimas i ekrana uztruko: " << fixed << setprecision(5) << elapsed.count() << " s\n";
}


// Nuskaitymas is failo su laiko matavimu
void readFromFile(list<Student> &students, const string &filename) {
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
            list<int> tempGrades; // ✅ Pakeista iš vector<int> į list<int>
            while (iss >> grade) {
                tempGrades.push_back(grade);
            }

            if (tempGrades.empty()) {
                throw std::runtime_error("Studentas " + s.name + " neturi pazymiu!");
            }

            s.examGrade = tempGrades.back();
            tempGrades.pop_back();
            s.grades = tempGrades;  // ✅ Pakeista: tiesiog priskiriam list<int>
            students.push_back(s);
        }

        file.close();
        auto end_time = high_resolution_clock::now();
        duration<double> elapsed = end_time - start_time;
        //cout << "Failo nuskaitymas uztruko: " << fixed << setprecision(5) << elapsed.count() << " s\n";
    } catch (const std::exception &e) {
        cout << "Klaida: " << e.what() << endl;
    }
}


// Issaugojimas i faila su laiko matavimu
void saveResultsToFile(list<Student> students, const string& filename, bool showAverage, bool showMedian) {
    try {
        auto start_time = high_resolution_clock::now();

        ofstream file(filename);
        if (!file) throw std::runtime_error("Nepavyko sukurti failo: " + filename);

        // Vartotojo pasirinkimas rikiavimo būdui
        char sortOption;
        while (true) {
            cout << "Pasirinkite rikiavima:\n"
                 << "1 - Pagal varda\n"
                 << "2 - Pagal pavarde\n"
                 << "Pasirinkimas: ";
            cin >> sortOption;
        
            if (sortOption == '1' || sortOption == '2') {
                break; // Teisinga įvestis
            } else {
                cout << "Neteisingas pasirinkimas! Bandykite dar karta.\n";
                cin.clear();            // Išvalome `cin` būseną
                cin.ignore(100, '\n');  // Išvalome neteisingą įvedimą
            }
        }

        // Rikiavimas pagal pasirinkimą naudojant `list.sort()`
        if (sortOption == '1') {
            students.sort([](const Student& a, const Student& b) {
                return a.name < b.name;
            });
        } else {
            students.sort([](const Student& a, const Student& b) {
                return a.surname < b.surname;
            });
        }

        // Antraštė
        file << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
        if (showAverage) file << setw(20) << "Galutinis (Vid.)";
        if (showMedian) file << setw(20) << "Galutinis (Med.)";
        file << endl << string(50 + (showAverage ? 20 : 0) + (showMedian ? 20 : 0), '-') << endl;

        // Duomenų įrašymas
        for (const auto& s : students) {
            file << left << setw(15) << s.name << setw(15) << s.surname;
            if (showAverage) file << setw(20) << fixed << setprecision(2) << calculateFinalGrade(s, false);
            if (showMedian) file << setw(20) << fixed << setprecision(2) << calculateFinalGrade(s, true);
            file << endl;
        }

        file.close();
        auto end_time = high_resolution_clock::now();
        duration<double> elapsed = end_time - start_time;
        cout << "Failo \"" << filename << "\" išsaugojimas užtruko: " << fixed << setprecision(5) << elapsed.count() << " s\n";
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

void splitStudents(const list<Student>& students, list<Student>& vargsiukai, list<Student>& kietiakiai, bool useMedian) {
    vargsiukai.clear();
    kietiakiai.clear();

    for (const auto& student : students) {
        double finalGrade = calculateFinalGrade(student, useMedian); // Pasirinkimas pagal nora

        if (finalGrade >= 5.0) {
            kietiakiai.push_back(student);
        } else {
            vargsiukai.push_back(student);
        }
    }
}

// Funkcija, kuri studentus padalina i dvi grupes (vargsiukai ir kietiakiai)
void splitStudents3(std::list<Student>& students, bool useMedian, std::chrono::duration<double>& irasymoTrukme) {
    using namespace std::chrono;

    std::list<Student> vargsiukai;

    // Skirstymas: iš students pašaliname vargsiukus ir perkeliame į vargsiukai
    for (auto it = students.begin(); it != students.end(); ) {
        if (calculateFinalGrade(*it, useMedian) < 5.0) {
            vargsiukai.splice(vargsiukai.end(), students, it++);
        } else {
            ++it;
        }
    }

    // Įrašymas
    auto start1 = high_resolution_clock::now();
    saveStudentsToFile(students, "kietiakiai_test.txt");  // students dabar tik kietiakiai
    auto end1 = high_resolution_clock::now();
    duration<double> laik = end1 - start1;

    cout << students.size() << " \"kietiakai\" studentu issaugojimas uztruko: "<< fixed << setprecision(5) << laik.count() << " sek.\n";

    auto start2 = high_resolution_clock::now();
    saveStudentsToFile(vargsiukai, "vargsiukai_test.txt");
    auto end2 = high_resolution_clock::now();
    duration<double> laik1 = end2 - start2;

    cout << vargsiukai.size() << " \"vargsiukai\" studentu issaugojimas uztruko: "<< fixed << setprecision(5) << laik1.count() << " sek.\n";

    irasymoTrukme = laik + laik1;
}


void splitStudents2(list<Student>& students, list<Student>& vargsiukai, bool useMedian) {
    vargsiukai.clear();

    for (auto it = students.begin(); it != students.end(); ) {
        if (calculateFinalGrade(*it, useMedian) < 5.0) {
            vargsiukai.splice(vargsiukai.end(), students, it++); // Perkeliam ir iskart salinam
        } else {
            ++it;
        }
    }
}

void splitStudents1(const list<Student>& students, list<Student>& vargsiukai, list<Student>& kietiakiai, bool useMedian) {
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
void saveStudentsToFile(const list<Student>& students, const string& filename) {
    auto start_time = high_resolution_clock::now();

    ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Nepavyko sukurti failo: " + filename);
    }

    // Antraštė
    file << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(10) << "Galutinis\n";
    file << string(40, '-') << "\n";

    for (const auto& student : students) {
        double finalGrade = calculateFinalGrade(student, false);
        file << left << setw(15) << student.name << setw(15) << student.surname << fixed << setprecision(2) << finalGrade << "\n";
    }

    file.close();

    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    //cout << "Failas \"" << filename << "\" issaugotas per: " << fixed << setprecision(5) << elapsed.count() << " s\n";
}


void testDataProcessing(const string& filename, int strategy) {
    auto total_start_time = high_resolution_clock::now(); // Visos operacijos pradzios laikas

    list<Student> students;  // Naudojamas list kaip konteineris
    list<Student> vargsiukai, kietiakiai;

    
    // 1. Duomenu nuskaitymas is failo
    auto start_time = high_resolution_clock::now();
    readFromFile(students, filename);
    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << "Failo su " << students.size() << " studentu duomenimis nuskaitymas uztruko: " << fixed << setprecision(5) << elapsed.count() << " sek.\n";

    std::chrono::duration<double> irasymoTrukme;
    // 2. Studentu rusiavimas didejancia tvarka (sort funkcija)
    start_time = high_resolution_clock::now();

    switch (strategy) {
        case 1:
            splitStudents1(students, vargsiukai, kietiakiai, false);
            break;
        case 2:
            splitStudents2(students, vargsiukai, false);
            kietiakiai = students;
            break;
        case 3:
            splitStudents3(students, false, irasymoTrukme);
            break;
        default:
            cout << "Neteisinga strategija. Naudojama numatytoji (1 strategija)).\n";
            splitStudents1(students, vargsiukai, kietiakiai, false);
            break;
        }
    
        end_time = high_resolution_clock::now();
        elapsed = end_time - start_time;
        if (strategy == 3){
            elapsed = elapsed - irasymoTrukme;
            cout << students.size() << " studentu skirstymas i dvi grupes uztruko: " << fixed << setprecision(5) << elapsed.count() << " sek.\n";
        }
    
        if (strategy == 1 || strategy == 2) {
        cout << students.size() << " studentu skirstymas i dvi grupes uztruko: " << fixed << setprecision(5) << elapsed.count() << " sek.\n";

    // 4. Rezultatu issaugojimas i failus
    start_time = high_resolution_clock::now();
    saveStudentsToFile(kietiakiai, "kietiakiai_test.txt");
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << kietiakiai.size() << " \"kietiakiai\" studentu issaugojimas uztruko: " << fixed << setprecision(5) << elapsed.count() << " sek.\n";

    start_time = high_resolution_clock::now();
    saveStudentsToFile(vargsiukai, "vargsiukai_test.txt");
    end_time = high_resolution_clock::now();
    elapsed = end_time - start_time;
    cout << vargsiukai.size() << " \"vargsiukai\" studentu issaugojimas uztruko: " << fixed << setprecision(5) << elapsed.count() << " sek.\n";
        }
    // 5. Bendras testavimo laikas
    auto total_end_time = high_resolution_clock::now();
    elapsed = total_end_time - total_start_time;
    cout << "Visas studentu failo apdorojimas uztruko: " << fixed << setprecision(5) << elapsed.count() << " sek.\n";
}