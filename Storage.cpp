
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Storage.h"
using namespace std;


	void Storage::add_package() { // dodanie paczki
		string name;
		int destination;
		int size;
		map.show_list(map.places_names, map.places_size, map.places);
		map.show_list(map.cities_names, map.cities_size, map.cities);
		cout << "\nEnter name of the package: " << endl;
		cin >> name;
		while (true) {
			cout << "Enter index of destination of the package: " << endl;
			cin >> destination;
			if (destination < 0) {
				throw runtime_error("This value cannot be less than zero!");
			}
			if (!cin) {
				safe_input();
				while (cin.get() != '\n');
			}
			else break;
		}
		while (true) {
			cout << "Enter size of the package: " << endl;
			cin >> size;
			if (size <= 0) {
				throw runtime_error("This value cannot be zero or less!");
			}
			if (!cin) {
				safe_input();
				while (cin.get() != '\n');
			}
			else break;
		}
		bool was_added = false, for_city = false;
		for (int i = 0; i < map.places_size; i++) {
			if (map.places[i] == destination) {
				for_city = true, was_added = true;
			}
		}
		if (for_city) {
			Package_for_city package(name, destination, size);
			packages_for_main_city.push_back(package);
		}
		else {
			for (int i = 0; i < map.cities_size; i++) {
				if (map.cities[i] == destination) {
					was_added = true;
					Package_for_cities package(name, destination, size);
					packages_for_cities.push_back(package);
				}
			}
		}
		if (was_added)
			cout << "New package was sucsessfully added" << endl;
		else
			cout << "New package was not added" << endl;
	};

	void Storage::safe_input() { // checking input data
		cout << "Uncorrect input, you tried to enter letters when number is needed!" << endl;
		cin.clear();
	}

	void Storage::read_from_file(string filename) { // odczyt pojazdów z pliku
		string line, readline;
		vector <string> data;
		ifstream in(filename);
		if (in.is_open())
		{
			while (getline(in, line))
			{
				data.push_back(readline);
				istringstream ist(line);
				while (getline(ist, readline, ',')) {
					data.push_back(readline);
				}		
			}
		}
		in.close();
		for (int i = 0; i < (int)(data.size()); i = i + 3) {
			++i;
			if (filename == "packages_for_city.txt") {
				Package_for_city package(data[i], stoi(data[i + 1], nullptr, 10), stoi(data[i + 2], nullptr, 10));
				packages_for_main_city.push_back(package);
			}
			else {
			Package_for_cities package(data[i], stoi(data[i+1], nullptr, 10), stoi(data[i+2], nullptr, 10));
			packages_for_cities.push_back(package);
			}
		}
	}