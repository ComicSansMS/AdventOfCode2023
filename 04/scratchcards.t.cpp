#include <catch.hpp>

import scratchcards;

TEST_CASE("Scratchcards")
{
    char const sample_input[] =
        R"(Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11
)";

    auto const cards = parseInput(sample_input);
    SECTION("Parse Input")
    {
        REQUIRE(cards.size() == 6);
        CHECK(cards[0].numbers == std::vector<int>{41, 48, 83, 86, 17});
        CHECK(cards[0].winning == std::vector<int>{83, 86, 6, 31, 17, 9, 48, 53});
        CHECK(cards[1].numbers == std::vector<int>{13, 32, 20, 16, 61});
        CHECK(cards[1].winning == std::vector<int>{61, 30, 68, 82, 17, 32, 24, 19});
        CHECK(cards[2].numbers == std::vector<int>{1, 21, 53, 59, 44});
        CHECK(cards[2].winning == std::vector<int>{69, 82, 63, 72, 16, 21, 14, 1});
        CHECK(cards[3].numbers == std::vector<int>{41, 92, 73, 84, 69});
        CHECK(cards[3].winning == std::vector<int>{59, 84, 76, 51, 58, 5, 54, 83});
        CHECK(cards[4].numbers == std::vector<int>{87, 83, 26, 28, 32});
        CHECK(cards[4].winning == std::vector<int>{88, 30, 70, 12, 93, 22, 82, 36});
        CHECK(cards[5].numbers == std::vector<int>{31, 18, 13, 56, 72});
        CHECK(cards[5].winning == std::vector<int>{74, 77, 10, 23, 35, 67, 36, 11});
    }

    SECTION("Count winning numbers")
    {
        CHECK(countWinningNumbers(cards[0]) == 4);
        CHECK(countWinningNumbers(cards[1]) == 2);
        CHECK(countWinningNumbers(cards[2]) == 2);
        CHECK(countWinningNumbers(cards[3]) == 1);
        CHECK(countWinningNumbers(cards[4]) == 0);
        CHECK(countWinningNumbers(cards[5]) == 0);
    }

    SECTION("Answer 1")
    {
        CHECK(answer1(cards) == 13);
    }

    SECTION("Answer 2")
    {
        CHECK(answer2(cards) == 30);
    }
}
