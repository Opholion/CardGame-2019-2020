#include "CLightning.h"

bool CLightning::UseCard(CUser& ally, CUser& enemy)
{
	for (auto it = enemy.pDeck[highPriority].begin(); it != enemy.pDeck[highPriority].end(); ++it)
	{
		it->get()->increaseStat(health, mCardAttack);
	}
	for (auto it = enemy.pDeck[active].begin(); it != enemy.pDeck[active].end(); ++it)
	{
		it->get()->increaseStat(health, mCardAttack);
	}
	enemy.playerDamage(mCardAttack);

	std::cout << CMD_LightningOutput[0] << mCardName << CMD_LightningOutput[1] << mCardAttack << CMD_LightningOutput[2];

	//This should return truth as I've delegated all card management to the CCardsInPlay class, which is my current manager, to avoid filling the deck with null values.
	return true;
};