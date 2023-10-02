#pragma once
#include <string>
#include "utils.h"

class CStation
{
    int id;
public:
    std::string name;
    int number_of_guild;
    int number_of_working_guild;
    float effectiveness;

    friend std::ostream& operator << (std::ostream& out, const CStation& s);
    friend std::istream& operator >> (std::istream& in, CStation& s);
};

