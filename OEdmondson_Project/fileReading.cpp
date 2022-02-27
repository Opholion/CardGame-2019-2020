// ReadingGamecpp : This file contains the 'main' function. Program execution begins and ends there.
// OEDMONDSON

//#include "pch.h"
//#include "stdafx.h"

#include "fileReading.h"
#include "CCardFactory.h"

//These variables will be later deleted so they shall be placed here rather than the header class.
//Constants

const std::string fileNameAddition[2] = {".txt", "seed.txt"};
const std::string textOutputs[] = { "The file has failed to open...", "Please enter the file name...", "The file has been found. \n" };

enum StrOutputs
{
	Outputerror = 0,
	EnterName = 1,
	FoundFile = 2,
};

const std::string baseDecks[PLAYER_COUNT]
{
	"sorceress",
	"wizard",
};


//Name is self explanatory. 
int CFileMap::getSeed()
{
	std::ifstream infile;
	infile.clear();
	infile.open(fileNameAddition[1]);
	if (!infile)
	{
		throw textOutputs[0];
		return -1; //It's broken. 
	}
	else
	{
		std::string seedTxt;
		seedTxt = "";
		std::getline(infile, seedTxt); //Seed should only be 1 line.
		return std::stoi(seedTxt);	
	}
}

std::vector<std::unique_ptr<CBaseCard>> CFileMap::initiate()
{
	std::vector<std::unique_ptr<CBaseCard>> userDecks;

	//Loops through each players deck name. It should be possible to use any deck multiple times.
	std::ifstream infile;
	do
	{

		setFileName();
		infile.clear();
		infile.open(fileName + fileNameAddition[0]);
		if (!infile) //Error check
		{
			//Informing the user before looping again. 
			std::cout << textOutputs[Outputerror];
			system("PAUSE"); //Stop it ending automatically.
		}

	} while (!infile);

	std::cout << textOutputs[FoundFile];
	userDecks = ReadFileMap(infile); //Sends in the current file with the deck it's meant to be listed under.

	return userDecks;
}


//This will grab the user input for the file name.
void CFileMap::setFileName()
{
	fileName = baseDecks[currPlayer];
	++currPlayer;
	return;
}


std::vector<std::unique_ptr<CBaseCard>> CFileMap::ReadFileMap(std::ifstream& infile)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::vector<std::unique_ptr<CBaseCard>> finalDeck;
	std::unique_ptr<CBaseCard> currCard;
	std::string cardText;
	do  //Grab the first two values, seperately.
	{

		//This, after confirming that it's a file, will grab the first 'type'	
		if (!infile.eof())
		{
			std::vector<std::string> tempHold;

			cardText = "";
			std::getline(infile, cardText);

			int j = 0; //Allows to set a custom start point for reading character by character.
			for (int i = 0; i < cardText.size(); ++i)
			{
				if (cardText[i] == ' ' || i + 1 >= cardText.size())
				{
					if (i + 1 >= cardText.size())
					{
						++i;
					}

					tempHold.push_back("");
					for (int k = j; k < i; ++k)
					{
						//Avoid passing spaces.
						if (cardText[k] != ' ')
						tempHold.back() += cardText[k];
					}
					j = i;
				}
			}

			//Avoid errors and pass through empty values.
			while (tempHold.size() < 5)
			{
				tempHold.push_back("0");
			}


			//Factory template for finding the appropriate card class.
			currCard = NewSearch(EUnitTypes(std::stoi(tempHold[0])), tempHold[1], std::stoi(tempHold[2]), std::stoi(tempHold[3]), std::stoi(tempHold[4]));

			//Moves the deck into the main initiate function to be returned.
			finalDeck.push_back(move(currCard));

			tempHold.clear();
		}


	} while (!infile.eof());

	//General memory check.
	_CrtCheckMemory();
	return finalDeck;
}
