module;

#include <experimental/mdspan>

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

export module gear_ratios;

using FieldSpanLayout = std::experimental::layout_left;
using FieldSpanExtents = std::experimental::extents<int, std::experimental::dynamic_extent,
    std::experimental::dynamic_extent>;

export struct Field {
    std::vector<char> field;
    std::experimental::mdspan<char, FieldSpanExtents, FieldSpanLayout> span;
};

export Field parseInput(std::string_view input)
{
    Field ret;
    int field_width = 0;
    int field_height = 0;
    int line_count = 0;
    for (auto const& c : input) {
        if (c == '\n') {
            if (field_width == 0) {
                field_width = line_count;
            }
            assert(field_width == line_count);
            line_count = 0;
            ++field_height;
        } else {
            ++line_count;
            ret.field.push_back(c);
        }
    }
    ret.span = decltype(ret.span)(ret.field.data(), field_width, field_height);
    return ret;
}

void iterate8Neighborhood(Field const& f, int x, int y, int len, std::function<bool(int /* ix */, int /* iy */, char /* c */)> const& func)
{
    auto const visitCell = [&f, &func](int ix, int iy) -> bool {
        if ((ix >= 0) && (ix < f.span.extent(0))) {
            char const c = f.span(ix, iy);
            return func(ix, iy, c);
        }
        return true;
    };
    auto const iterateRow = [&visitCell, &f](int x, int iy, int len) -> bool {
        if ((iy >= 0) && (iy < f.span.extent(1))) {
            for (int ix = x - 1; ix < x + len + 1; ++ix) {
                if (!visitCell(ix, iy)) { return false; }
            }
        }
        return true;
    };
    // top row
    int iy = y - 1;
    if (!iterateRow(x, iy, len)) { return; }
    // middle row
    ++iy;
    if ((iy >= 0) && (iy < f.span.extent(1))) {
        if (!visitCell(x - 1, iy)) { return; }
        if (!visitCell(x + len, iy)) { return; }
    }
    // bottom row
    ++iy;
    if (!iterateRow(x, iy, len)) { return; }
}

struct Symbol {
    char c;
    int x;
    int y;
};

Symbol extractAdjacentSymbol(Field const& f, int x, int y, int len)
{
    // iterate 8 neighbourhood
    Symbol ret = Symbol{ .c = '.', .x = -1, .y = -1 };
    iterate8Neighborhood(f, x, y, len, [&ret](int ix, int iy, char c) {
        if (c != '.') {
            ret.c = c;
            ret.x = ix;
            ret.y = iy;
            return false;
        }
        return true;
    });
    return ret;
}

export void iterateParts(Field const& f, std::function<void(int /* part */, int /* idx_x */, int /* idx_y */, char /* adjacent_symbol */)> const& func)
{
    struct InDigit {
        int value;
        int idx;
        int idy;
        int len;
    };
    std::optional<InDigit> in_digit;
    for (int iy = 0; iy < f.span.extent(1); ++iy) {
        for (int ix = 0; ix < f.span.extent(0); ++ix) {
            char const c = f.span(ix, iy);
            if ((c >= '0') && (c <= '9')) {
                int digit = c - '0';
                if (!in_digit) {
                    in_digit = InDigit{ .value = digit, .idx = ix, .idy = iy, .len = 1 };
                } else {
                    ++in_digit->len;
                    in_digit->value = (in_digit->value * 10) + digit;
                }
            } else if (in_digit) {
                Symbol const s = extractAdjacentSymbol(f, in_digit->idx, in_digit->idy, in_digit->len);
                func(in_digit->value, s.x, s.y, s.c);
                in_digit = std::nullopt;
            }
        }
        if (in_digit) {
            Symbol const s = extractAdjacentSymbol(f, in_digit->idx, in_digit->idy, in_digit->len);
            func(in_digit->value, s.x, s.y, s.c);
            in_digit = std::nullopt;
        }
    }
}

export std::int64_t answer1(Field const& f)
{
    int64_t ret = 0;
    iterateParts(f, [&ret](int part, int, int, char c) {
        if (c != '.') {
            ret += static_cast<std::int64_t>(part);
        }
    });
    return ret;
}

struct Point {
    int x;
    int y;

    friend bool operator==(Point const&, Point const&) = default;
};

struct HashPoint {
    inline std::size_t operator()(Point const& p) const {
        return p.y * 1000 + p.x;
    }
};

export std::int64_t answer2(Field const& f)
{
    std::unordered_map<Point, std::vector<std::int64_t>, HashPoint> gears;
    iterateParts(f, [w = f.span.extent(0), h = f.span.extent(1), &gears](int part, int ix, int iy, char c) {
        if (c == '*') {
            gears[Point{ .x = ix, .y = iy }].push_back(part);
        }
    });
    std::int64_t ret = 0;
    for (auto const& [point, parts] : gears) {
        if (parts.size() == 2) {
            ret += parts[0] * parts[1];
        }
    }
    return ret;
}
