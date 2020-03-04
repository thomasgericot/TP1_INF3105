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

int code_ASCII(char c)
{
 return int(c);
}

int seuil_pauvrete(int nbPersonnes){
    return round(7000+850*(nbPersonnes-2));
}

int tp1(istream& entree){
    
    Tableau<Quartier> re1= Tableau<Quartier>(8);
    Tableau<Quartier> re2= Tableau<Quartier>(8);
    std::string line;
    bool ajouterFoyer=false;
    Quartier quartier_bas;
    Quartier quartier_haut;
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
    
    
    cout<<"a) ";
    int moyenne = 0;
    for(int i=0;i<re1.nbElements;i++)
    {
        moyenne += re1[i].MoyenneQuartier();
    }
    moyenne /=re1.nbElements;
    cout<<"Revenu moyen:\t"<<round(moyenne)<<endl;
    
    
        //Affichage Ordre Croissant
    
    for(int i=0;i<re1.nbElements;i++)
    {
        if(re1[i].MoyenneQuartier()<=moyenne)
        {
            
            re2.ajouter(re1[i]);
        }
    }
    cout<<re2[0].MoyenneQuartier()<<endl;
    cout<<re2[1].MoyenneQuartier()<<endl;
        
    for (int u=0; u<re2.nbElements;u++){
        
        for(int p=0;p<re2.nbElements;p++){
        if(re2[u].MoyenneQuartier()>re2[p].MoyenneQuartier()){
            
            re2.inserer(re2[u],p+1);
            re2.enlever(u);
        }
        
        }
        
        
    }
    
        
    
            
               
        
    
    
    
    cout<<"b) Liste des quartiers defavorables.\n";
    
    for(int i=0;i<re2.nbElements;i++)
    {
        
        cout<<re2[i].NomQuartier<<"\t\t"<<"Revenu moyen: "<<re2[i].MoyenneQuartier()<<endl;
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



    
