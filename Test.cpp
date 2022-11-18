#include "Test.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;


	void Test::test_calculate_way() { // funkcja testujaca liczenie przebutej drogi
		assert(test_firm.calculate_way(test_vector_1) == 1539);
		assert(test_firm.calculate_way(test_vector_2) == 1440);
		assert(test_firm.calculate_way(test_vector_3) == 883);
		cout << "\nTests of calculating way passed sucsessfully" << endl;
	}

	void Test::test_reorganize_destinations() { // funkcja testujaca reorganizacje miejsc do odwiedzenia
		vector <int> result_1 = { 4, 2, 1, 3, 4 };
		vector <int> result_2 = { 4, 2, 1, 0, 4 };
		vector <int> result_3 = { 4, 0, 3, 4 };
		assert(test_firm.reorganize_destinations(test_vector_4) == result_1);
		assert(test_firm.reorganize_destinations(test_vector_5) == result_2);
		assert(test_firm.reorganize_destinations(test_vector_3) == result_3);
		cout << "\nTests of reorganizing destinations passed sucsessfully" << endl;
	}

	void Test::test_choose_vehicle() { // funkcja testujaca wybranie najbardziej pasujacego wedlug pojemnosci samochodu
		Garage::Vehicle<int, int, int>* car_1 = NULL;
		car_1 = new Garage::Vehicle<int, int, int>("car_1", 80, 100, 7, 14);
		test_firm.garage.vehicles.push_back(car_1);
		Garage::Vehicle<int, int, int>* car_2 = NULL;
		car_2 = new Garage::Vehicle<int, int, int>("car_2", 90, 200, 10, 16);
		test_firm.garage.vehicles.push_back(car_2);
		Garage::Vehicle<int, int, int>* car_3 = NULL;
		car_3 = new Garage::Vehicle<int, int, int>("car_3", 90, 300, 13, 18);
		test_firm.garage.vehicles.push_back(car_3);
		(this)->test_calculate_cost(900, test_firm.garage.vehicles[0], 5, 81);
		(this)->test_calculate_cost(1200, test_firm.garage.vehicles[1], 10, 68);
		(this)->test_calculate_cost(1600, test_firm.garage.vehicles[2], 20, 56);
		cout << "\nTests of calculating cost passed sucsessfully" << endl;
		assert(test_firm.choose_vehicle(test_vector_6)->capacity == 200);
		assert(test_firm.choose_vehicle(test_vector_7)->capacity == 100);
		assert(test_firm.choose_vehicle(test_vector_8)->capacity == 200);
		assert(test_firm.choose_vehicle(test_vector_9)->capacity == 300);
		for (int i = 0; i < (int)test_firm.garage.vehicles.size(); ++i) {
			delete test_firm.garage.vehicles[i];
		}
		cout << "\nTests of choosing vehicle passed sucsessfully" << endl;
		test_firm.garage.vehicles.clear();
	}

	void Test::test_calculate_cost(const int way, const Garage::Vehicle<int, int, int>* vehicle, const int& number, const int result) { // funkcja testujaca liczenie kosztow dostawy
		assert(test_firm.calculate_cost(way, vehicle, number) == result);
	}

	void Test::test_collect_destinations() { // funkcja testujaca zebranie miejsc do odwiedzenia
		vector <int> result_1 = { 4, 5, 7, 8, 4 };
		vector <int> result_2 = { 4, 5, 6, 7, 4 };
		vector <int> result_3 = { 4, 0, 1, 3, 4 };
		vector <int> result_4 = { 4, 0, 2, 3, 4 };
		assert(test_firm.collect_destinations(test_vector_6, test_map.places) == result_1);
		assert(test_firm.collect_destinations(test_vector_7, test_map.places) == result_2);
		assert(test_firm.collect_destinations(test_vector_8, test_map.cities) == result_3);
		assert(test_firm.collect_destinations(test_vector_9, test_map.cities) == result_4);
		cout << "\nTests of collecting destinations passed sucsessfully" << endl;
	}