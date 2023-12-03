import gear_ratios;

#include <experimental/mdspan>

#include <catch.hpp>

TEST_CASE("Cube Conundrum")
{
    char const sample_input[] =
        R"(467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..
)";

    auto const field = parseInput(sample_input);
    SECTION("Parse Input")
    {
        CHECK(field.span.extent(0) == 10);
        CHECK(field.span.extent(1) == 10);
        CHECK(field.span(0, 0) == '4');
        CHECK(field.span(1, 0) == '6');
        CHECK(field.span(2, 0) == '7');
        CHECK(field.span(3, 0) == '.');
        CHECK(field.span(0, 1) == '.');
        CHECK(field.span(3, 1) == '*');
    }

    SECTION("Iterate Parts")
    {
        int i = 0;
        iterateParts(field, [&i](int part, int ix, int iy, char adj_symbol) {
            ++i;
            if (i == 1) {
                CHECK(part == 467);
                CHECK(ix == 3);
                CHECK(iy == 1);
                CHECK(adj_symbol == '*');
            } else if (i == 2) {
                CHECK(part == 114);
                CHECK(ix == -1);
                CHECK(iy == -1);
                CHECK(adj_symbol == '.');
            } else if (i == 3) {
                CHECK(part == 35);
                CHECK(ix == 3);
                CHECK(iy == 1);
                CHECK(adj_symbol == '*');
            }
        });
        CHECK(i == 10);
    }

    SECTION("Answer 1")
    {
        CHECK(answer1(field) == 4361);
    }

    SECTION("Answer 2")
    {
        CHECK(answer2(field) == 467835);
    }
}
