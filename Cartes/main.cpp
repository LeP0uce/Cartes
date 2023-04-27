#include "Joueur.h"
#include "sp_cartes.h"
#include "le_jeu.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

int main() {

const int PrestigeMax = 25;
const int carteMAX = 20;
vector<string> creaCarte;
vector<Carte> deckCarteJ1;
vector<Carte> deckCarteJ2;
vector<int> rangCarte;
readF("Cartes/cartes.txt", creaCarte);
  
   bool jouer = true;
     while (jouer)
     {
        Jeu partie;
        Joueur j1;
        Joueur j2;
        cout<<endl;
        partie.afficheRegle();
        cout << "Voulez vous jouez avec un autre etre humain ou bien avec un bot ?\n" << endl; //demande au user le mode qu'il souhaite faire
        cout << "Pour 2 joueurs humains, tapez 1" << endl;
        cout << "Pour humain versus bot, tapez 2" << endl;
        int mode;
        cin>>mode; //choix du mode voulu
        while (mode < 1 || mode > 2) //Si ni 1 ni 2 est saisi
        {
            cout<< "\nVeuillez suivre les consignes et entrer 1 ou 2."<<endl;
            cin>>mode;
        }

        if (mode == 1) //Si 1 est choisi (H vs H)
        {
          string nomJ1, nomJ2;
          cout << "\nVeuillez entrer le nom du joueur 1 : " ;
          cin >> nomJ1;
          cout << "\nVeuillez entrer le nom du joueur 2 : " << endl;
          cin >> nomJ2;
          j1 =Joueur(nomJ1,PrestigeMax,deckCarteJ1); // creation du joueur 1
          j2 =Joueur(nomJ2,PrestigeMax,deckCarteJ2); // creation du joueur 2
          cout<<nomJ1<<" VS "<<nomJ2<<endl;
          partie = Jeu({},j1,j2); // creation du jeu
          cout<<endl;
          
        }else if (mode == 2) //Si 2 est choisi (H vs bot)
        {
            cout << "\nVeuillez entrer le nom du joueur 1 : ";
            string nomJ1;
            cin >> nomJ1;
            j1=Joueur(nomJ1,PrestigeMax,deckCarteJ1); // creation du joueur 1
            j2=Joueur("Bot",PrestigeMax,deckCarteJ2); // creation du joueur 2 bot
            cout<<nomJ1<<" VS "<<"Bot"<<endl;
            partie = Jeu({},j1,j2); // creation du jeu
        } 
            cout<<endl;
            partie.reserve("Cartes/cartes.txt"); // creation de la reserve de carte
            partie.insertion();
            partie.affichageReserve();
            cout<<endl;
            partie.distribuerCartes(mode, rangCarte); // distribution des cartes
             cout << endl;
            j1.initialiser(partie.CarteReserve());
            j2.initialiser(partie.CarteReserve());
            if (mode == 2){
              j2.melangePileAlea();
            }
            cout<<"\nVoici le deck de "<<j1.sonNom()<<" : "<<endl;
            j1.afficherPileCarte(); //affiche la pile du joueur 1
            cout<<endl;
            cout<<"\nVoici le deck de "<<j2.sonNom()<<" : "<<endl;
            cout << endl;
            j2.afficherPileCarte(); //affiche la pile du joeueur 2
            cout << "\nle jeu commence!\n" << endl;
            cout<<endl;
            int k = 1;
            while (!partie.partieFini())
              {
              cout << endl<<endl;
              cout << "Tour " << k << endl;
              cout << endl;
              partie.joueurJoue();
              k++;
                }
            if (partie.VainqueurPartie() == 1)
                cout << "\n" << j1.sonNom() << " a gagne" << endl;
            else if (partie.VainqueurPartie() == -1)
                cout << "\n" << j2.sonNom() << " a gagne" << endl;
            else
                cout << "égalité" << endl;

            cout<<endl;
            cout << "\nRejouer ?(1 pour oui et 2 pour non)" << endl;
            int rej;
            cin >> rej;
            while (mode < 1 || mode > 2)
            {
                cout << "Veuillez entrer 1 ou 2" << endl;
                cin >> rej;
            }
            if (rej == 1)
            {
                jouer = true;
            }
            else
            {
                cout << "Fin de la partie" << endl;
                jouer = false;
            }
    }
}