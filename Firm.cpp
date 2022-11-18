#include "Firm.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;



	void Firm::start_delivery_for_main_city() { // rospoczecie dostawy w punkty dostawy

		if (storange.packages_for_main_city.empty() == true) {
			cout << "There is no packages to deliver" << endl;
			main_menu();
		}
		string destination;
		vector <int> destinations = collect_destinations(storange.packages_for_main_city, map.places);
		vector <int> ways = {};
		delivering(destinations, storange.packages_for_main_city, map.places_size, map.places_names, map.places, ways);
		storange.packages_for_main_city.clear();
	}

	void Firm::start_delivery_for_cities() { // rospoczecie dostawy do miast

		if (storange.packages_for_cities.empty() == true) {
			cout << "There is no packages to deliver" << endl;
			main_menu();
		}
		int number_of_packages = storange.packages_for_cities.size();
		vector <int> destinations = collect_destinations(storange.packages_for_cities, map.cities);
		destinations = reorganize_destinations(destinations);
		vector <int> ways = distances(destinations);
		Garage::Vehicle<int, int, int>* vehicle = delivering(destinations, storange.packages_for_cities, map.cities_size, map.cities_names, map.cities, ways);
		int way = calculate_way(destinations);
		cout << "It drove " << way << " km " << endl;
		cout << "Cost of this deliver for single package is " << calculate_cost(way, vehicle, number_of_packages) << " zl" << endl;
		storange.packages_for_cities.clear();
	}

	vector <int> Firm::distances(vector <int> cities) { // wyliczenie przebytej drogi
		vector <int> distances = {};
		for (int j = 0; j < int(cities.size() - 1); j++) {
			distances.push_back((int)((map.distances[cities[j]][cities[j + 1]])));
		}
		return distances;
	}

	int Firm::calculate_way(vector <int> cities) { // wyliczenie przebytej drogi
		int way = 0;
		for (int j = 0; j < int(cities.size() - 1); j++) {
			way += map.distances[cities[j]][cities[j + 1]];
		}
		return way;
	}

	int Firm::calculate_cost(const int way, const Garage::Vehicle<int, int, int>* vehicle, const int& number) { //  wyliczenie kosztow dostawy
		int cost = ((way / vehicle->speed) * vehicle->drivers_salary + (way * vehicle->gas_consumption * gas_cost) / 100) / number;
		return cost;
	}

	vector<int> Firm::reorganize_destinations(vector<int> cities) { // ustawienie miejsc do odwiedzenia w odpowiedniej kolejnosci
		for (int i = 0; i < int(cities.size()) - 1; i++)
			for (int j = i + 1; j < int(cities.size()) - 1; j++) {
				if (map.distances[cities[i]][cities[i + 1]] > map.distances[cities[i]][cities[j]]) {
					int temp;
					temp = cities[i + 1];
					cities[i + 1] = cities[j];
					cities[j] = temp;
				}
			}
		return cities;
	}


	void Firm::main_menu() { // glowne menu
		cout << "\n\nWelcome to symulator of courier service!\nYou are in the main menu. Enter relevant number for desired function.\n" << endl;
		cout << "\n0 - Information\n1 - Exit from program\n2 - Add package\n3 - Organize delivery for main city\n4 - Organize delivery for cities\n5 - Add vehicle\n6 - Delete vehicle\n7 - Show packages for main city\n8 - Show packages for cities\n9 - Show list of cities\n10 - Show list of delivery points\n11 - Show list of vehicles\n12 - Write packages to files\n13 - Write vehicles to file\n14 - Read vechicles from file\n15 - Read packages from files\n" << endl;
		int choice;
		cin >> choice;
		switch (choice) {
		case 0:
			cout << " This program is a simulation of a courier service which delivers packages from\n" << map.main_city_str << " (signed as the main city) to Krakow, Gdansk, Bialostok\nand Wroclaw and to 4 delivery points in Warszaw.\n\nIt is considered that this delivery points in Warszaw are in sich order\nthat the first point is closest to the base, the second point\nis closest to the first point and so on." << endl;
			cout << "\nFor finding optimal way between cities is used nearest neighbor algorithm.\nFor it there is a two-dimensional array which contains distances\nbetween all cities in program." << endl;
			main_menu();
			break;
		case 1:
			cout << "Exit from program" << endl;
			if (!garage.vehicles.empty()) {
				for (size_t i = 0; i < garage.vehicles.size(); ++i) {
					delete garage.vehicles[i];
				}
				garage.vehicles.clear();
			}
			break;
		case 2:
			cout << "Adding package" << endl;
			storange.add_package();
			main_menu();
			break;
		case 3:
			cout << "Organizing delivery for main city:" << endl;
			start_delivery_for_main_city();
			main_menu();
			break;
		case 4:
			cout << "Organizing delivery for cities:" << endl;
			start_delivery_for_cities();
			main_menu();
			break;
		case 5:
			cout << "Adding vehicle:" << endl;
			garage.add_vehicle();
			main_menu();
			break;
		case 6:
			cout << "Deleting vehicle:" << endl;
			garage.delete_vehicle();
			main_menu();
			break;
		case 7:
			cout << "Showing packages for main city:" << endl;
			storange.show_packages_list(storange.packages_for_main_city, map.places_names, map.places_size, map.places);
			main_menu();
			break;
		case 8:
			cout << "Showing packages for cities:" << endl;
			storange.show_packages_list(storange.packages_for_cities, map.cities_names, map.cities_size, map.cities);
			main_menu();
			break;
		case 9:
			cout << "Showing list of cities:" << endl;
			map.show_list(map.cities_names, map.cities_size, map.cities);
			main_menu();
			break;
		case 10:
			cout << "Showing list of delivery points:" << endl;
			map.show_list(map.places_names, map.places_size, map.places);
			main_menu();
			break;
		case 11:
			cout << "Showing list of vechicles:" << endl;
			garage.show_vechicles_list();
			main_menu();
			break;
		case 12:
			cout << "Writing packages to files:" << endl;
			storange.write_to_file(storange.packages_for_main_city, true);
			storange.write_to_file(storange.packages_for_cities, false);
			main_menu();
			break;
		case 13:
			cout << "Writing vechicles to file:" << endl;
			garage.write_to_file();
			main_menu();
			break;
		case 14:
			cout << "Reading vechicles from file:" << endl;
			garage.read_from_file();
			main_menu();
			break;
		case 15:
			cout << "Reading packages from files:" << endl;
			storange.read_from_file("packages_for_city.txt");
			storange.read_from_file("packages_for_cities.txt");
			main_menu();
			break;
		default:
			cout << "Command was not defined. You will be returned to the main menu." << endl;
			main_menu();
			break;
		}
	}
