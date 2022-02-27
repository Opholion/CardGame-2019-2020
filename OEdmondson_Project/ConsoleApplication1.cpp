// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define Flag(_CRTDBG_MAP_ALLOC)
#define Flag(_CRTDBG_ALLOC_MEM_DF)
#define Flag(_CRTDBG_LEAK_CHECK_DF)
#include <stdlib.h>
#include <crtdbg.h>


#include <iostream>
#include "Definitions.h"
#include "fileReading.h"
#include "CCardsInPlay.h"

using namespace std;

//These will show up as memory leaks but they should be constructed as the program ends.
const std::string CMD_MainOutput[] = { "There has been a critical error. The game will now be closed."  , "\nYou win!", "sorceress", "Round: ", "\nWould you like to shuffle the deck? Y/N?\n" };


int main()
{
	//It wasn't specified that we needed to provide proof of having no memory leaks but these are placed around the code in order to showcase that it is the case.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	//It should create two instances of the below class. After transferring the stored deck to the player or enemy  class it should be deleted.
	CFileMap deckFinder; 
	CCardsInPlay currentField;
	std::vector<std::unique_ptr<CBaseCard>> temp[2];// 2 players.

	//This should ask for a file name and then return a deck created with that file.
	temp[0] = move(deckFinder.initiate());
	temp[1] = move(deckFinder.initiate());
	

	//Attempts to find the seed. If it fails then end the game.
	if (!currentField.setSeed(0, deckFinder.getSeed()) && !currentField.setSeed(1, deckFinder.getSeed()))
	{
		cout << CMD_MainOutput[0];

		system("PAUSE");
		return 0;
	}
	
	

	//If player 2 is not sorceress then player 1 must be. ((Sorceress always goes first)
	if (deckFinder.getDeckName() == CMD_MainOutput[2]) //Top of FileReading for array; Move to definitions and link this to that.
	{
		currentField.setPlayers(move(temp[1]), move(temp[0]));
	}
	else
	{
		currentField.setPlayers(move(temp[0]), move(temp[1]));
	}


	//Gets the user input for randomization, as was specified.
	cout << CMD_MainOutput[4];
	string userInput;
	cin >> userInput;
	if (userInput == "y")
	{
		currentField.randDeck(0);
		currentField.randDeck(1);
	}
	//delete(temp);

	std::cout << std::endl;

	//The name should be pretty clear on what it does.
	currentField.drawCard(0); //Players start with extra cards.
	currentField.drawCard(1); //Players start with extra cards.

	std::cout << std::endl;
	


	//While there isn't a set winner (-1 can't be a player ID) loop.
	int rounds = 0;
	std::cout << std::endl;
	while(currentField.isGameActive() == -1)
	{
		++rounds;
		std::cout << CMD_MainOutput[3] << rounds << std::endl;
		for (int currentPlayer = 0; currentPlayer < 2 && currentField.isGameActive() == -1; ++currentPlayer)
		{
			int secondPlayer = currentPlayer + 1;
			if (secondPlayer >= 2)
			{
				secondPlayer = 0;
			}

			//If there isn't anything to target then target the player.
			if (currentField.getDeckSize(active,secondPlayer) > 0)
			{
				currentField.getRandom((float)currentField.getDeckSize(active, secondPlayer) - 1.0f, currentPlayer);
			}
			else
			{
				currentField.getRandom((float)currentField.getDeckSize(active, secondPlayer), currentPlayer);
			}

			if (currentField.drawCard(currentPlayer)) //Always have 2 cards before using them.
			{

				//Make a getSize function for each vector.
				//While loop is here for testing; It would cause a bug otherwise.
				while (!currentField.playerTurn(currentPlayer, currentField.getRandom(currentField.getDeckSize(inHand, currentPlayer) - 1.0f, secondPlayer))); //Use random cards until it works, if there is an error.
				currentField.showTable(currentPlayer);
				currentField.activateTable(currentPlayer); //Make each minion attack the other.
			}

		}
		
	}

	std::cout << CMD_MainOutput[1];
	_CrtCheckMemory();

	system("PAUSE");
	return 0;
}
