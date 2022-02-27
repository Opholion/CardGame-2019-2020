#pragma once
#include "Definitions.h"
#include "CCard.h"
#include "CPlayer.h"
#include <deque>




const std::string managerTableOutput[] = {"Cards on table: " , "\n", "'s ", " has been killed.", ", plays: ", " draws a '","' card. \n" };
const std::string playerName[2] = {"Sorceresss", "Wizard"};
class CCardsInPlay
{
public:
	//This will output the specified players table.
	void showTable(int currentPlayer);

	//This will check for killed units within the specified players deck.
	void findDead(ECardStates deck, int enemyPlayer);
	//This will check if the game has ended.
	int isGameActive();

	//This allows targets to be chosen outside of this class.
	int getRandom(float n, int currentPlayer); //Sets the current players target and returns it.

	//This will go through each unit on the table and activate their abilities.
	void activateTable(int currentPlayers);

	//This will move teh decks from the filereader to this game manager class.
	void setPlayers(playerDecks pP1, playerDecks pP2);

	//Draws a card for the specified player. Used extermally but could be used as a card ability.
	bool drawCard(int currentPlayer);

	//Activates the chosen player; Making them play a card in their hand and activate their table.
	bool playerTurn(int currentPlayer ,int cardID);

	//Sets the seed of the chosen player.
	bool setSeed(int currentPlayer, int seed);

	//Plays a specific card for the player. Typically used internally.
	void playCard(int currentPlayer, int secondPlayer, int cardID);

	//Randomizes the deck.
	void randDeck(int currPlayer);
	
	//Returns the size of the specified deck.
	int getDeckSize(ECardStates storage, int playerID) { return (int)mCPlayers[playerID].pDeck[storage].size();  };

private:
	// Moves the chosen card to the back of the deck and deletes it.
	void DeleteCard(int player, ECardStates location, int cardID);

	CUser mCPlayers[2];
};



