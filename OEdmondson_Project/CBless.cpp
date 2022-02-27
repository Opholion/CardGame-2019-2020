#include "CBless.h"

bool CBless::UseCard(CUser& ally, CUser& enemy)
{
	//As we're including both players, I haven't removed the excess number at the end but I will be removing a value of 2 whenever interacting with a deck.
	ally.findTarget((float)ally.pDeck[active].size() + (float)enemy.pDeck[active].size() + (float)ally.pDeck[highPriority].size() - 1 + (float)enemy.pDeck[highPriority].size() - 1); //Will need to find a new target for unique card type.
	//High priority vectors are part of the active so they lose 1 size as the player is already being targetted.

	//The below code will grab each array size and increase it through the given priority-queue to find the randomized location.

	//Ally tank-deck

	//These are for debugging purpoes. Pretend they aren't here.
	int target = ally.getTarget();
	int randTarget = (int)ally.pDeck[highPriority].size() - 1;

	if (ally.getTarget() < randTarget)
	{
		ally.pDeck[highPriority][randTarget - (ally.getTarget() + 1)]->increaseStat(health, -mCardAttack);
		std::cout << CMD_BLESS_OUTPUT[2] << ally.pDeck[highPriority][ally.getTarget()]->cardName() << CMD_BLESS_OUTPUT[0] << mCardAttack << CMD_BLESS_OUTPUT[1] << ally.pDeck[highPriority][ally.getTarget()]->getStat(health);


		if (ally.pDeck[highPriority][randTarget - (ally.getTarget() + 1)]->getStat(health) < 0)
		{
			return true;
		}
	}

	//Ally base-deck.
	randTarget += (int)ally.pDeck[active].size();
	if (ally.getTarget() < randTarget)
	{
		ally.pDeck[active][randTarget - (ally.getTarget() + 1)]->increaseStat(health, -mCardAttack);
		std::cout << CMD_BLESS_OUTPUT[2] << ally.pDeck[active][randTarget - (ally.getTarget() + 1)]->cardName() << CMD_BLESS_OUTPUT[0] << mCardAttack << CMD_BLESS_OUTPUT[1] << ally.pDeck[active][randTarget - (ally.getTarget() + 1)]->getStat(health);

		if (ally.pDeck[active][randTarget - (ally.getTarget() + 1)]->getStat(health) < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//Ally player.
	if (ally.getTarget() == randTarget)
	{
		ally.playerDamage(-mCardAttack);
		std::cout << CMD_BLESS_OUTPUT[3] << mCardAttack << CMD_BLESS_OUTPUT[4] << ally.lifePoints();
		if (ally.lifePoints() < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//Enemy tank-deck
	randTarget += (int)enemy.pDeck[highPriority].size() - 1;
	if (ally.getTarget() < randTarget)
	{
		enemy.pDeck[highPriority][randTarget - (ally.getTarget() + 1)]->increaseStat(health, mCardAttack);
		std::cout << CMD_BLESS_OUTPUT[5] << ally.pDeck[highPriority][randTarget - (ally.getTarget() + 1)]->cardName() << CMD_BLESS_OUTPUT[6] << mCardAttack << CMD_BLESS_OUTPUT[4] << ally.pDeck[highPriority][randTarget - (ally.getTarget() + 1)]->getStat(health);

		if (enemy.pDeck[highPriority][randTarget - (ally.getTarget() + 1)]->getStat(health) < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//Enemy base-deck
	randTarget += (int)enemy.pDeck[active].size();
	if (ally.getTarget() < randTarget)
	{
		enemy.pDeck[active][randTarget - (ally.getTarget() + 1)]->increaseStat(health, mCardAttack);
		std::cout << CMD_BLESS_OUTPUT[5] << enemy.pDeck[active][randTarget - (ally.getTarget() + 1)]->cardName() << CMD_BLESS_OUTPUT[5] << mCardAttack << CMD_BLESS_OUTPUT[4] << enemy.pDeck[active][randTarget - (ally.getTarget() + 1)]->getStat(health);

		if (enemy.pDeck[active][randTarget - (ally.getTarget() + 1)]->getStat(health) < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//Enemy player.
	if (ally.getTarget() >= randTarget)
	{
		enemy.playerDamage(mCardAttack);
		std::cout << CMD_BLESS_OUTPUT[7] << mCardAttack << CMD_BLESS_OUTPUT[4] << enemy.lifePoints();
		if (ally.lifePoints() < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
};