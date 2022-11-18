#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Package { // klasa paczki

	friend class Firm;
	string name;
	int destination;
	int size;
public:
	Package(string n, int dest, int s) {
		name = n;  destination = dest; size = s;
	}
};

class Package_for_city : public Package { // klasa paczki do dostawy w główne miasto
	friend class Firm;
	bool for_city = true;
	Package_for_city(string n, int dest, int s) :Package(n, dest, s) {
	}
};

class Package_for_cities : public Package { // klasa paczki do dostawy w innne miasta
	friend class Firm;
	bool for_city = false;
	Package_for_cities(string n, int dest, int s) :Package(n, dest, s) {
	}
};

class Garage { // klasa zewnetrzna przechowująca liste wskażnikow na obiekty pojazdow i operujaca na nich
	friend class Firm;
public:
	template <class T1, class T2, class T3>
	class Vehicle { // klasa pojazdu z szablonem, wewnetrzna
		friend class Firm;
	public:
		string name;
		T1 speed;
		int capacity;
		T2 gas_consumption;
		T3 drivers_salary;
		Vehicle(string n, T1 sp, int cap, T2 gas, T3 salary) {
			name = n; speed = sp; capacity = cap; gas_consumption = gas; drivers_salary = salary;
		}

	public:

		Vehicle(const Vehicle& other) { // konstruktor kopijacy
			this->name = other.name; this->speed = other.speed; this->capacity = other.capacity; this->gas_consumption = other.gas_consumption, this->drivers_salary = other.drivers_salary;
		}
	};

	vector <Vehicle<int, int, int>*> vehicles;

	void add_vehicle() { // dodanie nowego obiektu pojazdu
		string name;
		int speed;
		int capasity;
		int gas_consumption;
		int drivers_salary;
		cout << "Enter name of vehicle: " << endl;
		cin >> name;
		cout << "Enter speed of vehicle (km/h) : " << endl;
		cin >> speed;
		cout << "Enter capasity of vehicle: " << endl;
		cin >> capasity;
		cout << "Enter gas consumption of vehicle (for 100 km) : " << endl;
		cin >> gas_consumption;
		cout << "Enter driver's salary for this vehicle (for hour of work) :" << endl;
		cin >> drivers_salary;
		Vehicle<int, int, int>* p = NULL;
		p = new Vehicle<int, int, int>(name, speed, capasity, gas_consumption, drivers_salary); // dynamiczna alokacja pamieci dla nowego obiektu pojazdu
		vehicles.push_back(p);
	};

	void delete_vehicle() { // usuniecie pojazdu i zwolnienie pamieci
		show_vechicles_list();
		int index;
		cout << "Enter number of vehicle from list (counting from 0) of vehicle to delete: ";
		cin >> index;
		auto start = vehicles.cbegin();
		delete vehicles[index];
		vehicles.erase(start + index);
	}

	void show_vechicles_list() { // Wyświetlanie listy pojazdów
		if (vehicles.empty()) {
			cout << "This list is empty now" << endl;
			return;
		}
		for (int i = 0; i < int(vehicles.size()); i++) {
			cout << "Name: " << vehicles[i]->name << " " << "Speed: " << vehicles[i]->speed << " " << "Gas consumption: " << vehicles[i]->gas_consumption << " " << "Capacity: " << vehicles[i]->capacity << " " << "Driver's salary: " << vehicles[i]->drivers_salary << endl;
		}
	}
};

class Map_info { // klasa przechowyjaca informacje o miastach, odleglosciach pomiedzy nimi i punktach dostawy
	friend Firm;
	friend Garage;
public:
	string main_city_str = "Warszaw";
	int main_city = 4;
	string cities_names[5] = { "Krakow", "Gdansk", "Bialostok", "Wroclaw" };
	vector <int> cities = { 0, 1, 2, 3 };
	string places_names[5] = { "Delivery point 1", "Delivery point 2", "Delivery point 3", "Delivery point 4" };
	vector <int> places = { 5, 6, 7, 8 };
	int distances[5][5] = {
							{0, 556, 498, 272, 256},
							{556, 0, 430, 556, 344},
							{498, 430, 0, 545, 198},
							{272, 556, 545, 0, 355},
							{256, 344, 198, 355, 0} };
	int cities_size = cities.size();
	int places_size = places.size();

	void show_list(const string* list, const int& size, vector <int> indexes) { // wyswietlenie listy atrubutow
		for (int i = 0; i < size; i++) {
			cout << list[i] << " " << "index: " << indexes[i] << endl;
		}
	}
};


class Firm {
	friend Garage;
	friend Map_info;
	Garage garage;
	Map_info map;

	int gas_cost = 4;
	vector <Package_for_city> packages_for_main_city;
	vector <Package_for_cities> packages_for_cities;

	void add_package() { // dodanie paczki
		string name;
		int destination;
		int size;
		map.show_list(map.places_names, map.places_size, map.places);
		map.show_list(map.cities_names, map.cities_size, map.cities);
		cout << "\nEnter name of the package: " << endl;
		cin >> name;
		cout << "Enter index of destination of the package: " << endl;
		cin >> destination;
		cout << "Enter size of the package: " << endl;
		cin >> size;
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

	template <class Package_type> // funkcja szablonowa do wyswietlania listy paczek
	void show_packages_list(const vector <Package_type>& packages, const string destinations_names[], const int& size, const vector <int>& destinations) {
		if (packages.empty()) {
			cout << "This list is empty now" << endl;
			return;
		}
		string destination;
		for (int i = 0; i < int(packages.size()); i++) {
			for (int j = 0; j < size; j++) {
				if (destinations[j] == packages[i].destination)
					destination = destinations_names[j];
			}

			cout << "Name: " << packages[i].name << " " << "Destination: " << destination << " " << "Size: " << packages[i].size << endl;
		}
	}

	void start_delivery_for_main_city() { // rospoczecie dostawy w punkty dostawy

		if (packages_for_main_city.empty() == true) {
			cout << "There is no packages to deliver" << endl;
			main_menu();
		}
		string destination;
		vector <int> destinations = collect_destinations(packages_for_main_city, map.places);
		delivering(destinations, packages_for_main_city, map.places_size, map.places_names, map.places);
		packages_for_main_city.clear();
	}

	void start_delivery_for_cities() { // rospoczecie dostawy do miast

		if (packages_for_cities.empty() == true) {
			cout << "There is no packages to deliver" << endl;
			main_menu();
		}
		int number_of_packages = packages_for_cities.size();
		vector <int> destinations = collect_destinations(packages_for_cities, map.cities);
		destinations = reorganize_destinations(destinations);
		Garage::Vehicle<int, int, int>* vehicle = delivering(destinations, packages_for_cities, map.cities_size, map.cities_names, map.cities);
		int way = calculate_way(destinations);
		cout << "It drove " << way << " km " << endl;
		cout << "Cost of this deliver for single package is " << calculate_cost(way, vehicle, number_of_packages) << " zl" << endl;
		packages_for_cities.clear();
	}

	template <class Package_type> // wyswietlanie informacji o dostawie
	Garage::Vehicle<int, int, int>* delivering(vector <int>& destinations, vector <Package_type>& packages_list, int& size, string* names, vector <int> places) {
		string destination;
		Garage::Vehicle<int, int, int>* vehicle = choose_vehicle(packages_list);
		cout << vehicle->name << " was choosen for this delivery and it left the base" << endl;
		for (int i = 1; i < int(destinations.size()) - 1; i++) {
			for (int k = 0; k < size; k++) {
				if (places[k] == destinations[i])
					destination = names[k];
			}
			cout << vehicle->name << " arrived to " << destination << endl;
			for (int j = 0; j < int(packages_list.size()); j++) {
				if (packages_list[j].destination == destinations[i]) {
					cout << "Parsel " << packages_list[j].name << " was succesfully delivered" << endl;
				};
			}
		}
		cout << vehicle->name << " returns to the base " << endl;
		return vehicle;
	}

	int calculate_way(vector <int> cities) { // wyliczenie przebytej drogi
		int way = 0;
		for (int j = 0; j < int(cities.size() - 1); j++) {
			way += map.distances[cities[j]][cities[j + 1]];
		}
		return way;
	}

	int calculate_cost(const int way, const Garage::Vehicle<int, int, int>* vehicle, const int number) { //  wyliczenie kosztow dostawy
		int cost = ((way / vehicle->speed) * vehicle->drivers_salary + (way * vehicle->gas_consumption * gas_cost) / 100) / number;
		return cost;
	}

	vector <int> reorganize_destinations(vector <int> cities) {
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

	template <class Package_type> // szablonowa funkcja wyboru najbardziej pasujacego pojazdu
	Garage::Vehicle<int, int, int>* choose_vehicle(const vector <Package_type>& packages) {
		if (garage.vehicles.empty()) {
			cout << "List of vehicles is empty now" << endl;
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
			cout << "Every vehicle is too small for all packages" << endl;
			main_menu();
		}
		for (int i = 0; i < int(garage.vehicles.size()); i++)
			if (garage.vehicles[i]->capacity < vehicle->capacity and garage.vehicles[i]->capacity >= space)
				vehicle = garage.vehicles[i];
		return vehicle;
	};

	template <class Package_type> // wyznaczenie miejsc do odwiedzenia
	vector <int> collect_destinations(const vector <Package_type>& packages, const vector <int> places) {
		vector <int> destinations = {};
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
	void main_menu() { // glowne menu
		cout << "\n\nWelcome to symulator of courier service!\nYou are in the main menu. Enter relevant number for desired function.\n" << endl;
		cout << "Information" << endl;
		cout << "\n0 - Information\n1 - Exit from program\n2 - Add package\n3 - Organize delivery for main city\n4 - Organize delivery for cities\n5 - Add vehicle\n6 - Delete vehicle\n7 - Show packages for main city\n8 - Show packages for cities\n9 - Show list of cities\n10 - Show list of delivery points\n11 - Show list of vehicles\n" << endl;
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
			garage.vehicles.clear(); // usuniecie wszystkich pojazdow i zwolnienie pamieci
			for (int i = 0; i < garage.vehicles.size(); ++i) {
				delete garage.vehicles[i];
			}
			exit(0);
			break;
		case 2:
			cout << "Adding package" << endl;
			add_package();
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
			show_packages_list(packages_for_main_city, map.places_names, map.places_size, map.places);
			main_menu();
			break;
		case 8:
			cout << "Showing packages for cities:" << endl;
			show_packages_list(packages_for_cities, map.cities_names, map.cities_size, map.cities);
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
		default:
			cout << "Command was not defined. You will be returned to the main menu." << endl;
			main_menu();
			break;
		}
	}
};


int main()
{
	Firm firm;
	firm.main_menu();
	return 0;
};