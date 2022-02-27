#include "CPlayer.h"

void CUser::findTarget(const float n)
{
	mTarget =  static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * (n + 1));
}


void CUser::setTarget(float n)
{
	mTarget = n;
}
