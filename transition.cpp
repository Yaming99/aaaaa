#include "transition.h"

transition::transition(): m_source(""), m_destination(""), m_caractere("")
{

}

transition::transition(string source, string destination, string caractere) : m_source(source), m_destination(destination), m_caractere(caractere)
//pas besoin de valeur par d�faut, les string en ont
{

}

string transition::getsource()
{
    return this->m_source;
}

string transition::getdesti()
{
    return this->m_destination;
}

string transition::getcarac()
{
    return this->m_caractere;
}

int getnbtransition(transition a)
{
    return a.m_source.size(); //nb: source, destination et caract�re ont le m�me nombre d'�l�ments dans les vectors
}
void transition::setsource(string source)
{
    this->m_source += source;
    return;
}

void transition::setdesti(string destination)
{
    this->m_destination += destination;
    return;
}

void transition::setcarac(string caractere)
{
    this->m_caractere += caractere;
    return;
}

char transition::getcarac(int numtrans)
{
    return this->m_caractere[numtrans];
}

char transition::getsource(int numtransition)
{
    return this->m_source[numtransition];
}

int transition::getnbtrans()
{
    return this->m_source.size();
}

void transition::setsource2(string source)
{
    this->m_source = source;
    return;
}

void transition::setdestination2(string destination)
{
    this->m_destination = destination;
    return;
}

void transition::setcaractere2(string caractere)
{
    this->m_caractere = caractere;
    return;
}
