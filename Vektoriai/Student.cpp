#include "Student.h"

// Konstruktorius
Student::Student() : examGrade_(0) {}

// Destruktorius
Student::~Student() {
    //cout << "Iskviestas destruktorius studentui:" << name_ << " " << surname_ << endl; // Jei reikia pavaizduoti, kad veikia destruktorius
    name_ = "";
    surname_ = "";
    grades_.clear();
    examGrade_ = 0;
}

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

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << s.name_ << " " << s.surname_ << " ";
    for (int grade : s.grades_) {
        os << grade << " ";
    }
    os << s.examGrade_;
    return os;
}

std::istream& operator>>(std::istream& is, Student& s) {
    s.grades_.clear();
    is >> s.name_ >> s.surname_;

    int value;
    while (is >> value) {
        s.grades_.push_back(value);
    }

    if (!s.grades_.empty()) {
        s.examGrade_ = s.grades_.back();
        s.grades_.pop_back(); // paskutinis skaicius (egzas)
    } else {
        s.examGrade_ = 0;
    }

    is.clear(); // isvaloma srauto busena jei while baigesi del EOF ar ne skaiciaus
    return is;
}