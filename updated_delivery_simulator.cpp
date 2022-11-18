#include <iostream>
#include <string>
#include <vector>
#include "Map_info.h"
#include "Garage.h"
#include "Storage.h"
#include "Firm.h"
#include "Test.h"
using namespace std;



int main()
{
	Firm firm;
	try {
		firm.main_menu();
	}
	catch (exception& ex) { // handling exceptions
		cout << "An exception ocurred: " << endl;
		cout << ex.what() << endl;
		exit(1);
	}
	Test test;
	test.test_calculate_way();
	test.test_reorganize_destinations();
	test.test_collect_destinations();
	test.test_choose_vehicle();
	exit(0);
	return 0;
};