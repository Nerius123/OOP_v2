#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

struct Student {
    string name = "name";
    string surname = "surname";
    vector<int> grades;
    int examGrade = 10;
};