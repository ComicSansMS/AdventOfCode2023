module;

#include <algorithm>
#include <cassert>
#include <charconv>
#include <format>
#include <functional>
#include <numeric>
#include <optional>
#include <ostream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>
#include <print>
#include <unordered_map>

export module scratchcards;

export struct Card {
    std::vector<int> numbers;
    std::vector<int> winning;
};

export std::vector<Card> parseInput(std::string_view input)
{
    enum class Parse {
        AwaitColon,
        AwaitNumber,
        InNumber,
        AwaitWinning,
        InWinning
    } state = Parse::AwaitColon;
    int n;
    std::vector<Card> ret;
    for (std::string_view::const_iterator it = std::ranges::begin(input), it_end = std::ranges::end(input); it != it_end; ++it) {
        char const c = *it;
        switch (state) {
        case Parse::AwaitColon:
            if (c == ':') {
                ret.emplace_back();
                state = Parse::AwaitNumber;
            }
            assert(c != '|');
            break;
        case Parse::AwaitNumber:
            if (std::isdigit(c)) {
                n = c - '0';
                state = Parse::InNumber;
            } else if (c == '|') {
                state = Parse::AwaitWinning;
            }
            assert(c != '\n');
            break;
        case Parse::InNumber:
            if (std::isdigit(c)) {
                n = n*10 + (c - '0');
            } else {
                ret.back().numbers.push_back(n);
                state = Parse::AwaitNumber;
            }
            assert(c != '\n');
            break;
        case Parse::AwaitWinning:
            if (std::isdigit(c)) {
                n = c - '0';
                state = Parse::InWinning;
            }
            assert(c != '|');
            break;
        case Parse::InWinning:
            if (std::isdigit(c)) {
                n = n*10 + (c - '0');
            } else {
                ret.back().winning.push_back(n);
                state = Parse::AwaitWinning;
            }
            assert(c != '|');
            break;
        }
        if (c == '\n') {
            assert(state == Parse::AwaitWinning);
            state = Parse::AwaitColon;
        }
    }
    return ret;
}

export int64_t countWinningNumbers(Card const& c)
{
    return std::ranges::count_if(c.numbers, [&winning = c.winning](int n) {
            return (std::ranges::find(winning, n) != std::ranges::end(winning));
    });
}

export int64_t answer1(std::vector<Card> const& cards)
{
    return std::accumulate(std::ranges::begin(cards), std::ranges::end(cards), std::int64_t{ 0 },
        [](std::int64_t acc, Card const& c) {
            auto const w = countWinningNumbers(c);
            return acc + ((w > 0) ? (std::int64_t{ 1 } << (w - 1)) : 0);
        });
}

export int64_t answer2(std::vector<Card> const& cards)
{
    std::vector<std::int64_t> copies(cards.size(), 1);
    for (std::size_t i = 0, i_end = cards.size(); i != i_end; ++i) {
        Card const& card = cards[i];
        int64_t const win = countWinningNumbers(card);
        for (std::size_t j = i + 1; j < std::min(i + 1 + win, i_end); ++j) {
            copies[j] += copies[i];
        }
    }
    return std::accumulate(std::ranges::begin(copies), std::ranges::end(copies), std::int64_t{ 0 });
}
