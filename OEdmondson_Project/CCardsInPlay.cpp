#define DEBUG_NEW new(__FILE__, __LINE__)
#define new DEBUG_NEW
#include "CCardsInPlay.h"


//Get a random value from each player. This is to make it possible to give each player different seeds and create a quasi-global function as I retarget cards on a semi-regular basis to adujst for new information.
int CCardsInPlay::getRandom(float n, int currentPlayer)
{
	mCPlayers[currentPlayer].findTarget(n);
	return mCPlayers[currentPlayer].getTarget();
}


//This function is made to exclusively delete cards.
void CCardsInPlay::DeleteCard(int player, ECardStates location, int cardID)
{
	//Even if it's not removed from the hand (Spell); the hand needs to clear the front slot as it'd be a nullptr or a used card. Both of which need to go.
	if (mCPlayers[player].pDeck[location].size() > 0)
	{
		//SPlayer[currentPlayer].pDeck[inHand].erase(SPlayer[currentPlayer].pDeck[inHand].begin(), SPlayer[currentPlayer].pDeck[inHand].begin() + 1);
		if (cardID != mCPlayers[player].pDeck[location].size() - 1)
		{
			int tmp;
			while (cardID < mCPlayers[player].pDeck[location].size() - 1)
			{
				if (cardID + 1 >= mCPlayers[player].pDeck[location].size())
				{
					tmp = 0;
				}
				else
				{
					tmp = cardID + 1;
				}

				mCPlayers[player].pDeck[location][cardID] = move(mCPlayers[player].pDeck[location][tmp]);
				++cardID;
			}
		}

		mCPlayers[player].pDeck[location].back().release();
		mCPlayers[player].pDeck[location].pop_back();

	}
}

//The purpose of this function is to move the card into the active deck and delete the nullptr left behind. It also will cast spells automatically and delete them.
void CCardsInPlay::playCard(int currentPlayer, int secondPlayer, int cardID)
{
	if (mCPlayers[currentPlayer].pDeck[inHand].size() > 0)
	{
		//The second condition is for non-implemented cards such as equipment. 
		if (mCPlayers[currentPlayer].pDeck[inHand][cardID]->getIsPlaced() != inactive)
		{
			mCPlayers[currentPlayer].pDeck[mCPlayers[currentPlayer].pDeck[inHand][cardID]->getIsPlaced()].push_back(std::move(mCPlayers[currentPlayer].pDeck[inHand][cardID]));
		}
		else
		{
			if (mCPlayers[currentPlayer].pDeck[inHand][cardID]->UseCard(mCPlayers[currentPlayer], mCPlayers[secondPlayer]))
			{
				//Make sure no cards are alive.
				for (int j = 0; j < 4; j = j + 3)
				{
					//This needs to be an int loop for the delete card function.
					for (int i = 0; i < mCPlayers[secondPlayer].pDeck[ECardStates(j)].size(); ++i)
					{
						if (mCPlayers[secondPlayer].pDeck[ECardStates(j)][i]->getStat(health) <= 0)
						{
							std::cout << managerTableOutput[1] << playerName[secondPlayer] << managerTableOutput[2] << mCPlayers[secondPlayer].pDeck[ECardStates(j)][i]->cardName() << managerTableOutput[3];
							DeleteCard(secondPlayer, ECardStates(j), i);
						}
					}
				}
			}
		}


		DeleteCard( currentPlayer, inHand, cardID);
	}
}

//A function specialised for finding killed units.
void CCardsInPlay::findDead(ECardStates deck, int enemyPlayer)
{
	//Due to the delete function this is required to be a int loop.
	for (int j = 0; j < mCPlayers[enemyPlayer].pDeck[deck].size(); ++j)
	{
		if (mCPlayers[enemyPlayer].pDeck[deck][j]->getStat(health) <= 0)
		{
			std::cout << playerName[enemyPlayer] << managerTableOutput[2] << mCPlayers[enemyPlayer].pDeck[deck][j]->cardName() << managerTableOutput[3];
			DeleteCard(enemyPlayer, deck, j);
		}
	}
}

//This is what I activate at the end of each round to make the current players minions attack the others. 
void CCardsInPlay::activateTable(int currentPlayer)
{
	int enemyPlayer = currentPlayer + 1;
	if (enemyPlayer > 1)
	{
		enemyPlayer = 0;
	}

	for (int i = 0; i < mCPlayers[enemyPlayer].pDeck[active].size(); ++i)
	{
		if (mCPlayers[enemyPlayer].pDeck[active][i]->getStat(health) <= 0)
		{
			std::cout << playerName[enemyPlayer] << managerTableOutput[2] << mCPlayers[enemyPlayer].pDeck[active][i]->cardName() << managerTableOutput[3];
			DeleteCard(enemyPlayer, ECardStates(active), i); 
		}
	}

	for (int currentArr = active; currentArr <= highPriority; currentArr = currentArr + highPriority)
	{
		for (auto it = mCPlayers[currentPlayer].pDeck[ECardStates(currentArr)].begin(); it < mCPlayers[currentPlayer].pDeck[ECardStates(currentArr)].end(); ++it)
		{
			ECardStates targetArr = active;

			mCPlayers[currentPlayer].findTarget((float)mCPlayers[enemyPlayer].pDeck[ECardStates(targetArr)].size() - 1.0f);
			if (it->get()->UseCard(mCPlayers[currentPlayer], mCPlayers[enemyPlayer]))
			{
				findDead(active, enemyPlayer);
				findDead(highPriority, enemyPlayer);
			}
		}
	}
	std::cout << std::endl << std::endl;
}

//Allows the specified card and player to activate.
bool CCardsInPlay::playerTurn(int currentPlayer, int cardID)
{
	int enemyPlayer = currentPlayer + 1;
	if (enemyPlayer > 1)
	{
		enemyPlayer = 0;
	}

	//If the card doesn't exist then delete it. Shouldn't happen but this is a contingancy
	if (mCPlayers[currentPlayer].pDeck[inHand][cardID] != nullptr)
	{
		std::cout << mCPlayers[currentPlayer].getName() << managerTableOutput[4] << mCPlayers[currentPlayer].pDeck[inHand][cardID]->cardName();

		playCard(currentPlayer, enemyPlayer, cardID);

		std::cout << std::endl; 
		return true;
	}
	else
	{
		DeleteCard(currentPlayer, inHand, cardID);
	}
	std::cout << std::endl << std::endl;
	return false;
}


//Allows us to make a specified player draw a card, whilst there are cards remaining in the deck.
bool CCardsInPlay::drawCard(int currentPlayer)
{
	if (mCPlayers[currentPlayer].pDeck[inactive].size() > 0)
	{
		std::cout <<mCPlayers[currentPlayer].getName() << managerTableOutput[5] << mCPlayers[currentPlayer].pDeck[inactive].front()->cardName() << managerTableOutput[6];
		mCPlayers[currentPlayer].pDeck[inHand].push_back(move(mCPlayers[currentPlayer].pDeck[inactive].front()));
		if (mCPlayers[currentPlayer].pDeck[inactive].size() > 0)
		{
			//Look into changing this for efficiency; //Consider making it a push-front function too;
			mCPlayers[currentPlayer].pDeck[inactive].erase(mCPlayers[currentPlayer].pDeck[inactive].begin(), mCPlayers[currentPlayer].pDeck[inactive].begin() + 1);
			
		}
		return true;
	}
	else
	{
		return false;

	}
}

//Sets the decks stored in the filereader to players and assigns them ID's for the console output;
void CCardsInPlay::setPlayers(playerDecks pP1, playerDecks pP2)
{
	//Place each deck into the player classes. Player 1 will always be sorceress and player 2 will always be wizard. Custom names is not a current feature as we have been told to make sorceress always go first.
	mCPlayers[0].pDeck[inactive] = move(pP1);
	mCPlayers[1].pDeck[inactive] = move(pP2);

	mCPlayers[0].setName(0);
	mCPlayers[1].setName(1);
};


//Grab the current game result. Used for ifGameActive checks.
int CCardsInPlay::isGameActive()
{
	if (mCPlayers[0].lifePoints() <= 0)
	{
		return 1; //If player 0 has no lifepoints remaining then player 1 wins. 
	}
	if (mCPlayers[1].lifePoints() <= 0)
	{
		return 0; //If player 1 has no lifepoints remaining then player 0 wins. 
	}

	return -1; //If all players have more than 0 LP then no one can be winning.
}


//Sets the seed but limits the player to a value above 0.
bool CCardsInPlay::setSeed(int currentPlayer, int seed)
{
	if (seed <= -1)
	{
		return false;
	}
	else
	{
		mCPlayers[currentPlayer].findTarget(static_cast<unsigned int> (seed));
		return true;
	}
}

//Randomizes the specified players deck.
void CCardsInPlay::randDeck(int currPlayer)
{
	int deckSize = (int)mCPlayers[currPlayer].pDeck[inactive].size();
	for (int i = 0; i < deckSize; ++i)
	{
		mCPlayers[currPlayer].setTarget((float)mCPlayers[currPlayer].pDeck[inactive].size() - 1.0f);

		int test = mCPlayers[currPlayer].getTarget();
		mCPlayers[currPlayer].pDeck[active].push_back(move(mCPlayers[currPlayer].pDeck[inactive][mCPlayers[currPlayer].getTarget()]));
		DeleteCard(currPlayer, inactive, mCPlayers[currPlayer].getTarget());
	}

	mCPlayers[currPlayer].pDeck[inactive] = std::move(mCPlayers[currPlayer].pDeck[active]);
}

void CCardsInPlay::showTable(int currentPlayer)
{

	std::cout << managerTableOutput[0];
	for (auto it = mCPlayers[currentPlayer].pDeck[highPriority].begin(); it != mCPlayers[currentPlayer].pDeck[highPriority].end(); ++it)
	{
		std::cout << it->get()->cardName() << "(" << it->get()->getStat(health) << ") ";
		//std::cout << SPlayer[currentPlayer].pDeck[highPriority][]->cardName() << "(" << SPlayer[currentPlayer].pDeck[highPriority][i]->getStat(health) << ") ";
	}
	for (auto it = mCPlayers[currentPlayer].pDeck[active].begin(); it != mCPlayers[currentPlayer].pDeck[active].end(); ++it)
	{
		std::cout << it->get()->cardName() << "(" << it->get()->getStat(health) << ") ";
		//std::cout << SPlayer[currentPlayer].pDeck[highPriority][]->cardName() << "(" << SPlayer[currentPlayer].pDeck[highPriority][i]->getStat(health) << ") ";
	}
	//for (int i = 0; i < SPlayer[currentPlayer].pDeck[active].size(); ++i)
	//{
	//	std::cout << SPlayer[currentPlayer].pDeck[active][i]->cardName() << "(" << SPlayer[currentPlayer].pDeck[active][i]->getStat(health) << ") ";
	//}		
	std::cout << std::endl;
};