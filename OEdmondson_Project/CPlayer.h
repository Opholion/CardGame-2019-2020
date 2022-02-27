#pragma once

#include "Definitions.h"

class CBaseCard;
const int MAX_HEALTH = 30;

typedef std::vector<std::unique_ptr<CBaseCard>> playerDecks;
//Names of each array fir the decks.

const std::string PLAYER_NAMES[2] = {"Sorceress", "Wizard" };

//Such as smol class. Pointless really; Should be a struct. *Hint hint.
class CUser
{
	//This class has little to no internal functions. It is used to hold values and seperate the players more obviously.
public:
	playerDecks pDeck[4]; //Look at states enum for more detail.
	int lifePoints() { return mHealth; };
	void playerDamage(int damage) { mHealth -= damage; };

	//Stores the current target for ease of use without passing.
	void findTarget(const float n);
	void setTarget(float n); //Emergency set command. Ask about seeding.
	int getTarget() { return mTarget; };

	void setName(int ID) { if (ID < PLAYER_NAMES->size()) { mName = PLAYER_NAMES[ID]; } }
	std::string getName() { return mName; };
private:
	std::string mName = "";
	int mHealth = MAX_HEALTH;
	int mTarget = 0;
};

