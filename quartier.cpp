
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
    os<<"Le nom du quartier est: "<<q.NomQuartier<<". Dans ce quartier reside la famille "<<q.ide<<"qui gagne "<<q.revenu<<"tout en s'occupant de "<<q.NombreMenage<<" personnes"<<endl;
  return os;
}

std::istream& operator >> (std::istream& is, Quartier& q) {
    
    
    std::string chaine_courante2;
    getline(is, chaine_courante2);
    
    
    
    std:: getline(is,chaine_courante2,'\t');
    q.ide=std::stoi(chaine_courante2);
    cout<<q.ide<<endl;
    
    
    std::getline(is,chaine_courante2,' ');
    q.revenu=std::stoi(chaine_courante2);
    cout<<q.revenu<<endl;
    
    
    q.NombreMenage=std::stoi(chaine_courante2);
    
    
    
    
    
    
    
    
    
    return is;
    
}

