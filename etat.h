#ifndef _ETAT_H_
#define _ETAT_H_
#include "transition.h"

class etat
{
private:
    int m_nom; //le nom sera toujours en chiffre, 0 : etat poubelle
    transition m_trans; // un etat contient plusieurs transitions rentrantes et/ou sortante, ces types sont dans les classes transitions
    int m_type; // 0 : aucun, 1 : initial, 2 : terminal, 3 : initial et terminal
public:
    etat();
    etat(int nom,int type);
    etat(int nom, transition trans, int type);
    int getnom();
    int gettype();
    transition gettrans(); //le nom est la transition que l'on souhaite accéder dans l'état,
                                                            //par défaut int = 0 car c'est la première transition
    void setnom(int nom);
    void settype(int type);
    void settrans(transition trans); //permet de rajouter des transitions


    //ces fonctions ne font que créer des transitions, elles ne les modifient pas
    void settrans1(string trans);
    void settrans2(string trans);
    void settrans3(string trans);
    //

    //fonctions pour remplacer les champs m_source, m_destination, m_caractere
    void setsource(string source);
    void setdestination(string destination);
    void setcaractere(string caractere);

    //avoir la chaîne de caractere source,destination,nom de transition
    string getsource();
    string getdesti();
    string getcarac();

    int getnbtransition(int numetat);

    char getsource(int numtransition);
    char getcarac(int numtransition); //avoir la transition correspondante à l'état

    friend ostream& operator<<(ostream& flux, etat& state);
};

#endif // _ETAT_H_

