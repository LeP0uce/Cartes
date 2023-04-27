#include "Joueur.h"
#include "le_jeu.h"
#include "sp_cartes.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

int maint() {
  try {
    bool ok = false;
    vector<string> creaCarte;
    vector<Carte> deckCarte;
    vector<int> rangCarte;
    string cheminCarte;
    
    // On met le chemin dans une variable string pour eviter de tout le temps
    // mettre le chemin
    cheminCarte = "Cartes/cartes.txt";
    
    // On lit le fichier "cartes.txt et on les met dans le vecteur string
    // "creaCarte"
    readF(cheminCarte, creaCarte);
    
    /// On crée une carte ppp et bouclier et on regarde s'ils sont bien
    /// initialisés à la même valeur
    Carte ppp, bouclier; // Cartes : parchemin, bouclier
    while (!ok) {
      if (bouclier.sommeScore() == ppp.sommeScore())
        ok = true;
      else
        throw invalid_argument("ERR : Pas bien initialisé");
    }
    
    // On met dans la carte les lignes correspondantes
    ok = false;
    ppp.remplir(creaCarte[9]); // [parchemin,0,0,5]
    bouclier.remplir(creaCarte[5]);
    while (!ok) {
      if (ppp.atkCarte() == 0 && ppp.defCarte() == 0 && ppp.magieCarte() == 5) {
        cout << "Il n'y a pas de problèmes" << endl;
        ok = true;
      } else {
        throw invalid_argument("ERR : La carte ppp n'a pas été bien initualisé");
      }
    }
    
    // On crée notre propre carte du nom de dague
    Carte p("Dague", 10, 1, 8);
    cout << "Le score de dague est de : " << p.sommeScore() << endl;
    
    Carte p1; // (carte initialisé de base)
    cout << p1.sommeScore() << endl;
    
    // On fait de meme avec une carte Kamehameha
    Carte p2("Kamehameha", 50, 300, 30);
    cout << p2.sommeScore() << endl;
    
    // On affiche la carte p
    p.affiche();
    
    // On regarde si cela affiche le nom de la carte
    cout << "Le nom de la carte p est : " << p.nomCarte() << endl;
    
    /// On regarde si cela met bien des dégats
    cout << "Degats physique de p à p1" << p.degatPhysique(p1) << endl;
    cout << "Dégats magique de p à p1" << p.degatMagique(p1) << endl;

    // On crée un vecteur de cartes
    vector<Carte> testCarte = {ppp, p, p2, bouclier, p1};
    
    // On crée un joueur pas initialisé puis deux joueurs initialisés
    Joueur j;
    Joueur j1("Gigigiroud", 3, deckCarte);
    Joueur j2("Dora", 3, deckCarte);
    
    // On crée un jeu 
    Jeu partie_1(cheminCarte, j1, j2);
    // partie_1.remplirTotCarte(j1,creaCarte[0]); //le joueur prend les 20 premiers cartes dans sa reserve
    // partie_1.remplirTotCarte(j2,creaCarte[4]); //le joueur prend les cartes de la ligne 4 à 24 dans sa reserve     
            
    // On affiche les noms des joueurs
    cout << "Le nom de j est : "<< j.sonNom() << "et son prestige est de : "<< j.sonPrestige() << endl;
    cout << "Le nom de j1 est : " << j1.sonNom() << endl;
    cout << "Le nom de j2 est :" <<j2.sonNom() << endl;
    
    // On affiche les information de j
    j.affichage();
    cout << j2.sonNom() << endl;
    partie_1.reserve(cheminCarte);

    // regarde si j1 joue toujours ou non avec prestigePositif
    if (j2.prestigePositif()) {
      cout << "Le joueur est toujours en jeu" << endl;
    } else {
      cout << "Le joueur a perdu" << endl;
    }

    // regarde si j1 joue toujours ou non avec JoueToujours
    if (j1.JoueToujours()) {
      cout << "Le joueur joue toujours" << endl;
    } else {
      cout << "Le joueur a perdu" << endl;
    }

    // On affiche puis on joue la carte ppp et on réaffiche pour voir si la carte ppp a bien été joué
    j.affichage();
    j.carteSuiv(ppp);
    j.affichage();

    // On regarde si le score de la carte p2 est bien 380
    ok=false;
    while(!ok)
      {
        if(p2.sommeScore() == 380) ok=true;
        else throw invalid_argument("ERR : Le score de la carte p2 n'est pas 380 donc faux");
      }

    // On range le vecteur en fonction des scores et on affiche le vecteur
    rangement_score_decroissant(testCarte, rangCarte);
    afficherVectorInt(rangCarte);

    // On range le vecteur en fonction de l'attaque de façon décroissante
    rangement_decroissant_attaque(testCarte, rangCarte);
    afficherVectorInt(rangCarte);

    // On range le vecteur en fonction de l'attaque de façon croissante
    rangement_croissant_attaque(testCarte, rangCarte);
    afficherVectorInt(rangCarte);

    // Ajout d'une carte disponible dans testCarte (20 max)
    cout << "Ajout carte dispo dans testCarte (20 max)" << endl;
    j.remplirPileAtk(testCarte, rangCarte);
    j.affichage();
    j.afficherPileCarte();

    // Range le vecteur par attaque puis par magie et pour finir par défense
    cout << "Range par atk, puis magie, puis def" << endl;
    j.rangeCarte(testCarte, rangCarte);

    // Normalement, Yugi a 8 cartes
    cout << "normalement ici Yugi a 8 cartes" << endl;
    afficherVectorInt(rangCarte);

    // On demande ce que le joueur veut ajouter puis affiche sa pile
    j.ChoixAjoutJoueur(testCarte);

    // recherche dichotomique de la carte demandé puis on l'affiche
    j.ChoixSiReserveRanger(testCarte);

    j.affichage();
    return 0;
  } catch (invalid_argument e) {
    cerr << e.what();
  }
}
