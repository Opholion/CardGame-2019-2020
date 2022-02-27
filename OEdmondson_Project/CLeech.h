#pragma once

#include "CBasicMinion.h"
class CLeech : public CBasicMinion
{
public:
	CLeech(std::string name, int attack, int health, int xtra) : CBasicMinion(name, attack, health)
	{
		mLifeSteal = xtra;
	};
	bool UseCard(CUser& ally, CUser& enemy);

	int getStat(EStatID statSearch);

private:
	int mLifeSteal;
};
