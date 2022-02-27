#pragma once

#include "CBasicSpell.h"

const std::string CMD_BLESS_OUTPUT[] = { " card is healed "," health. Current: ","\nYour ","\nYou have gained "," health points. Current: ", "\nEnemy's "," card has been damaged ", "Enemy has lost " };

class CBless : public CBasicSpell
{
public:
	CBless(std::string name, int attack) { mCardName = name; mCardAttack = attack; };

	bool UseCard(CUser& ally, CUser& enemy);

	ECardStates getIsPlaced() { return inactive; }

};