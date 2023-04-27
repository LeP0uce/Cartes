#include <string>
#include <iostream>
#include <vector>

#ifndef SP_CARTES_H_INCLUDED
#define SP_CARTES_H_INCLUDED

using namespace std;

class Carte{ 
    //les parametres d'une carte de la class Carte
    string _nom;
    int _attaque;
    int _defense;
    int _magie;


public:

    //constructeur vide
    Carte();
    //constructeur parametré
    Carte(const string&, int, int, int);

    //affiche de maniere esthétique les parametres d'une carte
    void affiche() const; 
    //affiche de maniere concise les parametres d'une carte
    void afficheOpti() const; 
    //une carte inflige des dgts physique sur une autre carte
    int degatPhysique(const Carte &)const; 
    //une carte inflige des dgts magique sur une autre carte
    int degatMagique(const Carte &)const;  
    //remplie UNE carte depuis les informations donnée depuis un fichier externe (1 ligne du fichier = 1 carte)
    void remplir(const string & ligne); 
    //retourne le nom d'une carte
    string nomCarte() const; 
    //retourne la magie d'une carte
    int magieCarte() const; 
    //retourne la defense d'une carte
    int defCarte() const; 
    //retourne l'attaque d'une carte
    int atkCarte() const; 
    //retourne le score d'une carte (la somme des parametres numérique)
    int sommeScore() const; 
    
};

//lis le fichier ligne par ligne 
void readF(const string& in, vector<string>& tot);

#endif // SP_CARTES_H_INCLUDED
