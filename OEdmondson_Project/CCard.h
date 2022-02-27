
//Represents a basic card setup.
#pragma once

#include "Definitions.h"
#include <iostream>
#define Flag(_CRTDBG_MAP_ALLOC)
enum EStatID
{
	attack = 0,
	defence = 1,
	extra = 2,
	health = 3
};


class CUser;
class CBaseCard
{
public:
	virtual ~CBaseCard() {}


	void buffDamage(int modifier) { mCardAttack += modifier; }; //Change attack;
	//virtual void UseCard(CCard& Enemy, void(CCard::*attack)(std::string,int,int,int)) = 0; //if true; Place on the field. Otherwise, just delete it.

	//Which array it will be placed in. Reference the CPlayer.h states enum for more details.
	

	int basicAttack(CUser& ally, CUser& enemy, int damage); //A single target attack that returns excess damage and allows a custom damage input. This is to accomodate the more advanced cards.
	
	std::string cardName() { return mCardName; }; //This is universal. No need to change it to a getStat value. That and it would mean getStat would return a string and for everything but this; it'd have to be converted to an int.

	virtual ECardStates getIsPlaced() { return active; }; //Returns inactive if you delete it. Otherwise place it in the specified location. This is done to allow potential future development of a graveyard.
	virtual bool UseCard(CUser& ally, CUser& enemy) = 0; //Generic attack is stored in CCard.cpp


	virtual void increaseStat(EStatID statSearch, int valIncrease) {/*Spells don't need this but that could be changed *wiggles eyesbrows */};
	//Give the user the ability to call unique stats without creating unnecessary functions.
	virtual int getStat(EStatID statSearch) = 0; //getStat(attack)
	//SUser* myParent;
	
protected:

	std::string mCardName;
	int mCardAttack = 0;
};
