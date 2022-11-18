#include <iostream>
#include <string>
#include <vector>
#include "Map_info.h"
using namespace std;


	void Map_info::show_list(const string* list, const int& size, vector <int> indexes) { // wyswietlenie listy punktow dostawy lub miast do dostawy i ich indeksow
		for (int i = 0; i < size; i++) {
			cout << list[i] << " " << "index: " << indexes[i] << endl;
		}
	}