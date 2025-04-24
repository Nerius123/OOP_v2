#pragma once

#include "../my_library.h"

class Zmogus {
protected:
    string name_;
    string surname_;

public:
    // Konstruktorius
    Zmogus();
    // Virtualus destruktorius
    virtual ~Zmogus();  

    // Kopijavimo konstruktorius
    Zmogus(const Zmogus& other);  

    // Kopijavimo priskyrimo operatorius
    Zmogus& operator=(const Zmogus& other);  

    // Move konstruktorius
    Zmogus(Zmogus&& other) noexcept; 
    
    // Move priskyrimo operatorius
    Zmogus& operator=(Zmogus&& other) noexcept; 

    // Abstrakti funkcija (padaro klasę abstrakcia)
    virtual void printInfo() const = 0;

    // Geteriai
    inline string name() const { return name_; }
    inline string surname() const { return surname_; }

    // Seteriai
    inline void setName(const string& name) { name_ = name; }
    inline void setSurname(const string& surname) { surname_ = surname; }
};
