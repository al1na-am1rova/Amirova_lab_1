#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "utils.h"

class CStation
{
public:
    int id;
    static int MaxId;
    std::string name;
    int number_of_guild;
    int number_of_working_guild;
    float effectiveness;

    CStation();

    friend std::ostream& operator << (std::ostream& out, const CStation& s);
    friend std::istream& operator >> (std::istream& in, CStation& s);
    void edit_station();
    friend CStation& select_station(std::unordered_map<int, CStation>& stations);
};

