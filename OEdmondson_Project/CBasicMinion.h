#pragma once

#include "Definitions.h"  // Type definitions
#include "CCard.h"
#include "CPlayer.h"

//The basic card model. It won't do much but it comes with a single-target attack function that can be used on any card without a specific attack-style.
class CBasicMinion : public CBaseCard
{
public:
	CBasicMinion(std::string name, int attack, int health) { mCardName = name; mCardAttack = attack; mCardHealth = health; };


	//Generic basic attack mentioned above the class. Held within the related .cpp file.
	virtual bool UseCard(CUser& ally, CUser& enemy);

	//Typically cards should be placed within active but if they're a tank or a spell they would be placed somewhere else.
	virtual ECardStates getIsPlaced() { return active; };




	//This is a search function that will return the value found within a switch. If it isn't found then it returns nothing.
	virtual int getStat(EStatID statSearch);

	//As we haven't been asked to modify anything outside of the: Health/Attack/Defence This should only be able to find them. By using the statID enum I don't have to link them to the actual stat with other classes.
	void increaseStat(EStatID statSearch, int valIncrease); 

protected:
	//Stats required to be placed on the board.
	int mCardHealth = 0;//
	int mProtection = 0;
};
