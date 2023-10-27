#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<set>
#include <unordered_map>
#include "CPipe.h"
#include "CStation.h"
#include "utils.h"
using namespace std;

template<typename T>
void add_object(unordered_map<int, T>& objects) {
    T obj;
    cin >> obj;
    objects.insert({obj.id, obj});
}

void show_objects(unordered_map<int, CPipe>& pipes, unordered_map<int, CStation>& stations) {
    if (pipes.size() > 0) {
        cout << "Pipes" << endl;
        for (auto& i: pipes) cout << i.second << endl;
    }
    else cout << "no pipes" << endl;
    if (stations.size() > 0) {
        cout << "Stations" << endl;
        for (auto& i:stations) cout << i.second << endl;
    }
    else cout << "no stations" << endl;
}

void edit_pipes(unordered_map<int, CPipe>& pipes) {
    set<int> pipes_to_edit;
    if (pipes.size() > 0) {
        cout << "Edit all pipes - 0, choose pipes to edit - 1" << endl;
        if (get_correct_number(0, 1)) {
            while (true) {
                cout << "0 - stop, 1 - continue" << endl;
                if (get_correct_number(0, 1)) {
                    cout << "Enter id: " << endl;
                    pipes_to_edit.insert(get_correct_number(0, CPipe::MaxId));
                }
                else break;
            }
            for (auto i : pipes_to_edit) for (auto& j : pipes) if (j.second.id == i) j.second.edit_pipe();
        }
        else for (auto& i : pipes) i.second.edit_pipe();
    }
    else cout << "no pipe" << endl;
}

void edit_stations(unordered_map<int, CStation>& stations) {
    if (stations.size() > 0) (select_station(stations)).edit_station();
    else cout << "no stations" << endl;
}

void delete_object(unordered_map<int, CPipe>& pipes, unordered_map<int, CStation>& stations) {
    int id;
    cout << "Delete pipe - 0, delete station - 1" << endl;
    int command = get_correct_number(0, 1);
    if (command && stations.size() > 0) {
        cout << "Enter id" << endl;
        id = get_correct_number(0, CStation::MaxId - 1);
        erase(stations, id);
    }
    else if (command && stations.size() == 0) cout << "no station" << endl;
    if (!command && pipes.size() > 0) {
        cout << "Enter id" << endl;
        id = get_correct_number(0, CPipe::MaxId - 1);
        erase(pipes, id);
    }
    else if (!command && pipes.size() == 0) cout << "no pipe" << endl;
}

template<typename T>
using PFilter = bool(*)(const CPipe& s, T param);

template<typename T>
using SFilter = bool(*)(const CStation& s, T param);

template <typename T>
unordered_map<int, CPipe> find_pipe_by_filter(const unordered_map<int, CPipe>& objects, PFilter<T> f, T param) {
    unordered_map<int, CPipe> res;
    for (auto s : objects) if (f(s.second, param)) res.insert({ s.first, s.second });
    if (res.size() == 0) cout << "no pipes with such parameters" << endl;
    return res;
}

template <typename T>
unordered_map<int, CStation> find_station_by_filter(const unordered_map<int, CStation>& objects, SFilter<T> f, T param) {
    unordered_map<int, CStation> res;
    for (auto& s : objects) if (f(s.second, param)) res.insert(s);
    if (res.size() == 0) cout << "no stations with such parameters" << endl;
    return res;
}

template<typename T>
bool check_by_name(const T& s, string param)
{
    bool found = s.name.find(param) != string::npos;
    return found;
}

bool check_by_reparied(const CPipe& s, bool param)
{
    return s.reparied == param;
}

bool check_by_working_guilds(const CStation& s, double target)
{
    double wg = s.number_of_working_guild;
    double g = s.number_of_guild;
    return ((g - wg)/g) * 100 == target;
}

void find_pipe(const unordered_map<int, CPipe>& pipes) {
    if (pipes.size() == 0) {
        cout << "no pipes" << endl;
        return;
    }
    string name;
    int command;
    bool status;
    cout << "Find pipe by name - 0, find pipe by reparied status - 1 :" << endl;
    command = get_correct_number(0, 1);
    if (command) {
        cout << "Enter reparied status (0 - no, 1 - yes): " << endl;
        cin >> status;
        for (auto i : find_pipe_by_filter(pipes, check_by_reparied, status))
            cout << i.second;
    }
    else {
        cout << "Enter name: " << endl;
        cin.ignore(1000, '\n');
        getline(cin, name);
        for (auto i : find_pipe_by_filter(pipes, check_by_name, name))
            cout << i.second;
    }
}

void find_station(const unordered_map<int, CStation>& stations) {
    if (stations.size() == 0) {
        cout << "no stations" << endl;
        return;
    }
    string name;
    int command;
    cout << "Find station by name - 0, find station by percentage of not working guilds - 1 :" << endl;
    command = get_correct_number(0, 1);
    if (command) {
        cout << "Enter percentage of not working guilds" << endl;
        double target = get_correct_number(0.0, 100.0);
        for (auto i : find_station_by_filter(stations, check_by_working_guilds, target))
            cout << i.second;
    }
    else {
        cout << "Enter name: " << endl;
        cin.ignore(1000, '\n');
        getline(cin, name);
        for (auto i : find_station_by_filter(stations, check_by_name, name))
            cout << i.second;
    }
}

void menu() {
    cout << "Menu" << endl
        << "1 - create oil pipe" << endl
        << "2 - create oil pumping station" << endl
        << "3 - show all objects" << endl
        << "4 - edit oil pipe" << endl
        << "5 - edit oil pumping station" << endl
        << "6 - save to file" << endl
        << "7 - load from file" << endl
        << "8 - find pipe by filter " << endl
        << "9 - find station by filter " << endl
        << "10 - delete object by id " << endl
        << "0 - exit" << endl;
}

int main()
{
    unordered_map<int, CPipe> pipes;
    unordered_map<int, CStation> stations;

    while (true) {
        menu();
        int command = get_correct_number(0, 10);
        switch (command) {
        case 1:
            add_object(pipes);
            break;
        case 2:
            add_object(stations);
            break;
        case 3:
            show_objects(pipes, stations);
            break;
        case 4:
            edit_pipes(pipes);
            break;
        case 5:
            edit_stations(stations);
            break;
        case 6:
            save_to_file(pipes, stations);
            break;
        case 7:
            load_from_file(pipes, stations);
            break;
        case 8:
            find_pipe(pipes);
            break;
        case 9:
            find_station(stations);
            break;
        case 10:
            delete_object(pipes, stations);
            break;
        case 0: return 0;
        }
    }
    return 0;
}

//вынести функции в файл утилс
//вынести функции в файл трубы и станции