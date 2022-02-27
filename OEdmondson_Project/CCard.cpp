#include "Definitions.h"
#include "CCard.h"
#include "CPlayer.h"


const std::string CMD_BasicAttack[] = { " attacks " , ". ", " health now: " };

int CBaseCard::basicAttack(CUser& ally, CUser& enemy, int damage)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ECardStates target = active;
	//If there is a 'taunt' unit active then change to that target. 
	if (enemy.pDeck[highPriority].size() > 0)
	{
		target = highPriority;
		ally.findTarget(enemy.pDeck[highPriority].size() - 1.0f);
	}
	//This is large but due to it being an unlikely scenario it should be more efficient.
	else if(ally.getTarget() >= 0) //If it's below 0 then the player is being targetted and this can be skipped.
	{
		if (enemy.pDeck[target].size() == 0)
		{
			target = playerTarget;
		}
		else
		{
			//If highpriority is passed in then this should work too.
			//If the current searched list is full of dead cards then go to the next one until you reach the player.

			while (enemy.pDeck[target][ally.getTarget()]->getStat(health) <= 0 && target != playerTarget)
			{
				bool ifNotEmpty = false;
				for (int i = 0; i < enemy.pDeck[target].size(); ++i)
				{
					if (enemy.pDeck[target][i]->getStat(health) > 0)
					{
						ifNotEmpty = true;
						ally.setTarget((float)i);
						i = (int)enemy.pDeck[target].size();//End it early. Source: SuicideJokesForDummies
					}
				}

				if (!ifNotEmpty)
				{
					//
					if (target == highPriority)
					{
						target = active;
						ally.findTarget((float)enemy.pDeck[target].size());
					}
					else
					{
						target = playerTarget;
						break;
					}

				}



			}
		}
	}
	//Implemented to avoid issues with trample and as a general bug-fix. Avoid the already dead enemies, they'll delete themselves when this is returned.

	//If the target isn't the player then do the below.

	//If there are no cards then attack the player.
	if (enemy.pDeck[target].size() <= ally.getTarget() || target == playerTarget)
	{
		if (enemy.lifePoints() > 0)
		{
			enemy.playerDamage(damage);
			std::cout << mCardName << CMD_BasicAttack [0] << enemy.getName() << CMD_BasicAttack[1] << enemy.getName() << CMD_BasicAttack[2] << enemy.lifePoints() << CMD_BasicAttack[1];
		} //Stop trample loops and end the attacks faster.
		
		if (enemy.lifePoints() <= 0)
		{
			return 0; //Makes the output cleaner.
		}
		return enemy.lifePoints();
	}
	else
	{
		enemy.pDeck[target][ally.getTarget()]->increaseStat(health, damage);
		std::cout << mCardName << CMD_BasicAttack[0] << enemy.pDeck[target][ally.getTarget()]->cardName() << CMD_BasicAttack[1] << enemy.pDeck[target][ally.getTarget()]->cardName() << CMD_BasicAttack[2] << enemy.pDeck[target][ally.getTarget()]->getStat(health) << CMD_BasicAttack[1];
	}

	//Return the leftover health for further use.
	

	return enemy.pDeck[target][ally.getTarget()]->getStat(health);
}




