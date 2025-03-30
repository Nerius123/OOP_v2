#pragma once

#include "../my_library.h"

class Student {
private:
    string name_; //rasau zodzio gale _ del to kad butu lengviau atskirti private kintamaji nuo funkcijos parametro
    string surname_; // tas pats
    vector<int> grades_; // tas pats
    int examGrade_; // tas pats

public:
    // Konstruktoriai
    Student();                          // Default
    Student(std::istream& is);          // Is stream'o

    // Geteriai (skaitymui)
    inline string name() const { return name_; }
    inline string surname() const { return surname_; }
    inline const vector<int>& grades() const { return grades_; }
    inline int exam() const { return examGrade_; }

    // Seteriai (keitimui)
    inline void setName(const std::string& name) { name_ = name; }
    inline void setSurname(const std::string& surname) { surname_ = surname; }
    inline void setGrades(const std::vector<int>& grades) { grades_ = grades; }
    inline void setExam(int examGrade) { examGrade_ = examGrade; }

    // Skaitymas is srauto
    std::istream& read(std::istream&);

    // Naudojamos funkcijos
    double calculateAverage() const;
    double calculateMedian() const;
    double calculateFinalGrade(bool useMedian) const;
};

// Lyginimo operatoriai (naudinga rikiavimui)
bool compareByName(const Student& a, const Student& b);
bool compareBySurname(const Student& a, const Student& b);
bool compareByFinalGrade(const Student& a, const Student& b);
