/*
  INF3105 -- Structures de donn�es et algorithmes
  UQAM | D�partement d'informatique
  Hiver 2020 | TP1 | foyer.cpp
*/

#include <assert.h>
#include <math.h>
#include "foyer.h"

//...
Foyer::Foyer(int ide, int revenu, int NombreMenage)
{
    this->ide=ide;
    this->revenu=revenu;
    this->NombreMenage=NombreMenage;
    
}





std::ostream& operator << (std::ostream& os, const Foyer& foyer) {
  
  return os;
}

std::istream& operator >> (std::istream& bob, Foyer& foyer)
{
    bob>>foyer.ide>>foyer.revenu>>foyer.NombreMenage;
    return bob;
}
