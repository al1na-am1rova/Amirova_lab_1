#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CPipe.h"
#include "CStation.h"
using namespace std;

//void edit_pipe(CPipe& p) {
//    p.reparied = !p.reparied;
//    cout << "pipe status (1 - is reparied, 0 - is not reparied): " << p.reparied << endl;
//}
//
//void edit_station(CStation& s) {
//        int command;
//        cout << "Number of working guild" << endl;
//        s.number_of_working_guild = get_correct_number(0, s.number_of_guild);
//        cout << "Number of working guild: " << s.number_of_working_guild << endl;
//}
//
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

template <typename S>
S& select_object(vector<S>& x) {
    cout << "Enter index" << endl;
    unsigned int index = get_correct_number(1u, x.size());
    return x[index-1];
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
        if (cin.fail() || command < 0 || command > 7)
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

        /*case 4:
            if (pipes.size() > 0) edit_pipe(select_object(pipes));
            else cout << "no pipe" << endl;
            break;

        case 5:
            if (stations.size() > 0) edit_station(select_object(stations));
            else cout << "no station" << endl;
            break;

        case 6:
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

        case 0: return 0;
        }
    }
    return 0;
}

//чтение из файла getline