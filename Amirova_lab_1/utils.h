#pragma once
#include <iostream>

using namespace std;

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

int get_correct_diam()
{
    int x;
    while ((cin >> x).fail()
        || cin.peek() != '\n'
        || (x != 500 && x != 700 && x != 1000 && x != 1400))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number 500, 700, 1000 or 1400:" << endl;
    }
    return x;
}

template<typename T>
using PFilter = bool(*)(const CPipe& s, T param);

template<typename T>
using SFilter = bool(*)(const CStation& s, T param);

template<typename T>
bool check_by_name(const T& s, string param)
{
    bool found = s.name.find(param) != string::npos;
    return found;
}

bool check_by_reparied(const CPipe& s, bool param)
{
    return s.reparied == param;
}

bool check_by_diameter(const CPipe& p, int param) {
    return p.diameter == param;
}

bool check_by_working_guilds(const CStation& s, double target)
{
    double wg = s.number_of_working_guild;
    double g = s.number_of_guild;
    return ((g - wg) / g) * 100 == target;
}

template <typename T>
unordered_map<int, CPipe> find_pipe_by_filter(const unordered_map<int, CPipe>& objects, PFilter<T> f, T param) {
    unordered_map<int, CPipe> res;
    for (auto s : objects) if (f(s.second, param)) res.insert({ s.first, s.second });
    if (res.size() == 0) cout << "no pipes with such parameters" << endl;
    return res;
}

template <typename T>
unordered_map<int, CStation> find_station_by_filter(const unordered_map<int, CStation>& objects, SFilter<T> f, T param) {
    unordered_map<int, CStation> res;
    for (auto& s : objects) if (f(s.second, param)) res.insert(s);
    if (res.size() == 0) cout << "no stations with such parameters" << endl;
    return res;
}

template<typename T>
void erase(unordered_map<int, T>& objects, int id) {
    if (objects.find(id) != objects.end()) objects.erase(objects.find(id));
    else cout << "there is no object with this id" << endl;
}

void erase_system(unordered_map<int, CSystem>& systems, int id, unordered_map<int, CPipe>& pipes) {
    if (systems.find(id) != systems.end()) {
        for (auto& i : systems) if (i.first == id) (pipes.at(i.second.pipe_id)).in_system=false;
        systems.erase(systems.find(id));
    }
    else cout << "there is no object with this id" << endl;
}

bool is_correct_station_id(unordered_map<int, CStation> stations, int id) {
    for (auto i : stations) if (i.first == id) return true;
    return false;
}

int get_correct_entrance_id(unordered_map<int, CStation> stations) {
    int x;
    while ((cin >> x).fail()
        || cin.peek() != '\n'
        || x < 0 || x > CStation::MaxId || ! is_correct_station_id(stations, x))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number (" << 0 << "-" << (CStation::MaxId - 1) << ", you cannot select the ID of the deleted station):";
    }
    return x;
}

int get_correct_exit_id(unordered_map<int, CStation> stations, int entrance_id) {
    int x;
    while ((cin >> x).fail()
        || cin.peek() != '\n'
        || x < 0 || x > CStation::MaxId || !is_correct_station_id(stations, x) || x == entrance_id)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number (" << 0 << "-" << (CStation::MaxId-1) << ", you cannot select the ID of the deleted station, entrance and exit stations must be different):";
    }
    return x;
}

bool already_in_system(int entrance_id, int exit_id, unordered_map<int, CSystem> systems) {
    for (auto i : systems) if (i.second.entrance_id == entrance_id and i.second.exit_id == exit_id) return true;
    return false;
}

int is_station_in_system(int id, unordered_map<int, CSystem> systems) {
    for (auto i : systems) if (i.second.entrance_id == id || i.second.exit_id == id) return i.first;
    return -1;
}

int is_pipe_in_system(int id, unordered_map<int, CSystem> systems) {
    for (auto i : systems) if (i.second.pipe_id == id) return i.first;
    return -1;
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

void dfs(unordered_map<int, vector<int>>& graph, int v, vector<int>& visited, vector<int>& order) {
    visited.push_back(v);
    if (graph.find(v) != graph.end()){
        for (int i : graph.at(v)) if (find(visited.begin(), visited.end(), i) == visited.end()) {
            dfs(graph, i, visited, order);
        }
    }
    order.push_back(v);
    return;
}

void sort_graph(unordered_map<int, CSystem> systems) {
    unordered_map<int, vector<int>> graph = create_graph(systems);
    /*for (auto i : graph) cout << i.first << i.second[0] << "\t";*/
    vector<int> counter;
    for (auto i : systems) {
        if (find(counter.begin(), counter.end(), i.second.entrance_id) == counter.end()) counter.push_back(i.second.entrance_id);
        if (find(counter.begin(), counter.end(), i.second.exit_id) == counter.end()) counter.push_back(i.second.exit_id);
    }
    vector<int> visited;
    vector<int> order;
    counter.pop_back();
        /*for (auto i : counter) cout << i << "\t";*/
    for (int v :counter) if (find(visited.begin(), visited.end(), v) == visited.end()) dfs(graph, v, visited, order);
    reverse(order.begin(), order.end());
    cout << "Result" << endl;
    for (int v : order) cout << v << '\t';
    cout << endl;
}
