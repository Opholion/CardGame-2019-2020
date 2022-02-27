// CCardFactory.cpp
// =================
//
// Factory function implementation to create CSearchXXX objects 
//

/* TODO - include each implemented search class here */


#include "CCardFactory.h" // Factory declarations

// Create new search object of the given type and return a pointer to it.
// Note the returned pointer type is the base class. This is how we implement polymorphism.
std::unique_ptr<CBaseCard> NewSearch(EUnitTypes search, std::string name, int atk, int hlth, int ect)
{
	//Error checking.
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//These classes have 2 levels of inheritance. They grab the CBaseCard at the first layer, grab a minion or spell type class after that and then they will always grab another layer for the spell class but will only 
	//add layers to the CBasicMinion class if it isn't type-1 as they have unique requirements. The Wall, for example, despite having a similar attack will need to be placed in the highpriority deck to act as a tank.

	switch (search)
	{
	case BasicMinion:
	{
		//std::unique_ptr<CBasicMinion> = std::move(CBasicMinion());
		return move(std::unique_ptr<CBaseCard>(new CBasicMinion(name, atk, hlth)));
		break;
	}
	case FireBall:
	{
		//std::unique_ptr<CBasicMinion> = std::move(CBasicSpell());
		return move(std::unique_ptr<CBaseCard>(new CFireBall(name, atk)));//new CBasicMinion()
		break;
	}
	case Lightning:
	{
		//std::unique_ptr<CBasicMinion> = std::move(CBasicSpell());
		return move(std::unique_ptr<CBaseCard>(new CLightning(name, atk)));//new CBasicMinion()
		break;
	}
	case Blessing:
	{
		//std::unique_ptr<CBasicMinion> = std::move(CBasicSpell());
		return move(std::unique_ptr<CBaseCard>(new CBless(name, atk)));//new CBasicMinion()
		break;
	}
	case Vampire:
	{
		//std::unique_ptr<CBasicMinion> = std::move(CBasicMinion());
		return move(std::unique_ptr<CBaseCard>(new CVampire(name, atk, hlth, ect)));
		break;
	}
	case Wall:
	{
		//std::unique_ptr<CBasicMinion> = std::move(CBasicMinion());
		return move(std::unique_ptr<CBaseCard>(new CWall(name, atk, hlth)));
		break;
	}
	case Horde:
	{
		//std::unique_ptr<CBasicMinion> = std::move(CBasicMinion());
		return move(std::unique_ptr<CBaseCard>(new CRat(name, atk, hlth, ect)));
		break;
	}
	case Trample:
	{
		//std::unique_ptr<CBasicMinion> = std::move(CBasicMinion());
		return move(std::unique_ptr<CBaseCard>(new CTrample(name, atk, hlth)));
		break;
	}
	case Sword:
	{
		//std::unique_ptr<CBasicMinion> = std::move(CBasicSpell());
		//Equipment is done this way to allow new equipment to be easily accessed. I could, for example, change attack to lifesteal 
		//and it will work without breaking anything but will only affect Vampires and Leeches.
		return move(std::unique_ptr<CBaseCard>(new CEquipment(name, atk, attack)));//new Spell Type()
		break;
	}
	case Armour:
	{
		//std::unique_ptr<CBasicMinion> = std::move(CBasicSpell());
		return move(std::unique_ptr<CBaseCard>(new CEquipment(name, atk, defence)));//new Spell Type()
		break;
	}
	}

	

	//General 'fix it' for any out of context cards. Will give them the basic loadout depending on their card type. If they don't have health then they're probably a casting ability.
	if (hlth > 0)
	{
		return move(std::unique_ptr<CBaseCard>(new CBasicMinion(name, atk, hlth)));
	}
	else
	{
		return move(std::unique_ptr<CBaseCard>(new CFireBall(name, atk)));
	}
}
