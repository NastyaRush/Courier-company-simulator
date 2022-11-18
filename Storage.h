#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Map_info.h"
#pragma once

class Storage // klasa zewnetrzna przechowująca liste obiektow paczek i operujaca na nich
{
	friend class Map_info;
	friend class Firm;
	friend class Test;

	class Package { // klasa paczki
		friend class Storage;
		friend class Firm;

		std::string name;
		int destination;
		int size;

		Package(std::string n, int dest, int s) { // konstruktor
			name = n;  destination = dest; size = s;
		}
	};

	class Package_for_city : public Package { // klasa paczki do dostawy w glowne miasto
		friend class Firm;
		friend class Storage;
		friend class Test;

		bool for_city = true;
		Package_for_city(std::string n, int dest, int s) :Package(n, dest, s) { // dziedziczenie konstruktora
		}
	};

	class Package_for_cities : public Package { // klasa paczki do dostawy w inne miasta
		friend class Firm;
		friend class Storage;
		friend class Test;

		bool for_city = false;
		Package_for_cities(std::string n, int dest, int s) :Package(n, dest, s) { // dziedziczenie konstruktora
		}
	};

	std::vector <Package_for_city> packages_for_main_city; // lista obiektow paczek do dostawy w glowne miasto 
	std::vector <Package_for_cities> packages_for_cities; // lista obiektow paczek do dostawy w inne miasta 
	Map_info map;

	void add_package();
	void read_from_file(std::string filename);
	void safe_input();

	template <class Package_type>
	void write_to_file(const std::vector <Package_type>& packages, bool for_city) { // funkcja szablonowa do zapisywania list paczek do plików
		std::ofstream out;
		if (for_city) {
			out.open("packages_for_city.txt");
		}
		else {
			out.open("packages_for_cities.txt");
		}
		if (out.is_open())
		{
			for (int i = 0; i < int(packages.size()); i++) {
				out << packages[i].name << "," << packages[i].destination << "," << packages[i].size << std::endl;
			}
		}
		out.close();
	}

	template <class Package_type> // funkcja szablonowa do wyswietlania listy paczek
	void show_packages_list(const std::vector <Package_type>& packages, const std::string destinations_names[], const int& size, const std::vector <int>& destinations) {
		if (packages.empty()) {
			std::cout << "This list is empty now" << std::endl;
			return;
		}
		std::string destination;
		for (int i = 0; i < int(packages.size()); i++) {
			for (int j = 0; j < size; j++) {
				if (destinations[j] == packages[i].destination)
					destination = destinations_names[j];
			}

			std::cout << "Name: " << packages[i].name << " " << "Destination: " << destination << " " << "Size: " << packages[i].size << std::endl;
		}
	}

};

