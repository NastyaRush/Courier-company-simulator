#include <iostream>
#include <string>
#include <vector>
#pragma once


class Map_info // klasa przechowywajaca informacje o miastach, odleglosciach pomiedzy nimi i punktach dostawy
{
public:
	friend class Firm;
	friend class Garage;
	friend class Test;
	friend class Storage;

	std::string main_city_str = "Warszaw";
	int main_city = 4;
	std::string cities_names[5] = { "Krakow", "Gdansk", "Bialostok", "Wroclaw" };
	std::vector <int> cities = { 0, 1, 2, 3 };
	std::string places_names[5] = { "Delivery point 1", "Delivery point 2", "Delivery point 3", "Delivery point 4" };
	std::vector <int> places = { 5, 6, 7, 8 };
	int distances[5][5] = {
							{0, 556, 498, 272, 256},
							{556, 0, 430, 556, 344},
							{498, 430, 0, 545, 198},
							{272, 556, 545, 0, 355},
							{256, 344, 198, 355, 0} };
	int cities_size = cities.size();
	int places_size = places.size();
	void show_list(const std::string* list, const int& size, std::vector <int> indexes);
};

