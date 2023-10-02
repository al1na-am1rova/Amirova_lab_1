#pragma once
#include "CPipe.h"
#include <string>
#include "utils.h"

using namespace std;

int CPipe::MaxId = 0;

CPipe::CPipe()
{
    id = MaxId++;
}

ostream& operator << (ostream& out, const CPipe& p) {
    out <<"Id: " << p.id
        << "Name: " << p.name
        << "\tLenght: " << p.lenght
        << "\tDiameter: " << p.diameter
        << "\tReparied: " << p.reparied << endl;
    return out;
}
istream& operator >> (istream& in, CPipe& p) {
    cout << "Oil pipe" << endl;
    cout << "Name: ";
    in.ignore(1000, '\n');
    getline(in, p.name);
    cout << "Lenght" << endl;
    p.lenght = get_correct_number(1.0, 1000.0);
    cout << "Diameter" << endl;
    p.diameter = get_correct_number(1, 1000);
    cout << "Is reparied (1 - yes, 0 - no): " << endl;
    p.reparied = get_correct_number(0, 1);
    return in;
}
