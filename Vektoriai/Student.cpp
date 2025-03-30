#include "Student.h"

// Default konstruktorius
Student::Student() : examGrade_(0) {}

// Konstruktorius is srauto
Student::Student(std::istream& is) {
    read(is);
}

// Skaitymas is srauto (naudojamas kai skaitoma is failo)
std::istream& Student::read(std::istream& is) {
    is >> name_ >> surname_;
    
    int grade;
    grades_.clear();

    while (is >> grade) {
        grades_.push_back(grade);
    }

    if (grades_.empty()) {
        throw std::runtime_error("Studentas " + name_ + " neturi pazymiu!");
    }

    examGrade_ = grades_.back();
    grades_.pop_back();

    return is;
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
    return (n % 2 == 0)
        ? (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0
        : sorted[n / 2];
}

// Apskaiciuoja galutini bala
double Student::calculateFinalGrade(bool useMedian) const {
    double result = 0.4 * (useMedian ? calculateMedian() : calculateAverage()) + 0.6 * examGrade_;
    return result;
}
