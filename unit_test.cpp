#define CATCH_CONFIG_RUNNER
#include "Catch.hpp"
#include "DynamicArray.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::cin;
using std::string;


TEST_CASE("Description", "[label]") 
{
	SECTION("Dynamic Array") 
	{
		DynamicArray<string> stringArray;
		cout << "Size of Array is " << stringArray.size() << endl;

		REQUIRE(stringArray.empty());

		stringArray.clear();

		stringArray.push_back(" bork");
		cout << stringArray[0] << endl;

		stringArray.push_back(" blep");
		cout << stringArray[1] << endl;

		REQUIRE(stringArray.size() == 2);
		cout << "Size of Array is " << stringArray.size() << endl;

		stringArray.pop_back();
		cout << "POP!" << endl;

		REQUIRE(stringArray.size() == 1);
		cout << "Size of Array is " << stringArray.size() << endl;

		stringArray.push_back(" Doggo");
		stringArray.push_back(" says");

		cout << stringArray[0] << stringArray[1] << stringArray[2] << endl;
		cout << "Size of Array is " << stringArray.size() << endl;

		REQUIRE(stringArray.size() == 3);

		stringArray.erase_at(0);

		cout << "Erased 0" << endl;
		cout << stringArray[0] << stringArray[1] << endl;

		stringArray.add_at(1, "Timmy");
		stringArray.erase_at(0);

		cout << "Added a Timmy" << endl;
		cout << "Erased a Doggo" << endl;
		cout << stringArray[0] << stringArray[1] << endl;

		REQUIRE(stringArray.front() == "Timmy");
		REQUIRE(stringArray.back() == " says");

		cout << "Front and Back are 'Timmy' and ' says'" << endl;

		int Num = 0;
		for (auto word : stringArray)
		{
			cout << word << endl;
			REQUIRE(word == stringArray[Num]);
			Num++;
		}
	}
}

int main(int argc, char** argv) 
{
	int result = Catch::Session().run(argc, argv);

	cin.get();

	return (result < 0xff ? result : 0xff);
}