#pragma once

#include "CBasicMinion.h"
#include <iostream>
class CTrample : public CBasicMinion
{
public:
	//Really, this is only its own class as it's easier to read and we aren't required to add minion buffs for tankiness so that would be an underused feature if it was added.
	CTrample(std::string name, int attack, int health) : CBasicMinion(name, attack, health)
	{
		mCardName = name; mCardAttack = attack; mCardHealth = health;
	};

	bool UseCard(CUser& ally, CUser& enemy);

	//This is the main different between this and the CBasicMinionClass. (The only difference, oh and that comment at the top.)
};
