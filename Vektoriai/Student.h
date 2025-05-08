/**
 * @mainpage Studentų valdymo sistema
 * 
 * Ši C++ programa leidžia:
 * 
 * 1. Pridėti naują studentą per vartotojo įvestį.
 * 2. Nuskaityti studentų duomenis iš failo.
 * 3. Spausdinti studentų sąrašą, pasirinkus galutinio balo skaičiavimo metodą (vidurkis arba mediana).
 * 4. Išsaugoti studentų rezultatus į failą.
 * 5. Generuoti didelius studentų duomenų failus (iki 10 milijonų įrašų).
 * 6. Padalinti studentus į dvi kategorijas: „kietiakai“ ir „vargšiukai“ pagal jų rezultatus.
 * 7. Testuoti didelių duomenų apdorojimo greitį (nuskaitymas, rūšiavimas, išsaugojimas).
 * 8. Patikrinti Rule of Five principo įgyvendinimą klasėje Student.
 * 9. Patikrinti, ar galima sukurti abstraktų objektą Zmogus.
 * 10. Baigti programos vykdymą.
 * 
 * Dokumentacija sukurta naudojant Doxygen.
 * 
 * @author
 * Nerijus Ponomariovas
 */

#pragma once

#include "../my_library.h"
#include "zmogus.h"

/**
 * @brief Klasė, aprašanti studentą.
 * 
 * Paveldi iš Zmogus klasės ir papildomai saugo pažymių sąrašą bei egzamino balą.
 */

class Student : public Zmogus {
    private:
    vector<int> grades_; //rasau zodzio gale _ del to kad butu lengviau atskirti private kintamaji nuo funkcijos parametro
    int examGrade_; // tas pats

public:

    /**
     * @brief Numatytoji konstruktoriaus funkcija.
     */
    // Konstruktoriai
    Student();

     /**
     * @brief Destruktorius.
     */
    // Destruktorius
    ~Student();

    /**
     * @brief Kopijavimo konstruktorius.
     * @param other Kitas studento objektas, iš kurio kopijuojama.
     */
    // Kopijavimo konstruktorius
    Student(const Student& other);

    /**
     * @brief Kopijavimo priskyrimo operatorius.
     * @param other Kitas studentas.
     * @return Nuoroda į priskirtą objektą.
     */
    // Kopijavimo priskyrimo operatorius
    Student& operator=(const Student& other);


    /**
     * @brief Move (judejimo) konstruktorius.
     * @param other Kitas studentas.
     */
    // Judejimo konstruktorius (move)
    Student(Student&& other) noexcept;

    /**
     * @brief Move (judejimo) priskyrimo operatorius.
     * @param other Kitas studentas.
     * @return Nuoroda į priskirtą objektą.
     */
    // Judejimo priskyrimo operatorius (move assignment)
    Student& operator=(Student&& other) noexcept;

    // Geteriai (skaitymui)
    /**
     * @brief Gauti studento namų darbų pažymius.
     * @return Pažymiai.
     */
    inline const std::vector<int>& grades() const { return grades_; }
    /**
     * @brief Gauti egzamino pažymį.
     * @return Egzamino balas.
     */
    inline int exam() const { return examGrade_; }

    // Seteriai (keitimui)
    /**
     * @brief Nustatyti studento namų darbų pažymius.
     * @param grades Nauji pažymiai.
     */
    inline void setGrades(const std::vector<int>& grades) { grades_ = grades; }
    /**
     * @brief Nustatyti egzamino pažymį.
     * @param examGrade Naujas egzamino balas.
     */
    inline void setExam(int examGrade) { examGrade_ = examGrade; }

    // Naudojamos funkcijos
    /**
     * @brief Apskaičiuoja pažymių vidurkį.
     * @return Vidurkis.
     */
    double calculateAverage() const;
    /**
     * @brief Apskaičiuoja pažymių medianą.
     * @return Mediana.
     */
    double calculateMedian() const;
     /**
     * @brief Apskaičiuoja galutinį pažymį.
     * @return Galutinis pažymys.
     */
    double calculateFinalGrade(bool useMedian) const;

    // Įgyvendinta abstrakti funkcija
    /**
     * @brief Išveda studento informaciją į ekraną.
     */
    void printInfo() const override;

    /**
     * @brief Įvesties operatorius (>>).
     * @param is Įvesties srautas.
     * @param s Studentas, į kurį įvedama.
     * @return Įvesties srautas.
     */
    friend std::istream& operator>>(std::istream& is, Student& s);
    /**
     * @brief Išvesties operatorius (<<).
     * @param os Išvesties srautas.
     * @param s Studentas, kurį išvesti.
     * @return Išvesties srautas.
     */
    friend std::ostream& operator<<(std::ostream& os, const Student& s);

};

// Lyginimo operatoriai (naudinga rikiavimui)
/**
 * @brief Lygina du studentus pagal vardą.
 */
bool compareByName(const Student& a, const Student& b);
/**
 * @brief Lygina du studentus pagal pavardę.
 */
bool compareBySurname(const Student& a, const Student& b);
/**
 * @brief Lygina du studentus pagal galutinį pažymį.
 */
bool compareByFinalGrade(const Student& a, const Student& b);
