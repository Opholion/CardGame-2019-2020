// CCardFactory.h
// ===============
//
// Factory function declaration to create CSearchXXX objects 
//

#pragma once

//This should contain a #include for each card type.
#include "CCard.h" // Search interface class
#include "CBasicMinion.h" // NoStar search class
#include "CFireBall.h"
#include "CLightning.h"
#include "CBless.h"
#include "CWall.h"
#include "CVampire.h"
#include "CRat.h"
#include "CTrample.h"
#include "CEquipment.h"

// List of implemented seach algorithms

//EUnitTypes is held in definitions.
// Factory function to create CSearchXXX object where XXX is the given search type
std::unique_ptr<CBaseCard> NewSearch(EUnitTypes search, std::string name, int atk, int hlth, int ect);
