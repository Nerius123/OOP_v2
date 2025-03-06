#include "functions.h"
#include "my_library.h"

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

                cout << "Pasirinkite, koki galutini bala norite matyti isvedime:" << endl;
                cout << "1 - Tik vidurkio galutini" << endl;
                cout << "2 - Tik medianos galutini" << endl;
                cout << "3 - Abu" << endl;
                cout << "Jusu pasirinkimas: ";
                cin >> saveChoice;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    throw std::runtime_error("Netinkama įvestis! Prasome ivesti skaiciu nuo 1 iki 3.");
                }

                switch (saveChoice) {
                    case 1:
                        showAverage = true;
                        break;
                    case 2:
                        showMedian = true;
                        break;
                    case 3:
                        showAverage = true;
                        showMedian = true;
                        break;
                    default:
                        cout << "Netinkamas pasirinkimas. Naudojamas numatytasis variantas (abu)." << endl;
                        showAverage = true;
                        showMedian = true;
                        break;
                }

                saveResultsToFile(students, filename, showAverage, showMedian);
            }

            else if (choice == '5') {
                cout << "Generuojami failai...\n";
                generateStudentFile("students_1000.txt", 1000);
                generateStudentFile("students_10000.txt", 10000);
                generateStudentFile("students_100000.txt", 100000);
                generateStudentFile("students_1000000.txt", 1000000);
                generateStudentFile("students_10000000.txt", 10000000);
            }
            
            else if (choice == '6') {
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
