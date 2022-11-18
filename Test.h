#include "Storage.h"
#include "Garage.h"
#include "Map_info.h"
#include "Firm.h"
#include <cassert>

#pragma once

class Test // klasa z testami
{
	Firm test_firm;
	Map_info test_map;
	Garage garage;

	std::vector <int> test_vector_1 = { 4, 2, 1, 3, 4 };
	std::vector <int> test_vector_2 = { 4, 2, 1, 0, 4 };
	std::vector <int> test_vector_3 = { 4, 0, 3, 4 };
	std::vector <int> test_vector_4 = { 4, 1, 2, 3, 4 };
	std::vector <int> test_vector_5 = { 4, 0, 1, 2, 4 };
	std::vector <Storage::Package_for_city> test_vector_6 = { Storage::Package_for_city("p1", 7, 80), Storage::Package_for_city("p2", 8, 80), Storage::Package_for_city("p3", 5, 20) };
	std::vector <Storage::Package_for_city> test_vector_7 = { Storage::Package_for_city("p1", 5, 40), Storage::Package_for_city("p2", 7, 30), Storage::Package_for_city("p3", 6, 20) };
	std::vector <Storage::Package_for_cities> test_vector_8 = { Storage::Package_for_cities("p1", 3, 40), Storage::Package_for_cities("p2", 1, 40), Storage::Package_for_cities("p3", 0, 120) };
	std::vector <Storage::Package_for_cities> test_vector_9 = { Storage::Package_for_cities("p1", 2, 80), Storage::Package_for_cities("p2", 3, 70), Storage::Package_for_cities("p3", 0, 90) };

public:
	void test_calculate_way();
	void test_reorganize_destinations();
	void test_choose_vehicle();
	void test_calculate_cost(const int way, const Garage::Vehicle<int, int, int>* vehicle, const int& number, const int result);
	void test_collect_destinations();
};

