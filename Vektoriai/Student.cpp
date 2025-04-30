#include "Student.h"

// Konstruktorius
Student::Student() : examGrade_(0) {}

// Destruktorius
Student::~Student() {
    //cout << "Iskviestas destruktorius studentui:" << name_ << " " << surname_ << endl; // Jei reikia pavaizduoti, kad veikia destruktorius
    grades_.clear();
    examGrade_ = 0;
}

// Kopijavimo konstruktorius
Student::Student(const Student& other)
    : Zmogus(other),
      grades_(other.grades_),
      examGrade_(other.examGrade_) {}

// Kopijavimo priskyrimo operatorius
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        Zmogus::operator=(other);
        grades_ = other.grades_;
        examGrade_ = other.examGrade_;
    }
    return *this;
}

// Judejimo konstruktorius (move)
Student::Student(Student&& other) noexcept
    : Zmogus(move(other)),
      grades_(move(other.grades_)),
      examGrade_(exchange(other.examGrade_, 0)) {}

 // Judejimo priskyrimo operatorius (move assignment)
Student& Student::operator=(Student&& other) noexcept {
    if (this != &other) {
        Zmogus::operator=(move(other));
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

    double sum = accumulate(grades_.begin(), grades_.end(), 0.0);
    return sum / grades_.size();
}

// Apskaiciuoja mediana
double Student::calculateMedian() const {
    if (grades_.empty()) {
        throw std::runtime_error("Negalima skaiciuoti medianos be pazymiu.");
    }

    vector<int> sorted = grades_;
    sort(sorted.begin(), sorted.end());

    size_t n = sorted.size();
    return (n % 2 == 0) ? (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0 : sorted[n / 2];
}

// Apskaiciuoja galutini bala
double Student::calculateFinalGrade(bool useMedian) const {
    double result = 0.4 * (useMedian ? calculateMedian() : calculateAverage()) + 0.6 * examGrade_;
    return result;
}

void Student::printInfo() const {
    cout << "Studentas: " << name_ << " " << surname_ << ", Egzaminas: " << examGrade_ << endl;
}