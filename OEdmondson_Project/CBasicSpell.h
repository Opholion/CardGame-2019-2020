#pragma once

#include "Definitions.h"
#include "CCard.h"
#include "CPlayer.h"

class CBasicSpell : public CBaseCard
{
public:
	

	virtual bool UseCard(CUser& ally, CUser& enemy) = 0;

	ECardStates getIsPlaced() { return inactive; }

	
	//I've used this to make the function work with the CBasicMinion hierarchy without adding extra variables to the spell classes.
	int getStat(EStatID statSearch)
	{
		//As the spell class only has one stat it shouldn't be able to return anything else.
		if (statSearch == attack)
		{
			return mCardAttack;
		}
		//This shouldn't happen. If it does then a spell is in the incorrect location.
		return -1;
	}

};
