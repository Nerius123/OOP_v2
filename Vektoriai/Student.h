#pragma once

#include "../my_library.h"
#include "zmogus.h"

class Student : public Zmogus {
    private:
    vector<int> grades_; //rasau zodzio gale _ del to kad butu lengviau atskirti private kintamaji nuo funkcijos parametro
    int examGrade_; // tas pats

public:
    // Konstruktoriai
    Student();

    // Destruktorius
    ~Student();

    // Kopijavimo konstruktorius
    Student(const Student& other);

    // Kopijavimo priskyrimo operatorius
    Student& operator=(const Student& other);

    // Judejimo konstruktorius (move)
    Student(Student&& other) noexcept;

    // Judejimo priskyrimo operatorius (move assignment)
    Student& operator=(Student&& other) noexcept;

    // Geteriai (skaitymui)
    inline const std::vector<int>& grades() const { return grades_; }
    inline int exam() const { return examGrade_; }

    // Seteriai (keitimui)
    inline void setGrades(const std::vector<int>& grades) { grades_ = grades; }
    inline void setExam(int examGrade) { examGrade_ = examGrade; }

    // Naudojamos funkcijos
    double calculateAverage() const;
    double calculateMedian() const;
    double calculateFinalGrade(bool useMedian) const;

    // Įgyvendinta abstrakti funkcija
    void printInfo() const override;
};

// Lyginimo operatoriai (naudinga rikiavimui)
bool compareByName(const Student& a, const Student& b);
bool compareBySurname(const Student& a, const Student& b);
bool compareByFinalGrade(const Student& a, const Student& b);
