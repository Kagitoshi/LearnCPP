#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "userInput.h"
#include "generator.h"


int main()
{
	//Game Loop
	while (true){

		//User inputs for generating the vector (userInput.h/cpp)
		int startingNum{ getStartingNum() };
		int numIncrease{ getNumIncrease() };


		//Generates a random 2 or 4 multiplier (generator.h/cpp)
		int multiplier{ getMultiplier() };

		//Vector inilized with 0's and size set but getNumIncrease function. (generator.h/cpp)
		std::vector<int> numberList{ getNumberList(startingNum, numIncrease, multiplier) };

		//For quick testing. Delete later.
		for (int i : numberList)
		{
			std::cout << i << '\n';
		}

		std::cout << "I generated " << numIncrease << " sqaure numbers."
			<< " Do you know what each number is after multiplying it by "
			<< multiplier << "?\n";

		do
		{
			int guess{ getGuess() };

			auto found{ std::find(numberList.begin(), numberList.end(), guess) };

			//If guess is incorrect, end the game.
			if (found == numberList.end())
			{
				/*Lambda that returns the element closest to the guess.Uses min_element to find the smallest number
				after using std::abs to find the difference between the user's guess and each element.*/
				const auto close{
					std::min_element(numberList.begin(), numberList.end(), [guess](const auto& a, const auto& b) {
						return std::abs(a - guess) < std::abs(b - guess);
					})
				};


				//If the "close" is equal to 4 or less, provide the element that is closest to the guess. 
				if (std::abs(*close - guess) <= 4)
				{
					std::cout << "Oh so close! It was " << *close << ". Nice Try!\n";
				}
				else
				{
					std::cout << guess << " is incorrect.\n";
				}

				break;
			}

			/*If guess is correct, the game will loop, removed the correctly guessed element and tell the
			user how many numbers are left to guess.*/
			else
			{
				std::cout << guess << " is correct! Good Job!\n";

				//Remove Correct answer from the list.
				numberList.erase(found);

				std::cout << "You have " << numberList.size() << " numbers left! \n\n";
			}
		} while (numberList.size() > 0);


		if (numberList.size() == 0)
		{
			std::cout << "Nice job! You guessed all of the numbers.\n\n";
		}
		else
		{
			std::cout << "Game Over!\n\n I am sorry, but you had " << numberList.size()
				<< " numbers left to guess. Better luck next time.\n\n";
		}

		std::cout << "Would you like to play again? (Y/N): ";

		//Gets bool from userInput.h/cpp by asking the user to type 'Y' or 'N'
		bool playAgain{ getPlayAgain() };

		// If 'yes'(returned bool as true) the game will loop.
		if (playAgain)
		{
			std::cout << "\n\n\n\n\n\nAwesome. Let's play agian!\n\n";
		}
		//If 'no'(returned bool as false) the game loop will break and the program will terminate.
		else
		{
			std::cout << "\n Well... Thanks for playing, see you next time. \n\n";
			break;
		}
		
	}

	return 0;
}