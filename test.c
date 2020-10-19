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
    CHECK(serialize(-1.28, a) == "-1.28");
    CHECK(serialize(-0.12, a) == "-0.12");
    CHECK(serialize(0.0, a) == "0");
    CHECK(serialize(0.12, a) == "0.12");
    CHECK(serialize(1.28, a) == "1.28");
    CHECK(deserialize("-1.28", a) == -1.28);
    CHECK(deserialize("-0.12", a) == -0.12);
    CHECK(deserialize("0", a) == 0);
    CHECK(deserialize("0.0", a) == 0);
    CHECK(deserialize("0.12", a) == 0.12);
    CHECK(deserialize("2", a) == 2);
    CHECK(deserialize("1.28", a) == 1.28);
}

TEST_CASE("string handling") {
    std::string a = "";
    CHECK(serialize("asdf", a) == "\"asdf\"");
    CHECK(serialize("as\\\"df", a) == "\"as\\\"df\"");
    CHECK(deserialize("\"asdf\"", a) == "asdf");
}

TEST_CASE("lists") {
    std::vector<int> a = {};
    std::vector<int> xs = {1,2,3};
    CHECK(serialize(xs, a) == "[1,2,3]");
    CHECK(deserialize("[1,2,3]", a) == xs);

    std::vector<std::vector<int>> bs = {};
    std::vector<std::vector<int>> ys = {{1,2},{3,4},{5,6}};
    CHECK(serialize(ys, bs) == "[[1,2],[3,4],[5,6]]");
    CHECK(deserialize("[[1,2],[3,4],[5,6]]", bs) == ys);
}

TEST_CASE("tuples") {
    std::tuple<int,double> a = std::make_tuple(0,0.0);
    std::tuple<int,double> xs = std::make_tuple(1,2.48);
    CHECK(serialize(xs, a) == "[1,2.48]");
    CHECK(deserialize("[1,2.48]", a) == xs);

    std::tuple<int,double,std::string> b = std::make_tuple(0,0.0,"");
    std::tuple<int,double,std::string> ys = std::make_tuple(1,2.48,"asdf");
    CHECK(serialize(ys, b) == "[1,2.48,\"asdf\"]");
    CHECK(deserialize("[1,2.48,\"asdf\"]", b) == ys);
}

TEST_CASE("lists of tuples") {
    std::vector<std::tuple<int,double>> cs = {};
    std::vector<std::tuple<int,double>> zs =
        {std::make_tuple(1,1.2), std::make_tuple(2,2.48), std::make_tuple(3,2.48)};
    CHECK(serialize(zs, cs) == "[[1,1.2],[2,2.48],[3,2.48]]");
    CHECK(deserialize("[[1,1.2],[2,2.48],[3,2.48]]", cs) == zs);

    std::vector<std::tuple<int,std::string>> ds = {};
    std::vector<std::tuple<int,std::string>> zzs =
        {std::make_tuple(1,"qwer"), std::make_tuple(2,"asdf"), std::make_tuple(3,"zxcv")};
    CHECK(serialize(zzs, ds) == "[[1,\"qwer\"],[2,\"asdf\"],[3,\"zxcv\"]]");
    CHECK(deserialize("[[1,\"qwer\"],[2,\"asdf\"],[3,\"zxcv\"]]", ds) == zzs);
}

TEST_CASE("tuple of lists") {

    std::vector<int> xs = {1,2};
    std::vector<double> ys = {1.2,2.48};

    std::tuple<std::vector<int>,std::vector<double>> zs = std::make_tuple(xs,ys);

    CHECK(serialize(zs, zs) == "[[1,2],[1.2,2.48]]");
    CHECK(deserialize("[[1,2],[1.2,2.48]]", zs) == zs);
}
