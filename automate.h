#ifndef _AUTOMATE_H_
#define _AUTOMATE_H_

#include "etat.h"


using namespace std;

class automate
{
private:
    vector <etat> m_state;
    vector <char> m_alphabet;
    string detailautomate;
public:
    automate();
    automate(vector <etat> state, vector <char> alphabet);
    int nbetat();
    int getnometat(int numetat); //savoir quel etat a quel nom
    etat getetat(int nom); //en premier argument le vecteur d'�tat et en deuxi�me l'�tat numero x qui correspondra au nom de l'�tat, fera un -1 dans la fonction
    string getalphabet();
    char getalphabet1(int nombre); //quel caractere on souhaite acc�der
    void setetat(int nom); //quel etat on veut ajouter
    void setalphabet(char caractere); //quel caractere on veut ajouter
    void setinitial(int nometat);
    void setterminal(int nometat);
    void setiniterm(int nometat);
    void settransition1(int nometat, int etatdestination); //pour source
    void settransition2(int nometat, int etatdestination); //pour destination
    void settransition3(int nometat,char b); //pour caract�re

    int getinitial(int numetat);//v�rifie si un �tat est initial, si c'est le cas il le renvoie, sinon renvoie false. Attention, il regarde � partir des indices du vector, donc pas oublier de faire -1 � l'�tat qu'on rentre
    int getterminal(int numetat); //idem que terminal
    int getnbinitial();
    int gettype(int numetat);

    string getsource(int numetat);
    string getdestination(int numetat);
    string getcaractere(int numetat);

    bool est_un_automate_Standard();//reconnaissance standardisation
    bool est_un_automate_Determine();
    bool est_un_automate_Complet();
    bool complet(string recherche); //fonction utilis�e par la recherche d'automate complet

    string getdetail(); //afficher la ligne
    void setdetail(string ligne); //fonction pour conserver la ligne dans l'automate

    void standardiser();
    void completer();
    void completion(int numetat);
    //bool lecturemot(string mot); //incomplet
    friend ostream& operator<<(ostream &flux, automate & projet);
};

int saisiesecu(int &N );
int saisiesecu(int &N, int sup, int inf);
automate lectureautomate(string nom_fichier, automate &projet);
automate ecritureautomate(string nom_fichier,string ligne,int numautomate, automate &projet);
void lecturedir();

#endif // _AUTOMATE_H_
