#pragma once
#include <string>
#include "utils.h"

class CPipe
{  
    int id;
public:
    std::string name;
    double lenght;
    int diameter;
    bool reparied;

    friend  std::ostream& operator << (std::ostream& out, const CPipe& p);
    friend std::istream& operator >> (std::istream& in, CPipe& p);

};

