#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<set>
#include "CPipe.h"
#include "CStation.h"
using namespace std;

void save_to_file(const vector<CPipe>& pipes, const vector<CStation>& stations) {
    ofstream fout;
    string filename;
    cout << "Enter file name" << endl;
    cin >> filename;
    fout.open(filename, ios::out);
    if (fout.is_open()) {
        fout << pipes.size() << endl;
        if (pipes.size() > 0) {
            for (CPipe p : pipes) {
                fout << p.name << endl << p.lenght << endl << p.diameter << endl << p.reparied << endl;
            };
            cout << "pipes successfully saved to file" << endl;
        }
        else cout << "no pipe to save" << endl;
        fout << stations.size() << endl;
        if (stations.size() > 0) {
            for (CStation s : stations) {
                fout << s.name << endl << s.number_of_guild << endl << s.number_of_working_guild << endl << s.effectiveness << endl;
            }
            cout << "stations successfully saved to file" << endl;
        }
        else cout << "no station to save" << endl;
        fout.close();
    }
    else cout << "File is not open. Maybe it doesn't exist." << endl;
}

void load_from_file(vector<CPipe>& pipes, vector<CStation>& stations) {
    int counter;
    ifstream fin;
    string str;
    string filename;
    cout << "Enter file name" << endl;
    cin >> filename;
    fin.open(filename, ios::in);
    if (fin.is_open()) {
        fin >> counter;
        for (int i = counter; i > 0; i--) {
            CPipe p;
            fin.ignore();
            getline(fin, p.name);
            fin >> p.lenght >> p.diameter >> p.reparied;
            pipes.push_back(p);
        }
        fin >> counter;
        for (int i = counter; i > 0; i--) {
            CStation s;
            fin.ignore();
            getline(fin, s.name);
            fin >> s.number_of_guild >> s.number_of_working_guild >> s.effectiveness;
            stations.push_back(s);
        }
    }
    else cout << "File is not open. Maybe it doesn't exist" << endl;
}

CPipe& select_pipe(vector<CPipe>& pipes) {
    cout << "Enter id: " << endl;
    int id = get_correct_number(0, CPipe::MaxId - 1);
    for (auto i : pipes) if (i.id == id) return i;
}

CStation& select_station(vector<CStation>& stations) {
    cout << "Enter id" << endl;
    int id = get_correct_number(0, CStation::MaxId - 1);
    for (auto& i : stations) if (i.id == id) return i;
}

template<typename T>
void delete_object(vector<T>& objects, int id) {
    auto it = objects.begin();
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i].id == id) {
            it = it + i;
            objects.erase(it);
            return;
        }
    }
    cout << "there is no object with this id" << endl;
}

template<typename T>
using PFilter = bool(*)(const CPipe& s, T param);

template<typename T>
using SFilter = bool(*)(const CStation& s, T param);

template <typename T>
vector<int> find_pipe_by_filter(const vector<CPipe>& objects, PFilter<T> f, T param) {
    vector<int> res;
    int i = 0;
    for (auto& s : objects)
    {
        if (f(s, param))
            res.push_back(i);
        i++;
    }
    if (res.size() == 0) cout << "no pipes with such parameters" << endl;
    return res;
}

template <typename T>
vector<int> find_station_by_filter(const vector<CStation>& objects, SFilter<T> f, T param) {
    vector<int> res;
    int i = 0;
    for (auto& s : objects)
    {
        if (f(s, param))
            res.push_back(i);
        i++;
    }
    if (res.size() == 0) cout << "no stations with such parameters" << endl;
    return res;
}

template<typename T>
bool check_by_name(const T& s, string param)
{
    return s.name == param;
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
    vector <CPipe> pipes;
    vector <CStation> stations;

    while (true) {
        menu();
        int command = get_correct_number(0, 10);
        switch (command) {
        case 1:
        {
            CPipe p;
            cin >> p;
            pipes.push_back(p); }
        break;
        case 2:
        {CStation s;
        cin >> s;
        stations.push_back(s); }
        break;
        case 3:
        {
            if (pipes.size() > 0) {
                cout << "Pipes" << endl;
                for (auto i : pipes) cout << i;
            }
            else cout << "no pipes" << endl;
            if (stations.size() > 0) {
                cout << "Stations" << endl;
                for (auto i : stations) cout << i;
            }
            else cout << "no stations" << endl;
            break;
        }

        case 4:
        {set<int> pipes_to_edit;
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
                for (auto i : pipes_to_edit) for (auto& j : pipes) if (j.id == i) j.edit_pipe();
            }
            else for (auto& i : pipes) i.edit_pipe();
        }
        else cout << "no pipe" << endl;
        break; }

        case 5:
            if (stations.size() > 0) (select_station(stations)).edit_station();
            else cout << "no station" << endl;
            break;

        case 6:
            if (pipes.size() == 0 && stations.size() == 0) cout << "no pipe, no station" << endl;
            else save_to_file(pipes, stations);
            break;

        case 7:
            cout << "The data from the file will replace the existing data. Continue anyway? (0 - no, 1 - yes)" << endl;
            command = get_correct_number(0, 1);
            if (command) {
                pipes.clear();
                stations.clear();
                load_from_file(pipes, stations);
            }
            break;

        case 8:
        {
            if (pipes.size() == 0) {
                cout << "no pipes" << endl;
                continue;
            }
            string name;
            int command;
            bool status;
            cout << "Find pipe by name - 0, find pipe by reparied status - 1 :" << endl;
            command = get_correct_number(0, 1);
            if (command) {
                cout << "Enter reparied status (0 - no, 1 - yes): " << endl;
                cin >> status;
                for (int i : find_pipe_by_filter(pipes, check_by_reparied, status))
                    cout << pipes[i];
            }
            else {
                cout << "Enter name: " << endl;
                cin >> name;
                for (int i : find_pipe_by_filter(pipes, check_by_name, name))
                    cout << pipes[i];
            }
            break;
        }
        case 9:
        {
            if (stations.size() == 0) {
                cout << "no stations" << endl;
                continue;
            }
            string name;
            int command;
            cout << "Find station by name - 0, find station by percentage of working guilds - 1 :" << endl;
            command = get_correct_number(0, 1);
            if (command) {
                cout << "Enter percentage of not working guilds" << endl;
                double target = get_correct_number(0.0, 100.0);
                for (int i : find_station_by_filter(stations, check_by_working_guilds, target))
                    cout << stations[i];
            }
            else {
                cout << "Enter name: " << endl;
                cin >> name;
                for (int i : find_station_by_filter(stations, check_by_name, name))
                    cout << stations[i];
            }
            break;
        }
        case 10:
        {
            int id;
            cout << "Delete pipe - 0, delete station - 1" << endl;
            int command = get_correct_number(0, 1);
            if (command && stations.size() > 0) {
                cout << "Enter index" << endl;
                id = get_correct_number(0, CStation::MaxId - 1);
                delete_object(stations, id);
            }
            else if (command && stations.size() == 0) cout << "no station" << endl;
            if (!command && pipes.size() > 0) {
                cout << "Enter index" << endl;
                id = get_correct_number(0, CPipe::MaxId - 1);
                delete_object(pipes, id);
            }
            else if (!command && pipes.size() == 0) cout << "no pipe" << endl;
            break;
        }
        case 0: return 0;
        }
    }
    return 0;
}

//заменить вектор на мэп
//слово длина неправильно написано))
// редактирование труб убрать сет
//вынести функции в файл утилс
//вынести функции в файл трубы и станции