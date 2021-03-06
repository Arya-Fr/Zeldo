#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#include "type.c"

void afficherImage ( int x ,int y ,SDL_Renderer* renderer ,char* nomFichier );

void AfficherInventaire (item inventaire[4],SDL_Renderer* renderer);
void AfficherEtatInventaire (SDL_Renderer* renderer,int inv);

void ActuEcranTitre (SDL_Renderer* renderer,int actu,uint8_t alpha);
void AfficherMenu (SDL_Renderer* renderer,int posMenu, int actu);
void AfficherMenuPause (SDL_Renderer* renderer,int menuP);

void AfficherPosition (int numLaby,SDL_Renderer* renderer);
void AfficherRuby (int argent,SDL_Renderer* renderer,int etat);

void AfficherVie (Perso Joueur, int vieSpecial,SDL_Renderer* renderer);
void AfficherNiveau (char labyrinthe [4][DIMY][DIMX+1], item inventaire[4], Perso Joueur, int numLaby, int argent,int clignotant,SDL_Renderer* renderer,char* persoBas,char* sol,char* mur,int vieSpecial,int invPos);
void AfficherVieEnnemie (Perso Dummies[], int numLaby,SDL_Renderer* renderer);


#endif // AFFICHAGE_H_INCLUDED
