#include "Storage.h"
#include "Garage.h"
#include "Map_info.h"
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <cstdlib>

#pragma once

class Firm
{
	friend class Test;
	Garage garage;
	Storage storange;
	Map_info map;
	int gas_cost = 4;

	void start_delivery_for_main_city();
	void start_delivery_for_cities();
	std::vector <int> reorganize_destinations(std::vector <int> cities);
	int calculate_way(std::vector <int> cities);
	int calculate_cost(const int way, const Garage::Vehicle<int, int, int>* vehicle, const int& number);
	std::vector <int> distances(std::vector <int> cities);

	template <class Package_type> // wyswietlanie informacji o dostawie
	Garage::Vehicle<int, int, int>* delivering(std::vector <int>& destinations, std::vector <Package_type>& packages_list, int& size, std::string* names, std::vector <int>& places, std::vector <int>& ways) {
		std::string destination;
		bool for_cities = false;
		if (ways.size())
			for_cities = true;
		Garage::Vehicle<int, int, int>* vehicle = choose_vehicle(packages_list);
		std::cout << vehicle->name << " was choosen for this delivery and it left the base" << std::endl;
		for (int i = 1; i < int(destinations.size()) - 1; i++) {
			for (int k = 0; k < size; k++) {
				if (places[k] == destinations[i])
					destination = names[k];
			}
			if (for_cities) {
				std::cout << "Road..." << std::endl;
				for (int n = 0; n < ways[i - 1]; n++) {
					sleep(12);
					std::cout << "_";
				}
				std::cout << std::endl;
				std::cout << "Drove " << ways[i - 1] << " km" << std::endl;
			}
			std::cout << vehicle->name << " arrived to " << destination << std::endl;
			for (int j = 0; j < int(packages_list.size()); j++) {
				if (packages_list[j].destination == destinations[i]) {
					std::cout << "Parsel " << packages_list[j].name << " was succesfully delivered" << std::endl;
				};
			}
		}
		if (for_cities) {
			for (int n = 0; n < ways[ways.size() - 1]; n++) {
				sleep(12);
				std::cout << "_";
			}
			std::cout << std::endl;
			std::cout << "Drove " << ways[ways.size() - 1] << " km" << std::endl;
		}
		std::cout << vehicle->name << " returns to the base " << std::endl;
		return vehicle;
	}

	template <class Package_type> // szablonowa funkcja wyboru najbardziej pasujacego pojazdu
	Garage::Vehicle<int, int, int>* choose_vehicle(const std::vector <Package_type>& packages) {
		if (garage.vehicles.empty()) {
			std::cout << "List of vehicles is empty now" << std::endl;
			main_menu();
		}
		Garage::Vehicle<int, int, int>* vehicle(garage.vehicles[0]);
		int space = 0;
		for (int i = 0; i < int(garage.vehicles.size()); i++) {
			if (garage.vehicles[i]->capacity > vehicle->capacity)
				vehicle = garage.vehicles[i];
		}
		for (int i = 0; i < int(packages.size()); i++)
			space += packages[i].size;
		if (vehicle->capacity < space) {
			std::cout << "Every vehicle is too small for all packages" << std::endl;
			main_menu();
		}
		for (int i = 0; i < int(garage.vehicles.size()); i++)
			if (garage.vehicles[i]->capacity < vehicle->capacity and garage.vehicles[i]->capacity >= space)
				vehicle = garage.vehicles[i];
		return vehicle;
	};

	template <class Package_type> // wyznaczenie miejsc do odwiedzenia
	std::vector <int> collect_destinations(const std::vector <Package_type>& packages, const std::vector <int>& places) {
		std::vector <int> destinations = {};
		destinations.push_back(map.main_city);
		for (int i = 0; i < int(places.size()); i++) {
			bool mark = false;
			for (int j = 0; j < int(packages.size()); j++) {
				if (places[i] == packages[j].destination) {
					for (int k = 1; k < int(destinations.size()); k++) {
						if (destinations[k] == packages[j].destination)
							mark = true;
					};
					if (mark == false)
						destinations.push_back(packages[j].destination);
				}
			}
		}
		destinations.push_back(map.main_city);
		return destinations;
	};

public:
	void main_menu();
};
