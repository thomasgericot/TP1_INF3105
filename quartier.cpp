#include <assert.h>
#include "quartier.h"
#include <string>
#include <iostream>
#include <cstring>


using namespace std;



Quartier::Quartier(const Quartier& obj) :
NomQuartier(obj.NomQuartier),
foyers(obj.foyers)
{
    
}

Quartier& Quartier::operator = (const Quartier& obj)
{
    NomQuartier=obj.NomQuartier;
    foyers=obj.foyers;
    
    return *this;
}


std::ostream& operator << (std::ostream& os, const Quartier& q) {
    
  return os;
}

std::istream& operator >> (std::istream& is, Quartier& q)
    {
    return is;
    
}


// Fonction de la classe Quartier permettant de calculer la moyenne de revenu d'un quartier dont les foyers sont stockés
//dans le Tableau foyers.
int Quartier::MoyenneQuartier()
{
    int moyenne = 0;
    for(int i=0;i<foyers.nbElements;i++)
    {
        moyenne += foyers[i].revenu;
    }
    
    if(foyers.nbElements > 0)
        moyenne /= foyers.nbElements;
    
    return moyenne;
}
