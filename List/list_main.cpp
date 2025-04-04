#include "list_functions.h"
#include "../my_library.h"

int main() {
    list<Student> students;
    char choice;

    while (true) {
        try {
            displayMenu();
            cin >> choice;

            if (cin.fail()) {  
                throw std::runtime_error("Netinkama įvestis! Prasome ivesti skaiciu.");
            }

            if (choice == '1') {
                Student s;
                inputStudentData(s);
                students.push_back(s);
            } 

            else if (choice == '2') {
                string filename;
                cout << "Iveskite failo pavadinima: ";
                cin >> filename;

                if (filename.empty()) throw std::invalid_argument("Failo pavadinimas negali buti tuscias.");
                
                readFromFile(students, filename);
            } 

            else if (choice == '3') {
                char method;
                while (true) {
                    cout << "Pasirinkite metoda skaiciavimui (v - vidurkis, m - mediana): ";
                    cin >> method;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(100, '\n');
                        throw std::runtime_error("Netinkama įvestis! Prasome ivesti 'v' arba 'm'.");
                    }

                    if (method == 'v' || method == 'V' || method == 'm' || method == 'M') {
                        break;
                    } else {
                        cout << "Neteisinga reiksme. Prasome ivesti 'v' arba 'm'." << endl;
                    }
                }
                printStudents(students, method == 'm' || method == 'M');
            }

            else if (choice == '4') {
                if (students.empty()) {
                    cout << "Nera ivestu studentu, failas nebus issaugotas." << endl;
                    continue;
                }

                string filename;
                cout << "Iveskite failo pavadinima issaugojimui: ";
                cin >> filename;

                if (filename.empty()) throw std::invalid_argument("Failo pavadinimas negali buti tuscias.");
                
                int saveChoice;
                bool showAverage = false, showMedian = false;

                while (true) {
                    cout << "Pasirinkite, koki galutini bala norite matyti isvedime:" << endl;
                    cout << "1 - Tik vidurkio galutini" << endl;
                    cout << "2 - Tik medianos galutini" << endl;
                    cout << "3 - Abu" << endl;
                    cout << "Jusu pasirinkimas: ";
                    cin >> saveChoice;
            
                    if (cin.fail() || (saveChoice < 1 || saveChoice > 3)) {
                        cout << "Netinkama įvestis! Prasome ivesti skaiciu nuo 1 iki 3." << endl;
                        cin.clear();
                        cin.ignore(100, '\n');
                    } else {
                        break; 
                    }
                }

                showAverage = (saveChoice == 1 || saveChoice == 3);
                showMedian = (saveChoice == 2 || saveChoice == 3);

                saveResultsToFile(students, filename, showAverage, showMedian);
            }

            else if (choice == '5') {
                generateStudentFiles();
            }

            else if (choice == '6') { 
                if (students.empty()) {
                    cout << "Nera studentu sarase, nera ka skirstyti!" << endl;
                    continue;
                }

                char method;
                while (true) {
                    cout << "Pasirinkite metoda skirstymui (v - vidurkis, m - mediana): ";
                    cin >> method;

                    if (method == 'v' || method == 'V' || method == 'm' || method == 'M') {
                        break;
                    } else {
                        cout << "Neteisinga reiksme. Prasome ivesti 'v' arba 'm'." << endl;
                    }
                }

                bool useMedian = (method == 'm' || method == 'M');

                char sortOrder;
                while (true) {
                    cout << "Pasirinkite rikiavimo tvarka (a - didejanciai, d - mazejanciai): ";
                    cin >> sortOrder;

                    if (sortOrder == 'a' || sortOrder == 'A' || sortOrder == 'd' || sortOrder == 'D') {
                        break;
                    }
                    else {
                        cout << "Neteisinga reiksme. Prasome ivesti 'a' arba 'd'." << endl;
                    }
                }

                bool ascending = (sortOrder == 'a' || sortOrder == 'A');

                list<Student> vargsiukai, kietiakiai;  // ✅ Pakeista iš vector į list

                // Suskirstymas į dvi grupes
                splitStudents(students, vargsiukai, kietiakiai, false);
                
                // Rikiavimas pasirinkta tvarka
                auto comparator = [useMedian, ascending](const Student& a, const Student& b) {
                    double gradeA = calculateFinalGrade(a, useMedian);
                    double gradeB = calculateFinalGrade(b, useMedian);
                    return ascending ? (gradeA < gradeB) : (gradeA > gradeB);
                };

                vargsiukai.sort(comparator);
                kietiakiai.sort(comparator);

                // Išsaugome į failus
                saveStudentsToFile(vargsiukai, "vargsiukai.txt");
                saveStudentsToFile(kietiakiai, "kietiakiai.txt");
            }

            else if (choice == '7') {
                string filename;
                cout << "Iveskite testuojamo failo pavadinima: ";
                cin >> filename;
            
                int strategy;
                cout << "Pasirinkite studentu skirstymo strategija:\n";
                cout << "1 - strategija\n";
                cout << "2 - strategija\n";
                cout << "3 - strategija\n";
                cout << "Pasirinkimas: ";
                cin >> strategy;
            
                testDataProcessing(filename, strategy);
            }

            else if (choice == '8') {
                cout << "Programa baigta!" << endl;
                break;
            }

            else {
                cout << "\n-------------------------" << endl;
                cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
                cout << "-------------------------\n" << endl;
            }
        } 

        catch (const std::exception& e) {  
            cout << "Klaida: " << e.what() << endl;
            cin.clear();
            cin.ignore(100, '\n');  
        }
    }

    return 0;
}
