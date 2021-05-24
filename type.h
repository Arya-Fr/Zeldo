#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#include <SDL2/SDL.h>

#define DIMX 20
#define DIMY 8

#define VRAI 1
#define FAUX 0

#define Ville 0
#define Auberge 1
#define Prison 2
#define Cellule 3

#define clef 0
#define pot 1
#define armure 2
#define epee 3

typedef int bool;

typedef struct Coord {
    int x;
    int y;
} Coord;

typedef struct Perso {
    Coord coord;
    int vie;
    int atck;
    char* nom;
} Perso;

typedef struct item {
    int type;
    char* nom;
    bool pris;
} item;

void triInventaire (item inv[]);

#endif // TYPE_H_INCLUDED
