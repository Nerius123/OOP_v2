#include "zmogus.h"
#include "../my_library.h"

// Konstruktorius
Zmogus::Zmogus() : name_(""), surname_("") {}

// Virtualus destruktorius
Zmogus::~Zmogus() {
    name_.clear();
    surname_.clear();
}

// Kopijavimo konstruktorius
Zmogus::Zmogus(const Zmogus& other)
    : name_(other.name_), surname_(other.surname_) {}

// Kopijavimo priskyrimo operatorius
Zmogus& Zmogus::operator=(const Zmogus& other) {
    if (this != &other) {
        name_ = other.name_;
        surname_ = other.surname_;
    }
    return *this;
}

// Move konstruktorius
Zmogus::Zmogus(Zmogus&& other) noexcept
    : name_(move(other.name_)), surname_(move(other.surname_)) {}

// Move priskyrimo operatorius
Zmogus& Zmogus::operator=(Zmogus&& other) noexcept {
    if (this != &other) {
        swap(name_, other.name_);
        swap(surname_, other.surname_);
    }
    return *this;
}
