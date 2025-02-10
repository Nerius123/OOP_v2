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
    
}