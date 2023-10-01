#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct oil_pipe
{
    string name;
    double lenght;
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

template <typename T>
T get_correct_number (T min, T max){
    T x;
    do {
        cout << "Type number (" << min << " - " << max << " ): ";
        cin >> x;
        if (cin.fail() || x > max || x < min) {
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (cin.fail() || x > max || x < min);
    return x;
}

bool get_correct_bool() {
    bool x;
    do {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Type (true - 1 /false - 0): ";
        cin >> x;
    } while (cin.fail());
    return x;
}

void edit_pipe(oil_pipe& p) {
    p.reparied = !p.reparied;
    cout << "pipe status (1 - is reparied, 0 - is not reparied): " << p.reparied << endl;
}

void edit_station(oil_pumping_station& s) {
        int command;
        cout << "Number of working guild" << endl;
        s.number_of_working_guild = get_correct_number(0, s.number_of_guild);
        cout << "Number of working guild: " << s.number_of_working_guild << endl;
}

void save_to_file(const oil_pipe& p, const oil_pumping_station& s, bool is_pipe, bool is_station) {
    ofstream fout;
    fout.open("pipe_and_station.txt", ios::out);
    if (fout.is_open()) {
        if (is_pipe) {
            fout << true << endl
                << p.name << endl
                << p.lenght << endl
                << p.diameter << endl
                << p.reparied << endl;
            cout << "pipe successfully saved to file" << endl;
        }
        else {
            fout << false << endl;
            cout << "no pipe to save" << endl;
        }

        if (is_station) {
            fout << true << endl
                << s.name << endl
                << s.number_of_guild << endl
                << s.number_of_working_guild << endl
                << s.effectiveness << endl;
            cout << "station successfully saved to file" << endl;
        }
        else {
            fout << false << endl;
            cout << "no station to save" << endl;
        }
        fout.close();
    }
    else cout << "file is not open" << endl;
}

void load_from_file(oil_pipe& p, oil_pumping_station& s, bool& is_pipe, bool& is_station) {
    bool is_pipe_in_file;
    bool is_station_in_file;
    int command = 1;
    string a;
    ifstream fin("pipe_and_station.txt");
    if (!fin.is_open()) {
        cout << "File is not open(the file may not exist)" << endl;
        return;
    }
    fin >> is_pipe_in_file;
    if (is_pipe_in_file) {
        if (is_pipe) {
            cout << "Do you want to overwrite pipe? (0 - no, 1 - yes)" << endl;
            do {
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> command;
            } while (cin.fail() || (command != 0 && command != 1));
        }
        if (command == 1) {
            is_pipe = true;
            //getline(fin, p.name);
            fin >> p.name;
            fin >> p.lenght;
            fin >> p.diameter;
            fin >> p.reparied;
        }
        else {
            for (int i = 0; i < 6; i++) {
                fin >> a;
            }

        }

    }
     else cout << "no pipe in file" << endl;

     command = 1;
     fin >> is_station_in_file;
     if (is_station_in_file) {
         if (is_station) {
             cout << "Do you want to overwrite station? (0 - no, 1 - yes)" << endl;
             do {
                 cin.clear();
                 cin.ignore(1000, '\n');
                 cin >> command;
             } while (cin.fail() || (command != 0 && command != 1));
         }
         if (command == 1) {
             is_station = true;
             fin >> s.name;
             fin >> s.number_of_guild;
             fin >> s.number_of_working_guild;
             fin >> s.effectiveness;
         }
         else {
             for (int i = 0; i < 6; i++) {
                 fin >> a;
             }

         }

     }
     else cout << "no station in file" << endl;
}

ostream& operator << (ostream& out, const oil_pipe& p) {
    out << "Name: " << p.name
        << "\tLenght: " << p.lenght
        << "\tDiameter: " << p.diameter
        << "\tReparied: " << p.reparied << endl;
    return out;
}

ostream& operator << (ostream& out, const oil_pumping_station& s) {
    out << "Name: " << s.name
        << "\tNumber of guild: " << s.number_of_guild
        << "\tNumber of working guild: " << s.number_of_working_guild
        << "\tEffectiveness: " << s.effectiveness << endl;
    return out;
}

istream& operator >> (istream& in, oil_pipe& p) {
    cout << "Oil pipe" << endl;
    cout << "Name: ";
    in.ignore(1000, '\n');
    getline(in, p.name);
    cout << "Lenght" << endl;
    p.lenght = get_correct_number(1.0, 1000.0);
    cout << "Diameter" << endl;
    p.diameter = get_correct_number(1, 1000);
    cout << "Is reparied (1 - yes, 0 - no): " << endl;
    p.reparied = get_correct_bool();
    return in;
}

istream& operator >> (istream& in, oil_pumping_station& s) {
    cout << "Oil station" << endl;
    cout << "Name: ";
    cin.ignore(1000, '\n');
    getline(cin, s.name);
    cout << "Number of guild" << endl;
    s.number_of_guild = get_correct_number(1, 1000);
    cout << "Number of working guild" << endl;
    s.number_of_working_guild = get_correct_number(0, s.number_of_guild);
    cout << "Effectiveness" << endl;
    s.effectiveness = get_correct_number(0, 100);
    return in;
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
            cin >> p;
            is_pipe = true;
            break;

        case 2:
            cin >> s;
            is_station = true;
            break;

        case 3:
            if (is_pipe) cout << p;
            else cout << "no pipe" << endl;
            if (is_station) cout << s;
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
            load_from_file(p, s, is_pipe, is_station);
            break;

        case 0: return 0;
        }
    }
    return 0;
}

//вывод с гетлайном из файла