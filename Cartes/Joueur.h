#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "sp_cartes.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Joueur {
  string _nom;
  int _prestige;
  vector<Carte> _pileCarte;

public:
  Joueur();
  Joueur(const string &, int, const vector<Carte>& pileCarte);
  string sonNom() const;
  int sonPrestige() const;
  void affichage() const;
  void carteJouer();
  void afficherPileCarte();
  void initialiser(const vector<Carte>& vc);
  bool JoueToujours();
  bool prestigePositif();
  void carteSuiv(Carte &c);
  void jouentUneCarte(Joueur & joueurPara);
  void melangePileAlea();
  void remplirPileAtk(const vector<Carte> &vecCarte, vector<int>& rangCarte);
  void rangeCarte(const vector<Carte> & vecCarte, vector<int> & rangCarte);
  void ChoixAjoutJoueur(const vector<Carte> & vecCarte);
  void ChoixSiReserveRanger(const vector<Carte> & vecCarte);
  void remplirPile(const vector<Carte> &vecCarte,vector<int> &rangCarte,int choix);
  void choisirRangement(const vector<Carte> &vecCarte,vector<int> &rangCarte);

};

void vecteur_de_rang(const vector<Carte> &vecCarte, vector<int> &rangCarte);
void tri_insertion_decroissant(vector<int> &rangCarte,const vector<int>& vecCarte);
void tri_insertion_croissant(vector<int> &rangCarte,const vector<int>& vecCarte);
void afficherVectorInt(vector<int>& vecCarte);
void afficherVectorStr(vector<string> &vecCarte);
void rangement_croissant_attaque(const vector<Carte>& vecCarte, vector<int> &rangCarte);
void rangement_decroissant_attaque(const vector<Carte> &vecCarte, vector<int> &rangCarte);
void rangement_croissant_defense(const vector<Carte>& vecCarte, vector<int> &rangCarte);
void rangement_decroissant_defense(const vector<Carte>& vecCarte, vector<int> &rangCarte);
void rangement_croissant_magique(const vector<Carte>& vecCarte, vector<int> &rangCarte);
void rangement_decroissant_magique(const vector<Carte> & vecCarte, vector<int> &rangCarte);
void rangement_score_decroissant(const vector<Carte> &vecCarte,vector<int> &rangCarte);


#endif // JOUEUR_H_INCLUDED
