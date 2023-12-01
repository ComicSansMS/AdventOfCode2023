module;

#include <numeric>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

export module trebuchet;

export struct CalibrationDocument {
    std::vector<std::string> v;
};

export CalibrationDocument parseInput(std::string_view input)
{
    CalibrationDocument ret;
    std::ranges::copy(input |
        std::ranges::views::split('\n') |
        std::ranges::views::filter([](auto r) { return !std::ranges::empty(r); }) |
        std::ranges::views::transform([](auto r) -> std::string { return std::string{ r.begin(), r.end() }; }),
        std::back_inserter(ret.v));
    return ret;
}

export int getCalibrationNumber(std::string_view s)
{
    char const* digits = "0123456789";
    int const first = s[s.find_first_of(digits)] - '0';
    int const last = s[s.find_last_of(digits)] - '0';
    return first * 10 + last;
}

export int answer1(CalibrationDocument const& d)
{
    auto rv = d.v | std::ranges::views::transform(getCalibrationNumber);
    return std::accumulate(std::ranges::begin(rv), std::ranges::end(rv), 0);
}

export int getCalibrationNumber2_old(std::string_view s)
{
    char const* digits = "0123456789";
    char const* digit_strs[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    std::size_t it_first = s.find_first_of(digits);
    int first = (it_first != std::string_view::npos ? s[it_first] - '0' : 99);
    std::size_t it_last = s.find_last_of(digits);
    int last = (it_last != std::string_view::npos ? s[it_last] - '0' : 99);
    for (int i = 0; i < 9; ++i) {
        auto it = s.find(digit_strs[i]);
        if (it != std::string_view::npos) {
            if ((it < it_first) || (it_first == std::string_view::npos)) {
                it_first = it;
                first = i + 1;
            }
        }
        it = s.rfind(digit_strs[i]);
        if (it != std::string_view::npos) {
            if ((it > it_last) || (it_last == std::string_view::npos)) {
                it_last = it;
                last = i + 1;
            }
        }
    }
    return first * 10 + last;
}


export int getCalibrationNumber2(std::string_view s)
{
    char const* digits = "0123456789";
    char const* digit_strs[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    std::size_t it_first = s.find_first_of(digits);
    int first = (it_first != std::string_view::npos ? s[it_first] - '0' : 99);
    std::size_t it_last = s.find_last_of(digits);
    int last = (it_last != std::string_view::npos ? s[it_last] - '0' : 99);
    for (int i = 0; i < 9; ++i) {
        auto it = s.find(digit_strs[i]);
        if (it != std::string_view::npos) {
            if ((it < it_first) || (it_first == std::string_view::npos)) {
                it_first = it;
                first = i + 1;
            }
        }
        it = s.rfind(digit_strs[i]);
        if (it != std::string_view::npos) {
            if ((it > it_last) || (it_last == std::string_view::npos)) {
                it_last = it;
                last = i + 1;
            }
        }
    }
    return first * 10 + last;
}

export int answer2(CalibrationDocument const& d)
{
    auto rv = d.v | std::ranges::views::transform(getCalibrationNumber2);
    return std::accumulate(std::ranges::begin(rv), std::ranges::end(rv), 0);
}
