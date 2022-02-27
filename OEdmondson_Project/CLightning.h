#pragma once

#include "CBasicSpell.h"

const std::string CMD_LightningOutput[] = { "\nThe "," card deals, " ,", to every enemy card." };

class CLightning : public CBasicSpell
{
public:
	CLightning(std::string name, int attack) { mCardName = name; mCardAttack = attack; };


	//This function will cycle through each possible enemy unit, including the player, and deal the current attack damage to their hp.
	bool UseCard(CUser& ally, CUser& enemy);

	ECardStates getIsPlaced() { return inactive; }

};
