#include "CRat.h"

bool CRat::UseCard(CUser& ally, CUser& enemy)
{
	//Stores the original attack so the increment doesn't increase the attack perm.
	int baseAttack = mCardAttack - mHordeAtk; //Remove one rat so it doesn't include itself.

	for (auto it = ally.pDeck[active].begin(); it != ally.pDeck[active].end(); ++it)
	{
		if (it->get()->cardName() == mCardName) //Allows more horde minions to be added to the deck whilst keeping them seperate.
		{
			//Creates a reference to the attack that I can easily manipulate and remove when done.
			baseAttack = baseAttack + mHordeAtk;
		}
	}

	//If the target is killed then return true. It requires damage as some cards have unique effects, such as the rat, trample or any heal but is limited to attacking the enemy.
	return basicAttack(ally, enemy, baseAttack) <= 0;
};

int CRat::getValue(EStatID statSearch)
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
		return mHordeAtk;
	}

	//This shouldn't happen. If it does then the code is wrong.
	return -1;
};