

//Definitions are used to share Enums/IfDefs/Using/ect with every file. Can break things so you typically shouldn't include things; which is why the deck ifDef is part of the player.
#pragma once

//Testing for memory leaks.
#define Flag(_CRTDBG_MAP_ALLOC)
#define Flag(_CRTDBG_ALLOC_MEM_DF)
#define Flag(_CRTDBG_LEAK_CHECK_DF)

#include <stdlib.h>
#include <crtdbg.h>

#include <vector>
#include <deque>
#include <memory>
#include <iostream>
#include <string>


//0+ is for deck storage areas. -1 is for attacking the player;
enum ECardStates
{
	playerTarget = -1, //Target the player.
	active = 0, //Cards in play
	inactive = 1, //Cards in deck
	inHand = 2, //Cards in hand.
	highPriority = 3, //High priority targets.
	
};

// Each unit type'
enum EUnitTypes
{
	BasicMinion = 1,
	FireBall = 2,
	Lightning = 3,
	Blessing = 4,
	Vampire = 5,
	Wall = 6,
	Horde = 7,
	Trample = 8,
	Leech = 9,
	Sword = 10,
	Armour = 11,
};
