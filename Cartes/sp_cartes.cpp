#include <cstdlib>
#include <random>
#include "sp_cartes.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

// Construit une carte avec des valeurs initiales.
Carte::Carte()
{
    _nom = "Mains nues";
    _attaque = 15;
    _defense = 1;
    _magie = 10;
}

// constructeur avec des valeurs données depuis le main
Carte::Carte(const string& nom, int attaque, int defense, int magie)
{
    _nom = nom;
    _attaque = attaque;
    _defense = defense;
    _magie = magie;
}

// Procédure permettant de lire le fichier
void readF(const string& in, vector<string>& tot ){
  ifstream cart(in);
  string getL;
  while (getline(cart,getL)){
    tot.push_back(getL);
  }
}

// Permet de voir si la ligne est conforme et peut donc être ajouté a une carte
void Carte::remplir(const string & ligne)
{

    char ln0[ligne.length()];
    char ln[20];
    for (int i = 0; i < ligne.length(); i++){
        ln0[i]=ligne[i];}
    ln0[ligne.length()]='\0';
    int a = 0 , b = 0 , c = 0;

    if(sscanf(ln0," %[^,], %d , %d , %d", &ln, &a, &b, &c) == 4)
    {
        _attaque=a;
        _defense=b;
        _magie=c;
        _nom=ln;
    }
    else throw "ligne non conforme";
}

// Affiche les informations d'une carte
void Carte::affiche() const{
    cout << "****************\nNom : " << _nom << endl;
    cout << "Attaque : " << _attaque << endl;
    cout << "Defense : " << _defense << endl;
    cout << "Magie : " << _magie << endl;
    cout << "*****************\n"; }

// Affiche les informations de maniere concise sur d'une carte
void Carte::afficheOpti() const{
    cout << _nom << " [ " << _attaque << " ; " << _defense << " ; " << _magie << " ] " << endl;
}

// Inflige des dégats physiques à celui qui a la plus grande valeur
int Carte::degatPhysique(const Carte & c2)const{
    int degats;
    if(_attaque > c2._attaque){
        degats = _attaque - c2._defense;
        return degats;}
    else{
        degats = _defense - c2._attaque ;
        return  degats;
    }
}

// Inflige des dégats magiques à celui qui a la plus grande valeur
int Carte::degatMagique(const Carte & c2)const{
    int dgt;
    if(_magie > c2._magie){
        dgt = _magie - c2._magie;
        return dgt;
    }
    else{
        dgt = _magie - c2._magie;
        return dgt;
    }
}

// Retourne le nom de la carte
string Carte::nomCarte() const{
  return _nom;
}

// Retourne l'attaque de la carte
int Carte::atkCarte() const{
  return _attaque;
}

// Retourne la defense de la carte
int Carte::defCarte() const{
  return _defense;
}

// Retourne la magie d'une carte
int Carte::magieCarte() const{
  return _magie;
}

//retourne la somme d'une carte
int Carte::sommeScore() const {
  return _attaque+_defense+_magie;
}
