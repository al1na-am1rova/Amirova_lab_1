#include "CSystem.h"
#include <iostream>
#include <string>
#include "CStation.h"
#include "CPipe.h"

using namespace std;

int CSystem::MaxId = 0;
CSystem::CSystem() {
    id = MaxId++;
}

string CSystem::get_type()
{
    return "system";
}

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

ostream& operator<<(ostream& out, const CSystem& g)
{
    out << "Id: " << g.id
        << "\tEntrance station id: " << g.entrance_id
        << "\tPipe id: " << g.pipe_id
        << "\tExit station id: " << g.exit_id << endl;
    return out;
}

istream& operator>>(istream& in, CSystem& g)
{
    cout << "Oil Pipeline System" << endl;
    cout << "Enter id of entrance station: ";
    g.entrance_id = get_correct_number(0, CStation::MaxId);
    cout << "Enter id of exit station: " << endl;
    g.exit_id = get_correct_number(0, CStation::MaxId);
    cout << "Enter id of of pipe: " << endl;
    g.pipe_id = get_correct_number(0, CPipe::MaxId);
    return in;
}
