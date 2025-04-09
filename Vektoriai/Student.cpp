#include "Student.h"

// Default konstruktorius
Student::Student() : examGrade_(0) {}

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
