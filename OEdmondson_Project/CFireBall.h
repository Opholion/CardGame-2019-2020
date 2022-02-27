#pragma once

#include "CBasicSpell.h"


class CFireBall : public CBasicSpell
{
public:
	CFireBall(std::string name, int attack) { mCardName = name; mCardAttack = attack; };

	//Short enough to justify being held in header.
	//Uses the automatic single-target function set in the basic card.
	bool UseCard(CUser& ally, CUser& enemy)
	{
		return basicAttack(ally, enemy, mCardAttack);
	};

	//This should be deleted.
	ECardStates getIsPlaced() { return inactive; }

};
