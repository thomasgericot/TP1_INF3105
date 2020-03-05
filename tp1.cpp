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
#include <time.h>



using namespace std;


// Fonction permettant de calculer le seuil de pauvrete pour chaque menage de tous les quartiers.
int seuil_pauvrete(int nbPersonnes)
{
    return round(7000+850*(nbPersonnes-2));
}


// bubbleSortNom permet de trier les noms de quartiers possédant les memes revenus moyens les plus bas dans l'ordre
// alphabétique.
void bubbleSortNom(Tableau<Quartier>& arr)
{
    int n = arr.nbElements;
    for (int i = 0; i < n-1; i++)
    {
        
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


// bubbleSortMoyenne permet de trier les revenus moyens des quartier les plus faibles dans l'ordre croissant.
void bubbleSortMoyenne(Tableau<Quartier>& arr)
{
    int n = arr.nbElements;
    for (int i = 0; i < n-1; i++)
    {
        
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
    Tableau<Quartier> quartier_sous_moyenne= Tableau<Quartier>(8);
    
    // Parcourt fichier
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
    
    
    // Affichage du revenu moyen de tous les quartiers.
    cout<<"a) ";
    int moyenne = 0;
    for(int i=0;i<re1.nbElements;i++)
    {
        moyenne += re1[i].MoyenneQuartier();
    }
    moyenne /=re1.nbElements;
    cout<<"Revenu moyen:\t"<<round(moyenne)<<endl;
    
    
    // Trouve les quartiers sous la moyenne.
    for(int i=0;i<re1.nbElements;i++)
    {
        if(re1[i].MoyenneQuartier()<=moyenne)
        {
            quartier_sous_moyenne.ajouter(re1[i]);
        }
    }
    
    // Tri les moyennes de quartier des quartiers "pauvres" par ordre croissant.
    bubbleSortMoyenne(quartier_sous_moyenne);
    
    // Stocke les quartiers ayant la meme Moyenne de quartier dans un tableau.
    // Le tableau obtenu est passé en argument de bubbleSortNom() afin de trier ces quartiers par ordre alphabétique.
    Tableau<Quartier> finalQuartier;
    for(int i=0;i<quartier_sous_moyenne.nbElements;i++)
    {
        Tableau<Quartier> memeQuartier;
        
        int debut = i;
        memeQuartier.ajouter(quartier_sous_moyenne[debut]);
        while ((i<quartier_sous_moyenne.nbElements-1) && (quartier_sous_moyenne[debut].MoyenneQuartier() == quartier_sous_moyenne[i+1].MoyenneQuartier()))
        {
            memeQuartier.ajouter(quartier_sous_moyenne[i+1]);
            i++;
        }
        
        bubbleSortNom(memeQuartier);
        
        finalQuartier += memeQuartier; // overload de l'opérateur += pour les tableaux de quartiers explicité dans tableau.h
    }
    
    // Affichage des quartiers defavorables, par ordre croissant de Moyenne de quartier et par ordre alphabetique
    //dans le cas d'une egalite.
    cout<<"b) Liste des quartiers defavorables.\n";
    for(int i=0;i<finalQuartier.nbElements;i++)
    {
        cout<<finalQuartier[i].NomQuartier<<"\t\t"<<"Revenu moyen: "<<finalQuartier[i].MoyenneQuartier()<<endl;
    }
    
    // Determination des quartiers possedant le plus petit et le plus grand revenu moyen.
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
    
    //Affichage de ces quartiers.
    cout<<"c)\n";
    cout<<quartier_bas.NomQuartier<<"\t\t"<<"Quartier avec le plus petit revenu moyen: "<<revenu_quartier_bas<<endl;
    cout<<quartier_haut.NomQuartier<<"\t\t"<<"Quartier avec le plus grand revenu moyen: "<<revenu_quartier_haut<<endl;
    
    
    
    // % de quartiers sous le seuil de pauvrete.
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
    // Gestion de l'entree :
    //  - lecture depuis un fichier si un argument est specifie;
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



    
