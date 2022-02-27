#pragma once

#include "CBasicMinion.h"
class CWall : public CBasicMinion
{
public:
	//Really, this is only its own class as it's easier to read and we aren't required to add minion buffs for tankiness so that would be an underused feature if it was added.
	CWall(std::string name, int attack, int health) : CBasicMinion(name, attack, health) {};

	//This is the main different between this and the CBasicMinionClass. (The only difference, oh and that comment at the top.)
	ECardStates getIsPlaced() { return highPriority; };
};
