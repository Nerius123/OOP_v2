#pragma once

#include "../my_library.h"

/**
 * @brief Abstrakti klasė, aprašanti bendrus žmogaus duomenis.
 * 
 * Klasė turi vardą ir pavardę, kuriuos paveldi kitos klasės.
 */

class Zmogus {
protected:
    string name_;
    string surname_;

public:
    // Konstruktorius
    /**
     * @brief Konstruktorius
     */
    Zmogus();


    // Virtualus destruktorius
    /**
     * @brief Virtualus destruktorius.
     */
    virtual ~Zmogus();  

    // Kopijavimo konstruktorius
    /**
     * @brief Kopijavimo konstruktorius.
     */
    Zmogus(const Zmogus& other);  

    // Kopijavimo priskyrimo operatorius
    /**
     * @brief Kopijavimo priskyrimo operatorius.
     * @return Nuoroda į priskirtą objektą.
     */
    Zmogus& operator=(const Zmogus& other);  

    // Move konstruktorius
    /**
     * @brief Move (judejimo) konstruktorius.
     * @param other Objektas, iš kurio perimama info.
     */
    Zmogus(Zmogus&& other) noexcept; 
    
    // Move priskyrimo operatorius
     /**
     * @brief Move (judejimo) priskyrimo operatorius.
     * @param other Objektas, iš kurio perimama info.
     * @return Nuoroda į priskirtą objektą.
     */
    Zmogus& operator=(Zmogus&& other) noexcept; 

    // Abstrakti funkcija (padaro klasę abstrakcia)
    /**
     * @brief Abstrakti funkcija, skirta informacijai apie objektą išvesti.
     */
    virtual void printInfo() const = 0;

    // Geteriai
    /**
     * @brief Gauti žmogaus vardą.
     * @return Vardas (string).
     */
    inline string name() const { return name_; }
    /**
     * @brief Gauti žmogaus pavardę.
     * @return Pavardė (string).
     */
    inline string surname() const { return surname_; }

    // Seteriai
    /**
     * @brief Nustatyti vardą.
     * @param name Naujas vardas.
     */
    inline void setName(const string& name) { name_ = name; }
    /**
     * @brief Nustatyti pavardę.
     * @param surname Nauja pavardė.
     */
    inline void setSurname(const string& surname) { surname_ = surname; }
};
