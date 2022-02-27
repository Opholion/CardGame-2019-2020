#pragma once

#include "CBasicMinion.h"
class CVampire : public CBasicMinion
{
public:
	CVampire(std::string name, int attack, int health, int xtra) : CBasicMinion(name, attack, health) 
	{ mCardName = name; mCardAttack = attack; mCardHealth = health; mLifeSteal = xtra;};
	
	bool UseCard(CUser& ally, CUser& enemy);

	int getStat(EStatID statSearch);

private:
	int mLifeSteal;
};
