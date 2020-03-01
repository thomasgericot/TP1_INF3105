
/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Hiver 2020 | TP1 | quartier.cpp
*/

#include <assert.h>
#include "quartier.h"
#include <string>
#include <iostream>

#include <cstring>


using namespace std;
std::ostream& operator << (std::ostream& os, const Quartier& q) {
    os<<"Le nom du quartier est: "<<q.NomQuartier<<endl;
    for(int i=0;i<q.foyers.nbElements;i++)
    {
        cout<<"Dans ce quartier reside la famille "<<q.foyers[i].ide<<"qui gagne "<<q.foyers[i].revenu<<"tout en s'occupant de "<<q.foyers[i].NombreMenage<<" personnes"<<endl;
    }
    /*". Dans ce quartier reside la famille "<<q.ide<<"qui gagne "<<q.revenu<<"tout en s'occupant de "<<q.NombreMenage<<" personnes"<<endl;*/
  return os;
}

std::istream& operator >> (std::istream& is, Quartier& q)
    {
    return is;
    
}

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
