module;

#include <cassert>

module cube_conundrum;

template<>
struct std::formatter<Cubes>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(Cubes const& c, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "{{ red : {}, green : {}, blue : {} }}", c.red, c.green, c.blue);
    }
};

std::ostream& operator<<(std::ostream& os, Cubes const& c) {
    return os << std::format("{}", c);
}

std::vector<Game> parseInput(std::string_view input)
{
    std::vector<Game> ret;
    assert(input.ends_with('\n'));
    input = input.substr(0, input.size() - 1);
    for (auto const& r_line : input | std::ranges::views::split('\n')) {
        std::string_view line(std::ranges::begin(r_line), std::ranges::end(r_line));
        auto it_number_end = line.find(": ");
        auto const str_game_id = line.substr(5, it_number_end - 5);
        ret.emplace_back();
        std::from_chars(&str_game_id.front(), &str_game_id.back() + 1, ret.back().id);
        line = line.substr(it_number_end + 1);
        for (auto const& r_reveal : line | std::ranges::views::split(';')) {
            std::string_view reveal(std::ranges::begin(r_reveal), std::ranges::end(r_reveal));
            Cubes c{};
            for (auto const& r_cube : reveal | std::ranges::views::split(',')) {
                std::string_view cube(std::ranges::begin(r_cube), std::ranges::end(r_cube));
                assert(cube[0] == ' ');
                cube = cube.substr(1);
                auto const n = cube.substr(0, cube.find(" "));
                int i;
                std::from_chars(&n.front(), &n.back() + 1, i);
                if (cube.ends_with("red")) {
                    c.red = i;
                } else if (cube.ends_with("green")) {
                    c.green = i;
                } else {
                    assert(cube.ends_with("blue"));
                    c.blue = i;
                }
            }
            ret.back().reveals.push_back(c);
        }
    }
    return ret;
}

Cubes guess1()
{
    return Cubes{ .red = 12, .green = 13, .blue = 14 };
}

bool isPossible(Cubes const& guess, Cubes const& reveal) {
    return (reveal.red <= guess.red) && (reveal.green <= guess.green) && (reveal.blue <= guess.blue);
}

bool isPossible(Cubes const& guess, Game const& game) {
    return std::ranges::all_of(game.reveals, [&guess](Cubes const& c) { return isPossible(guess, c); });
}

int answer1(std::vector<Game> const& games)
{
    Cubes const guess = guess1();
    auto r = games | std::ranges::views::filter([&guess](Game const& g) { return isPossible(guess, g); });
    auto v = std::ranges::to<std::vector<Game>>(r);
    return std::accumulate(std::ranges::begin(r), std::ranges::end(r), 0, [](int acc, Game const& g) { return acc + g.id; });
}

int64_t power(Game const& g)
{
    Cubes max{};
    for (auto const r : g.reveals) {
        max.red = std::max(max.red, r.red);
        max.green = std::max(max.green, r.green);
        max.blue = std::max(max.blue, r.blue);
    }
    return static_cast<int64_t>(max.red) * static_cast<int64_t>(max.green) * static_cast<int64_t>(max.blue);
}

int64_t answer2(std::vector<Game> const& games)
{
    auto r = games | std::ranges::views::transform(power);
    return std::accumulate(std::ranges::begin(r), std::ranges::end(r), int64_t{ 0 });
}
