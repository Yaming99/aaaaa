#include "automate.h"
#include <cstddef>

int main()
{
    system("mode con LINES=50 COLS=120");
    string nom_fichier("automates.txt");
    //placer le .exe dans le m��me r��pertoire que les .cpp, .h et le .txt des automates
    vector <automate> projet;
    automate test;
    int choix;
    //projet.getinitial(0);
    //projet.estStandard();
    //projet.estDetermine();
    //projet.estComplet();
    //projet.standardiser();
    //cout << projet.nbetat() << endl;
    //projet.estStandard();
    //cout << projet.getdetail() << endl;
    do
    {
        projet.push_back(test);
        lectureautomate(nom_fichier,projet[0]);
        cout << projet[0].getdetail() << endl << endl;
        choix = 0;
        do
        {
            cout << "Choisissez une option" << endl;
            cout << "1)Verifier l'automate standard" << endl;
            cout << "2)Verifier l'automate determinise" << endl;
            cout << "3)Verifier l'automate complet" << endl;
            cout << "4)Standardiser l'automate" << endl;
            cout << "5)Completer l'automate" << endl;
            cout << "6)Changer d'automate" << endl;
            cout << "7)Quitter" << endl;
            saisiesecu(choix,7,1);
            if(choix == 1)
            {
                cout << projet[0].getdetail() << endl;
                projet[0].est_un_automate_Standard();
                cout << endl;
                cout << projet[0] << endl;
            }
            else if (choix == 2)
            {
                cout << projet[0].getdetail() << endl;
                projet[0].est_un_automate_Determine();
                cout << endl;
                cout << projet[0] << endl;
            }
            else if (choix == 3)
            {
                cout << projet[0].getdetail() << endl;
                projet[0].est_un_automate_Complet();
                cout << endl;
                cout << projet[0] << endl;
            }
            else if (choix == 4)
            {
                cout << projet[0].getdetail() << endl;
                cout << projet[0] << endl;
                if(projet[0].est_un_automate_Standard() == false)
                {
                    cout << endl;
                    projet[0].standardiser();
                    cout << endl;
                    projet[0].est_un_automate_Standard();
                }

                cout << endl;
                cout << projet[0] << endl;
            }
            else if (choix == 5)
            {
                cout << projet[0].getdetail() << endl;
                cout << projet[0] << endl;
                if(projet[0].est_un_automate_Complet() == false);
                {
                    cout << endl;
                    projet[0].completer();
                    cout << endl;
                    projet[0].est_un_automate_Complet();
                }
                cout << endl;
                cout << projet[0] << endl;
            }
            system("Pause");

        }while(choix != 6 && choix != 7);
        projet.resize(0);
    }while(choix != 7);
    system("cls");
    system("Pause");
    return 0;
}
