#include "my_library.h"

int main () {
    vector<Student> students;

    for (int i = 0; i < 2; i++) {
        Student something;
        std::cin >> something.name >> something.surname >> something.examGrade;
        students.push_back(something);
    }

    for (auto n:students) {
        cout << n.name << " " << n.surname << endl;
    }
}