#pragma once
#include <string>
#include "utils.h"

class CPipe
{  
    int id;
public:
    static int MaxId;
    std::string name;
    double lenght;
    int diameter;
    bool reparied;

    CPipe();

    friend  std::ostream& operator << (std::ostream& out, const CPipe& p);
    friend std::istream& operator >> (std::istream& in, CPipe& p);
    void edit_pipe();

};

