#include "Joueur.h"
#include "sp_cartes.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;
const int carteMAX = 20;
// constructeur par default d'un joueur
Joueur::Joueur() {
  _nom = "Yugi";
  _prestige = 25;
  _pileCarte = {};
  _pileCarte.push_back(Carte("MainDroite", 1, 0, 0));
  _pileCarte.push_back(Carte("MainGauche", 0, 1, 0));
  _pileCarte.push_back(Carte("Tete", 1, -2, 0));
  _pileCarte.push_back(Carte("Bouche", 1, -1, 2));
  _pileCarte.push_back(Carte("Genou", 2, 0, 0));
}

// constructeur "remplie" par le "client"
Joueur::Joueur(const string &nom, int prestige,
               const vector<Carte> &pileCarte) {
  _nom = nom;
  _prestige = prestige;
  _pileCarte = pileCarte;
}

// donne le nom du joueur
string Joueur::sonNom() const { return _nom; }

// donne les points de vie du joueur
int Joueur::sonPrestige() const { return _prestige; }

// donne les infos du joueur (son nom, sa vie, son nombre de carte)
void Joueur::affichage() const {
  cout << "Le joueur " << _nom << " a " << _prestige
       << " points de prestige, il lui reste " << _pileCarte.size()
       << " cartes dans sa pile." << endl;
}

// Affiche la pile de carte du joueur
void Joueur::afficherPileCarte(){
  for (int i = 0; i < _pileCarte.size();i++){
    _pileCarte[i].afficheOpti();
  }
}

// Affiche la carte que le joueur a joué 
// void Joueur::carteJouer() {
//   Carte c;
//   c = _pileCarte[_pileCarte.size() - 1];
//   c.afficheOpti();
// }

// initialise un deck de 20 cartes au joueur
void Joueur::initialiser(const vector<Carte> &vc) {
  for (int i = 0; i < 20 && i < vc.size(); i++) {
    _pileCarte.push_back(vc[i]);
  }
}

// fonction qui nous dit s'il reste des cartes au joueur ou non
bool Joueur::JoueToujours() { return (_pileCarte.size() > 0); }

// fonction qui nous dit s'il reste de la vie au joueur ou non
bool Joueur::prestigePositif() { return (_prestige > 0); }

// donne et dit au joueur quelle est la carte qu'il a pioché (avant de la
// supprimer de sa pile)
void Joueur::carteSuiv(Carte &c) {
  if (JoueToujours() && !_pileCarte.empty()) {
    c = _pileCarte[_pileCarte.size() - 1];
    cout<<_nom<<" a joue la carte : ";
    c.afficheOpti();
    _pileCarte.pop_back();
  } else {
    throw invalid_argument("ERR : Attention le joueur n'a plus de carte");
  }
}

// Le joueur joue une carte et baisse les points de prestige en fonction de son
// action (S'il réussi son action, il baisse les points de prestige de
// l'adversaire et perd des pts de prestige sinon)
void Joueur::jouentUneCarte(Joueur &joueurParam) {
  Carte joueurCibleCarte;
  Carte joueurParamCarte;
  carteSuiv(joueurCibleCarte);
  joueurParam.carteSuiv(joueurParamCarte);
  int degatPhy = joueurCibleCarte.degatPhysique(joueurParamCarte);
  int degatMag = joueurCibleCarte.degatMagique(joueurParamCarte);
  if (degatPhy > 0) {
    joueurParam._prestige -= degatPhy;
    cout << joueurParam.sonNom() << " a recu " << degatPhy
         << " points de degats physique." << endl;
  } else if (degatPhy < 0) {
    _prestige += degatPhy;
    cout << sonNom() << " a recu " << -degatPhy << " points de degats physique."
         << endl;
  } else {
    cout << "Les joueurs n'ont recu aucun points de degat physique" << endl;
  }

  if (degatMag > 0) {
    joueurParam._prestige -= degatMag;
    cout << joueurParam.sonNom() << " a recu " << degatMag
         << " points de degats magique." << endl;
  } else if (degatMag < 0) {
    _prestige += degatMag;
    cout << sonNom() << " a recu " << -degatMag << " points de degats magique."
         << endl;
  } else {
    cout << "Les joueurs n'ont recu aucun points de degats magique." << endl;
  }
}

// l'algorithme de Fisher-Yates qui mélange les cartes aléatoirement
void Joueur::melangePileAlea()
{
    int n = _pileCarte.size();
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(_pileCarte[i], _pileCarte[j]);
    }
}


// Avoir un vecteur trié de rang
void vecteur_de_rang(const vector<Carte> &vecCarte, vector<int> &rangCarte) {
  for (int i = 0; i < vecCarte.size(); i++) 
    rangCarte.push_back(i);}


// fait un tri insertion decroissant du rang des vecteurs donnée
void tri_insertion_decroissant(vector<int> &rangCarte,
                               const vector<int> &vecCarte) {
  int i, j, k;
  for (i = 1; i < rangCarte.size(); i++) {
    k = rangCarte[i];
    j = i - 1;
    while (j >= 0 && vecCarte[rangCarte[j]] < vecCarte[k]) {
      rangCarte[j + 1] = rangCarte[j];
      j--;
    }
    rangCarte[j + 1] = k;
  }
}

// fait un tri insertion croissant du rang des vecteurs donnée
void tri_insertion_croissant(vector<int> &rangCarte,
                             const vector<int> &vecCarte) {
  int i, j, k;
  for (i = 1; i < rangCarte.size(); i++) {
    k = rangCarte[i];
    j = i - 1;
    while (j >= 0 && vecCarte[rangCarte[j]] > vecCarte[k]) {
      rangCarte[j + 1] = rangCarte[j];
      j--;
    }
    rangCarte[j + 1] = k;
  }
}

// range de maniere décroissante le vecteur selon l'atk des cartes donnée dans
// le vecteur
void rangement_decroissant_attaque(const vector<Carte> &vecCarte,
                                   vector<int> &rangCarte) {
  vecteur_de_rang(vecCarte, rangCarte);
  vector<int> tempVec;
  for (const Carte &i : vecCarte)
    tempVec.push_back(i.atkCarte());
  tri_insertion_decroissant(rangCarte, tempVec);
}

// range de maniere décroissante le vecteur selon la defense des cartes donnée
// dans le vecteur
void rangement_decroissant_defense(const vector<Carte> &vecCarte,
                                   vector<int> &rangCarte) {
  vecteur_de_rang(vecCarte, rangCarte);
  vector<int> tempVec;
  for (const Carte &i : vecCarte)
    tempVec.push_back(i.defCarte());
  tri_insertion_decroissant(rangCarte, tempVec);
}

// range de maniere décroissante le vecteur selon la magie des cartes donnée
// dans le vecteur
void rangement_decroissant_magique(const vector<Carte> &vecCarte,
                                   vector<int> &rangCarte) {
  vecteur_de_rang(vecCarte, rangCarte);
  vector<int> tempVec;
  for (const Carte &i : vecCarte)
    tempVec.push_back(i.magieCarte());
  tri_insertion_decroissant(rangCarte, tempVec);
}

// range de maniere croissante le vecteur selon l'atk des cartes donnée dans le
// vecteur
void rangement_croissant_attaque(const vector<Carte> &vecCarte,
                                 vector<int> &rangCarte) {
  vecteur_de_rang(vecCarte, rangCarte);
  vector<int> tempVec;
  for (const Carte &i : vecCarte)
    tempVec.push_back(i.atkCarte());
  tri_insertion_croissant(rangCarte, tempVec);
}

// range de maniere croissante le vecteur selon la defense des cartes donnée
// dans le vecteur
void rangement_croissant_defense(const vector<Carte> &vecCarte,
                                 vector<int> &rangCarte) {
  vecteur_de_rang(vecCarte, rangCarte);
  vector<int> tempVec;
  for (const Carte &i : vecCarte)
    tempVec.push_back(i.defCarte());
  tri_insertion_croissant(rangCarte, tempVec);
}

// range de maniere croissante le vecteur selon la magie des cartes donnée dans
// le vecteur
void rangement_croissant_magique(const vector<Carte> &vecCarte,
                                 vector<int> &rangCarte) {
  vecteur_de_rang(vecCarte, rangCarte);
  vector<int> tempVec;
  for (const Carte &i : vecCarte)
    tempVec.push_back(i.magieCarte());
  tri_insertion_croissant(rangCarte, tempVec);
}

// range de maniere croissante le vecteur de carte selon le score de chaque
// carte
void rangement_score_decroissant(const vector<Carte> &vecCarte,
                                 vector<int> &rangCarte) {
  vecteur_de_rang(vecCarte, rangCarte);
  vector<int> tempVec;
  for (const Carte &i : vecCarte)
    tempVec.push_back(i.sommeScore());
  tri_insertion_decroissant(rangCarte, tempVec);
}

// Affiche un vecteur de int
void afficherVectorInt(vector<int> &vecCarte) {
  for (int i = 0; i < vecCarte.size(); i++) {
    cout << vecCarte[i] << " ";
  }
  cout << endl;
}

// Affiche un vecteur de string
void afficherVectorStr(vector<string> &vecCarte) {
  for (int i = 0; i < vecCarte.size(); i++) {
    cout << vecCarte[i] << " ";
  }
  cout << endl;
}

// Permet de remplir pileCarte (deck du J) avec les cartes ayant la + forte atk
// dispo dans la reserve (décroissant)
void Joueur::remplirPileAtk(const vector<Carte> &vecCarte, vector<int> &rangCarte) {
  rangement_decroissant_attaque(vecCarte, rangCarte);
  for (int i = 0; i < vecCarte.size(); i++) {
    _pileCarte.push_back(vecCarte[rangCarte[i]]);
  }
}


// Permet au joueur de choisir le rangement qu'il veut
void Joueur::choisirRangement(const vector<Carte> &vecCarte,vector<int> &rangCarte)
{
        cout << "Pour choisir un rangement avec des tri pré concu, tapez 1 \n";
        cout << "Pour choisir un rangement personalisé, tapez 2 \n";
        int choix;
        cin >> choix;
        cout << endl;
        while (choix < 1 || choix > 2)
        {
            cout << "choix non enregistré, veuillez suivre les consignes \n";
            cout << "Veuillez choisir votre rangement : ";
            cin >> choix;
        }  

        if (choix == 1){
            cout << "Pour ranger par attaque croissante, tapez 1 \n";
            cout << "Pour ranger par attaque decroissante, tapez 2 \n";
            cout << "Pour ranger par defense croissante, tapez 3 \n";
            cout << "Pour ranger par defense decroissante, tapez 4 \n";
            cout << "Pour ranger par magie croissante, tapez 5 \n";
            cout << "Pour ranger par magie decroissant, tapez 6 \n";
            cout << "Pour ranger par score decroissant, tapez 7 \n";
            cout << "Pour ranger par atk, puis magie, puis def selon les doublons, tapez 8 \n";
            cin >> choix;
            while (choix > 8 || choix < 1)
            {
                cout << "choix non enregistré, veuillez suivre les consignes \n";
                cout << "Veuillez taper un rangement disponible : ";
                cin >> choix;
            }
            remplirPile(vecCarte,rangCarte,choix);
        }
        else{
          for(int i=0; i<carteMAX; i++){
            ChoixAjoutJoueur(vecCarte);
            cout << "Carte enregistree. Carte numéro : " << i+1 << "/20" << endl;
          }
          }
}

// Rempli la pile du joueur en fonction du choix qu'il a fait
void Joueur::remplirPile(const vector<Carte> &vecCarte,vector<int> &rangCarte,int choix)
{
    switch (choix)
    {
    case 1:
        rangement_croissant_attaque(vecCarte,rangCarte);
        break;
    case 2:
        rangement_decroissant_attaque(vecCarte,rangCarte);
        break;
    case 3:
        rangement_croissant_defense(vecCarte,rangCarte);
        break;
    case 4:
       rangement_decroissant_defense(vecCarte,rangCarte);
        break;
    case 5:
        rangement_croissant_magique(vecCarte,rangCarte);
        break;
    case 6:
        rangement_decroissant_magique(vecCarte,rangCarte);
        break;
    case 7:
        rangement_score_decroissant(vecCarte,rangCarte);
        break;
    case 8:
        rangeCarte(vecCarte,rangCarte);
        break;
    default:
        break;
    }
    for (int i = vecCarte.size() - 1; i >= 0 && _pileCarte.size() < 20; i--)
    {
        _pileCarte.push_back(vecCarte[rangCarte[i]]);
        _pileCarte[_pileCarte.size() - 1];
      }

}

// range les cartes par atk puis par magie et enfin par defense selon si oui ou non ses stats ont des doublons avec un triple tri par insertion
// Optimisé avec l'aide de ChatGPT
void Joueur::rangeCarte(const vector<Carte> &vecCarte, vector<int> &rangCarte) {
  vecteur_de_rang(vecCarte,rangCarte);
  for (int i = 1; i < vecCarte.size(); i++) {
    int j = i - 1;
    int key = rangCarte[i];
    while (j >= 0 && (vecCarte[rangCarte[j]].atkCarte() < vecCarte[key].atkCarte() ||
                     (vecCarte[rangCarte[j]].atkCarte() == vecCarte[key].atkCarte() && vecCarte[rangCarte[j]].magieCarte() < vecCarte[key].magieCarte()) ||
                     (vecCarte[rangCarte[j]].atkCarte() == vecCarte[key].atkCarte() && vecCarte[rangCarte[j]].magieCarte() == vecCarte[key].magieCarte() && vecCarte[rangCarte[j]].defCarte() < vecCarte[key].defCarte()))) {
      rangCarte[j + 1] = rangCarte[j];
      j--;
    }
    rangCarte[j + 1] = key;
  }
}

// Code originel du sous programme au dessus
// void Joueur::rangeCarte(const vector<Carte> &vecCarte, vector<int> &rangCarte) {
//   {
//     bool ok = false;
//     vecteur_de_rang(vecCarte,rangCarte);
//     for (int i = 1; i < vecCarte.size(); i++)
//     {
//         int j = i - 1;
//         ok = false;
//         while (j >= 0 && !ok)
//         {
//             if (vecCarte[rangCarte[i]].atkCarte() == vecCarte[rangCarte[j]].atkCarte())
//             {
//                 if (vecCarte[rangCarte[i]].magieCarte() > vecCarte[rangCarte[j]].magieCarte())
//                 {
//                     rangCarte[j + 1] = rangCarte[j];
//                     j--;
//                 }
//                 else if (vecCarte[rangCarte[i]].magieCarte() == vecCarte[rangCarte[j]].magieCarte())
//                 {
//                     if (vecCarte[rangCarte[i]].defCarte() > vecCarte[rangCarte[j]].defCarte())
//                     {
//                         rangCarte[j + 1] = rangCarte[j];
//                         j--;
//                     }
//                     else
//                         ok = true;
//                 }
//                 else
//                     ok = true;
//             }
//             else if (vecCarte[rangCarte[i]].atkCarte() > vecCarte[rangCarte[j]].atkCarte())
//             {
//                 rangCarte[j + 1] = rangCarte[j];
//                 j--;
//             }
//             else
//                 ok = true;
//         }
//         rangCarte[j + 1] = rangCarte[i];

//     }
// }



// permet au jour de choisir une carte dans la reserve et de la prendre grace a
// son nom
void Joueur::ChoixAjoutJoueur(const vector<Carte> &vecCarte) {
  string nomCarte;
  bool ok = false;
  do{
  cout << "Quel est le nom de la carte que vous souhaiter prendre ?" << endl;
  cin >> nomCarte;
  for (int i = 0; i < vecCarte.size(); i++) {
    if (nomCarte == vecCarte[i].nomCarte()) {
      _pileCarte.push_back(vecCarte[i]); 
      ok = true;
      break;
    }
  }
    }while(!ok);
}

// permet au joueur de choisir une carte dans la reserve et de la prendre grace
// a son nom mais le vecteur de la reserve est rangé par ordre alpha (donc
// recherche dicho)
void Joueur::ChoixSiReserveRanger(const vector<Carte> &vecCarte) {
  string nomCarte;
  int debut = 0;
  bool trouve = false;
  int fin = vecCarte.size() - 1;
  cout << "Quel est le nom de la carte que vous souhaiter prendre ?" << endl;
  cin >> nomCarte;
  while (!trouve && debut <= fin) {
    int milieu = (debut + fin) / 2;
    if (vecCarte[milieu].nomCarte() > nomCarte) {
      fin = milieu - 1;
    } else if (vecCarte[milieu].nomCarte() < nomCarte) {
      debut = milieu + 1;
    } else if (vecCarte[milieu].nomCarte() == nomCarte) {
      _pileCarte.push_back(vecCarte[milieu]);
      trouve = true;
    }
  }
}