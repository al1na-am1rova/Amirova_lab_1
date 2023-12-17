#pragma once
#include <iostream>
#include "CPipe.h"
#include "CStation.h"
#include <unordered_map>

using namespace std;

class CSystem
{
public:
	int id;
	static int MaxId;
	int entrance_id;
	int exit_id;
	int pipe_id;
	int flow_capacity;

	CSystem();

	template <typename T>
	friend T get_correct_number(T min, T max);
	friend  ostream& operator << (ostream& out, const CSystem& g);
	friend istream& operator >> (istream& in, CSystem& g);
	string get_type();
	friend void get_flow_capacity(unordered_map<int, CPipe>& pipes, CSystem& system);
	friend int is_pipe_in_system(int id, unordered_map<int, CSystem> systems);
	friend int is_station_in_system(int id, unordered_map<int, CSystem> systems);
	friend bool already_in_system(int entrance_id, int exit_id, unordered_map<int, CSystem> systems);
	friend unordered_map<int, vector<int>> create_graph(unordered_map<int, CSystem>& systems);
	friend vector<vector<int>> create_matrix(unordered_map<int, CSystem>& systems, unordered_map<int, CPipe>& pipes, int vertex_num);
	friend CPipe& select_pipe(unordered_map<int, CPipe>& pipes, int id);
	friend void erase_system(unordered_map<int, CSystem>& systems, int id, unordered_map<int, CPipe>& pipes);
};