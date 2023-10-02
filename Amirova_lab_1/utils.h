#pragma once
#include <iostream>

template <typename T>
T get_correct_number(T min, T max)
{
	T x;
	while ((std::cin >> x).fail()
		|| std::cin.peek() != '\n'	
		|| x < min || x > max)		
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Type number (" << min << "-" << max << "):";
	}
	return x;
}

bool get_correct_bool() {
	bool x;
	do {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Type (true - 1 /false - 0): ";
		std::cin >> x;
	} while (std::cin.fail());
	return x;
}