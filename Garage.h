#include <iostream>
#include <string>
#include <vector>
#pragma once

class Garage // klasa zewnetrzna przechowująca liste wskażnikow na obiekty pojazdow i operujaca na nich
{
	friend class Firm;
	friend class Test;
	template <class T1, class T2, class T3>

	class Vehicle { // klasa pojazdu z szablonem, wewnetrzna
		friend class Firm;
		friend class Test;
		friend class Garage;

		std::string name;
		T1 speed;
		int capacity;
		T2 gas_consumption;
		T3 drivers_salary;

		Vehicle(std::string n, T1 sp, int cap, T2 gas, T3 salary) { // konstruktor
			this->name = n; this->speed = sp; this->capacity = cap; this->gas_consumption = gas; this->drivers_salary = salary;
		}

		Vehicle(const Vehicle& other) { // konstruktor kopijacy
			this->name = other.name; this->speed = other.speed; this->capacity = other.capacity; this->gas_consumption = other.gas_consumption, this->drivers_salary = other.drivers_salary;
		}
	};
	std::vector <Garage::Vehicle<int, int, int>*> vehicles; // vector przechowywajacy wskazniki na obiekty klasy Vehicle, ktore sa w pamieci dynamicznej
	void add_vehicle();
	void delete_vehicle();
	void show_vechicles_list();
	void write_to_file();
	void read_from_file();
	void safe_input();
	void check(int value);
};

