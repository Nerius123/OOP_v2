#include "functions.h"
#include "../my_library.h"

int main() {
    vector<Student> students;
    char choice;

    while (true) {
        try {
            displayMenu();
            cin >> choice;

            if (cin.fail()) {  // Jei ivestis sugadinta
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
                        break; // Jei ivestas skaicius tinkamas, iseiname is ciklo
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
            
                // Leidžiame vartotojui pasirinkti skaičiavimo metodą
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
            
                vector<Student> vargsiukai, kietiakiai;
                
                // Suskirstymas i dvi grupes
                splitStudents3(students, useMedian);

                // Rikiavimas naudojant sort
                sort(vargsiukai.begin(), vargsiukai.end(), [useMedian](const Student& a, const Student& b) {
                    return calculateFinalGrade(a, useMedian) < calculateFinalGrade(b, useMedian);
                });

                sort(kietiakiai.begin(), kietiakiai.end(), [useMedian](const Student& a, const Student& b) {
                    return calculateFinalGrade(a, useMedian) < calculateFinalGrade(b, useMedian);
                    });

                // Jei reikia mazejancia tvarka
                if (!ascending) {
                    std::reverse(vargsiukai.begin(), vargsiukai.end());
                    std::reverse(kietiakiai.begin(), kietiakiai.end());
                }

                // Issaugome i failus
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
