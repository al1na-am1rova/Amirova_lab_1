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

	CSystem();

	template <typename T>
	friend T get_correct_number(T min, T max);
	friend  ostream& operator << (ostream& out, const CSystem& g);
	friend istream& operator >> (istream& in, CSystem& g);
	string get_type();
	/*CPipe& select_pipe(vector<CPipe>& pipes);*/
};