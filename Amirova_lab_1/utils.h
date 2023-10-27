#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include<set>
#include "CPipe.h"
#include "CStation.h"

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

template<typename T>
void erase(unordered_map<int, T>& objects, int id) {
    if (objects.find(id) != objects.end()) objects.erase(objects.find(id));
    else cout << "there is no object with this id" << endl;
}

void save_to_file(unordered_map<int, class CPipe>& pipes, unordered_map<int, class CStation>& stations);

void load_from_file(unordered_map<int, class CPipe>& pipes, unordered_map<int, class CStation>& stations);
