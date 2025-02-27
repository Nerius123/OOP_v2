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

        else if (choice == '3') {
            char method;
            while (true) {
                cout << "Pasirinkite metoda skaičiavimui (v - vidurkis, m - mediana): ";
                cin >> method;
                if (method == 'v' || method == 'V' || method == 'm' || method == 'M') {
                    break;
                } else {
                    cout << "Neteisinga reiksme. Prasome ivesti 'v' arba 'm'." << endl;
                }
            }
            printStudents(students, method == 'm' || method == 'M');
        }


    cout << "\nPavarde    Vardas    Galutinis (" << (useMedian ? "Med." : "Vid.") << ")\n";
    cout << "----------------------------------------\n";
    for (auto &s : students) {
        cout << std::left << std::setw(12) << s.name << std::setw(12)  << s.surname << "  " << std::fixed << std::setprecision(2) << s.calculateFinalGrade(useMedian) << endl;
        }
    }
    return 0;
}