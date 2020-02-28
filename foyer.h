/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Hiver 2020 | TP1 | foyer.h
*/

#if !defined(__FOYER_H__)
#define __FOYER_H__
#include <iostream>
#include "tableau.h"


class Foyer {
  public:
    int ide;
    int revenu;
    int NombreMenage;

    Foyer(int ide, int revenu, int NombreMenage);
  private:
    



  friend std::ostream& operator << (std::ostream&, const Foyer&);
  friend std::istream& operator >> (std::istream&, Foyer&);
};

#endif
