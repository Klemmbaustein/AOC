#define HARD 1
#define TEST 0
#include <iostream>
#include <fstream>
#include <string>

#if HARD
#include <set>


/*
 The std::set stores it's data ordered from lowest to highest.
 We can just insert all the elve's calories into that set and
 read the last 3 values.
*/

int main()
{
	std::set<unsigned int> OrderedCalories;

	std::string InputFile = TEST ? "TestInput.in" : "Input.in";
	std::ifstream InputStream = std::ifstream(InputFile);

	unsigned int CurrentNumCalories = 0;
	while(!InputStream.eof())
	{
		char FoodValueString[8];
		InputStream.getline(FoodValueString, 8);

		if(FoodValueString[0] != '\0')
		{
			CurrentNumCalories += std::stoi(FoodValueString);
		}
		else 
		{
			OrderedCalories.insert(CurrentNumCalories);
			CurrentNumCalories = 0;
		}
	}

	unsigned int Top3[] = 
	{
		*std::prev(OrderedCalories.end(), 1),
		*std::prev(OrderedCalories.end(), 2),
		*std::prev(OrderedCalories.end(), 3)
	};

	std::cout << "Top1: " << Top3[0] << std::endl;
	std::cout << "Top2: " << Top3[1] << std::endl;
	std::cout << "Top3: " << Top3[2] << std::endl;
	std::cout << "Result: " << Top3[0] + Top3[1] + Top3[2] << std::endl;
}

#else

int main()
{
	unsigned int MaxCalories = 0;
	std::string InputFile = TEST ? "TestInput.in" : "Input.in";
	std::ifstream InputStream = std::ifstream(InputFile);

	unsigned int CurrentNumCalories = 0;
	while(!InputStream.eof())
	{
		char FoodValueString[8];
		InputStream.getline(FoodValueString, 8);

		if(FoodValueString[0] != '\0')
		{
			CurrentNumCalories += std::stoi(FoodValueString);
		}
		else 
		{
			MaxCalories = std::max(CurrentNumCalories, MaxCalories);
			CurrentNumCalories = 0;
		}
	}
	std::cout << MaxCalories << std::endl;
}

#endif