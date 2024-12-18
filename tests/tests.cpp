#include <iostream>
#include "Cool/get_system_error.hpp"

int main()
{
    std::cout << Cool::get_system_error() << '\n';
}