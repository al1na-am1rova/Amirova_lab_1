#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct oil_pipe
{
    string name;
    float lenght;
    int diameter;
    bool reparied;
};

struct oil_pumping_station
{
    string name;
    int number_of_guild;
    int number_of_working_guild;
    int effectiveness;

};

oil_pipe create_pipe() {

    oil_pipe new_pipe;
    cout << "Oil pipe" << endl;
    cout << "Name: ";
    cin >> new_pipe.name;
    cout << "Lenght: ";
    cin >> new_pipe.lenght;
    cout << "Diameter: ";
    cin >> new_pipe.diameter;
    cout << "Is reparied (true/false): ";
    cin >> new_pipe.reparied;
    return new_pipe;
}

oil_pumping_station create_station() {

    oil_pumping_station new_station;
    cout << "Oil station" << endl;
    cout << "Name: ";
    cin >> new_station.name;
    cout << "Number of guild: ";
    cin >> new_station.number_of_guild;
    cout << "Number of working guild: ";
    cin >> new_station.number_of_working_guild;
    cout << "Effectiveness: ";
    cin >> new_station.effectiveness;
    return new_station;
}

void print_pipe(const oil_pipe& p) {
    cout << "Oil pipe" << endl;
    cout << "Name: " << p.name
        << "\tLenght: " << p.lenght
        << "\tDiameter: " << p.diameter
        << "\tReparied: " << p.reparied << endl;
}

void print_station(const oil_pumping_station& s) {
    cout << "Oil station" << endl;
    cout << "Name: " << s.name
        << "\tNumber of guild: " << s.number_of_guild
        << "\tNumber of working guild: " << s.number_of_working_guild
        << "\tEffectiveness: " << s.effectiveness << endl;
}

void edit_pipe(oil_pipe& p) {
    if (p.reparied == true) {
        p.reparied = false;
    }
    else {
        p.reparied = true;
    }
}

void edit_station(oil_pumping_station& s) {
    int command;
    cout << "0 - start-up guild" << endl;
    cout << "1 - stop guild" << endl;
    cin >> command;
    if (command == 0) {
        s.number_of_working_guild ++ ;
    }
    if (command == 1) {
        s.number_of_working_guild -= 1;
    }
}

void save_pipe(const oil_pipe& p) {
    ofstream fout;
    fout.open ("oil_pipes.txt", ios::out);
    if (fout.is_open()) {
        fout << p.name << endl << p.lenght << endl << p.diameter << endl << p.reparied << endl;
        fout.close();
    }
}

void save_station(const oil_pumping_station& s) {
    ofstream fout;
    fout.open("oil_pumping_stations.txt", ios::out);
    if (fout.is_open()) {
        fout << s.name << endl << s.number_of_guild << endl << s.number_of_working_guild << endl << s.effectiveness << endl;
        fout.close();
    }
}

oil_pipe load_pipe() {
    oil_pipe p;
    ifstream fin;
    fin.open("oil_pipes.txt", ios:: in);
    if (fin.is_open()) {
        fin >> p.name >> p.lenght >> p.diameter >> p.reparied;
        fin.close();
    }
    return p;

}

oil_pumping_station load_station() {
    oil_pumping_station s;
    ifstream fin;
    fin.open("oil_pumping_stations.txt", ios:: in);
    if (fin.is_open()) {
        fin >> s.name >> s.number_of_guild >> s.number_of_working_guild >> s.effectiveness;
        fin.close();
    }
    return s;
}

void menu() {
    cout << "Menu" << endl
        << "1 - create oil pipe" << endl
        << "2 - create oil pumping station" << endl
        << "3 - show all objects" << endl
        << "4 - edit oil pipe" << endl
        << "5 - edit oil pumping station" << endl
        << "6 - save oil pipe to file" << endl
        << "7 - save oil pumping station to file" << endl
        << "8 - load oil pipe from file" << endl
        << "9 - load oil pumping station from file" << endl
        << "0 - exit" << endl;
}

int main()
{
    oil_pipe p;
    oil_pumping_station s;

    while (1) {
        menu();
        int command = 0;
        cin >> command;
        switch (command) {
        case 1: 
        {
            p = create_pipe();
            break;
        }
        case 2:
        {
            s = create_station();
            break;
        }
        case 3:
        {
            print_pipe(p);
            print_station(s);
            break;
        }
        case 4:
        {   
            edit_pipe(p);
            break;
        }
        case 5:
        {
            edit_station(s);
            break;
        }
        case 6:
        {  
            save_pipe(p);
            break;
        }
        case 7:
        {
            save_station(s);
            break;
        }
        case 8:
        {
            print_pipe(load_pipe());
            break;
        }
        case 9:
        {
            print_station(load_station());
            break;
        }
        case 0:
        {
            return 0;
        }
        default: {
            cout << "Wrong action" << endl;
        }
        }
    }
    return 0;
}
