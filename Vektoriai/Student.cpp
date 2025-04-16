#include "Student.h"

// Default konstruktorius
Student::Student() : examGrade_(0) {}

// Destruktorius
// Yra defaultinis, nes visi nariai (string, vector, int) ir automatiskai susitvarko savo resursus.
//Student::~Student() {}

// Kopijavimo konstruktorius
Student::Student(const Student& other)
    : name_(other.name_),
      surname_(other.surname_),
      grades_(other.grades_),
      examGrade_(other.examGrade_) {}

// Kopijavimo priskyrimo operatorius
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        name_ = other.name_;
        surname_ = other.surname_;
        grades_ = other.grades_;
        examGrade_ = other.examGrade_;
    }
    return *this;
}

// Judejimo konstruktorius (move)
Student::Student(Student&& other) noexcept
    : name_(move(other.name_)),
      surname_(move(other.surname_)),
      grades_(move(other.grades_)),
      examGrade_(exchange(other.examGrade_, 0)) {}

 // Judejimo priskyrimo operatorius (move assignment)
Student& Student::operator=(Student&& other) noexcept {
    if (this != &other) {
        swap(name_, other.name_);
        swap(surname_, other.surname_);
        swap(grades_, other.grades_);
        swap(examGrade_, other.examGrade_);
    }
    return *this;
}

// Apskaiciuoja vidurki
double Student::calculateAverage() const {
    if (grades_.empty()) {
        throw std::runtime_error("Negalima skaiciuoti vidurkio be pazymiu.");
    }

    double sum = std::accumulate(grades_.begin(), grades_.end(), 0.0);
    return sum / grades_.size();
}

// Apskaiciuoja mediana
double Student::calculateMedian() const {
    if (grades_.empty()) {
        throw std::runtime_error("Negalima skaiciuoti medianos be pazymiu.");
    }

    std::vector<int> sorted = grades_;
    std::sort(sorted.begin(), sorted.end());

    size_t n = sorted.size();
    return (n % 2 == 0) ? (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0 : sorted[n / 2];
}

// Apskaiciuoja galutini bala
double Student::calculateFinalGrade(bool useMedian) const {
    double result = 0.4 * (useMedian ? calculateMedian() : calculateAverage()) + 0.6 * examGrade_;
    return result;
}

