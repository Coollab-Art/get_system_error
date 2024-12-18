#include <cassert>
#include <fstream>
#include <iostream>
#include "Cool/get_system_error.hpp"

int main()
{
    auto file = std::ifstream{"nonexistent_file.txt"};
    assert(!file);
    std::cout << Cool::get_system_error() << '\n';
}