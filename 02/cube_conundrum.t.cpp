import cube_conundrum;

#include <catch.hpp>

TEST_CASE("Cube Conundrum")
{
    char const sample_input[] =
        R"(Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
)";

    auto const games = parseInput(sample_input);
    SECTION("Parse Input")
    {
        REQUIRE(games.size() == 5);
        CHECK(games[0].id == 1);
        REQUIRE(games[0].reveals.size() == 3);
        CHECK(games[0].reveals[0] == Cubes{ .red = 4, .green = 0, .blue = 3 });
        CHECK(games[0].reveals[1] == Cubes{ .red = 1, .green = 2, .blue = 6 });
        CHECK(games[0].reveals[2] == Cubes{ .red = 0, .green = 2, .blue = 0 });
        CHECK(games[1].id == 2);
        REQUIRE(games[1].reveals.size() == 3);
        CHECK(games[1].reveals[0] == Cubes{ .red = 0, .green = 2, .blue = 1 });
        CHECK(games[1].reveals[1] == Cubes{ .red = 1, .green = 3, .blue = 4 });
        CHECK(games[1].reveals[2] == Cubes{ .red = 0, .green = 1, .blue = 1 });
        CHECK(games[2].id == 3);
        REQUIRE(games[2].reveals.size() == 3);
        CHECK(games[2].reveals[0] == Cubes{ .red = 20, .green = 8, .blue = 6 });
        CHECK(games[2].reveals[1] == Cubes{ .red = 4, .green = 13, .blue = 5 });
        CHECK(games[2].reveals[2] == Cubes{ .red = 1, .green = 5, .blue = 0 });
        CHECK(games[3].id == 4);
        REQUIRE(games[3].reveals.size() == 3);
        CHECK(games[3].reveals[0] == Cubes{ .red = 3, .green = 1, .blue = 6 });
        CHECK(games[3].reveals[1] == Cubes{ .red = 6, .green = 3, .blue = 0 });
        CHECK(games[3].reveals[2] == Cubes{ .red = 14, .green = 3, .blue = 15 });
        CHECK(games[4].id == 5);
        REQUIRE(games[4].reveals.size() == 2);
        CHECK(games[4].reveals[0] == Cubes{ .red = 6, .green = 3, .blue = 1 });
        CHECK(games[4].reveals[1] == Cubes{ .red = 1, .green = 2, .blue = 2 });
    }

    SECTION("Guess 1")
    {
        CHECK(guess1() == Cubes{ .red = 12, .green = 13, .blue = 14 });
    }

    SECTION("Game Is Possible")
    {
        CHECK(isPossible(guess1(), games[0]));
        CHECK(isPossible(guess1(), games[1]));
        CHECK_FALSE(isPossible(guess1(), games[2]));
        CHECK_FALSE(isPossible(guess1(), games[3]));
        CHECK(isPossible(guess1(), games[4]));
    }

    SECTION("Answer 1")
    {
        CHECK(answer1(games) == 8);
    }

    SECTION("Power")
    {
        CHECK(power(games[0]) == 48);
        CHECK(power(games[1]) == 12);
        CHECK(power(games[2]) == 1560);
        CHECK(power(games[3]) == 630);
        CHECK(power(games[4]) == 36);
    }

    SECTION("Answer 2")
    {
        CHECK(answer2(games) == 2286);
    }
}
