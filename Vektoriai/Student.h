#pragma once

#include "../my_library.h"

class Student {
private:
    std::string name_;
    std::string surname_;
    std::vector<int> grades_;
    int examGrade_;

public:
    // Konstruktoriai
    Student();                          // Default
    Student(std::istream& is);          // Iš stream'o

    // Geteriai (skaitymui)
    inline std::string name() const { return name_; }
    inline std::string surname() const { return surname_; }
    inline const std::vector<int>& grades() const { return grades_; }
    inline int exam() const { return examGrade_; }

    // Seteriai (keitimui)
    inline void setName(const std::string& name) { name_ = name; }
    inline void setSurname(const std::string& surname) { surname_ = surname; }
    inline void setGrades(const std::vector<int>& grades) { grades_ = grades; }
    inline void setExam(int examGrade) { examGrade_ = examGrade; }

    // Skaitymas iš srauto
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
