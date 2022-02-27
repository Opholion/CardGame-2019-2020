#include "CVampire.h"

bool CVampire::UseCard(CUser& ally, CUser& enemy)
{
	mCardHealth = mCardHealth + mLifeSteal;
	//If the target is killed then return true. It requires damage as some cards have unique effects, such as the rat, trample or any heal but is limited to attacking the enemy.
	return basicAttack(ally, enemy, mCardAttack) <= 0;
};

int CVampire::getStat(EStatID statSearch)
{
	if (statSearch == health)
	{
		return mCardHealth;
	}
	if (statSearch == attack)
	{
		return mCardAttack;
	}
	if (statSearch == defence)
	{
		return mProtection;
	}
	if (statSearch == extra)
	{
		return mLifeSteal;
	}

	//This shouldn't happen. If it does then the code is wrong.
	return -1;
};