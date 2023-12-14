#pragma once
#include <iostream>
#include <queue>
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

//CPipe& select_pipe(unordered_map<int, CPipe>& pipes, int id) {
//    for (auto& i : pipes) if (i.first == id) return i.second;
//}

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
    if (objects.find(id) != objects.end()) {

        ofstream fout;
        fout.open("log.txt", ios::app);
        fout << "delete " << objects.at(id).get_type() << "id: " << id;
        fout.close();

        objects.erase(objects.find(id));
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

void bfs(unordered_map<int, vector<int>>& graph, int id, vector<int>& visited, unordered_map<int, vector<int>>& steps, int step) {
    queue<int> q;
    visited.push_back(id);
    q.push(id);
    while (q.size() > 0) {
        int m = q.front();
        if (find(steps.at(step - 1).begin(), steps.at(step - 1).end(), m) == steps.at(step - 1).end()) {
            steps.at(step).push_back(m);
        }
        if (graph.count(m)) {
            for (int i : graph.at(id)) {
                if (find(visited.begin(), visited.end(), i) == visited.end()) {
                    q.push(i);
                    visited.push_back(i);
                }
            }
        }
        q.pop();

    }
}

void dfs(unordered_map<int, vector<int>>& graph, int v, unordered_map<int, int>& visited, vector<int>& order, bool& flag) {
    visited[v] = 1;
    if (graph.find(v) != graph.end()){
        for (int i : graph.at(v)) {
            if (visited[i] == 0) dfs(graph, i, visited, order, flag);
            else if (visited[i] == 1) {
                flag = false;
            }
        }
    }
    order.push_back(v);
    visited[v] = 2;
    return;
}

bool is_adj(int start, int stop, unordered_map<int, CSystem> systems) {
    for (auto i : systems) {
        if (i.second.entrance_id == start && i.second.exit_id == stop) {
            return true;
        }
    }
    return false;
}

bool contains_adj(int v, vector<int> vertexes, unordered_map<int, CSystem> systems) {
    for (int j : vertexes) {
        for (auto i : systems) {
            if (i.second.entrance_id == j && i.second.exit_id == v) {
                return true;
            }
        }
    }
    return false;
}

int get_system_capacity(int start, int stop, unordered_map<int, CSystem> systems) {
    for (auto& i : systems) {
        if (i.second.entrance_id == start and i.second.exit_id == stop) {
            return i.second.flow_capacity;
        }
    }
    return 0;
}

int max_path(vector<int> way, unordered_map<int, CSystem>& systems) {
    int mx = 10000;
    int i = 0;
    int j = 1;
    while (j < way.size()) {
        int stop = way[i];
        int start = way[j];
        mx = min(mx , get_system_capacity(start, stop, systems));
        i++;
        j++;
    }
    return mx;
}