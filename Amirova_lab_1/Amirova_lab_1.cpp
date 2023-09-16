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
    float effectiveness;

};

oil_pipe create_pipe(int& pipe_counter) {

    oil_pipe new_pipe;
    cout << "Oil pipe" << endl;
    cout << "Name: ";
    cin >> new_pipe.name;

    do {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Lenght: ";
        cin >> new_pipe.lenght;
    } while (cin.fail() || new_pipe.lenght <= 0);

    do {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Diameter: ";
        cin >> new_pipe.diameter;
    } while (cin.fail() || new_pipe.diameter <= 0);

    do {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Is reparied (true - 0 /false - 1): ";
        cin >> new_pipe.reparied;
    } while (cin.fail());

    pipe_counter++;
    return new_pipe;
}

oil_pumping_station create_station(int& station_counter) {

    oil_pumping_station new_station;
    cout << "Oil station" << endl;
    cout << "Name: ";
    cin >> new_station.name;
    do {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Number of guild: ";
        cin >> new_station.number_of_guild;
    } while (cin.fail() || new_station.number_of_guild <= 0);

    do {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Number of working guild: ";
        cin >> new_station.number_of_working_guild;
    } while (cin.fail() || new_station.number_of_working_guild < 0 || new_station.number_of_working_guild > new_station.number_of_guild);

    do {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Effectiveness: ";
        cin >> new_station.effectiveness;
    } while (cin.fail() || new_station.effectiveness <= 0);

    station_counter++;
    return new_station;
}

void print_pipe(int& pipe_counter, const oil_pipe& p) {
    if (pipe_counter == 0) {
        cout << "no pipe" << endl;
    }
    else {
        cout << "Oil pipe" << endl;
        cout << "Name: " << p.name
            << "\tLenght: " << p.lenght
            << "\tDiameter: " << p.diameter
            << "\tReparied: " << p.reparied << endl;
    }
}

void print_station(int& station_counter, const oil_pumping_station& s) {
    if (station_counter == 0) {
        cout << "no station" << endl;
    }
    else {
        cout << "Oil station" << endl;
        cout << "Name: " << s.name
            << "\tNumber of guild: " << s.number_of_guild
            << "\tNumber of working guild: " << s.number_of_working_guild
            << "\tEffectiveness: " << s.effectiveness << endl;
    }
}

void edit_pipe(int& pipe_counter, oil_pipe& p) {
    if (pipe_counter == 0) {
        cout << "no pipe" << endl;
    }
    else {
        if (p.reparied == true) {
            p.reparied = false;
            cout << "the pipe is not being repaired now" << endl;
        }
        else {
            p.reparied = true;
            cout << "the pipe is being repaired now" << endl;
        }
    }
}

void edit_station(int& station_counter, oil_pumping_station& s) {
    if (station_counter == 0) {
        cout << "no station" << endl;
    }
    else {
        int command;
        do {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "0 - start-up guild" << endl
                << "1 - stop guild" << endl;
            cin >> command;
        } while (cin.fail() || (command != 0 && command != 1));

        if (command == 0 && (s.number_of_guild - s.number_of_working_guild > 0)) {
            s.number_of_working_guild++;
        }
        if (command == 1 && (s.number_of_working_guild > 0)) {
            s.number_of_working_guild -= 1;
        }
        else {
            cout << "wrong action" << endl;
        }
    }
}

void save_pipe(const int& pipe_counter, const oil_pipe& p) {
    if (pipe_counter == 0) {
        cout << "no pipe" << endl;
    }
    else {
        ofstream fout;
        fout.open("oil_pipes.txt", ios::out);
        if (fout.is_open()) {
            fout << p.name << endl << p.lenght << endl << p.diameter << endl << p.reparied << endl;
            fout.close();
            cout << "pipe successfully saved to file";
        }
    }
}

void save_station(const int& station_counter, const oil_pumping_station& s) {
    if (station_counter == 0) {
        cout << "no station" << endl;
    }
    else {
        ofstream fout;
        fout.open("oil_pumping_stations.txt", ios::out);
        if (fout.is_open()) {
            fout << s.name << endl << s.number_of_guild << endl << s.number_of_working_guild << endl << s.effectiveness << endl;
            fout.close();
            cout << "station successfully saved to file";
        }
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
    int pipe_counter = 0;
    int station_counter = 0;

    while (1) {
        int command;
        int a;
        menu();
        cin >> a;
        do {
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> command;
        } while (cin.fail() || command < 0 || command > 9);

        switch (command) {
        case 1: 
        {
            p = create_pipe(pipe_counter);
            break;
        }
        case 2:
        {
            s = create_station(station_counter);
            break;
        }
        case 3:
        {
            print_pipe(pipe_counter, p);
            print_station(station_counter, s);
            break;
        }
        case 4:
        {   
            edit_pipe(pipe_counter, p);
            break;
        }
        case 5:
        {
            edit_station(station_counter, s);
            break;
        }
        case 6:
        {  
            save_pipe(pipe_counter, p);
            break;
        }
        case 7:
        {
            save_station(station_counter, s);
            break;
        }
        case 8:
        {
            print_pipe(pipe_counter, load_pipe());
            break;
        }
        case 9:
        {
            print_station(station_counter, load_station());
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
