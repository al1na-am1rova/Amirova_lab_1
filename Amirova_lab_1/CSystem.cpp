#include "CSystem.h"
#include <iostream>
#include <string>
#include "CPipe.h"
#include "CStation.h"
#include <unordered_map>

using namespace std;

int CSystem::MaxId = 0;
CSystem::CSystem() {
    id = MaxId++;
}

string CSystem::get_type()
{
    return "system";
}

template <typename T>
T get_correct_number(T min, T max)
{
    T x;
    while ((cin >> x).fail()
        || cin.peek() != '\n'
        || x < min || x > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number (" << min << "-" << max << "):";
    }
    return x;
}

ostream& operator<<(ostream& out, const CSystem& g)
{
    out << "Id: " << g.id
        << "\tEntrance station id: " << g.entrance_id
        << "\tPipe id: " << g.pipe_id
        << "\tExit station id: " << g.exit_id << endl;
    return out;
}

istream& operator>>(istream& in, CSystem& g)
{
    cout << "Oil Pipeline System" << endl;
    cout << "Enter id of start station: ";
    g.entrance_id = get_correct_number(0, CStation::MaxId);
    cout << "Enter id of end station: " << endl;
    g.exit_id = get_correct_number(0, CStation::MaxId);
    cout << "Enter id of of pipe: " << endl;
    g.pipe_id = get_correct_number(0, CPipe::MaxId);
    return in;
}

int is_pipe_in_system(int id, unordered_map<int, CSystem> systems) {
    for (auto i : systems) if (i.second.pipe_id == id) return i.first;
    return -1;
}

int is_station_in_system(int id, unordered_map<int, CSystem> systems) {
    for (auto i : systems) if (i.second.entrance_id == id || i.second.exit_id == id) return i.first;
    return -1;
}

bool already_in_system(int entrance_id, int exit_id, unordered_map<int, CSystem> systems) {
    for (auto i : systems) if (i.second.entrance_id == entrance_id and i.second.exit_id == exit_id) return true;
    return false;
}

CPipe& select_pipe(unordered_map<int, CPipe>& pipes, int id) {
    for (auto& i : pipes) if (i.first == id) return i.second;
}

unordered_map<int, vector<int>> create_graph(unordered_map<int, CSystem>& systems) {
    unordered_map<int, vector<int>> graph;
    for (auto i : systems) {
        if (graph.find(i.second.entrance_id) == graph.end()) {
            vector<int> current = { i.second.exit_id };
            graph.insert({ i.second.entrance_id, current });
        }
        else {
            graph.at(i.second.entrance_id).push_back(i.second.exit_id);
        }
    }
    return graph;
}

vector<vector<int>> create_matrix(unordered_map<int, CSystem>& systems, unordered_map<int, CPipe>& pipes, int vertex_num) {
    vector<vector<int>> matrix;
    for (int i = 0; i < vertex_num; i++) matrix.push_back({});
    for (int i = 0; i < vertex_num; i++) for (int j = 0; j < vertex_num; j++) {
        if (i == j) matrix[i].push_back(0);
        else matrix[i].push_back(10000);
    }

    for (auto i : systems) matrix[i.second.entrance_id][i.second.exit_id] = select_pipe(pipes, i.second.pipe_id).length;
    return matrix;

}

void erase_system(unordered_map<int, CSystem>& systems, int id, unordered_map<int, CPipe>& pipes) {
    if (systems.find(id) != systems.end()) {

        for (auto& i : systems) if (i.first == id) (pipes.at(i.second.pipe_id)).in_system = false;
        systems.erase(systems.find(id));
    }
    else cout << "there is no object with this id" << endl;
}

void get_flow_capacity(unordered_map<int, CPipe>& pipes, CSystem& system) {
    if (select_pipe(pipes, system.pipe_id).diameter == 500) system.flow_capacity = 5;
    if (select_pipe(pipes, system.pipe_id).diameter == 700) system.flow_capacity = 12;
    if (select_pipe(pipes, system.pipe_id).diameter == 1000) system.flow_capacity = 30;
    if (select_pipe(pipes, system.pipe_id).diameter == 1400) system.flow_capacity = 95;
    if (select_pipe(pipes, system.pipe_id).reparied == 1) system.flow_capacity = 0;
}




