#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


class CPipe
{  
public:
    int id;
    static int MaxId;
    std::string name;
    double length;
    int diameter;
    bool reparied;
    bool in_system;
    int productivity;

    template <typename T>
    friend T get_correct_number(T min, T max);
    friend int get_correct_diameter();

    CPipe();

    friend  std::ostream& operator << (std::ostream& out, const CPipe& p);
    friend std::istream& operator >> (std::istream& in, CPipe& p);
    void edit_pipe();
    std::string get_type();

};

