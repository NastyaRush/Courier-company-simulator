#include "Garage.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void Garage::add_vehicle() { // dodanie nowego obiektu pojazdu i alokacja go w
                             // pamieci dynamicznej
  string error = "This value cannot be zero or less!";
  string name;
  int speed;
  int capasity;
  int gas_consumption;
  int drivers_salary;
  cout << "Enter name of vehicle: " << endl;
  cin >> name;
  while (true) {
    cout << "Enter speed of vehicle (km/h) : " << endl;
    cin >> speed;
    check(speed);
    if (!cin) {
      safe_input();
      while (cin.get() != '\n')
        ;
    } else
      break;
  }
  while (true) {
    cout << "Enter capasity of vehicle: " << endl;
    cin >> capasity;
    check(capasity);
    if (!cin) {
      safe_input();
      while (cin.get() != '\n')
        ;
    } else
      break;
  }
  while (true) {
    cout << "Enter gas consumption of vehicle (for 100 km) : " << endl;
    cin >> gas_consumption;
    check(gas_consumption);
    if (!cin) {
      safe_input();
      while (cin.get() != '\n')
        ;
    } else
      break;
  }
  while (true) {
    cout << "Enter driver's salary for this vehicle (for hour of work) :"
         << endl;
    cin >> drivers_salary;
    check(drivers_salary);
    if (!cin) {
      safe_input();
      while (cin.get() != '\n')
        ;
    } else
      break;
  }
  Vehicle<int, int, int> *vehicle = NULL;
  vehicle = new Vehicle<int, int, int>(
      name, speed, capasity, gas_consumption,
      drivers_salary); // dynamiczna alokacja pamieci dla nowego obiektu pojazdu
  vehicles.push_back(vehicle);
};

void Garage::safe_input() { // checking input data
  cout << "Uncorrect input, you tried to enter letters when number is needed!"
       << endl;
  cin.clear();
}

void Garage::check(int value) { // checking input data
  if (value <= 0) {
    throw runtime_error("This value cannot be zero or less!");
  }
}

void Garage::delete_vehicle() { // usuniecie pojazdu i zwolnienie pamieci
  show_vechicles_list();
  int index;
  cout << "Enter number of vehicle from list (counting from 0) of vehicle to "
          "delete: ";
  cin >> index;
  auto start = vehicles.cbegin();
  delete vehicles[index];
  vehicles.erase(start + index);
}

void Garage::show_vechicles_list() { // wyświetlanie listy pojazdów
  if (vehicles.empty()) {
    cout << "This list is empty now" << endl;
    return;
  }
  for (int i = 0; i < int(vehicles.size()); i++) {
    cout << "Name: " << vehicles[i]->name << " "
         << "Speed: " << vehicles[i]->speed << " "
         << "Gas consumption: " << vehicles[i]->gas_consumption << " "
         << "Capacity: " << vehicles[i]->capacity << " "
         << "Driver's salary: " << vehicles[i]->drivers_salary << endl;
  }
}

void Garage::write_to_file() { // zapis listy pojazdów do pliku
  ofstream out;
  out.open("vehicles.txt");
  for (int i = 0; i < int(vehicles.size()); i++) {
    out << vehicles[i]->name << "," << vehicles[i]->speed << ","
        << vehicles[i]->capacity << "," << vehicles[i]->gas_consumption << ","
        << vehicles[i]->drivers_salary << endl;
  }
  out.close();
}

void Garage::read_from_file() { // odczyt pojazdów z pliku
  string line, readline;
  vector<string> data;
  ifstream in("vehicles.txt");
  if (in.is_open()) {
    while (getline(in, line)) {
      data.push_back(readline);
      istringstream ist(line);
      while (getline(ist, readline, ',')) {
        data.push_back(readline);
      }
    }
  }
  in.close();
  for (int i = 0; i < (int)(data.size()); i = i + 5) {
    ++i;
    Vehicle<int, int, int> *vehicle = NULL;
    vehicle = new Vehicle<int, int, int>(
        data[i], stoi(data[i + 1], nullptr, 10), stoi(data[i + 2], nullptr, 10),
        stoi(data[i + 3], nullptr, 10),
        stoi(data[i + 4], nullptr,
             10)); // dynamiczna alokacja pamieci dla nowego obiektu pojazdu
    vehicles.push_back(vehicle);
  }
}