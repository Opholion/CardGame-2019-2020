//OEDMONDSON
#ifndef _FILE_READING_
#define _FILE_READING_
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Definitions.h"
#include "CCard.h"


typedef std::vector<std::unique_ptr<CBaseCard>> fileStorage;
const int PLAYER_COUNT = 2;


class CFileMap {
public:	
	//Returns a deck to fill the player class.
	fileStorage initiate();


	//Returns the file name for initiating the game.
	std::string getDeckName() { return fileName; };

	//Returns the seed file value.
	int getSeed();

private:

	//Stores the current file name for external access.
	std::string fileName;
	//Sets the file name for the initiate function.
	void setFileName();
	//Goes through each file and inserts it into a 3 dimensional vector.
	fileStorage ReadFileMap(std::ifstream& infile);
	//Done for figuring out which is the Sorceress.
	int currPlayer = 0;
};

#endif