 #if !defined(__TABLEAU_H__)
#define __TABLEAU_H__

template <class T>
class Tableau
{
  public:
    Tableau(int capacite_initiale=8);
    Tableau(const Tableau&);
    ~Tableau();

    void           ajouter(const T& element); // � la fin
    //void           inserer_fin(const T& element){ajouter(element);}
    bool           vide() const {return nbElements==0;}
    void           vider();
    int            taille() const {return nbElements;}

    void           inserer(const T& element, int index=0);
    void           enlever(int index=0);
    void           enlever_dernier();
    int            trouver(const T& element) const;
    bool           contient(const T& element) const;

    T&	           operator[] (int index);
    const T&       operator[] (int index) const;


    Tableau<T>&    operator = (const Tableau<T>& autre);
    
    Tableau<T>&    operator += (const Tableau<T>& autre); 

    bool           operator == (const Tableau<T>& autre) const;

  public:
    T*             elements;
    int            capacite;
    int            nbElements;

};



#include <assert.h>


template <class T>
Tableau<T>::Tableau(int capacite_initiale)
{
    capacite = capacite_initiale;
    nbElements = 0;
    elements = new T[capacite];
}


template <class T>
Tableau<T>::Tableau(const Tableau& autre) {
    capacite = autre.nbElements;
    nbElements = autre.nbElements;
    elements = new T[capacite];
    for(int i=0;i<nbElements;i++)
        elements[i] = autre.elements[i];
}

template <class T>
Tableau<T>::~Tableau()
{
    delete[] elements;
    //elements = NULL; // cela est optionnel
}

template <class T>
void Tableau<T>::ajouter(const T& item){
    if(nbElements >= capacite){
        if(capacite==0) capacite=2;
        capacite *= 2;
        T* temp = new T[capacite];
        for(int i=0;i<nbElements;i++)
            temp[i] = elements[i];
        delete [] elements;
        elements = temp;
    }
    elements[nbElements++] = item;
}

template <class T>
void Tableau<T>::inserer(const T& element, int index){
    assert(index<=nbElements);
    if(nbElements >= capacite){
        if(capacite==0) capacite=2;
        capacite *= 2;
        T* temp = new T[capacite];
        for(int i=0;i<index;i++)
            temp[i] = elements[i];
        temp[index] = element;
        for(int i=index;i<nbElements;i++)
            temp[i+1] = elements[i];
        delete [] elements;
        nbElements++;
        elements = temp;
    }else{
        for(int i=nbElements;i>index;i--)
            elements[i] = elements[i-1];
        elements[index] = element;
        nbElements++;
    }
}

template <class T>
void Tableau<T>::enlever_dernier(){
    assert(nbElements>0);
    nbElements--;
}

template <class T>
void Tableau<T>::enlever(int index){
    assert(nbElements>0);
    nbElements--;
    for(int i=index;i<nbElements;i++)
        elements[i] = elements[i+1];
}

template <class T>
int Tableau<T>::trouver(const T& element) const{
    for(int i=0;i<nbElements;i++)
        if(elements[i]==element)
            return i;
    return -1;
}

template <class T>
bool Tableau<T>::contient(const T& element) const{
    return trouver(element)!=-1;
}

template <class T>
void Tableau<T>::vider(){
    nbElements = 0;
}


template <class T>
T& Tableau<T>::operator[] (int index){
    assert(index<nbElements);
    return elements[index];
}

template <class T>
const T& Tableau<T>::operator[] (int index) const{
    assert(index<nbElements);
    return elements[index];
}

template <class T>
Tableau<T>& Tableau<T>::operator = (const Tableau<T>& autre){
    if(this==&autre) return *this;

    nbElements = autre.nbElements;
    if(capacite<autre.nbElements || autre.nbElements*2<capacite)
    {
        delete[] elements;
        capacite = autre.capacite;
        elements = new T[capacite];
    }
    for(int i=0;i<nbElements;i++)
        elements[i] = autre.elements[i];
    return *this;
}

template <class T>
Tableau<T>& Tableau<T>::operator += (const Tableau<T>& autre)
{
    if(this==&autre) return *this;

    for(int i=0;i<autre.nbElements;i++)
        this->ajouter(autre.elements[i]);
    return *this;
}


template <class T>
bool Tableau<T>::operator == (const Tableau<T>& autre) const{
    if(this == &autre) return true;
    if(nbElements != autre.nbElements) return false;
    for(int i=0;i<nbElements;i++)
        if(!(elements[i]==autre.elements[i]))
            return false;
    return true;
}
#endif

