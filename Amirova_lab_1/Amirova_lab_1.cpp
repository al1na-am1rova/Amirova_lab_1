#include <iostream>
#include <fstream>
#include <string>

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

oil_pipe create_pipe() {

    oil_pipe new_pipe;
    cout << "Oil pipe" << endl;
    cout << "Name: ";
    cin.ignore(1000, '\n');
    getline(cin, new_pipe.name);

    do {
        cout << "Lenght: ";
        cin >> new_pipe.lenght;
        if (cin.fail() || new_pipe.lenght <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
        }
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
    return new_pipe;
}

oil_pumping_station create_station() {

    oil_pumping_station new_station;
    cout << "Oil station" << endl;
    cout << "Name: ";
    cin.ignore(1000, '\n');
    getline(cin, new_station.name);

    do {
        cout << "Number of guild: ";
        cin >> new_station.number_of_guild;
        if (cin.fail() || new_station.number_of_guild <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
        }
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
    return new_station;
}

void print_pipe(const oil_pipe& p) {
    cout << "Oil pipe" << endl;
    cout << "Name: " << p.name
        << "\tLenght: " << p.lenght
        << "\tDiameter: " << p.diameter
        << "\tReparied: " << p.reparied << endl;
}

void print_station(const oil_pumping_station & s) {
            cout << "Oil station" << endl;
            cout << "Name: " << s.name
                << "\tNumber of guild: " << s.number_of_guild
                << "\tNumber of working guild: " << s.number_of_working_guild
                << "\tEffectiveness: " << s.effectiveness << endl;
        }

void edit_pipe(oil_pipe& p) {
    p.reparied = !p.reparied;
    cout << "pipe status (0 - is reparied, 1 - is not reparied): " << p.reparied << endl;
}

void edit_station(oil_pumping_station& s) {
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

void save_to_file(const oil_pipe& p, const oil_pumping_station& s, bool is_pipe, bool is_station) {
    ofstream fout;
    fout.open("pipe_and_station.txt", ios::out);
    if (fout.is_open()) {
        if (is_pipe) {
            fout << "oil pipe" << endl
                << "name: " << p.name << endl
                << "lenght: " << p.lenght << endl
                << "diameter: " << p.diameter << endl
                << "Is reparied (true - 0 /false - 1): " << p.reparied << endl;
            cout << "pipe successfully saved to file" << endl;
        }
        else fout << "no pipe in file";
        if (is_station) {
            fout << "oil pumping station" << endl
                << "name: " << s.name << endl
                << "number_of_guild: " << s.number_of_guild << endl
                << "number of working guild: " << s.number_of_working_guild << endl
                << "effectiveness: " << s.effectiveness << endl;
            cout << "station successfully saved to file" << endl;
        }
        else fout << "no station in file";
        fout.close();
    }
    else {
        cout << "file is not open";
    }
}

void load_from_file() {
    string getcontent;
    ifstream openfile("pipe_and_station.txt");
    if (!openfile.is_open()) cout << "File is not open(the file may not exist)" << endl;
    else if (openfile.peek() == EOF) cout << "File is empty" << endl;
    else {
        while (std::getline(openfile, getcontent))
        {
            cout << getcontent << endl;
        }
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
        << "0 - exit" << endl;
}

int main()
{
    oil_pipe p;
    oil_pumping_station s;
    bool is_pipe = false;
    bool is_station = false;

    while (true) {
        menu();
        int command = 0;
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
            p = create_pipe();
            is_pipe = true;
            break;

        case 2:
            s = create_station();
            is_station = true;
            break;

        case 3:
            if (is_pipe) print_pipe(p);
            else cout << "no pipe" << endl;
            if (is_station) print_station(s);
            else  cout << "no station" << endl;
            break;

        case 4:
            if (is_pipe) edit_pipe(p);
            else cout << "no pipe" << endl;
            break;

        case 5:
            if (is_station) edit_station(s);
            else cout << "no station" << endl;
            break;

        case 6:
            if (is_pipe || is_station) save_to_file(p, s, is_pipe, is_station);
            else cout << "no pipe, no station" << endl;
            break;

        case 7:
            load_from_file();
            break;

        case 0: return 0;
        }

    }
    return 0;
}
