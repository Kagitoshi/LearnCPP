#include <iostream>

int getGuess()
{
	int guess{};

	//Loops until a vaild integer has been inputted.
	do
	{
		if (!(std::cin >> guess))
		{
			std::cout << "Please enter a valid integer.\n";

			std::cin.clear();
			std::cin.ignore();
		}
		else
		{
			break;
		}
	} while (true);

	return guess;
}

int getNumIncrease()
{
	std::cout << "How many numbers from the starting you would like to count up to?: ";
	int numIncrease{};

	//Loops until a vaild integer has been inputted.
	do
	{
		if (!(std::cin >> numIncrease))
		{
			std::cout << "Please enter a valid integer.\n";

			std::cin.clear();
			std::cin.ignore();
		}
		else
		{
			break;
		}
	} while (true);

	return numIncrease;
}

bool getPlayAgain()
{
	char playAgain{};

	std::cin >> playAgain;
	std::cin.ignore();

	do
	{
		if (playAgain == 'y' || playAgain == 'Y')
		{
			return true;
		}
		else if (playAgain == 'n' || playAgain == 'N')
		{
			return false;
		}
		else
		{
			std::cout << "That was not a valid choice. Please select 'Y' or 'N'.\n\n";
		}
	} while (true);
}

int getStartingNum()
{
	std::cout << "Which number would you like to start from?: ";
	int startingNum{};

	//Loops until a vaild integer has been inputted.
	do
	{
		if (!(std::cin >> startingNum))
		{
			std::cout << "Please enter a valid integer.\n";

			std::cin.clear();
			std::cin.ignore();
		}
		else
		{
			break;
		}
	} while (true);


	return startingNum;
}
