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
#include<string>



using namespace std;



int seuil_pauvrete(int nbPersonnes)
{
    return round(7000+850*(nbPersonnes-2));
}

void bubbleSortNom(Tableau<Quartier>& arr)
{
    int n = arr.nbElements;
    for (int i = 0; i < n-1; i++)
    {
        // Last i elements are already in place
        for (int j = 0; j < n-i-1; j++)
        {
            if (arr[j].NomQuartier > arr[j+1].NomQuartier)
            {
                Quartier temp = arr[j];
                arr[j] =arr[j+1];
                arr[j+1]=temp;
            }
        }
        
    }
}

void bubbleSortMoyenne(Tableau<Quartier>& arr)
{
    int n = arr.nbElements;
    for (int i = 0; i < n-1; i++)
    {
        // Last i elements are already in place
        for (int j = 0; j < n-i-1; j++)
        {
            if (arr[j].MoyenneQuartier() > arr[j+1].MoyenneQuartier())
            {
                Quartier temp = arr[j];
                arr[j] =arr[j+1];
                arr[j+1]=temp;
            }
        }
        
    }
}

int tp1(istream& entree)
{
    
    Tableau<Quartier> re1= Tableau<Quartier>(8);
    Tableau<Quartier> re2= Tableau<Quartier>(8);
    
    // parsing fichier
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
    
    // calculer moyenne
    cout<<"a) ";
    int moyenne = 0;
    for(int i=0;i<re1.nbElements;i++)
    {
        moyenne += re1[i].MoyenneQuartier();
    }
    moyenne /=re1.nbElements;
    cout<<"Revenu moyen:\t"<<round(moyenne)<<endl;
    
    // trouve quartier sous la moyenne
    for(int i=0;i<re1.nbElements;i++)
    {
        if(re1[i].MoyenneQuartier()<=moyenne)
        {
            re2.ajouter(re1[i]);
        }
    }
    
    // Affichage croissant, probleme d'index + pb de types pointŽ pour l'ordre alphabŽtique
    bubbleSortMoyenne(re2);
    
    // verifie nom
    Tableau<Quartier> finalQuartier;
    for(int i=0;i<re2.nbElements;i++)
    {
        Tableau<Quartier> memeQuartier;
        
        int debut = i;
        memeQuartier.ajouter(re2[debut]);
        while ((i<re2.nbElements-1) && (re2[debut].MoyenneQuartier() == re2[i+1].MoyenneQuartier()))
        {
            memeQuartier.ajouter(re2[i+1]);
            i++;
        }
        
        bubbleSortNom(memeQuartier);
        
        finalQuartier += memeQuartier;
    }
    
    // affichage
    cout<<"b) Liste des quartiers defavorables.\n";
    for(int i=0;i<finalQuartier.nbElements;i++)
    {
        cout<<finalQuartier[i].NomQuartier<<"\t\t"<<"Revenu moyen: "<<finalQuartier[i].MoyenneQuartier()<<endl;
    }
    
    // quartiers haut et bas
    int revenu_quartier_bas=re1[0].MoyenneQuartier();
    int revenu_quartier_haut=re1[0].MoyenneQuartier();
    quartier_bas.NomQuartier=re1[0].NomQuartier;
    quartier_haut.NomQuartier=re1[0].NomQuartier;
    
    for(int i=0;i<re1.nbElements;i++)
    {
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
    
    // affichage
    cout<<"c)\n";
    cout<<quartier_bas.NomQuartier<<"\t\t"<<"Quartier avec le plus petit revenu moyen: "<<revenu_quartier_bas<<endl;
    cout<<quartier_haut.NomQuartier<<"\t\t"<<"Quartier avec le plus grand revenu moyen: "<<revenu_quartier_haut<<endl;
    
    
    
    // % quartiers sous le seuil de pauvrete
    int nombre_sous_seuil=0;
    int nombre_menage_total=0;
    
    
    for(int i=0;i<re1.nbElements;i++)
    {
        for(int j=0;j<re1[i].foyers.nbElements;j++)
        {
            nombre_menage_total++;

            if (re1[i].foyers[j].revenu < seuil_pauvrete(re1[i].foyers[j].NombreMenage))
            {
                nombre_sous_seuil=nombre_sous_seuil+1;
            }
        }
    }
    
    cout<<"d) Pourcentage de menages dont le revenu est faible: "<<round(((double)nombre_sous_seuil/(double)nombre_menage_total)*100.0)<<"%"<<endl;
    
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



    
/*
 
 */
