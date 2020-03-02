/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Hiver 2020 | TP1 | tp1.cpp
*/

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include "tableau.h"
#include "quartier.h"
#include"math.h"


using namespace std;



int tp1(istream& entree){
    
    Tableau<Quartier> re1= Tableau<Quartier>(8);
    
    std::string line;
    bool ajouterFoyer=false;
    
    
    Quartier quartier;
    while(std::getline(entree,line))
    {
        if( (line.find(";") == string::npos)&& (ajouterFoyer==false) )
        {
            quartier.setName(line);
        }
        else if(line.find(";") != string::npos)
        {
            if(ajouterFoyer)
            {
                re1.ajouter(quartier);
                quartier.effacer();
                
            }
            
            ajouterFoyer = !ajouterFoyer;
        }
        else if(ajouterFoyer)
        {
             istringstream stringStream(line);
            Foyer f;
            stringStream>>f;
            quartier.ajouterFoyer(f);
            
        }
        
    }
    
    
    cout<<re1<<endl;
    //Affichage sur la sortie standart:
    
    
    // calcul revenu moyen par quartier
    
    return 0;
}









int main(int argc, const char** argv){
    // Gestion de l'entrée :
    //  - lecture depuis un fichier si un argument est spécifié;
    //  - sinon, lecture depuis std::cin.
    if(argc>1)
    {
         std::ifstream entree_fichier(argv[1]);
         if(entree_fichier.fail())
         {
             std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
             return 1;
         }
         return tp1(entree_fichier);
    }else
         return tp1(std::cin);

    return 0;
}
