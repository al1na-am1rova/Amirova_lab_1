#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<set>
#include <unordered_map>
#include "CPipe.h"
#include "CStation.h"
#include "CSystem.h"
#include "utils.h"

using namespace std;

//template <typename T>
//T get_correct_number(T min, T max)
//{
//    T x;
//    while ((cin >> x).fail()
//        || cin.peek() != '\n'
//        || x < min || x > max)
//    {
//        cin.clear();
//        cin.ignore(10000, '\n');
//        cout << "Type number (" << min << "-" << max << "):";
//    }
//    return x;
//}

//int get_correct_d()
//{
//    int x;
//    while ((cin >> x).fail()
//        || cin.peek() != '\n'
//        || (x != 500 && x != 700 && x != 1000 && x != 1400))
//    {
//        cin.clear();
//        cin.ignore(10000, '\n');
//        cout << "Type number 500, 700, 1000 or 1400:" << endl;
//    }
//    return x;
//}

//template<typename T>
//void erase(unordered_map<int, T>& objects, int id) {
//    if (objects.find(id) != objects.end()) objects.erase(objects.find(id));
//    else cout << "there is no object with this id" << endl;
//}

//template<typename T>
//using PFilter = bool(*)(const CPipe& s, T param);

//template<typename T>
//using SFilter = bool(*)(const CStation& s, T param);

//template <typename T>
//unordered_map<int, CPipe> find_pipe_by_filter(const unordered_map<int, CPipe>& objects, PFilter<T> f, T param) {
//    unordered_map<int, CPipe> res;
//    for (auto s : objects) if (f(s.second, param)) res.insert({ s.first, s.second });
//    if (res.size() == 0) cout << "no pipes with such parameters" << endl;
//    return res;
//}

//template <typename T>
//unordered_map<int, CStation> find_station_by_filter(const unordered_map<int, CStation>& objects, SFilter<T> f, T param) {
//    unordered_map<int, CStation> res;
//    for (auto& s : objects) if (f(s.second, param)) res.insert(s);
//    if (res.size() == 0) cout << "no stations with such parameters" << endl;
//    return res;
//}

//template<typename T>
//bool check_by_name(const T& s, string param)
//{
//    bool found = s.name.find(param) != string::npos;
//    return found;
//}
//
//bool check_by_reparied(const CPipe& s, bool param)
//{
//    return s.reparied == param;
//}
//
//bool check_by_diameter(const CPipe& p, int param) {
//    return p.diameter == param;
//}
//
//bool check_by_working_guilds(const CStation& s, double target)
//{
//    double wg = s.number_of_working_guild;
//    double g = s.number_of_guild;
//    return ((g - wg)/g) * 100 == target;
//}

template<typename T>
void add_object(unordered_map<int, T>& objects) {
    T obj;
    cin >> obj;
    objects.insert({ obj.id, obj });
}

void add_system(unordered_map<int, CSystem>& system, unordered_map<int, CPipe>& pipes, unordered_map<int, CStation> stations) {
    if (pipes.size() == 0) {
        cout << "no pipe" << endl;
        return;
    }
    if (stations.size() < 2) {
        cout << "not enough stations" << endl;
        return;
    }
    CSystem g;
    cout << "Oil Pipeline System" << endl;
    cout << "Enter id of entrance station: ";
    g.entrance_id = get_correct_entrance_id(stations);
    cout << "Enter id of exit station: " << endl;
    g.exit_id = get_correct_exit_id(stations, g.entrance_id);
    if (already_in_system(g.entrance_id, g.exit_id, system)) {
        cout << "This stations are already connected" << endl;
        return;
    }
    cout << "Enter diameter of of pipe: " << endl;
    int d = get_correct_d();
    for (auto& i : pipes) if (check_by_diameter(i.second, d) and i.second.in_system == false and i.second.reparied == false) {
        g.pipe_id = i.second.id;
        i.second.in_system = true;
        system.insert({ g.id, g });
        cout << g << endl;
        return;
    }
    cout << "no suitable pipe. Want to create a new pipe?(1- yes, 0 - no)" << endl;
    if (get_correct_number(0, 1)) {
        CPipe p;
        cin >> p;
        g.pipe_id = p.id;
        p.in_system = true;
        pipes.insert({ p.id, p });
        system.insert({ g.id, g });
        cout << g << endl;
        return;
    }
    return;
}

void show_objects(unordered_map<int, CPipe>& pipes, unordered_map<int, CStation>& stations, unordered_map<int, CSystem>& system) {
    if (pipes.size() > 0) {
        cout << "Pipes" << endl;
        for (auto& i : pipes) cout << i.second << endl;
    }
    else cout << "no pipes" << endl;
    if (stations.size() > 0) {
        cout << "Stations" << endl;
        for (auto& i : stations) cout << i.second << endl;
    }
    else cout << "no stations" << endl;
    if (system.size() > 0) {
        cout << "Systems" << endl;
        for (auto i : system) cout << i.second;
    }
    else cout << "no system" << endl;
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

void save_to_file(unordered_map<int, CPipe>& pipes, unordered_map<int, CStation>& stations, unordered_map<int, CSystem>& systems) {
    if (pipes.size() == 0 && stations.size() == 0) {
        cout << "no pipe, no station" << endl;
        return;
    }
    ofstream fout;
    string filename;
    cout << "Enter file name" << endl;
    cin >> filename;
    fout.open(filename, ios::out);
    if (fout.is_open()) {
        fout << pipes.size() << endl;
        if (pipes.size() > 0) {
            for (auto& p : pipes) {
                fout << p.second.name << endl << p.second.length << endl << p.second.diameter << endl << p.second.reparied << endl;
            };
            cout << "pipes successfully saved to file" << endl;
        }
        else cout << "no pipe to save" << endl;
        fout << stations.size() << endl;
        if (stations.size() > 0) {
            for (auto& s : stations) {
                fout << s.second.name << endl << s.second.number_of_guild << endl << s.second.number_of_working_guild << endl << s.second.effectiveness << endl;
            }
            cout << "stations successfully saved to file" << endl;
        }
        else cout << "no station to save" << endl;
        fout << systems.size() << endl;
        if (systems.size() > 0) {
            for (auto g : systems) {
                fout << g.second.entrance_id << endl << g.second.exit_id << endl << g.second.pipe_id << endl;
            }
            cout << "systems successfully saved to file" << endl;
        }
        else cout << "no system to save" << endl;
        fout.close();
    }
    else cout << "File is not open. Maybe it doesn't exist." << endl;
}

void load_from_file(unordered_map<int, CPipe>& pipes, unordered_map<int, CStation>& stations, unordered_map<int, CSystem>& systems) {
    if (pipes.size() > 0 || stations.size() > 0) {
        cout << "The data from the file will replace the existing data. Continue anyway? (0 - no, 1 - yes)" << endl;
        if (get_correct_number(0, 1)) {
            pipes.clear();
            stations.clear();
        }
        else return;
    }
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
            fin >> p.length >> p.diameter >> p.reparied;
            pipes.insert({ p.id, p });
        }
        fin >> counter;
        for (int i = counter; i > 0; i--) {
            CStation s;
            fin.ignore();
            getline(fin, s.name);
            fin >> s.number_of_guild >> s.number_of_working_guild >> s.effectiveness;
            stations.insert({ s.id, s });
        }
        fin >> counter;
        for (int i = counter; i > 0; i--) {
            CSystem g;
            fin.ignore();
            fin >> g.entrance_id >> g.exit_id >> g.pipe_id;
            systems.insert({ g.id, g });
        }
    }
    else cout << "File is not open. Maybe it doesn't exist" << endl;
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
        << "11 - create Oil Pipeline System " << endl
        << "0 - exit" << endl;
}

int main()
{
    unordered_map<int, CPipe> pipes;
    unordered_map<int, CStation> stations;
    unordered_map<int, CSystem> systems;

    while (true) {
        menu();
        int command = get_correct_number(0, 11);
        switch (command) {
        case 1:
            add_object(pipes);
            break;
        case 2:
            add_object(stations);
            break;
        case 3:
            show_objects(pipes, stations, systems);
            break;
        case 4:
            edit_pipes(pipes);
            break;
        case 5:
            edit_stations(stations);
            break;
        case 6:
            save_to_file(pipes, stations, systems);
            break;
        case 7:
            load_from_file(pipes, stations, systems);
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
        case 11:
            add_system(systems, pipes, stations);
            break;
        case 0: return 0;
        }
    }
    return 0;
}

// исправить ыункцию get_correct_d
// запись и чтение из фацла
//удаляем трубу = удаляем и систему 

