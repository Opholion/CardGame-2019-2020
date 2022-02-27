// SearchNoStar.cpp
// ======^^^^^^====
//
// Implementation of Search class for NoStar algorithm
//

//  NOTE - There is no such thing as the NoStar search algorithm
//         I have implemented it as a pattern for you to follow

#include "CBasicMinion.h" // Declaration of this class

//use the card. Wow. Weird. Almost like the name is the comment. This can have mulitple features so it's a virtual
bool CBasicMinion::UseCard(CUser& ally, CUser& enemy)
{
	//If the target is killed then return true. It requires damage as some cards have unique effects, such as the rat, trample or any heal but is limited to attacking the enemy.
	return basicAttack(ally, enemy, mCardAttack) <= 0;
};


//Name is self-explanatory. Use the statID to find the required stat. Adjust it.
void CBasicMinion::increaseStat(EStatID statSearch, int valIncrease) //increaseStat(health, )
{
	if (statSearch == health)
	{
		//If the target is alive.
		if (mCardHealth > 0)
		{
			//If the value is greater than 0 then it's damage. If so, reduce the amount of damage by your armour.
			if (valIncrease < 0)
			{
				//Heal them by that amount.
				mCardHealth -= valIncrease;
			}
			else if (valIncrease - mProtection > 0)
			{
				//If the damage minus the armour is greater than 0 then take the excess damage.
				mCardHealth -= valIncrease - mProtection;
			}
		}
	}
	else
		if (statSearch == attack)
		{
			mCardAttack += valIncrease;
		}
		else
			if (statSearch == defence)
			{
				mProtection += valIncrease;
			}
}


//Name is pretty self-explanatory. Get the card stat. Uses ID in order to allow spells to access search
int CBasicMinion::getStat(EStatID statSearch)
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

	//This shouldn't happen. If it does then the code is wrong.
	return -1;
};
