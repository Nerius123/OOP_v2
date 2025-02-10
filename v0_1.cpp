#include "my_library.h"

int main() {

    vector<Student> students;

    char choice;
    while (true){
        Student s;
        s.inputStudentData();
        students.push_back(s);
        cout << "Ivesti kita studenta? (t/n): ";
        cin >> choice;
        if (choice != 't' && choice != 'T') 
            break;
    }
    
    char method;
    while (true) {
        cout << "Pasirinkite metoda skaciavimui (v - vidurkis, m - mediana): ";
        cin >> method;
        if (method == 'v' || method == 'V' || method == 'm' || method == 'M') {
            break;
        } 
        else {
            cout << "Neteisinga reiksme. Prasome ivesti 'v' arba 'm'." << endl;
        }
    }

    bool useMedian = (method == 'm' || method == 'M');
}