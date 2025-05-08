#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Student.h" 

TEST_CASE("Kopijavimo konstruktorius") {
    Student s1;
    s1.setName("Jonas");
    s1.setSurname("Jonaitis");
    s1.setGrades({10, 9, 8});
    s1.setExam(9);

    Student s2(s1); // copy constructor

    REQUIRE(s2.name() == "Jonas");
    REQUIRE(s2.surname() == "Jonaitis");
    REQUIRE(s2.exam() == 9);
    REQUIRE(s2.grades() == s1.grades());
}

TEST_CASE("Kopijavimo priskyrimo operatorius") {
    Student s1;
    s1.setName("Ona");
    s1.setSurname("Onaitė");
    s1.setGrades({7, 8});
    s1.setExam(10);

    Student s2;
    s2 = s1;

    REQUIRE(s2.name() == "Ona");
    REQUIRE(s2.surname() == "Onaitė");
    REQUIRE(s2.exam() == 10);
    REQUIRE(s2.grades() == s1.grades());
}

// Move konstruktorius
TEST_CASE("Move konstruktorius") {
    Student s1;
    s1.setName("Vardenis");
    s1.setSurname("Pavardenis");
    s1.setGrades({5, 5, 5});
    s1.setExam(5);

    Student s2(std::move(s1));

    REQUIRE(s2.name() == "Vardenis");
    REQUIRE(s2.surname() == "Pavardenis");
    REQUIRE(s2.exam() == 5);
    REQUIRE(s2.grades().size() == 3);
}

// Move assignment
TEST_CASE("Move priskyrimo operatorius") {
    Student s1;
    s1.setName("Aidas");
    s1.setSurname("Aidaitis");
    s1.setGrades({4, 6});
    s1.setExam(7);

    Student s2;
    s2 = std::move(s1);

    REQUIRE(s2.name() == "Aidas");
    REQUIRE(s2.surname() == "Aidaitis");
    REQUIRE(s2.exam() == 7);
    REQUIRE(s2.grades().size() == 2);
}
