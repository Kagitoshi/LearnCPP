#include <cmath>
#include <iostream>
#include <random>
#include <vector>

int getMultiplier()
{
	std::random_device rd{};
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	std::mt19937 mt{ ss };

	// Gets a random number between 0 or 1 for the ternary operator below.
	std::uniform_int_distribution randomMultiplier{ 0 , 1 };

	// Gets a random 0 or 1 to decide the multiplier.
	int multiplier{ randomMultiplier(mt) ? 2 : 4 };

	return multiplier;
}

std::vector<int> getNumberList(int startingNum, int numIncrease, int multiplier)
{
	//Vector inilized with 0's and size set but getNumIncrease function.
	std::vector<int> numberList(numIncrease);

	//Filling out the vector with numbers based on startingNum and GetMultiplier
	for (int i{ 0 }; i < numIncrease; ++i)
	{
		numberList[i] = std::pow(startingNum, 2) * multiplier;
		startingNum++;
	}

	return numberList;
}
