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

CPipe& select_pipe(unordered_map<int, CPipe>& pipes, int id) {
    for (auto& i : pipes) if (i.first == id) return i.second;
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
    if (objects.find(id) != objects.end()) {

        ofstream fout;
        fout.open("log.txt", ios::app);
        fout << "delete " << objects.at(id).get_type() << "id: " << id;
        fout.close();

        objects.erase(objects.find(id));
    }
    else cout << "there is no object with this id" << endl;
}

void erase_system(unordered_map<int, CSystem>& systems, int id, unordered_map<int, CPipe>& pipes) {
    if (systems.find(id) != systems.end()) {

        ofstream fout;
        fout.open("log.txt", ios::app);
        fout << "delete system id: " << id;
        fout.close();

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

//void bfs(unordered_map<int, vector<int>>& graph, int id, vector<int>& visited, unordered_map<int, vector<int>>& steps, int step) {
//    queue<int> q;
//    visited.push_back(id);
//    q.push(id);
//    while (q.size() > 0) {
//        int m = q.front();
//        if (find(steps.at(step - 1).begin(), steps.at(step - 1).end(), m) == steps.at(step - 1).end()) {
//            steps.at(step).push_back(m);
//        }
//        if (graph.count(m)) {
//            for (int i : graph.at(id)) {
//                if (find(visited.begin(), visited.end(), i) == visited.end()) {
//                    q.push(i);
//                    visited.push_back(i);
//                }
//            }
//        }
//        q.pop();
//
//    }
//
//
//}
//

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

void find_shortest_way(unordered_map<int, CSystem>& systems, unordered_map<int, CStation>& stations, unordered_map<int, CPipe>& pipes) {
    if (systems.size() < 2) {
        cout << "Number of systems is too small" << endl;
        return;
    }
    int start_id, stop_id, min, minindex;
    vector<int> visited, d;
    cout << "Type start station: " << endl;
    start_id = get_correct_entrance_id(stations);
    cout << "Type stop station: " << endl;
    stop_id = get_correct_exit_id(stations, start_id);
    vector<int> counter;
    for (auto& i : systems) {
        if (find(counter.begin(), counter.end(), i.second.entrance_id) == counter.end()) counter.push_back(i.second.entrance_id);
        if (find(counter.begin(), counter.end(), i.second.exit_id) == counter.end()) counter.push_back(i.second.exit_id);
    }
    unordered_map<int, vector<int>> graph = create_graph(systems);
    vector<vector<int>> matrix = create_matrix(systems, pipes, counter.size());
    for (int i = 0; i < counter.size(); i++) d.push_back(10000);
    d[start_id] = 0;

    for (int i = 0; i < counter.size(); ++i) {
        min = 10000;
        for (int j = 0; j < counter.size() ; j++) {
            if ((find(visited.begin(), visited.end(), j) == visited.end()) && (d[j] < min)) {
                min = d[j];
                minindex = j;
            }
        }
        visited.push_back(minindex);
        for (int j = 0; j < counter.size() ; j++) {
            if ((find(visited.begin(), visited.end(), i) == visited.end()) && matrix[minindex][j] > 0 && d[minindex] != 10000 && d[minindex] + matrix[minindex][j] < d[j]) {
                d[j] = d[minindex] + matrix[minindex][j];
            } 
        }     
    }
    if (d[stop_id] == 10000) cout << "no way between station " << start_id << " and station " << stop_id << endl;
    else cout << "Distance : " << d[stop_id] << endl;
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
