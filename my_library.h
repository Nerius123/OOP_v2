#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>  
#include <algorithm> 

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::cin;

struct Student {
    string name;
    string surname;
    vector<int> grades;
    int examGrade;


void inputStudentData() {
    cout << "Vardas: "; 
    cin >> name;
    cout << "Pavardė: "; 
    cin >> surname;
    cout << "Įveskite namų darbus (-1 baigti): ";
    int grade;
    while (cin >> grade && grade != -1) grades.push_back(grade);
    cout << "Egzamino balas: "; 
    cin >> examGrade;
}
double calculateAverage() {
    if (grades.empty())
        return 0;
    return accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
}

double calculateMedian() {
    if (grades.empty()) 
        return 0;
    sort(grades.begin(), grades.end());
    int n = grades.size();
    return (n % 2 == 0) ? (grades[n / 2 - 1] + grades[n / 2]) / 2.0 : grades[n / 2];
}

double calculateFinalGrade(bool useMedian) {
    return 0.4 * (useMedian ? calculateMedian() + 0.6 * examGrade : calculateAverage()) + 0.6 * examGrade;
}

};