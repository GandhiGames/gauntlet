#include "PCH.h"
#include "C_Strength.h"


C_Strength::C_Strength(Object* owner) : C_BaseStat(owner)
{
}

//TODO: where should this go? Created virtual destructor so no one instantiates base stat.
C_BaseStat::~C_BaseStat()
{

}

C_Strength::~C_Strength() 
{
}
