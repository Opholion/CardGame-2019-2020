#pragma once

#include "CBasicSpell.h"



class CEquipment : public CBasicSpell
{
public:
	CEquipment(std::string name, int attack, EStatID statType) { mCardName = name; mCardAttack = attack; mBuffType = statType; };

	//Requires custom design, as it's not required for further inheritance.
	bool UseCard(CUser& ally, CUser& enemy);

	ECardStates getIsPlaced() { return inactive; }
private:
	EStatID mBuffType;
};
