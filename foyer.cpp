#include <assert.h>
#include <math.h>
#include "foyer.h"


Foyer::Foyer(int ide, int revenu, int NombreMenage)
{
    this->ide=ide;
    this->revenu=revenu;
    this->NombreMenage=NombreMenage;
    
}

std::ostream& operator << (std::ostream& os, const Foyer& foyer) {
  
  return os;
}

std::istream& operator >> (std::istream& ss, Foyer& foyer)
{
    ss>>foyer.ide>>foyer.revenu>>foyer.NombreMenage;
    return ss;
}
