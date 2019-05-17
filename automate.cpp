#include "automate.h"
#include <limits>

automate::automate() : m_state(), m_alphabet()
{

}
automate::automate(vector <etat> state, vector <char> alphabet) : m_state(state), m_alphabet(alphabet)
{

}

string automate::getalphabet()
{
    string alphabet;
    for(int i=0; i<(int)this->m_alphabet.size(); i++)
    {
        alphabet += this->m_alphabet[i];
    }
    return alphabet;
}

char automate::getalphabet1(int nombre) //avoir l'alphabet de l'automate
{
    return this->m_alphabet[nombre];
}

int automate::getnometat(int numetat) //avoir le nom de l'�tat
{
    return this->m_state[numetat].getnom();
}

int automate::getinitial(int numetat)
{
    if(this->m_state[numetat].gettype() == 1 || this->m_state[numetat].gettype() == 3)
    {
        int a(this->m_state[numetat].getnom());
        return a;
    }
    return 0;
}

int automate::getterminal(int nometat)
{
    if(this->m_state[nometat].gettype() == 2 || this->m_state[nometat].gettype() == 3 )
    {
        int a(this->m_state[nometat].getnom());
        return a;
    }
    return 0;
}

etat automate::getetat(int nom)
{
    return this->m_state[nom-1];
}

void automate::setetat(int nom)
{
    etat state(nom,0);
    this->m_state.push_back(state);
    return;
}

void automate::setalphabet(char caractere)
{
    this->m_alphabet.push_back(caractere);
    return;
}

void automate::settransition1(int nometat, int etatdestination)
{
    char a;
    string b;
    a = nometat+48;
    b = a;
    this->m_state[etatdestination-1].settrans1(b); //car le nom de l'�tat ne sera jamais �gal � 0, donc l'�tat 1 est � la position 0 etc
    return;
}

void automate::settransition2(int nometat, int etatdestination)
{
    char a;
    string b;
    a = (etatdestination+48);
    b = a;
    this->m_state[nometat-1].settrans2(b);
    return;
}

void automate::settransition3(int nometat,char b)
{
    string a;
    a = b;
    this->m_state[nometat-1].settrans3(a);
    return;
}

int automate::nbetat()
{
    return this->m_state.size();
}

void automate::setinitial(int nometat)
{
    this->m_state[nometat-1].settype(1); //-1 car un �tat est >= 1 et ils sont rang�s dans l'ordre
    return;
}

void automate::setterminal(int nometat)
{
    this->m_state[nometat-1].settype(2);
    return;
}

void automate::setiniterm(int nometat)
{
    this->m_state[nometat-1].settype(3);
    return;
}

string automate::getsource(int numetat)
{
    return this->m_state[numetat-1].getsource();
}
string automate::getdestination(int numetat)
{
    return this->m_state[numetat-1].getdesti();
}
string automate::getcaractere(int numetat)
{
    return this->m_state[numetat-1].getcarac();
}

string automate::getdetail()
{
    return this->detailautomate;
}
void automate::setdetail(string ligne)
{
    this->detailautomate = ligne;
    return;
}

int automate::getnbinitial()
{
    int cpt(0);
    for(int i=0; i< this->nbetat(); i++)
    {
        if (this->getinitial(i) != false)
        {
            cpt++;
        }
    }
    return cpt;
}

int automate::gettype(int numetat)
{
    return this->m_state[numetat-1].gettype();
}



void lecturedir()
{
    DIR* rep(NULL);
    struct dirent* fichier(NULL); //le typedef n'a pas �t� mis pour cette strucutre, pas besoin de r��crire struct dirent, dirent suffit
    rep = opendir("..");
    if (rep == NULL) // impossible d'ouvrir le dossier
    {
        cout << "Le dossier n'existe pas" << endl;
        exit(1);
    }
    while( (fichier = readdir(rep) ) != NULL) //readdir(rep) est une instruction qui lit la ligne o� se trouve le curseur, puis elle va sur la ligne suivante
    {
        if(strcmp(fichier->d_name, ".") != 0 && strcmp(fichier->d_name, "..") != 0 )
        printf("Le fichier lu s'appelle '%s'\n", fichier->d_name);
    }
    cout << endl;
    if (closedir(rep) == -1) //le dossier ne se ferme pas
    {
        cout << "Erreur fermeture" << endl;
        exit(-1);
    }
}

automate lectureautomate(string nom_fichier, automate &projet)
{
    ifstream fichier(nom_fichier.c_str(), ios::in); //ouverture du fichier en lecture, comme la fonction ne supporte pas les string, on appelle la m�thode c_str()
    string ligne;
    //automate projet;

    if (fichier)
    {
        string ligne;
        string rentree;
        int numautomate(0); //choisir l'automate

        //besoin de fonction s�curit� pour le num�ro
        cout << "Choisissez l'automate " << endl;
        numautomate = saisiesecu(numautomate); //la fonction ne fait que v�rifier s'il s'agit d'un nombre

        //lecture du fichier texte
        while(fichier.tellg() != -1)
        {
            getline(fichier,ligne);
            projet = ecritureautomate(nom_fichier,ligne,numautomate,projet);
        }
    }
    else
    {
        cout << "erreur pour ouvrir le fichier" << endl;
        exit(1);
    }
    fichier.close(); //fermeture du fichier
    return projet;
}
automate ecritureautomate(string nom_fichier, string ligne, int numautomate, automate &projet)
{
    fstream temp("./test.txt", ios::out | ios::trunc); //ouverture du fichier test avec �crasement (effacement des donn�es ult�rieures), on met sur la premi�re ligne de test.txt l'automate que l'on traite
    string rentree;
    //automate projet;
    etat test;
    int castint(0); //pour transf�rer un char vers un int
    int compteur(0);
    int compteur2(0);
    //int alphabet(0);
    vector <etat>::iterator it(NULL);


    if(temp)
    {
        temp << ligne << endl; //on �crit le string ligne dans le fichier test
        temp.close(); //fermeture du fichier en mode �criture

        temp.open("./test.txt", ios::in); //ouverture en mode lecture du fichier test.txt
        temp.seekg(0,ios::beg); //on place le curseur au d�but du fichier

        temp >> rentree; //on met les premiers caract�res dans le string rentree
        rentree[rentree.size()-1] = ' '; //c'est pour virer le point
        if ( atoi(rentree.c_str()) == numautomate ) //s�lectionne la ligne qui commence par le nombre choisi
        {
            //cout << ligne << endl;
            projet.setdetail(ligne);

            //on rentre l'alphabet A
            temp>> rentree;
            for( compteur = 2; compteur < (int)rentree.size(); compteur++) //on commence � deux car on ignore le A=
            {
                if(rentree[compteur] != ',') //on retire les virgules
                projet.setalphabet(rentree[compteur]);
            }
            //fin du setalphabet

            //set des etats Q
            temp >> rentree; //cout << rentree << endl;
            for( compteur = 2; compteur < (int)rentree.size(); compteur++)
            {
                if(rentree[compteur] != ',')
                {
                    projet.setetat( rentree[compteur] - 48 );
                }

            }
            //fin des set etats

            //attribution de l'�tat initial
            temp >> rentree;
            for(compteur = 0; compteur < projet.nbetat(); compteur++) //parcours des �tats
            {
                for(compteur2 = 2; compteur2 < (int)rentree.size(); compteur2++) //parcours des caract�res dans rentree
                {
                    if ( (rentree[compteur2] != ',') && (projet.getnometat(compteur) == (rentree[compteur2] - 48) ) )
                    {

                        castint = (rentree[compteur2] - 48); //attention, il nous pondra des 1234..., comme on a rang� les �tats par ordre num�rique,
                                                             //le 1 sera � la case 0, d'o� le -1 dans automate::setinitial
                        projet.setinitial(castint);

                    }
                }
            }

            castint= 0; //reset de la variable int
            // fin attribution etat initial

            //attribution des etats terminaux
            temp >> rentree;
            for(compteur = 0; compteur < projet.nbetat(); compteur++) //parcours des �tats
            {
                for(compteur2 = 2; compteur2 < (int)rentree.size(); compteur2++) //parcours des caract�res dans rentree
                {
                    if ( (rentree[compteur2] != ',') && (projet.getnometat(compteur) == (rentree[compteur2] - 48) ) && (projet.gettype(rentree[compteur2] - 48) != 1) )
                    {

                        castint = (rentree[compteur2] - 48); //attention, il nous pondra des 1234..., comme on a rang� les �tats par ordre num�rique,
                                                             //le 1 sera � la case 0, d'o� le -1 dans automate::setinitial
                        projet.setterminal(castint);


                    }
                    else if( (rentree[compteur2] != ',') && (projet.getnometat(compteur) == (rentree[compteur2] - 48) ) ) //l'�tat est terminal et initial
                    {
                        castint = rentree[compteur2] -48;
                        projet.setiniterm(castint);
                    }
                }
            }

            castint = 0; //reset de la variable
            //fin attribution des etats terminaux

            //attribution des transitions
            temp >> rentree;
            bool indice(0); //pour identifier quand on est sur l'�tat �metteur
            for(compteur = 2; compteur < (int)rentree.size(); compteur++)
            {
                if(compteur%2 == 0)
                {
                    castint = rentree[compteur];
                    compteur2 = 0;
                    //cout << rentree[compteur] << " ";
                    while( (rentree[compteur] != (projet.getnometat(compteur2) +48 ) ) && (projet.nbetat() > compteur2) ) //recherche de l'�tat
                    {
                        compteur2++; //on a l'indice pour retrouver l'�tat dans l'automate
                    }

                    if( (indice == 1) && (compteur2 < projet.nbetat()) ) //si l'�tat est trouv� et qu'il s'agit d'un �tat destination
                    {
                        if ( rentree[compteur] != rentree[compteur-2]) //pour mettre un 0 dans les transitions dans l'�tat source
                                                                       //dans sa destination, puisque qu'on trie les transitions sur des indices d'un string
                        {
                            projet.settransition1(0,(rentree[compteur-2] - 48)); //on met 0 dans la source de la transition puisque c'est l'�tat qui en est la source,
                                                                                // si source = destination, le probl�me sera r�gl� dans le else
                            projet.settransition2(rentree[compteur]-48,0);

                        }
                        else //si l'�tat pointe sur lui-m�me, on mettra le char du string m_destination � 0
                        {

                        }
                        projet.settransition1((rentree[compteur-2]-48),projet.getnometat(compteur2)); //on met l'�tat destination en source, la transition est source pour cet �tat
                                                                                                    //r�glement du probl�me du if au-dessus
                    }
                    else if( (indice == 0) && (compteur2 < projet.nbetat()) ) //si l'�tat est trouv� et qu'il s'agit d'un �tat source
                    {
                        indice = 1;
                        projet.settransition2(rentree[compteur]-48,rentree[compteur+2]-48);
                    }
                }
                else if (rentree[compteur] == ',') //changer de transition
                {
                    indice = 0; //reset de l'indice, pour avoir un nouvel �tat �metteur
                }
                else //introduire le caract�re, indice sera �gal � 1, compteur2 sera �gal � l'indice de l'�tat destination
                {
                    if(rentree[compteur-1] != rentree[compteur+1])
                    {
                        projet.settransition3(rentree[compteur-1]-48,rentree[compteur]);
                        projet.settransition3(rentree[compteur+1]-48,rentree[compteur]);
                    }
                    else
                    {
                        projet.settransition3(rentree[compteur-1]-48,rentree[compteur]);
                    }
                }

                compteur2 = 0;
            }
        }
        else //si le cast en marche pas ou l'automate n'existe pas
        {
        }


        //temp >> rentree >> rentree; //instruction pour avoir le troisi�me groupe de caract�re, peut se modifier
        //temp.seekg(temp.tellg(),ios::beg); //emp�che d'avoir l'espace qui suit le groupe de caract�re pr�c�dent

        //instructions pour attribuer les noms d'�tat
    }
    else
    {
        cout << "erreur pour ouvrir le fichier" << endl;
        exit(1);
    }
    temp.close();
    return projet;


}

int saisiesecu(int &N )
{
    while ( ! (cin >> N) )
    {
        if (cin.eof())
        {
            return false;
        }
        else if ( cin.fail())
        {
            cout << "Donnez un nombre !" << endl;
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(),'\n');
        }
    }
    return N;
}
int saisiesecu(int &N, int sup, int inf)
{
    while ( ! (cin >> N) || (( N < inf) || (N > sup)) )
    {
        if (cin.eof())
        {
            return false;
        }
        else if ( cin.fail())
        {
            system("cls");
            cout << "Choisissez un nombre entre " << inf << "et " << sup << endl;
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(),'\n');
            cout << "Nombre : ";
        }
        else
        {
            system("cls");
            cout << "Choisissez un nombre entre " << inf << "et " << sup << endl;
            cout <<"Nombre : ";

        }
    }
    return true;
}

bool automate::est_un_automate_Standard()//
{
    int nbentrees(0);
    int identree(0);

    for(int i = 0; i < this->nbetat(); i++)
    {
        if(m_state[i].gettype() == 1 || m_state[i].gettype() == 3)//Etat initial et etat initial/terminal
        {
            nbentrees++;
        }
    }
    if(nbentrees > 1)
    {
        cout << "Automate non-standard. Il y a plus d'un etat initial" << endl;
        return false;

    }
    //size_t recherche; //type donn� par cstddef
    for(int i = 0; i < this->nbetat(); i++)//On v�rifie les transitions
    {
        for (int cpt=0; cpt < (int)this->m_state[i].getdesti().size(); cpt++)
        {
            if (this->m_state[i].getdesti()[cpt] == '1')
            {
                cout << "Automate non-standard car une transition envoie vers l'etat initial" << endl;
                return false;
            }
        }
    }
    cout << "Automate standard" << endl;
    return true;
}

bool automate::est_un_automate_Determine()
{
    //compter nbetat initial
    int nbentrees(0);
    for(int i = 0; i < this->nbetat(); i++)
    {
        if(m_state[i].gettype() == 1 || m_state[i].gettype() == 3)//Etat initial et etat initial/terminal
        {
            nbentrees++;
        }
    }
    if(nbentrees > 1)
    {
        cout << "Automate non-deterministe. Il y a plus d'un etat initial" << endl;
        return false;

    }
    //v�rifier les transitions de caract�res
    nbentrees = 0;
    string source, caractere;
    for(int i =1; i< this->nbetat()+1; i++)
    {
        source = this->getsource(i); //on prend la cha�ne du nom de l'�tat qui rentre dans l'�tat, si c'est 0 ou l'�tat, il s'agit d'une transition qui part de l'�tat et donc on v�rifie le caractere
        caractere = this->getcaractere(i); //on prend tous les caracteres des transitions qui sont impliqu�es avec l'�tat
        if(i > 0)
        {
            for(int j=0; j< (int)source.size(); j++)
            {
               for(int k=1; k< (int)source.size(); k++)
               {
                   if (j!=k && caractere[j] == caractere[k]&& ((source[j] == '0' || source[j] == i+48)&& (source[k] == '0' || source[k] == i+48)) )
                   {//on compare le caractere d'une transition si elle part de l'�tat avec les autres caracteres
                       cout << "Non-deterministe. Des caracteres ont ete reutilises dans des transitions de l'etat "<< i << endl;
                       return false;
                   }
               }
            }
        }
    }
    cout << "automate deterministe" << endl;
    return true;
}

bool automate::est_un_automate_Complet()
{
    string source,caractere,recherche;
    for(int i =1; i< this->nbetat()+1; i++)
    {
        source = this->getsource(i); //on prend la cha�ne le nom de l'�tat qui rentre dans l'�tat, si c'est 0 ou l'�tat, il s'agit d'une transition qui part de l'�tat et donc on v�rifie le caractere
        caractere = this->getcaractere(i); //on prend tous les caracteres des transitions qui sont impliqu�es avec l'�tat
        if(i > 0)
        {
            for(int j=0; j< (int)source.size(); j++)//chercher dans le string si source = i ou 0, mettre dans le string le caract�re
            {
               if (source[j] == '0' || source[j] == i+48)
               {
                   if(caractere[j] == 'E')
                   {
                       cout << "Aucune transition utilisant un caractere de l'alphabet" << endl;
                       return false;
                   }
                   recherche += caractere[j]; //contiendra tous les caract�res des transitions provenant de l'�tat
               }
            }
        }
        if(this->complet(recherche) == false)
        {
            cout << i << " par exemple." << endl; //complete le message de fin de la fonction complet()
            return false;
        }
        recherche.resize(0);
    }
    cout << "Automate complet" << endl;
    return true;
}

bool automate::complet(string recherche) //v�rifie dans le string si tous les caract�res de l'alphabet sont utilis�s
{
    if(recherche.size() < this->m_alphabet.size())
    {//on regarde le nb de caractere si il n'est pas d�j� inf�rieur au nb de l'alphabet
        cout << "Automate non-complet, pas assez de transition donc tous les caracteres ne sont pas utilises pour l'etat ";
        return false;
    }
    for(int i =0; i<(int)recherche.size(); i++) //on retire tous caracteres similaires
    {
        for (int j =1; j<(int)recherche.size(); j++)
        {
            if(recherche[i] == recherche[j] && i!=j)
            {
                for(int k=j; k<(int)recherche.size()-1; k++)
                {
                    recherche[k] = recherche[k+1];
                }
                recherche.resize(recherche.size()-1);
            }
        }
    }
    if(recherche.size() < this->m_alphabet.size()) //apr�s avoir retir� la redondance de caractere,
                                                    //on compte pour voir le nb de caractere differents
    {
        cout << "Automate non-complet, tous les caracteres ne sont pas utilises pour l'etat " << endl;
        return false;
    }
    return true;
}

void automate::standardiser()
{
    string initial;
    string source, destination,caractere;
    string source2,destination2,caractere2;
    etat nouveletat;
    bool etatterminal(0); //permet de voir si un �tat initial de l'automate est aussi terminal
    for(int i =0; i < this->nbetat(); i++)
    {
        if(this->gettype(i+1) == 1 || this->gettype(i+1) == 3) //si il s'agit d'un �tat initial
        {
            source = this->getsource(i+1);
            destination = this->getdestination(i+1);
            caractere = this->getcaractere(i+1);

            for(int j=0; j<(int)source.size(); j++) //on regarde les �tats o� il se renvoie � lui-m�me la transition
            {
                if((source[j] == '0' && destination[j] != '0') || source[j] == (i+48+1) )
                {
                    if(source[j] == (i+48+1)) //si le caract�re est �gal au nom de l'�tat
                    {
                        source2 += source[j]+1;
                        destination2 += destination[j]+1;
                        caractere2 += caractere[j]+1;
                    }

                    else
                    {
                        source2 += source[j];
                        destination2 += destination[j];
                        caractere2 += caractere[j];
                    }

                }
            }

        }
    }
    nouveletat.setsource(source2);
    nouveletat.setdestination(destination2);
    nouveletat.setcaractere(caractere2);
    source.resize(0); destination.resize(0); //recyclage des variables
    for(int i =0; i < this->nbetat(); i++)
    {
        //d�terminer le type de l'�tat  initial
        if(this->gettype(i+1) == 1 || this->gettype(i+1) == 3) //si initial ou initialterminal
        {
            if(this->m_state[i].gettype() == 1) //si initial, il devient un �tat banal
            {
                this->m_state[i].settype(0);
            }
            else //si il �tait initial et terminal, on le transforme en terminal
            {
                this->m_state[i].settype(2);
                etatterminal = 1;
            }
            initial += (this->m_state[i].getnom() -48); //on r�cup�re les noms des �tats dans le string qui sont initiaux
        }
        if(etatterminal == 1)
        {
            nouveletat.settype(3);
        }
        else
        {
            nouveletat.settype(1);
        }
        //on prend les sources, destination... de l'�tat pour changer les noms des transitions, le 1 devient 2, 2 devient 3 etc
        source = this->getsource(i+1); //+1 car le param�tre prend le nom de l'�tat et pas l'indice qu'il a
        destination = this->getdestination(i+1);
        for(int j=0; j < (int)source.size(); j++) //on incr�mente tous les caract�res � 1
        {
            if(source[j] != '0') //si la transition part de lui et ne revient pas sur lui
            {
                source[j] += 1;
            }//si la transition revient vers lui, on laisse 0
        }
        for(int j=0; j < (int)destination.size(); j++)
        {
            if(destination[j] != '0')
            {
                destination[j] += 1;
            }
        }
        this->m_state[i].setsource(source); //on remplace les string m_source et m_destination des �tats
        this->m_state[i].setdestination(destination);
        source.resize(0); destination.resize(0);
    }
    //d�placer les caracteres dans les string source, destination et caract�re, on placera l'�tat initial en premier caract�re
    //on a r�cup�r� les �tats initiaux dans initial, il faudra les comparer au nom de m_state pour obtenir leurs transitions
    nouveletat.setnom(1); //�tat initial toujours premier
    if(etatterminal == 1)
    {
        nouveletat.settype(3); //on le met en initial et terminal car il y a un �tat initial qui �tait aussi sortie
    }
    else
    {
        nouveletat.settype(1); //on le met en initial
    }



    //r�cup�rer en un string les sources et destinations des �tats initiaux

    //

    //this->m_state.push_back(nouveletat); //on cr�e une nouvelle case dans m_state pour mettre l'�tat, on s'en fiche qu'il soit pos� � la derni�re case, on le replacera dans la premi�re case
    for(int i=0; i<(int)this->m_state.size(); i++) //je vais du premier etat � l'avant dernier
    {
        this->m_state[i].setnom(this->m_state[i].getnom()+1); //j'incr�mente de 1 le nom de l'�tat (le 1 devient 2 etc...)
    }

    //ce code permet de rajouter au d�but un etat � la premi�re place du vecteur, �a �viter de d�caler avec une it�ration
    vector <etat>::iterator it;
    it = this->m_state.begin();
    it = this->m_state.insert(it,nouveletat);
    //

    //ne pas oublier d'incr�menter les �tats sources destination du nouvel �tat car il a litt�ralement re�u les �tats sorties de l'ancien premier �tat
    destination = this->getdestination(1);
    for(int i =0; i<(int)destination.size() ; i++)
    {
        if(destination[i] != '0')
        {
                destination[i] += 1;
        }
    }
    this->m_state[0].setdestination(destination);
    //

    return;
}

void automate::completer()
{
    string source,caractere,recherche;
    int condition(0); //si = 0, d�j� complet, 1 : aucune transition utilise l'�tat de l'alphabet
    etat state;
    string test;
    for(int i =1; i< this->nbetat()+1; i++) //on parcours tous les �tats, +1 car les fonction get ont besoin du vrai nom de l'�tat
    {
        source = this->getsource(i); //on prend la cha�ne le nom de l'�tat qui rentre dans l'�tat, si c'est 0 ou l'�tat, il s'agit d'une transition qui part de l'�tat et donc on v�rifie le caractere
        caractere = this->getcaractere(i); //on prend tous les caracteres des transitions qui sont impliqu�es avec l'�tat
        if(i > 0)
        {
            for(int j=0; j< (int)source.size(); j++)//chercher dans le string si source = i ou 0, mettre dans le string le caract�re
            {
               if (source[j] == '0' || source[j] == i+48)
               {
                   if(caractere[j] == 'E')
                   {
                       //automate 1, cas particulier o� l'�tat espilon renvoie � lui m�me
                       this->m_state[0].settrans1("0");
                       this->m_state[0].settrans2("P");
                       this->m_state[0].settrans3("a");
                   }
                   recherche += caractere[j]; //contiendra tous les caract�res des transitions provenant de l'�tat
               }
            }
        }
        if(this->complet(recherche) == false)
        {
            cout << i << endl; //complete le message de fin de la fonction complet()
            this->completion(i); //on envoie l'�tat pour le compl�ter

        }
        recherche.resize(0);
    }
    //cout << this->getcaractere(1) << endl;
    return;
}

void automate::completion(int numetat)
{
    int compteur(0);
    int nbalphabet(0);
    string poubelle3; poubelle3[0] = (this->m_state[numetat-1].getcarac()[0]);
    string caracpoubelle;
    string test;

//si l'�tat n'a aucune transition sortante
        for(int i =0; i<(int)this->m_state[numetat-1].getsource().size(); i++)
        {
            if(this->m_state[numetat-1].getsource()[i] == '0')
            {
                compteur++;
            }
        }

        if(compteur == 0)
        {
            for(int j=0; j<(int)this->m_alphabet.size(); j++) //on parcours l'alphabet et on ajoute des transitions par caracteres
            {
                this->m_state[numetat-1].settrans1("0"); //m_source+=
                this->m_state[numetat-1].settrans2("P"); //m_destination+=
                caracpoubelle = m_alphabet[j]; //pas besoin de faire resize(0) puisqu'on mettra toujours un seul caractere
                this->m_state[numetat-1].settrans3(caracpoubelle); //m_caractere+=
            }
            return; //on sort pour �viter divers probl�mes en dessous
        }
//
        else
        {
            if(compteur < (int)this->m_alphabet.size()) //si on a moins de transition sortante que de lettres
            {
                compteur = 0;
                for(int i=0; i<(int)this->m_alphabet.size(); i++)
                {
                    for(int j=0; j<(int)this->m_state[numetat-1].getcarac().size(); j++)
                    {
                        if ( compteur == 0 &&( this->m_state[numetat-1].getsource()[j] == '0' ||this->m_state[numetat-1].getsource()[j] == (numetat+48) ) && this->m_state[numetat-1].getcarac()[j] == this->m_alphabet[i])
                        {
                            compteur = 1; //condition pour avertir que l'on ne cr�e pas de transition puisque l'on a rencontr� au moins 1 caractere = � celui de l'alphabet
                        }
                    }
                    if(compteur == 0)
                    {
                        this->m_state[numetat-1].settrans1("0"); //m_source+=
                        this->m_state[numetat-1].settrans2("P"); //m_destination+=
                        caracpoubelle = m_alphabet[i]; //pas besoin de faire resize(0) puisqu'on mettra toujours un seul caractere
                        this->m_state[numetat-1].settrans3(caracpoubelle); //m_caractere+=
                    }
                    compteur = 0;
                }
                return;
            }
            compteur = 0;
            for(int i=0; i<(int)this->m_alphabet.size(); i++)
            {
                for(int j=0; j<(int)this->m_state[numetat-1].getcarac().size(); j++)
                {
                    if ( compteur == 0 &&( this->m_state[numetat-1].getcarac()[j] == '0' ||this->m_state[numetat-1].getcarac()[j] == (numetat+48) ) && this->m_state[numetat-1].getcarac()[j] == this->m_alphabet[i])
                    {
                        compteur = 1; //condition pour avertir que l'on ne cr�e pas de transition puisque l'on a rencontr� au moins 1 caractere = � celui de l'alphabet
                    }
                }
                if(compteur == 1)
                {
                    this->m_state[numetat-1].settrans1("0"); //m_source+=
                    this->m_state[numetat-1].settrans2("P"); //m_destination+=
                    caracpoubelle = m_alphabet[i]; //pas besoin de faire resize(0) puisqu'on mettra toujours un seul caractere
                    this->m_state[numetat-1].settrans3(caracpoubelle); //m_caractere+=
                }
                compteur = 0;
            }
            return;
        }
//on sort si l'�tat n'avait aucune transition sortante

        compteur = 0;

//on se balade dans toutes les transitions de l'�tat, faire attention � rester dans les transitions sortantes de l'�tat
        for(int i=1; i<(int)this->getcaractere(numetat).size(); i++) //getsource a besoin du vrai nom de l'�tat
        {
            if(this->m_state[numetat-1].getcarac()[0] != this->m_state[numetat-1].getcarac()[i] && (this->getcaractere(numetat)[0] == '0'||this->getcaractere(numetat)[0] == (numetat+48)  ) && (this->getcaractere(numetat)[i-1] == '0' || (numetat+48) == this->getcaractere(numetat)[i-1]))
//on aura le vrai nom de l'�tat dans les param�tres
//=='0' ou numetat+48 (conversion en char) pour v�rifier qu'il s'agit bien d'une transition sortante
//[i-1] idem que pr�c�demment
            {
                compteur++;
                poubelle3+= this->m_state[numetat-1].getcarac()[i];
            }
//la boucle continue jusqu'� ce qu'on ait fait toutes les transitions de l'�tat
//compteur s'incr�mente � chaque fois qu'on trouve un caractere diff�rent pour une transition sortante de l'�tat

        }


    return;
}
/*
bool automate::lecturemot(string mot)
{
    vector <int> initial;
    int etatsuivant;
    for(int i =0; i < this->m_state.size(); i++) //recherche �tat initial
    {
        if (this->m_state[m_state.size()-1-i].gettype() == 1 || this->m_state[m_state.size()-1-i].gettype() == 3)
        {
            initial.push_back(this->m_state[i].getnom());
        }
    }
    if(initial.size() == 0)
    {
        cout << "pas d'etat initial" << endl;
        return false;
    }
    int j(0), compteur(0);
    for(int i=0; i< initial.size(); i++)
    {

        etatsuivant = initial[i]; //nom de l'�tat, faire -1 en utilisant dans vecteur
        do
        {
            j=0;
            if( (this->getsource(etatsuivant)[j] == '0' ||this->getsource(etatsuivant)[j] == initial[i] -1 +48 ) && this->getcaractere(etatsuivant)[j] == mot[compteur] )
            {
                etatsuivant = this->getdestination(etatsuivant)[j]-48; //on met l'�tat destination comme nouvel �tat � comparer
            }
            else
            {
                j++;
            }
        }while(this->getsource(initial[i]).size()-1 != j && compteur != mot.size()-1); //on sort dans la boucle quand on a atteint le dernier caractere du mot
        //et que le compteur j a atteint la derni�re transition
        if(compteur == mot.size()-1 && (this->m_state(etatsuivant-1).gettype() == 2 || this->m_state(etatsuivant-1).gettype() == 3) )
        {
            return true; //on a navigu� � travers tous le mot
        }
        compteur = 0;
    }
    return false;
}
*/

ostream& operator<<(ostream &flux, automate & projet)
{
    flux << "I=";
    for(int i =0; i<projet.nbetat(); i++)
    {
        if(projet.m_state[i].gettype() == 1 || projet.m_state[i].gettype() == 3)
        {
            flux << projet.m_state[i].getnom() << ",";
        }
    }
    flux << endl;

    flux << "T=";
    for(int i =0; i<projet.nbetat(); i++)
    {
        if(projet.m_state[i].gettype() == 2 || projet.m_state[i].gettype() == 3)
        {
            flux << projet.m_state[i].getnom() << ",";
        }
    }
    flux << endl;
    flux << "E=";
    for(int i =0; i<projet.nbetat(); i++)
    {
        flux << projet.m_state[i];
    }
    flux << endl;

    return flux;
}

