#pragma once
#include <iostream>

using namespace std;

template <typename T>
T get_correct_number(T min, T max)
{
    T x;
    while ((cin >> x).fail()
        || cin.peek() != '\n'
        || x < min || x > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number (" << min << "-" << max << "):";
    }
    return x;
}

int get_correct_d()
{
    int x;
    while ((cin >> x).fail()
        || cin.peek() != '\n'
        || (x != 500 && x != 700 && x != 1000 && x != 1400))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number 500, 700, 1000 or 1400:" << endl;
    }
    return x;
}

template<typename T>
using PFilter = bool(*)(const CPipe& s, T param);

template<typename T>
using SFilter = bool(*)(const CStation& s, T param);