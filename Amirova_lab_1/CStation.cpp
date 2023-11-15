#pragma once
#include <iostream>
#include "CStation.h"
#include <string>
#include <vector>

int CStation::MaxId = 0;

CStation::CStation()
{
    id = MaxId++;
}

template <typename T>
T get_correct_number(T min, T max)
{
    T x;
    while ((std::cin >> x).fail()
        || std::cin.peek() != '\n'
        || x < min || x > max)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Type number (" << min << "-" << max << "):";
    }
    return x;
}

void CStation::edit_station()
{
        int command;
        std::cout << "Enter number of working guild" << std::endl;
        number_of_working_guild = get_correct_number(0, number_of_guild);
        std::cout << "Station name: " << name << "  Number of working guild: " << number_of_working_guild << std::endl;
}

std::ostream& operator<<(std::ostream& out, const CStation& s)
{
    out << "Id: " << s.id
        << "\tName: " << s.name
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

CStation& select_station(std::unordered_map<int, CStation>& stations) {
    std::cout << "Enter id" << std::endl;
    int id = get_correct_number(0, CStation::MaxId - 1);
    for (auto& i : stations) if (i.first == id) return i.second;
}

