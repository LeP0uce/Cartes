#include "le_jeu.h"
#include "Joueur.h"
#include "sp_cartes.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
int CarteMAX = 20;
// reserve un vecteur d’objets Carte, représentant la liste des cartes
// disponibles pour la création des piles de chaque joueur. joueur1 et joueur2
// de la classe Joueur représentant les deux joueurs participant au jeu.

// constructeur par defaut du jeu
Jeu::Jeu() {
  _reserve = {};
  _joueur1 = Joueur();
  _joueur2 = Joueur();
}

// constructeur du jeu
Jeu::Jeu(const string &chemin, const Joueur &j1, const Joueur &j2) {
  _reserve = {};
  _joueur1 = j1;
  _joueur2 = j2;
}

// permet de remplir une "Carte" à partir d'un fichier de données et de l'ajouter dans la reserve 
void Jeu::reserve(const string &chemin) {
  Carte c1;
  ifstream fichier(chemin);
  string ligne = "";
  while (getline(fichier, ligne)) {
    c1.remplir(ligne);
    _reserve.push_back(c1);
  }
  fichier.close();
}

// permet de remplir 20 cartes depuis un indice donnée (ligne du fichier)
void Jeu::remplirTotCarte(Joueur& joueur, string ligne) {
  Carte carte;
  for (int i = 0; i < CarteMAX ; i++) {
        carte.remplir(ligne);
    }
}


// Tri les cartes dans l'ordre alphabétique grâce à un tri par insertion.
// Au passage, on met en majuscule le nom des cartes.
void Jeu::insertion() {
  Carte c1;
  int i = _reserve.size() - 1;
  string nomC1 = _reserve[i].nomCarte();
  string nomC2 = _reserve[i - 1].nomCarte();
  while (i > 0 && toupper(nomC1[0]) < toupper(nomC2[0])) {
    c1 = _reserve[i];
    _reserve[i] = _reserve[i - 1];
    _reserve[i - 1] = c1;
    i--;
    nomC1 = _reserve[i].nomCarte();
    nomC2 = _reserve[i - 1].nomCarte();
  }
}


//retourne un boolen vrai si la partie n'est pas fini
bool Jeu::partieFini() {
  return (!(_joueur1.JoueToujours() && _joueur2.JoueToujours() &&
            _joueur1.prestigePositif() && _joueur2.prestigePositif()));
}

//return un entier selon qui est gagant de la partie
int Jeu::VainqueurPartie() {
  if (_joueur1.sonPrestige() > _joueur2.sonPrestige()) {
    return 1;
  } else if (_joueur1.sonPrestige() < _joueur2.sonPrestige()) {
    return -1;
  } else {
    return 0;
  }
}

//distribue les cartes des joueurs selon le choix de le tri du joueur
void Jeu::distribuerCartes(int choix, vector<int> &rangCarte) {
  cout << "Quel rangement veut le joueur " << _joueur1.sonNom() << endl;
  _joueur1.choisirRangement(_reserve, rangCarte);
  cout << endl;

  int alea = 0;
  do{
    cout << "Voulez vous mélanger aleatoirement vos cartes ? (1 pour oui et 2 pour non)"<< endl;
    cin >> alea;
    cout << endl;
  }while(alea != 1 && alea != 2);
  if (alea == 1)
    _joueur1.melangePileAlea();

  if (choix == 1) {
    cout << "Quel rangement veut le joueur " << _joueur2.sonNom() << endl;
    _joueur2.choisirRangement(_reserve, rangCarte);
    cout << endl;

    alea = 0;
    do{
      cout << "Voulez vous mélanger aleatoirement vos cartes ? (1 pour oui et 2 pour non)"<< endl;
      cin >> alea;
      cout << endl;
    }while(alea != 1 && alea != 2);
    if (alea == 1)
      _joueur2.melangePileAlea();
  } else {
    _joueur2.remplirPile(_reserve, rangCarte, choix);
    _joueur2.melangePileAlea();
  }

  cout << "\nLes cartes ont bien été distribuées" << endl;
}

//permet de faire jouer les joueurs
void Jeu::joueurJoue() {
  _joueur1.jouentUneCarte(_joueur2);
  cout<<endl;
  _joueur1.affichage();
  _joueur2.affichage();
}

//renvoie la taille de la reserve
int Jeu::tailleReserve()const {
  return _reserve.size();
}

vector<Carte> Jeu::CarteReserve(){
  for(int i = 0; i<_reserve.size();i++){
    return _reserve;
  }
}

// donne les infos du joueur (son nom, sa vie, son nombre de carte dans sa reserve)
void Jeu::affichageReserve() const {
  cout << "Le joueur " << _joueur1.sonNom() << " a " << _joueur1.sonPrestige()
       << " points de prestige, il lui reste " << _reserve.size()
       << " cartes dans sa reserve." << endl;
  cout<<endl;
  cout << "Le joueur " << _joueur2.sonNom() << " a " << _joueur2.sonPrestige()
       << " points de prestige, il lui reste " << _reserve.size() 
    << " cartes dans sa reserve." << endl;
}

void Jeu::afficheRegle()const{
  cout<<"Voici les regles du jeu :"<<endl;
  cout<<"Le jeu consiste en l'affrontement de deux joueurs tres prestigieux (ils ont 25 points de prestige) chacun muni d'une pile de 20 cartes selectionnees a partir d'une reserve identique. Chaque carte a trois statistiques : une valeur d'attaque physique, une valeur de puissance magique et une valeur de defense physique. L'objectif est de reduire les points de prestige de son adversaire et de defendre les siens. Le vainqueur est le premier a envoyer son adversaire dans la boue (prestige a zero) ou d'avoir plus de prestige que son adversaire a la fin de l'affrontement (lorsqu'il n'y a plus de carte ou lorsque les deux joueurs sont dans le negatif).\n Dans un premier temps chaque joueur classe ses cartes dans l'ordre de son choix. Ensuite, on fait defiler les cartes, une carte de chaque joueur a la fois simultanement, comme a la bataille. Les cartes de chaque joueur sont comparees et des degats sont infliges au prestige de chacun. Les attaques se confrontent aux defenses et les magies se confrontent entre elles.\n"<<endl;
}