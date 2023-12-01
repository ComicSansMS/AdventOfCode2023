import trebuchet;

#include <catch.hpp>

TEST_CASE("Calorie Counting")
{
    char const sample_input1[] =
        R"(1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet)";

    char const sample_input2[] = R"(two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen)";


    SECTION("Parse Input")
    {
        CalibrationDocument d = parseInput(sample_input1);
        REQUIRE(d.v.size() == 4);
        CHECK(d.v[0] == "1abc2");
        CHECK(d.v[1] == "pqr3stu8vwx");
        CHECK(d.v[2] == "a1b2c3d4e5f");
        CHECK(d.v[3] == "treb7uchet");
    }

    SECTION("Get Calibration Number")
    {
        CHECK(getCalibrationNumber("1abc2") == 12);
        CHECK(getCalibrationNumber("pqr3stu8vwx") == 38);
        CHECK(getCalibrationNumber("a1b2c3d4e5f") == 15);
        CHECK(getCalibrationNumber("treb7uchet") == 77);
    }

    SECTION("Answer 1")
    {
        CHECK(answer1(parseInput(sample_input1)) == 142);
    }

    SECTION("Get Calibration Number 2")
    {
        CHECK(getCalibrationNumber2("two1nine") == 29);
        CHECK(getCalibrationNumber2("eightwothree") == 83);
        CHECK(getCalibrationNumber2("abcone2threexyz") == 13);
        CHECK(getCalibrationNumber2("xtwone3four") == 24);
        CHECK(getCalibrationNumber2("4nineeightseven2") == 42);
        CHECK(getCalibrationNumber2("zoneight234") == 14);
        CHECK(getCalibrationNumber2("7pqrstsixteen") == 76);
    }

    SECTION("Answer 2")
    {
        CHECK(answer2(parseInput(sample_input1)) == 142);
        CHECK(answer2(parseInput(sample_input2)) == 281);
    }
}
