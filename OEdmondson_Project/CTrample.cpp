#include "CTrample.h"

bool CTrample::UseCard(CUser& ally, CUser& enemy)
{
	//If the target is killed then return true. It requires damage as some cards have unique effects, such as the rat, trample or any heal but is limited to attacking the enemy.
	int excessDmg = basicAttack(ally, enemy, mCardAttack);

	//If the unit is killed and its health is in the negatives then deal damage to another minion with the amount of hp in the negatives.
	if (excessDmg > 0)
	{
		return false;
	}
	else
	{
		while (excessDmg < 0)
		{
			ally.findTarget(enemy.pDeck[active].size() - 1.0f);
			excessDmg = basicAttack(ally, enemy, -excessDmg);
		}
	}
	return true;
};