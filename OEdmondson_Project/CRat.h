#pragma once

#include "CBasicMinion.h"
class CRat : public CBasicMinion
{
public:
	CRat(std::string name, int attack, int health, int xtra) : CBasicMinion(name, attack, health)
	{
		mHordeAtk = xtra;
	};

	bool UseCard(CUser& ally, CUser& enemy);

	//As the rat has a unique stat I have to create a new factory function for returning the stat. 
	int getValue(EStatID statSearch);
private:
	int mHordeAtk;
};
