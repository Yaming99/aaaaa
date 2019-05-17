#ifndef _TRANSITION_H_
#define _TRANSITION_H_

#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <fstream>
//#include <cstddef> //size_t

using namespace std;

class transition
{
private:
    string m_source; //aura le chiffre qui représente l'état d'où vient la transition, si 0, ça signifie que l'état était destinataire mais ne renvoyait pas sur lui-même
    string m_destination; //idem que m_source
    string m_caractere; //caractère(s) fourni par la transition
    //tout les caractères de même indice concerne une unique transition
public:
    transition();
    transition(string source, string destination, string caractere);
    string getsource();
    string getdesti();
    string getcarac();
    char getcarac(int numtrans);
    friend int getnbtransition(transition a);

    void setsource(string source);//pn ajoute la transition dans le string
    void setdesti(string destination);
    void setcarac(string caractere);
    char getsource(int numtransition);
    int getnbtrans();

    void setsource2(string source); //on remplace m_source par le paramètre, idem pour en-dessous
    void setdestination2(string destination);
    void setcaractere2(string caractere);

};

#endif // _TRANSITION_H_
