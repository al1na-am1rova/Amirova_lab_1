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

template<typename T>
void add_object(unordered_map<int, T>& objects) {
    T obj;
    cin >> obj;
    objects.insert({ obj.id, obj });

    ofstream fout;
    fout.open("log.txt", ios::app);
    fout << "add " << obj.get_type() << " " << obj;
    fout.close();
}

void add_system(unordered_map<int, CSystem>& system, unordered_map<int, CPipe>& pipes, unordered_map<int, CStation>& stations) {
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
    ofstream fout;
    fout.open("log.txt", ios::app);
    cout << "Enter diameter of of pipe: " << endl;
    int d = get_correct_diam();
    for (auto& i : pipes) if (check_by_diameter(i.second, d) and i.second.in_system == false and i.second.reparied == false) {
        g.pipe_id = i.second.id;
        i.second.in_system = true;
        system.insert({ g.id, g });
        cout << g << endl;
        fout << "add " << g.get_type() << " " << g;
        fout.close();
        return;
    }
    cout << "no suitable pipe. Want to create a new pipe?(1- yes, 0 - no)" << endl;
    if (get_correct_number(0, 1)) {
        CPipe p;
        cout << "Oil pipe" << endl;
        cout << "Name: ";
        cin.ignore(1000, '\n');
        getline(cin, p.name);
        cout << "Length" << endl;
        p.length = get_correct_number(1.0, 1000.0);
        p.diameter = d;
        p.reparied = false;
        p.in_system = true;
        g.pipe_id = p.id;
        pipes.insert({ p.id, p });
        system.insert({ g.id, g });
        fout << "add " << p.get_type() << " " << p;
        fout << "add " << g.get_type() << " " << g;
        fout.close();
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
        for (auto& i : system) cout << i.second;
    }
    else cout << "no system" << endl;
}

void edit_pipes(unordered_map<int, CPipe>& pipes) {
    set<int> pipes_to_edit;
    if (pipes.size() > 0) {
        ofstream fout;
        fout.open("log.txt", ios::app);
        fout << "edit pipe ";
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
            for (auto i : pipes_to_edit) for (auto& j : pipes) if (j.second.id == i) {
                j.second.edit_pipe();
                fout << j.second;
            }
        }
        else for (auto& i : pipes) {
            i.second.edit_pipe();
            fout << i.second;
        }
    fout.close();
    }
    else cout << "no pipe" << endl;
}

void edit_stations(unordered_map<int, CStation>& stations) {
    if (stations.size() > 0) {
        ofstream fout;
        fout.open("log.txt", ios::app);
        fout << "edit station";
        (select_station(stations)).edit_station();
        fout.close();
    }
    else cout << "no stations" << endl;
}

void delete_object(unordered_map<int, CPipe>& pipes, unordered_map<int, CStation>& stations, unordered_map<int, CSystem>& systems) {
    int id;

    cout << "Delete pipe - 0, delete station - 1, delete system - 2 " << endl;
    int command = get_correct_number(0, 2);
    if (command == 1 && stations.size() > 0) {
        cout << "Enter id" << endl;
        id = get_correct_number(0, CStation::MaxId - 1);
        if (is_station_in_system(id, systems) >= 0) {
            cout << "the system containing this station will be deleted too" << endl;
            erase_system(systems, is_station_in_system(id, systems),pipes);
        }
        erase(stations, id);
    }
    else if (command && stations.size() == 0) cout << "no station" << endl;
    if (command == 0 && pipes.size() > 0) {
        cout << "Enter id" << endl;
        id = get_correct_number(0, CPipe::MaxId - 1);
        if (is_pipe_in_system(id, systems) >= 0) {
            cout << "the system containing this pipe will be deleted too" << endl;
            erase_system(systems, is_pipe_in_system(id, systems),pipes);
        }
        erase(pipes, id);
    }
    else if (!command && pipes.size() == 0) cout << "no pipe" << endl;
    if (command == 2 && systems.size() > 0) {
        cout << "Enter id" << endl;
        id = get_correct_number(0, CSystem::MaxId - 1);
        erase_system(systems, id, pipes);
    }
    else if (command == 2 && systems.size() == 0) cout << "no system" << endl;
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
    ofstream fout;
    fout.open("log.txt", ios::app);
    if (command) {
        cout << "Enter reparied status (0 - no, 1 - yes): " << endl;
        cin >> status;
        fout << "find pipe by reparied status " << status << " Result : ";
        for (auto i : find_pipe_by_filter(pipes, check_by_reparied, status)) {
            cout << i.second;
            fout << i.second;
        }
    }
    else {
        cout << "Enter name: " << endl;
        cin.ignore(1000, '\n');
        getline(cin, name);
        fout << "find pipe by name " << name << " Result : ";
        for (auto i : find_pipe_by_filter(pipes, check_by_name, name)){
            cout << i.second;
        fout << i.second;
    }
    }
    fout.close();
}

void find_station(const unordered_map<int, CStation>& stations) {
    if (stations.size() == 0) {
        cout << "no stations" << endl;
        return;
    }
    string name;
    int command;
    ofstream fout;
    fout.open("log.txt", ios::app);
    cout << "Find station by name - 0, find station by percentage of not working guilds - 1 :" << endl;
    command = get_correct_number(0, 1);
    if (command) {
        cout << "Enter percentage of not working guilds" << endl;
        double target = get_correct_number(0.0, 100.0);
        fout << "find station by percentage of work.guild " << target << " Result:";
        for (auto i : find_station_by_filter(stations, check_by_working_guilds, target)) {
            cout << i.second;
            fout << i.second;
        }
    }
    else {
        cout << "Enter name: " << endl;
        cin.ignore(1000, '\n');
        getline(cin, name);
        fout << "find station by name " << name << " Result:";
        for (auto i : find_station_by_filter(stations, check_by_name, name)){
            cout << i.second;
            fout << i.second;
    }
    }
    fout.close();
}

void save_to_file(unordered_map<int, CPipe>& pipes, unordered_map<int, CStation>& stations, unordered_map<int, CSystem>& systems) {
    if (pipes.size() == 0 && stations.size() == 0) {
        cout << "no pipe, no station" << endl;
        return;
    }
    
    string filename;
    cout << "Enter file name" << endl;
    cin >> filename;

    ofstream logout;
    logout.open("log.txt", ios::app);
    logout << "save to file " << filename << endl;
    logout.close();

    ofstream fout;
    fout.open(filename, ios::out);
    if (fout.is_open()) {
        fout << pipes.size() << endl;
        if (pipes.size() > 0) {
            for (auto& p : pipes) {
                fout << p.second.name << endl << p.second.length << endl << p.second.diameter << endl << p.second.reparied << endl << p.second.in_system<< endl;
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
            for (auto& g : systems) {
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

    ofstream fout;
    fout.open("log.txt", ios::app);
    fout << "load from file " << filename << endl;
    fout.close();

    fin.open(filename, ios::in);
    if (fin.is_open()) {
        fin >> counter;
        for (int i = counter; i > 0; i--) {
            CPipe p;
            fin.ignore();
            getline(fin, p.name);
            fin >> p.length >> p.diameter >> p.reparied >> p.in_system;
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

void sort_graph(unordered_map<int, CSystem> systems) {
    if (systems.size() == 0) {
        cout << "no system" << endl;
        return;
    }

    ofstream fout;
    fout.open("log.txt", ios::app);
    fout << "sort graph" << endl;

    bool flag = true;
    unordered_map<int, vector<int>> graph = create_graph(systems);
    vector<int> counter;
    for (auto& i : systems) {
        if (find(counter.begin(), counter.end(), i.second.entrance_id) == counter.end()) counter.push_back(i.second.entrance_id);
        if (find(counter.begin(), counter.end(), i.second.exit_id) == counter.end()) counter.push_back(i.second.exit_id);
    }
    unordered_map<int, int> visited;
    for (int i : counter) visited.insert({ i, 0 });
    vector<int> order;
    /*for (auto i : counter) cout << i;
    counter.pop_back();
    for (auto i : counter) cout << i;*/
    for (int v : counter) if (visited[v] == 0) (dfs(graph, v, visited, order, flag));
    if (flag) {
        reverse(order.begin(), order.end());
        cout << "Result" << endl;
        fout << "Result" << endl;
        for (int v : order) {
            cout << v << '\t';
            fout << v << '\t';
        }
        cout << endl;
        fout << endl;
    }
    else {
        cout << "Cycle in the graph. Topological sorting is not possible" << endl;
        fout << "Cycle in the graph" << endl;
    }
    fout.close();
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
        << "12 - sort graph of systems " << endl
        << "0 - exit" << endl;
}

int main()
{
    unordered_map<int, CPipe> pipes;
    unordered_map<int, CStation> stations;
    unordered_map<int, CSystem> systems;

    while (true) {
        menu();
        int command = get_correct_number(0, 12);
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
            delete_object(pipes, stations, systems);
            break;
        case 11:
            add_system(systems, pipes, stations);
            break;
        case 12:
            sort_graph(systems);
            break;
        case 0: return 0;
        }
    }
    return 0;
}

 //перенести функции , которые отвечают за редактирование , удаление и поиск в файл систем,в мэйне только меню. поменять вход и выъод местами
