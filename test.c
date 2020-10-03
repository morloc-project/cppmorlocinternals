#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "serial.hpp"

TEST_CASE("boolean handling") {
    CHECK(serialize(true, true) == "true");
    CHECK(serialize(false, true) == "false");
    CHECK(deserialize("true", true) == true);
    CHECK(deserialize("true", true) == true);
}

TEST_CASE("int handling") {
    int a = 0;
    CHECK(serialize(-21, a) == "-21");
    CHECK(serialize(-2, a) == "-2");
    CHECK(serialize(0, a) == "0");
    CHECK(serialize(2, a) == "2");
    CHECK(serialize(21, a) == "21");
    CHECK(deserialize("-29", a) == -29);
    CHECK(deserialize("-2", a) == -2);
    CHECK(deserialize("0", a) == 0);
    CHECK(deserialize("2", a) == 2);
    CHECK(deserialize("29", a) == 29);
}

TEST_CASE("double handling") {
    double a = 0;
    CHECK(serialize(-2.12, a) == "-2.12");
    CHECK(serialize(-0.12, a) == "-0.12");
    CHECK(serialize(0.0, a) == "0");
    CHECK(serialize(0.12, a) == "0.12");
    CHECK(serialize(2.1, a) == "2.1");
    CHECK(deserialize("-2.1", a) == -2.1);
    CHECK(deserialize("-0.12", a) == -0.12);
    CHECK(deserialize("0", a) == 0);
    CHECK(deserialize("0.0", a) == 0);
    CHECK(deserialize("0.12", a) == 0.12);
    CHECK(deserialize("2", a) == 2);
    CHECK(deserialize("2.1", a) == 2.1);
}

TEST_CASE("string handling") {
    std::string a = "";
    CHECK(serialize("asdf", a) == "\"asdf\"");
    CHECK(serialize("as\\\"df", a) == "\"as\\\"df\"");
    CHECK(deserialize("\"asdf\"", a) == "asdf");
}
