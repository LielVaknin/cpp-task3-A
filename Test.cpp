#include <string>
#include <sstream>
#include "doctest.h"
#include "NumberWithUnits.hpp"

using namespace ariel;
using namespace std;

bool t;

TEST_CASE ("Test before and after read_units") {
    ifstream units_file("myUnits.txt");
            CHECK_THROWS(NumberWithUnits(5, "kg"));
            CHECK_THROWS(NumberWithUnits(12, "celsius"));
    NumberWithUnits::read_units(units_file);
            CHECK_NOTHROW(NumberWithUnits(5, "kg"));
            CHECK_THROWS(NumberWithUnits(12, "celsius"));
}

TEST_CASE ("Test for binary operators - + , += , - , -=") {
            CHECK_EQ(NumberWithUnits(1, "kg") + NumberWithUnits(1, "kg"), NumberWithUnits(2, "kg"));
            CHECK_EQ(NumberWithUnits(1, "ton") + NumberWithUnits(1000000, "g"),
                     NumberWithUnits(2, "ton"));
            CHECK_EQ(NumberWithUnits(1000000, "g") + NumberWithUnits(1, "ton"),
                     NumberWithUnits(2000000, "g"));
            CHECK_THROWS(NumberWithUnits(4, "year") + NumberWithUnits(12, "EUR"));
            CHECK_THROWS(NumberWithUnits(12, "EUR") + NumberWithUnits(4, "year"));
            CHECK_THROWS(NumberWithUnits(10, "celsius") + NumberWithUnits(7, "EUR"));
            CHECK_THROWS(NumberWithUnits(7, "EUR") + NumberWithUnits(10, "celsius"));
            CHECK_THROWS(NumberWithUnits(3, "celsius") + NumberWithUnits(4, "liter"));

            CHECK_EQ(NumberWithUnits(1, "kg") += NumberWithUnits(1, "kg"), NumberWithUnits(2, "kg"));
            CHECK_EQ(NumberWithUnits(1, "ton") += NumberWithUnits(1000000, "g"),
                     NumberWithUnits(2, "ton"));
            CHECK_EQ(NumberWithUnits(1000000, "g") += NumberWithUnits(1, "ton"),
                     NumberWithUnits(2000000, "g"));
            CHECK_THROWS(NumberWithUnits(4, "year") += NumberWithUnits(12, "EUR"));
            CHECK_THROWS(NumberWithUnits(12, "EUR") += NumberWithUnits(4, "year"));
            CHECK_THROWS(NumberWithUnits(10, "celsius") += NumberWithUnits(7, "EUR"));
            CHECK_THROWS(NumberWithUnits(7, "EUR") += NumberWithUnits(10, "celsius"));
            CHECK_THROWS(NumberWithUnits(3, "celsius") += NumberWithUnits(4, "liter"));

            CHECK_EQ(NumberWithUnits(1, "kg") - NumberWithUnits(1, "kg"), NumberWithUnits(0, "kg"));
            CHECK_EQ(NumberWithUnits(1.5, "ton") - NumberWithUnits(1000000, "g"),
                     NumberWithUnits(0.5, "ton"));
            CHECK_EQ(NumberWithUnits(1500000, "g") - NumberWithUnits(1, "ton"),
                     NumberWithUnits(500000, "g"));
            CHECK_THROWS(NumberWithUnits(4, "year") - NumberWithUnits(12, "EUR"));
            CHECK_THROWS(NumberWithUnits(12, "EUR") - NumberWithUnits(4, "year"));
            CHECK_THROWS(NumberWithUnits(10, "celsius") - NumberWithUnits(7, "EUR"));
            CHECK_THROWS(NumberWithUnits(7, "EUR") - NumberWithUnits(10, "celsius"));
            CHECK_THROWS(NumberWithUnits(3, "celsius") - NumberWithUnits(4, "liter"));

            CHECK_EQ(NumberWithUnits(1, "kg") -= NumberWithUnits(1, "kg"), NumberWithUnits(0, "kg"));
            CHECK_EQ(NumberWithUnits(1.5, "ton") -= NumberWithUnits(1000000, "g"),
                     NumberWithUnits(0.5, "ton"));
            CHECK_EQ(NumberWithUnits(1500000, "g") -= NumberWithUnits(1, "ton"),
                     NumberWithUnits(500000, "g"));
            CHECK_THROWS(NumberWithUnits(4, "year") -= NumberWithUnits(12, "EUR"));
            CHECK_THROWS(NumberWithUnits(12, "EUR") -= NumberWithUnits(4, "year"));
            CHECK_THROWS(NumberWithUnits(10, "celsius") -= NumberWithUnits(7, "EUR"));
            CHECK_THROWS(NumberWithUnits(7, "EUR") -= NumberWithUnits(10, "celsius"));
            CHECK_THROWS(NumberWithUnits(3, "celsius") -= NumberWithUnits(4, "liter"));
}

TEST_CASE ("Test for unary operators - + , -") {
            CHECK(+NumberWithUnits(4, "EUR") == NumberWithUnits(4, "EUR"));
            CHECK(+NumberWithUnits(-4, "EUR") == NumberWithUnits(-4, "EUR"));
            CHECK(-NumberWithUnits(4, "EUR") == NumberWithUnits(-4, "EUR"));
            CHECK(-NumberWithUnits(-4, "EUR") == NumberWithUnits(4, "EUR"));
}

TEST_CASE ("Test for comparison operators - > , >= , < , <= , == , !=") {

            CHECK_GT(NumberWithUnits(5, "year"), NumberWithUnits(4, "year"));
            CHECK_GT(NumberWithUnits(5, "year"), NumberWithUnits(300000, "sec"));
            CHECK_GT(NumberWithUnits(300000, "sec"), NumberWithUnits(0.5, "hour"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "sec") > NumberWithUnits(0.3, "ton"));
            CHECK_THROWS(t = NumberWithUnits(1.7, "ton") > NumberWithUnits(1000000, "sec"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "celsius") > NumberWithUnits(0.3, "ton"));
            CHECK_THROWS(t = NumberWithUnits(1.7, "ton") > NumberWithUnits(1000000, "celsius"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "celsius") > NumberWithUnits(0.3, "Liter"));
            CHECK_THROWS(t = NumberWithUnits(1.7, "liter") > NumberWithUnits(1000000, "celsius"));

            CHECK_GE(NumberWithUnits(5, "year"), NumberWithUnits(4, "year"));
            CHECK_GE(NumberWithUnits(5, "year"), NumberWithUnits(5, "year"));
            CHECK_GE(NumberWithUnits(1000000, "g"), NumberWithUnits(0.3, "ton"));
            CHECK_GE(NumberWithUnits(1000000, "g"), NumberWithUnits(1, "ton"));
            CHECK_GE(NumberWithUnits(1.7, "ton"), NumberWithUnits(1000000, "g"));
            CHECK_GE(NumberWithUnits(1, "ton"), NumberWithUnits(1000000, "g"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "sec") >= NumberWithUnits(0.3, "ton"));
            CHECK_THROWS(t = NumberWithUnits(1.7, "ton") >= NumberWithUnits(1000000, "sec"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "celsius") >= NumberWithUnits(0.3, "ton"));
            CHECK_THROWS(t = NumberWithUnits(1.7, "ton") >= NumberWithUnits(1000000, "celsius"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "celsius") >= NumberWithUnits(0.3, "Liter"));
            CHECK_THROWS(t = NumberWithUnits(1.7, "liter") >= NumberWithUnits(1000000, "celsius"));

            CHECK_LT(NumberWithUnits(4, "year"), NumberWithUnits(5, "year"));
            CHECK_LT(NumberWithUnits(300000, "sec"), NumberWithUnits(5, "year"));
            CHECK_LT(NumberWithUnits(0.5, "hour"), NumberWithUnits(300000, "sec"));
            CHECK_THROWS(t = NumberWithUnits(0.3, "ton") > NumberWithUnits(1000000, "sec"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "sec") > NumberWithUnits(1.7, "ton"));
            CHECK_THROWS(t = NumberWithUnits(0.3, "ton") > NumberWithUnits(1000000, "celsius"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "celsius") > NumberWithUnits(1.7, "ton"));
            CHECK_THROWS(t = NumberWithUnits(0.3, "km") > NumberWithUnits(1000000, "celsius"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "celsius") > NumberWithUnits(1.7, "liter"));

            CHECK_LE(NumberWithUnits(4, "year"), NumberWithUnits(5, "year"));
            CHECK_LE(NumberWithUnits(5, "year"), NumberWithUnits(5, "year"));
            CHECK_LE(NumberWithUnits(0.3, "ton"), NumberWithUnits(1000000, "g"));
            CHECK_LE(NumberWithUnits(1, "ton"), NumberWithUnits(1000000, "g"));
            CHECK_LE(NumberWithUnits(1000000, "g"), NumberWithUnits(1.7, "ton"));
            CHECK_LE(NumberWithUnits(1000000, "g"), NumberWithUnits(1, "ton"));
            CHECK_THROWS(t = NumberWithUnits(0.3, "ton") >= NumberWithUnits(1000000, "sec"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "sec") >= NumberWithUnits(1.7, "ton"));
            CHECK_THROWS(t = NumberWithUnits(0.3, "ton") >= NumberWithUnits(1000000, "celsius"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "celsius") >= NumberWithUnits(1.7, "ton"));
            CHECK_THROWS(t = NumberWithUnits(0.3, "km") >= NumberWithUnits(1000000, "celsius"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "celsius") >= NumberWithUnits(1.7, "liter"));

            CHECK_EQ(NumberWithUnits(4, "km"), NumberWithUnits(4, "km"));
            CHECK_EQ(NumberWithUnits(1, "km"), NumberWithUnits(1000000, "mm"));
            CHECK_EQ(NumberWithUnits(1000000, "mm"), NumberWithUnits(1, "km"));
            CHECK_THROWS(t = NumberWithUnits(0.3, "ton") == NumberWithUnits(1000000, "sec"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "sec") == NumberWithUnits(1.7, "ton"));
            CHECK_THROWS(t = NumberWithUnits(0.3, "ton") == NumberWithUnits(1000000, "celsius"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "celsius") == NumberWithUnits(1.7, "ton"));
            CHECK_THROWS(t = NumberWithUnits(0.3, "km") == NumberWithUnits(1000000, "celsius"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "celsius") == NumberWithUnits(1.7, "liter"));

            CHECK_NE(NumberWithUnits(4, "km"), NumberWithUnits(5, "km"));
            CHECK_NE(NumberWithUnits(1, "km"), NumberWithUnits(140000, "mm"));
            CHECK_NE(NumberWithUnits(140000, "mm"), NumberWithUnits(2, "km"));
            CHECK_THROWS(t = NumberWithUnits(0.3, "ton") != NumberWithUnits(1000000, "sec"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "sec") != NumberWithUnits(1.7, "ton"));
            CHECK_THROWS(t = NumberWithUnits(0.3, "ton") != NumberWithUnits(1000000, "celsius"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "celsius") != NumberWithUnits(1.7, "ton"));
            CHECK_THROWS(t = NumberWithUnits(0.3, "km") != NumberWithUnits(1000000, "celsius"));
            CHECK_THROWS(t = NumberWithUnits(1000000, "celsius") != NumberWithUnits(1.7, "liter"));
}

TEST_CASE ("Test for prefix / postfix increment / decrement operators") {

    NumberWithUnits u(8, "cm");
            CHECK(u++ == NumberWithUnits(8, "cm"));
            CHECK(u == NumberWithUnits(9, "cm"));
            CHECK(++u == NumberWithUnits(10, "cm"));
            CHECK(u-- == NumberWithUnits(10, "cm"));
            CHECK(u == NumberWithUnits(9, "cm"));
            CHECK(--u == NumberWithUnits(8, "cm"));
}

TEST_CASE ("Test for multiply operators") {

    NumberWithUnits u(9, "ILS");
            CHECK_EQ(u * 4.5, 4.5 * u);
}

TEST_CASE ("Test for IO operators") {

    NumberWithUnits u1{-1, "km"};
    NumberWithUnits u2{-1, "cm"};
    NumberWithUnits u3{-1, "USD"};
    NumberWithUnits u4{-1, "year"};

    istringstream sample_input1{"8[ km ]"};
    istringstream sample_input2{"800000[ cm]"};
    istringstream sample_input3{"80[USD]"};
    istringstream sample_input4{"8[year ]"};

    sample_input1 >> u1;
    sample_input2 >> u2;
    sample_input3 >> u3;
    sample_input4 >> u4;

            CHECK_EQ(u1, NumberWithUnits(8, "km"));
            CHECK_EQ(u2, NumberWithUnits(800000, "cm"));
            CHECK_EQ(u3, NumberWithUnits(80, "USD"));
            CHECK_EQ(u4, NumberWithUnits(8, "year"));

    stringstream os1;
    stringstream os2;
    stringstream os3;
    stringstream os4;

    os1 << u1;
    os2 << u2;
    os3 << u3;
    os4 << u4;

            CHECK_EQ(os1.str(), "8[km]");
            CHECK_EQ(os2.str(), "800000[cm]");
            CHECK_EQ(os3.str(),  "80[USD]");
            CHECK_EQ(os4.str(), "8[year]");
}
