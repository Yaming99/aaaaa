#include "etat.h"

etat::etat(): m_nom(0), m_trans(), m_type(0)
{

}

etat::etat(int nom, int type): m_nom(nom), m_trans(), m_type(type)
{

}
etat::etat(int nom, transition trans, int type) : m_nom(nom), m_trans(trans), m_type(type)
{

}

int etat::getnom()
{
    return this->m_nom;
}

int etat::gettype()
{
    return this->m_type;
}

transition etat::gettrans()
{
    return this->m_trans;
}

void etat::setnom(int nom)
{
    this->m_nom= nom;
    return;
}

void etat::settype(int type)
{
    this->m_type = type;
    return;
}

void etat::settrans1(string trans)
{
    this->m_trans.setsource(trans);
    return;
}

void etat::settrans2(string trans)
{
    this->m_trans.setdesti(trans);
    return;
}

void etat::settrans3(string trans)
{
    this->m_trans.setcarac(trans);
    return;
}

string etat::getsource()
{
    return this->m_trans.getsource();
}
string etat::getdesti()
{
    return this->m_trans.getdesti();
}
string etat::getcarac()
{
    return this->m_trans.getcarac();
}

char etat::getcarac(int numtransition)
{
    return this->m_trans.getcarac(numtransition);
}

int etat::getnbtransition(int numetat)
{
    return this->m_trans.getnbtrans();
}

char etat::getsource(int numtransition)
{
    return this->m_trans.getsource(numtransition);
}

void etat::setsource(string source)
{
    this->m_trans.setsource2(source);
    return;
}

void etat::setdestination(string destination)
{
    this->m_trans.setdestination2(destination);
    return;
}

void etat::setcaractere(string caractere)
{
    this->m_trans.setcaractere2(caractere);
    return;
}

void etat::settrans(transition trans)
{
    this->settrans1(trans.getsource());
    this->settrans2(trans.getdesti());
    this->settrans3(trans.getcarac());
    return;
}

ostream& operator<<(ostream& flux, etat& state)
{

    string source(state.getsource());
    string destination(state.getdesti());
    string caractere(state.getcarac());
    for(int i =0; i< source.size(); i++)
    {
        if(source[i] == '0')
        {
            source[i] = state.m_nom+48; //quand c'est à 0, ça signifie qu'il s'agit du nom de l'état lui-même
        }
    }
    for(int i =0; i< destination.size(); i++)
    {
        if(destination[i] == '0')
        {
            destination[i] = state.m_nom+1+48;
        }
    }
    for(int i =0; i<source.size(); i++)
    {
        if(source[i] == state.m_nom+48)
        {
            flux << source[i]<< caractere[i]<< destination[i] << ",";
        }

    }
    return flux;
}
