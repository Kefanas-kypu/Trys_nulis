/**
 * @file test_studentas.cpp
 * @brief Unit testai klasėms Studentas ir StudentGroups funkcijoms.
 */

#include <vector>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "Studentas.h"
#include "Funkcijos.h"

using Catch::Approx;

// Pagalbinė funkcija, kad nereikėtų kartoti tų pačių REQUIRE
static void check_students_equal(const Studentas& a, const Studentas& b) {
    REQUIRE(a.vardas()   == b.vardas());
    REQUIRE(a.pavarde()  == b.pavarde());
    REQUIRE(a.egzaminas() == Approx(b.egzaminas()));
    REQUIRE(a.nd().size() == b.nd().size());
    for (std::size_t i = 0; i < a.nd().size(); ++i) {
        REQUIRE(a.nd()[i] == Approx(b.nd()[i]));
    }
}

TEST_CASE("Studento galutinis balas skaiciuojamas pagal vidurki", "[Studentas][galBalas-vidurkis]") {
    Studentas s;
    s.setVardas("Jonas");
    s.setPavarde("Jonaitis");
    s.setNd({10.0, 8.0, 6.0});
    s.setEgzaminas(9.0);

    double expected_nd_avg = Studentas::vidurkis({10.0, 8.0, 6.0});
    double expected = 0.4 * expected_nd_avg + 0.6 * 9.0;

    REQUIRE(s.galBalas(Studentas::vidurkis) == Approx(expected));
}

TEST_CASE("Studento galutinis balas skaiciuojamas pagal mediana", "[Studentas][galBalas-mediana]") {
    Studentas s;
    s.setVardas("Ona");
    s.setPavarde("Onaite");
    s.setNd({2.0, 10.0, 8.0}); // mediana = 8.0
    s.setEgzaminas(7.0);

    double expected_med = Studentas::mediana({2.0, 10.0, 8.0});
    double expected = 0.4 * expected_med + 0.6 * 7.0;

    REQUIRE(s.galBalas(Studentas::mediana) == Approx(expected));
}

TEST_CASE("Studento setteriai ir getteriai veikia korektiskai", "[Studentas][get/set]") {
    Studentas s;
    s.setVardas("Petras");
    s.setPavarde("Petraitis");
    s.setNd({5.0, 6.0, 7.0});
    s.setEgzaminas(8.0);

    REQUIRE(s.vardas()   == "Petras");
    REQUIRE(s.pavarde()  == "Petraitis");
    REQUIRE(s.egzaminas() == Approx(8.0));
    REQUIRE(s.nd().size() == 3);
    REQUIRE(s.nd()[0] == Approx(5.0));
    REQUIRE(s.nd()[1] == Approx(6.0));
    REQUIRE(s.nd()[2] == Approx(7.0));
}

TEST_CASE("Copy konstruktorius sukuria nepriklausoma kopija", "[Studentas][copy-ctor]") {
    Studentas original;
    original.setVardas("Vardenis");
    original.setPavarde("Pavardenis");
    original.setNd({5.0, 8.0, 7.0});
    original.setEgzaminas(9.0);

    Studentas copy(original);   // copy ctor

    // pradinė būsena vienoda
    check_students_equal(original, copy);

    // pakeičiam originalą ir tikrinam, kad kopija nepasikeitė
    original.setVardas("Kitas");
    original.setNd({1.0, 2.0, 3.0});
    original.setEgzaminas(4.0);

    REQUIRE(copy.vardas()   == "Vardenis");
    REQUIRE(copy.pavarde()  == "Pavardenis");
    REQUIRE(copy.nd().size() == 3);
    REQUIRE(copy.nd()[0] == Approx(5.0));
    REQUIRE(copy.nd()[1] == Approx(8.0));
    REQUIRE(copy.nd()[2] == Approx(7.0));
    REQUIRE(copy.egzaminas() == Approx(9.0));
}

TEST_CASE("Copy priskyrimo operatorius perraso duomenis ir veikia su self-assignment", "[Studentas][copy-assign]") {
    Studentas s1;
    s1.setVardas("Senis");
    s1.setPavarde("Senas");
    s1.setNd({1.0, 1.0, 1.0});
    s1.setEgzaminas(1.0);

    Studentas s2;
    s2.setVardas("Jaunas");
    s2.setPavarde("Jaunas");
    s2.setNd({9.0, 9.0, 9.0});
    s2.setEgzaminas(9.0);

    // copy assignment
    s1 = s2;
    check_students_equal(s1, s2);

    // self-assignment neturi sugadinti objekto
    s1 = s1;
    check_students_equal(s1, s2);
}

TEST_CASE("Studentai teisingai suskirstomi i kietiakius ir vargsiukus", "[suskirstytiStudentus][basic]") {
    Studentas geras;
    geras.setVardas("Geras");
    geras.setPavarde("Studentas");
    geras.setNd({8.0, 9.0, 10.0});
    geras.setEgzaminas(9.0);

    Studentas blogas;
    blogas.setVardas("Blogas");
    blogas.setPavarde("Studentas");
    blogas.setNd({2.0, 3.0, 4.0});
    blogas.setEgzaminas(3.0);

    std::vector<Studentas> grupe = {geras, blogas};

    StudentGroups groups = suskirstytiStudentus(grupe);

    REQUIRE(groups.kietiakiai.size() == 1);
    REQUIRE(groups.vargsiukai.size() == 1);
    REQUIRE(groups.kietiakiai[0].vardas() == "Geras");
    REQUIRE(groups.vargsiukai[0].vardas() == "Blogas");
}

TEST_CASE("Ribine reiksme 5.0 priskiriama kietiakiams", "[suskirstytiStudentus][boundary]") {
    Studentas antRibos;
    antRibos.setVardas("Ribinis");
    antRibos.setPavarde("Studentas");
    antRibos.setNd({5.0, 5.0, 5.0});
    antRibos.setEgzaminas(5.0);

    std::vector<Studentas> grupe = {antRibos};

    StudentGroups groups = suskirstytiStudentus(grupe);

    REQUIRE(groups.kietiakiai.size() == 1);
    REQUIRE(groups.vargsiukai.empty());
    REQUIRE(groups.kietiakiai[0].vardas() == "Ribinis");
}
