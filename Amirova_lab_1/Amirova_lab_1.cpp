#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CPipe.h"
#include "CStation.h"
using namespace std;

//void save_pipe_to_file(ofstream& fout, const CPipe& p) {
//    fout << p.name << endl
//      << p.lenght << endl
//      << p.diameter << endl
//      << p.reparied << endl;
//}
//
//void save_station_to_file(ofstream& fout, const CStation& s) {
//    fout << s.name << endl
//    << s.number_of_guild << endl
//    << s.number_of_working_guild << endl
//    << s.effectiveness << endl;
//}
//
//void load_from_file(vector<CPipe>& pipes, vector<CStation>& stations) {
//    int counter;
//    CPipe p;
//    CStation s;
//    ifstream fin;
//    string str;
//    fin.open("pipe_and_station.txt", ios::in);
//    if (fin.is_open()) {
//        fin >> counter;
//        for (int i = counter; i > 0; i--) {
//            fin >> p.name;
//            fin >> p.lenght >> p.diameter >> p.reparied;
//            pipes.push_back(p);
//        }
//        fin >> counter;
//        for (int i = counter; i > 0; i--) {
//            fin >> s.name;
//            fin >> s.number_of_guild >> s.number_of_working_guild >> s.effectiveness;
//            stations.push_back(s);
//        }
//    }
//    else cout << "File is not open. Maybe it doesn't exist" << endl;  
//}

template <typename T>
T& select_object(vector<T>& x) {
    cout << "Enter index" << endl;
    unsigned int index = get_correct_number(1u, x.size());
    return x[index-1];
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

bool check_by_working_guilds(const CStation& s, int mn)
{
    return (1 - (s.number_of_working_guild / s.number_of_guild)) * 100 <= mn;
}

void menu() {
    cout << "Menu" << endl
        << "1 - create oil pipe" << endl
        << "2 - create oil pumping station" << endl
        << "3 - show objects" << endl
        << "4 - edit oil pipe" << endl
        << "5 - edit oil pumping station" << endl
        << "6 - save to file" << endl
        << "7 - load from file" << endl
        << "8 - find pipe by filter " << endl
        << "9 - find station by filter " << endl
        << "0 - exit" << endl;
}

int main()
{
    vector <CPipe> pipes;
    vector <CStation> stations;

    while (true) {
        menu();
        int command;
        cin >> command;
        if (cin.fail() || command < 0 || command > 9)
        {
            cout << "Error: Invalid input. Please enter a number between 0 and 7" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (command) {
        case 1:
        {CPipe p;
        cin >> p;
        pipes.push_back(p); }
            break;

        case 2:
        {CStation s;
        cin >> s;
        stations.push_back(s); }
            break;

        case 3:
            if (pipes.size() > 0) {
                cout << "Pipe" << endl;
                cout << select_object(pipes);
            }
            else cout << "no pipe" << endl; 
            if (stations.size() > 0) {
                cout << "Station" << endl;
                cout << select_object(stations);
            }
            else  cout << "no station" << endl;
            break;

        case 4:
            if (pipes.size() > 0) (select_object(pipes)).edit_pipe();
            else cout << "no pipe" << endl;
            break;

        case 5:
            if (stations.size() > 0) (select_object(stations)).edit_station();
            else cout << "no station" << endl;
            break;

        /*case 6:
            if (pipes.size() == 0 && stations.size() == 0) cout << "no pipe, no station" << endl;
            else {
                ofstream fout;
                fout.open("pipe_and_station.txt", ios::out);
                if (fout.is_open()) {
                    fout << pipes.size() << endl;
                    if (pipes.size() > 0) {
                        for (CPipe p : pipes) save_pipe_to_file(fout, p);
                        cout << "pipes successfully saved to file" << endl;
                    }
                    else cout << "no pipe to save" << endl;
                    fout << stations.size() << endl;
                    if (stations.size() > 0) {
                        for (CStation s : stations) save_station_to_file(fout, s);
                        cout << "stations successfully saved to file" << endl;
                    }
                    else cout << "no station to save" << endl;
                    fout.close();
                }
                else cout << "file is not open";
            }
            break;

        case 7:
            cout << "The data from the file will replace the existing data. Сontinue anyway? (0 - no, 1 - yes)" << endl;
            command = get_correct_number(0, 1);
            if (command) load_from_file(pipes, stations);
            break;*/

        case 8 :
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
        case 9 : 
        {
            if (stations.size() == 0) {
                cout << "no stations" << endl;
                continue;
            }
            string name;
            int command;
            int mn;
            cout << "Find station by name - 0, find station by percentage of working guilds - 1 :" << endl;
            command = get_correct_number(0, 1);
            if (command) {
                cout << "Enter acceptable minimum of working guilds. The program will show stations with a smaller percentage of working guilds" << endl;
                mn = get_correct_number(0, 100);
                for (int i : find_station_by_filter(stations, check_by_working_guilds, mn))
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
        case 0: return 0;
        }
    }
    return 0;
}

//чтение из файла getline