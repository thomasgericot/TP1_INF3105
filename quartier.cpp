
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

int seuil_pauvrete(int nbPersonnes){
    return round(7000+850*(nbPersonnes-2));
}

std::ostream& operator << (std::ostream& os,  const Tableau<Quartier>& re1) {
    Quartier quartier_bas;
    Quartier quartier_haut;
    Tableau<Quartier> re2= Tableau<Quartier>(8);
    cout<<"a) ";
    
    int moyenne = 0;
    for(int i=0;i<re1.nbElements;i++)
    {
        moyenne += re1[i].MoyenneQuartier();
    }
    moyenne /=re1.nbElements;
    cout<<"Revenu moyen:\t"<<round(moyenne)<<endl;
    
    for(int i=0;i<re1.nbElements;i++)
    {
        if(re1[i].MoyenneQuartier()<moyenne)
        {
                re2.ajouter(re1[i]);
        }
        
        
            }
    
    
    cout<<"b) Liste des quartiers defavorables.\n";
    for(int i=0;i<re2.nbElements;i++)
    {
        
        cout<<re2[i].NomQuartier<<"\t"<<"Revenu moyen: "<<re2[i].MoyenneQuartier()<<endl;
    }
    
    
    int revenu_quartier_bas=re1[0].MoyenneQuartier();
    int revenu_quartier_haut=re1[0].MoyenneQuartier();
    quartier_bas.NomQuartier=re1[0].NomQuartier;
    quartier_haut.NomQuartier=re1[0].NomQuartier;
    
    
    for(int i=0;i<re1.nbElements;i++){
        
    if(re1[i].MoyenneQuartier()<revenu_quartier_bas)
    {
        revenu_quartier_bas=re1[i].MoyenneQuartier();
        quartier_bas.NomQuartier=re1[i].NomQuartier;
    }
        
    if(re1[i].MoyenneQuartier()>revenu_quartier_haut)
    {
        revenu_quartier_haut=re1[i].MoyenneQuartier();
        quartier_haut.NomQuartier=re1[i].NomQuartier;
    }
        
    }
    
    cout<<"c)\n";
    cout<<quartier_bas.NomQuartier<<"\t\t"<<"Quartier avec le plus petit revenu moyen: "<<revenu_quartier_bas<<endl;
    cout<<quartier_haut.NomQuartier<<"\t\t"<<"Quartier avec le plus grand revenu moyen: "<<revenu_quartier_haut<<endl;
    
    
    
    
    int nombre_sous_seuil=0;
    int nombre_menage_total=0;
    
    
    for(int i=0;i<re1.nbElements;i++){
        
        for(int j=0;j<re1[i].foyers.nbElements;j++){
            
            nombre_menage_total++;
            
            if (re1[i].foyers[j].revenu < seuil_pauvrete(re1[i].foyers[j].NombreMenage))
            {
                
                nombre_sous_seuil=nombre_sous_seuil+1;
                
                
            }
          }
        }
    
    
    
    
    
    cout<<"d) Pourcentage de menages dont le revenu est faible: "<<round(((double)nombre_sous_seuil/(double)nombre_menage_total)*100)<<endl;
    
    
  return os;
}


    
    
    
    std::istream& operator >> (std::istream& is, Quartier& q)
    {
    return is;
    
}

int  Quartier:: const MoyenneQuartier()
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
