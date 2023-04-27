#ifndef LE_JEU_H_INCLUDED
#define LE_JEU_H_INCLUDED

#include "Joueur.h"
#include "sp_cartes.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Jeu {
  //les parametres d'une partie/jeu de la class Jeu
  vector<Carte> _reserve;
  Joueur _joueur1;
  Joueur _joueur2;

public:
  //constructeur vide
  Jeu();
  //constructeur parametré
  Jeu(const string &chemin, const Joueur &j1, const Joueur &j2);

  void reserve(const string &chemin);
  void insertion();
  bool partieFini();
  int VainqueurPartie();
  void distribuerCartes(int choix,vector<int> &rangCarte);
  void joueurJoue();
  void remplirTotCarte(Joueur& joueur, string ligne);
  void remplirDeckCarte(Joueur& joueur, string ligne);
  int tailleReserve()const;
  vector<Carte> CarteReserve();
  void affichageReserve() const;
  void affichageInfoCarte() const;
  void afficheRegle()const;
};

#endif // LE_JEU_H_INCLUDED