import cube_conundrum;

#include <expected>
#include <fstream>
#include <format>
#include <iostream>
#include <print>
#include <sstream>
#include <string>

struct FileError {
    std::string e;
};

std::expected<std::string, FileError> readInput(char const* filename)
{
    std::ifstream fin(filename);
    if(!fin) {
        return std::unexpected(FileError{ .e = std::format("Unable to open input file '{}' for reading.", filename) });
    }

    std::stringstream sstr;
    sstr << fin.rdbuf();
    if(!fin) {
        return std::unexpected(FileError{ .e = std::format("Unable to read input from file '{}'.", filename) });
    }
    return sstr.str();
}

int main(int argc, char* argv[])
{
    char const* input_filename = "input";
    if(argc == 2) {
        input_filename = argv[1];
    }

    auto const exp_input = readInput(input_filename);

    if (!exp_input) {
        std::println(std::cerr, "Error: {}", exp_input.error().e);
        return 1;
    }

    auto const games = parseInput(*exp_input);
    std::println("First result is {}", answer1(games));
    std::println("Second result is {}", answer2(games));
}
