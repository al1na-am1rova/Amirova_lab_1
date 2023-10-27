#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include<set>
#include "utils.h"

using namespace std;

void save_to_file(unordered_map<int, CPipe>& pipes,unordered_map<int, CStation>& stations) {
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
        fout.close();
    }
    else cout << "File is not open. Maybe it doesn't exist." << endl;
}

void load_from_file(unordered_map<int, CPipe>& pipes, unordered_map<int, CStation>& stations) {
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
            stations.insert({s.id, s});
        }
    }
    else cout << "File is not open. Maybe it doesn't exist" << endl;
}
