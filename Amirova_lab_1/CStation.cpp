#pragma once
#include "CStation.h"
#include <string>
#include "utils.h"

std::ostream& operator<<(std::ostream& out, const CStation& s)
{
    out << "Name: " << s.name
        << "\tNumber of guild: " << s.number_of_guild
        << "\tNumber of working guild: " << s.number_of_working_guild
        << "\tEffectiveness: " << s.effectiveness << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, CStation& s)
{
    std::cout << "Oil station" << std::endl;
    std::cout << "Name: ";
    std::cin.ignore(1000, '\n');
    getline(std::cin, s.name);
    std::cout << "Number of guild" << std::endl;
    s.number_of_guild = get_correct_number(1, 1000);
    std::cout << "Number of working guild" << std::endl;
    s.number_of_working_guild = get_correct_number(0, s.number_of_guild);
    std::cout << "Effectiveness" << std::endl;
    s.effectiveness = get_correct_number(0, 100);
    return in;
}
