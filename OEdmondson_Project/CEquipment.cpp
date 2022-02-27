#include "CEquipment.h"


const std::string BUFF_TYPE_OUTPUT[2]{" attack", " defence"}; //Every equipment type buff. The order is linked the the statID enum as this is the only location where their actual value matter.

const std::string EQUIP_CONSOLE_OUTPUT[] = {"Player has healed 2 damage. Current HP:", " has given ", ". Current ", " "};


bool CEquipment::UseCard(CUser& ally, CUser& enemy)
{
	std::cout << std::endl;
	//Attack should be 0, defence should be 1. Future stats can be added below this in the StatID enum.


	//This changes the randomValue depending on the current active size. If there are mutiple taunts and/or active minions then increase the size.
	int searchRange = 0;
	bool isEmpty = true;
	if (ally.pDeck[highPriority].size() > 0)
	{
		isEmpty = false;
		searchRange += (int)ally.pDeck[highPriority].size() - 1;
	}
	if (ally.pDeck[active].size() > 0)
	{
		isEmpty = false;
		searchRange += (int)ally.pDeck[active].size() - 1;
	}
	if (isEmpty) //If both lists are empty then heal the player.
	{
		ally.playerDamage(-2);
		std::cout << EQUIP_CONSOLE_OUTPUT[0] << ally.lifePoints();
	}
	else
	{
		ECardStates targetDeck;
		int arrMod;
		ally.setTarget((float)searchRange);

		if (ally.getTarget() > ally.pDeck[active].size())
		{
			targetDeck = highPriority;
			arrMod = ally.getTarget() - (int)ally.pDeck[active].size();
		}
		else
		{
			targetDeck = active;
			arrMod = ally.getTarget();
		}
		ally.pDeck[targetDeck][arrMod]->increaseStat(mBuffType, mCardAttack);
		std::cout << this->cardName() << EQUIP_CONSOLE_OUTPUT[1] << ally.pDeck[targetDeck][arrMod]->cardName() << EQUIP_CONSOLE_OUTPUT[3] <<this->getStat(attack) << BUFF_TYPE_OUTPUT[(int)mBuffType] << EQUIP_CONSOLE_OUTPUT[2] << ally.pDeck[targetDeck][arrMod]->getStat(mBuffType);
	}
	/*
			std::cout << "Unit " << ally.pDeck[active][ally.getTarget()]->cardName() << " has gained 2 atk. Current atk:" << ally.pDeck[active][ally.getTarget()]->getStat(buffType);*/

	return true;
};