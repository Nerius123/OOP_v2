#include "functions.h"
#include "my_library.h"

int main() {

    vector<Student> students;
    char choice;
    while (true){
        displayMenu();
        cin >> choice;

        if (choice == '1') {
            addStudent(students);
        }

        else if (choice == '2') {
            string filename;
            cout << "Iveskite failo pavadinima: ";
            cin >> filename;
            readFromFile(students, filename);
        }
        
        else if (choice == '3') {
            char method;
            while (true) {
                cout << "Pasirinkite metoda skaiciavimui (v - vidurkis, m - mediana): ";
                cin >> method;
                if (method == 'v' || method == 'V' || method == 'm' || method == 'M') {
                    break;
                }
                else {
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
        
            int saveChoice;
            bool showAverage = false, showMedian = false;
        
            cout << "Pasirinkite, koki galutini bala norite matyti isvedime:" << endl;
            cout << "1 - Tik vidurkio galutini" << endl;
            cout << "2 - Tik medianos galutini" << endl;
            cout << "3 - Abu" << endl;
            cout << "Jusu pasirinkimas: ";
            cin >> saveChoice;
        
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
            cout << "Programa baigta!" << endl;
            break;
            }
        else {
            cout << endl;
            cout << "-------------------------" << endl;
            cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
            cout << "-------------------------" << endl;
            cout << endl;
            }
        }
        return 0;
    }