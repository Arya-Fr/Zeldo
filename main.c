#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "affichage.c"

int main(int argc, char** argv)
{
    if (!SetConsoleOutputCP(65001))
        printf ("ERREUR\n");

    char labyrinthe [4][DIMY][DIMX+1] = {
        {
            "####################",       // Ville HUB
            "#J  # p##   .    #T#",
            "#  .#  .           #",
            "#        ###   .   #",
            "##### .  ###    .  #",
            "#        ###       #",
            "#P# #     .   .    #",
            "####################"
        },

        {
            "####################",       // Auberge
            "########T###########",
            "##  .        .    ##",
            "##    .         D ##",
            "##                ##",
            "##    ___    .   .##",
            "###### V ###########",
            "####################"
        },

        {
            "####################",       // Prison
            "##P#|#|#|#|#|#|#|###",
            "## #-#-#-#-#-#-#-###",
            "##                ##",
            "##G               ##",
            "###-#-#-#-#-#-#C####",
            "###|#|#|#|#|#|#|####",
            "####################"
        },

        {
            "####################",       // Cellule
            "####   ###########C#",
            "###  # ###   ####  #",
            "##  H# ### # # g   #",
            "#H H##     # F     #",
            "#H H################",
            "##                S#",
            "####################"
        }
    };

    Perso Joueur;
    Perso Dummies[4];
    Coord PorteT[2];
    Coord PorteP[3];
    Coord Cell[4];
    item inventaire[4];
    bool ennemie[4];

    for (int i = 0; i < 4 ; i++) {
        inventaire[i].pris = FAUX;
        ennemie[i] = FAUX;
    }

    for ( int numLaby = 0 ; numLaby < 4; numLaby++ )
        for ( int y = 0 ; y < DIMY; y++ )
            for ( int x = 0 ; x < DIMX; x++ )
                switch (labyrinthe[numLaby][y][x]) {
                case 'J' :
                    Joueur.coord.x = x;
                    Joueur.coord.y = y;
                    break;
                case 'T' :
                    PorteT[numLaby].x = x;
                    PorteT[numLaby].y = y;
                    break;
                case 'P' :
                    PorteP[numLaby].x = x;
                    PorteP[numLaby].y = y;
                    break;
                case 'D' :
                    Dummies[1].coord.x = x;
                    Dummies[1].coord.y = y;
                    ennemie[numLaby] = VRAI;
                    break;
                case 'C' :
                    Cell[numLaby].x = x;
                    Cell[numLaby].y = y;
                    break;
                case 'F' :
                    Dummies[3].coord.x = x;
                    Dummies[3].coord.y = y;
                    ennemie[numLaby] = VRAI;
                    break;
                case 'G' :
                    Dummies[2].coord.x = x;
                    Dummies[2].coord.y = y;
                    ennemie[numLaby] = VRAI;
                    break;
                }

    Joueur.atck = 2;
    Dummies[1].atck = 1;
    Dummies[2].atck = 1;
    Dummies[3].atck = 0;

    Joueur.vie = 12;
    Dummies[1].vie = 16;
    Dummies[2].vie = 10;
    Dummies[3].vie = 2;

    int vieSpecial = 5;
    int vieMax = 12;
    int vieSpecialMax = 5;

    Dummies[1].nom = "§ Mannequin d'entrainnement";
    Dummies[2].nom = "☻ Garde";
    Dummies[3].nom = "▓ Faux mur";

    /*------------ Début Initialisation SDL -----------*/

    if ( SDL_Init (SDL_INIT_VIDEO) != 0 ) {
        fprintf (stderr, "Erreur d'initialisation du mécanisme SDL : %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }
    SDL_Window* fenetre = SDL_CreateWindow ("Exemple 5",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1400,900,SDL_WINDOW_SHOWN);

    if ( fenetre == NULL ) {
        fprintf (stderr, "Erreur de création de la fenêtre : %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_RendererInfo info;

    int nbDrivers = SDL_GetNumRenderDrivers ();
    for ( int i=0; i<nbDrivers; i++) {
        SDL_GetRenderDriverInfo ( i, &info );

        printf ("Driver numero %d : \n", i);
        printf (" - name : %s \n", info.name);
        printf (" - flags : ");

        if ( info.flags & SDL_RENDERER_SOFTWARE ) printf ("SDL_RENDERER_SOFTWARE ");
        if ( info.flags & SDL_RENDERER_ACCELERATED ) printf ("SDL_RENDERER_ACCELERATED ");
        if ( info.flags & SDL_RENDERER_PRESENTVSYNC ) printf ("SDL_RENDERER_PRESENTVSYNC ");
        if ( info.flags & SDL_RENDERER_TARGETTEXTURE) printf ("SDL_RENDERER_TARGETTEXTURE ");
        printf ("\n");
    }

    SDL_Renderer* renderer = SDL_CreateRenderer ( fenetre, -1, SDL_RENDERER_ACCELERATED);

    /*------------ Fin Initialisation SDL -----------*/
    /*------------ Début Initialisation Variable -------*/
    int fin = 0;
    int Achatdial = 2;
    int fix = 0;
    int invPos = 0;
    int invDial = 1;
    int describ = 1;
    int possClefC = 0;
    int numLaby = 0;
    int actu = 0;
    int direction = 0;
    int menuP = 0;

    int argent = 10;

    int inverserGardeP = 0;
    int moduloGard = 0;
    int clignotant = 0;

    char* persoHaut;
    char* persoBas;
    char* persoGauche;
    char* persoDroite;

    char* persoAttackHaut;
    char* persoAttackBas;
    char* persoAttackGauche;
    char* persoAttackDroite;

    char* sol = "asset/map/SolV.bmp";
    char* mur = "asset/map/MurV.bmp";

    int menuPos = 0;

    uint8_t alpha = 0 ;

    SDL_Event event;

    /*------------ Fin Initialisation Variable -------*/
    /*------------Début écran titre-----------------*/

    do {
        SDL_RenderPresent(renderer);

        ActuEcranTitre(renderer,actu,alpha);

        SDL_PollEvent(&event);

        switch(event.type) {
        case SDL_KEYDOWN:
            switch ( event.key.keysym.sym ) {
            case SDLK_RETURN :
                fin = 1;
                break;
            }
            break;
        }

        switch(clignotant){
        case 50:
            actu = 1;
            alpha = alpha + 1;
            break;
        case 300:
            actu = 2;
            break;
        case 400:
            actu = 3;
            clignotant = 200;
            break;
        }
        clignotant++;

    }while (fin == 0);

    /*------------Fin écran titre----------------*/

    fin = 0;
    clignotant = 0;
    actu = 0;

    /*------------Début Menu Selection Perso -------------*/

    SDL_RenderClear(renderer);
    afficherImage ( 0, 0, renderer, "asset/ui/fondMenu.bmp");
    do {
        SDL_RenderPresent(renderer);
        AfficherMenu(renderer,menuPos,actu);
        switch(menuPos) {
        case 0:
            persoBas = "asset/character/player/PersoBas0.bmp";
            persoHaut = "asset/character/player/PersoHaut0.bmp";
            persoDroite = "asset/character/player/PersoDroite0.bmp";
            persoGauche = "asset/character/player/PersoGauche0.bmp";
            break;
        case 1:
            persoBas = "asset/character/player/PersoBas1.bmp";
            persoHaut = "asset/character/player/PersoHaut1.bmp";
            persoDroite = "asset/character/player/PersoDroite1.bmp";
            persoGauche = "asset/character/player/PersoGauche1.bmp";
            break;
        case 2:
            persoBas = "asset/character/player/PersoBas2.bmp";
            persoHaut = "asset/character/player/PersoHaut2.bmp";
            persoDroite = "asset/character/player/PersoDroite2.bmp";
            persoGauche = "asset/character/player/PersoGauche2.bmp";
            break;
        case 3:
            persoBas = "asset/character/player/PersoBas3.bmp";
            persoHaut = "asset/character/player/PersoHaut3.bmp";
            persoDroite = "asset/character/player/PersoDroite3.bmp";
            persoGauche = "asset/character/player/PersoGauche3.bmp";
            break;

        }

        if (menuPos == 1 || menuPos == 0) {
            persoAttackHaut = "asset/effect/bleuHaut.bmp";
            persoAttackBas = "asset/effect/bleuBas.bmp";
            persoAttackGauche = "asset/effect/bleuGauche.bmp";
            persoAttackDroite = "asset/effect/bleuDroite.bmp";
        }
        if (menuPos == 2 || menuPos == 3) {
            persoAttackHaut = "asset/effect/jauneHaut.bmp";
            persoAttackBas = "asset/effect/jauneBas.bmp";
            persoAttackGauche = "asset/effect/jauneGauche.bmp";
            persoAttackDroite = "asset/effect/jauneDroite.bmp";
        }

        SDL_PollEvent(&event);

        switch(event.type) {
        case SDL_KEYDOWN:
            switch ( event.key.keysym.sym ) {
            case SDLK_q :
                menuPos--;
                break;
            case SDLK_d :
                menuPos++;
                break;
            case SDLK_f :
                fin++;
                break;
            }
            break;
        }
        if (menuPos < 0) {
            menuPos = 3;
        }
        if (menuPos > 3) {
            menuPos = 0;
        }
        if (clignotant == 100) {
            actu = 1;
        }
        if (clignotant == 200) {
            clignotant = 0;
            actu = 0;
        }
        clignotant++;

    } while(fin == 0);

    /*------------Fin Menu Selection Perso -------------*/

    actu = 0;
    clignotant = 0;
    fin = 0;

    SDL_RenderClear(renderer);
    AfficherNiveau(labyrinthe,inventaire,Joueur,numLaby,argent,clignotant,renderer,persoBas,sol,mur,vieSpecial,invPos);

//                                          Lancement du jeu  //

    do {
        SDL_RenderPresent(renderer);
        if (Joueur.vie <= 0) fin = 2;

        if (clignotant != 0) {
            AfficherVie(Joueur,vieSpecial,renderer);
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, sol);
        }
        if (clignotant == 10) {
            clignotant = 0;
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoBas);
        }
        if (clignotant > 0)clignotant++;

        if (actu != 0) {
            actu++;
        }

        if (actu == 100) {
            actu = 0;
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, sol);
            switch(direction) {
            case 0:
                afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoBas);
                break;
            case 1:
                afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoDroite);
                break;
            case 2:
                afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoHaut);
                break;
            case 3:
                afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoGauche);
                break;
            }
        }

        switch (describ) {
        case 2:
            afficherImage ( 75, 220, renderer, "asset/ui/DialoguePrion0.bmp");
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
            afficherImage ( 75, 220, renderer, "asset/ui/DialoguePrion1.bmp");
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
            AfficherNiveau(labyrinthe,inventaire,Joueur,numLaby,argent,clignotant,renderer,persoBas,sol,mur,vieSpecial,invPos);
            AfficherVieEnnemie(Dummies,numLaby,renderer);
            describ = 0;
            break;
        }
//                                          Partie Personnage Début  //
        switch(fix) {
        case 0:

            SDL_PollEvent(&event);

            switch(event.type) {
            case SDL_KEYDOWN:
                switch ( event.key.keysym.sym ) {
                case SDLK_z :
                    if ( labyrinthe[numLaby][Joueur.coord.y-1][Joueur.coord.x  ] != '#' && labyrinthe[numLaby][Joueur.coord.y-1][Joueur.coord.x  ] != 'F' && labyrinthe[numLaby][Joueur.coord.y-1][Joueur.coord.x  ] != 'g') {
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, sol);
                        Joueur.coord.y--;
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, sol);
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoHaut);
                        direction = 2;
                    }

                    break;
                case SDLK_q :
                    if ( labyrinthe[numLaby][Joueur.coord.y  ][Joueur.coord.x-1] != '#' && labyrinthe[numLaby][Joueur.coord.y  ][Joueur.coord.x-1] != 'F' && labyrinthe[numLaby][Joueur.coord.y  ][Joueur.coord.x-1] != 'g') {
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, sol);
                        Joueur.coord.x--;
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, sol);
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoGauche);
                        direction = 3;
                    }

                    break;
                case SDLK_d :
                    if ( labyrinthe[numLaby][Joueur.coord.y  ][Joueur.coord.x+1] != '#' && labyrinthe[numLaby][Joueur.coord.y  ][Joueur.coord.x+1] != 'F' && labyrinthe[numLaby][Joueur.coord.y  ][Joueur.coord.x+1] != 'g') {
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, sol);
                        Joueur.coord.x++;
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, sol);
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoDroite);
                        direction = 1;
                    }

                    break;
                case SDLK_s :
                    if ( labyrinthe[numLaby][Joueur.coord.y+1][Joueur.coord.x  ] != '#' && labyrinthe[numLaby][Joueur.coord.y+1][Joueur.coord.x  ] != 'F' && labyrinthe[numLaby][Joueur.coord.y+1][Joueur.coord.x  ] != 'g') {
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, sol);
                        Joueur.coord.y++;
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, sol);
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoBas);
                        direction = 0;
                    }

                    break;
                case SDLK_f :
                    switch(direction) {
                    case 0 :
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoAttackBas );
                        if ( labyrinthe[numLaby][Joueur.coord.y+1][Joueur.coord.x] == 'D' || labyrinthe[numLaby][Joueur.coord.y+1][Joueur.coord.x] == 'G' || labyrinthe[numLaby][Joueur.coord.y+1][Joueur.coord.x] == 'F') {
                            Dummies[numLaby].vie = Dummies[numLaby].vie - Joueur.atck;
                            AfficherVieEnnemie(Dummies,numLaby,renderer);
                        }
                        actu++;
                        break;
                    case 1 :
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoAttackDroite );
                        if ( labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x+1] == 'D' || labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x+1] == 'G' || labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x+1] == 'F') {
                            Dummies[numLaby].vie = Dummies[numLaby].vie - Joueur.atck;
                            AfficherVieEnnemie(Dummies,numLaby,renderer);
                        }
                        actu++;
                        break;
                    case 2 :
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoAttackHaut );
                        if ( labyrinthe[numLaby][Joueur.coord.y-1][Joueur.coord.x] == 'D' || labyrinthe[numLaby][Joueur.coord.y-1][Joueur.coord.x] == 'G' || labyrinthe[numLaby][Joueur.coord.y-1][Joueur.coord.x] == 'F') {
                            Dummies[numLaby].vie = Dummies[numLaby].vie - Joueur.atck;
                            AfficherVieEnnemie(Dummies,numLaby,renderer);
                        }
                        actu++;
                        break;
                    case 3 :
                        afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoAttackGauche );
                        if ( labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x-1] == 'D' || labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x-1] == 'G' || labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x-1] == 'F') {
                            Dummies[numLaby].vie = Dummies[numLaby].vie - Joueur.atck;
                            AfficherVieEnnemie(Dummies,numLaby,renderer);
                        }
                        actu++;
                        break;
                    }
                    break;
                case SDLK_i :
                    fix = 2;
                    break;
                case SDLK_p :
                    fix = 3;
                    break;
                }
                break;
            }
            break;
//                                          Partie Personnage fin  //

//                                          Partie Marchand début  //
        case 1:
            switch (Achatdial) {
            case 2:
                afficherImage ( 650, 250, renderer, "asset/ui/MenuShop10.bmp");
                break;
            case 3:
                afficherImage ( 650, 250, renderer, "asset/ui/MenuShop20.bmp");
                break;
            case 4:
                afficherImage ( 650, 250, renderer, "asset/ui/MenuShop30.bmp");
                break;
            }
            AfficherEtatInventaire (renderer,invPos);
            AfficherRuby(argent,renderer,0);
            afficherImage ( 0, 661, renderer, "asset/ui/CommandeShop.bmp");

            SDL_PollEvent(&event);
            switch(event.type) {
            case SDL_KEYDOWN:
                switch ( event.key.keysym.sym ) {
                case SDLK_q :
                    if (Achatdial > 2) Achatdial--;
                    break;
                case SDLK_d :
                    if (Achatdial < 4) Achatdial++;
                    break;
                case SDLK_g :
                    fix = 0;
                    Joueur.coord.y--;
                    AfficherNiveau(labyrinthe,inventaire,Joueur,numLaby,argent,clignotant,renderer,persoBas,sol,mur,vieSpecial,invPos);
                    break;
                case SDLK_f :
                    switch (Achatdial) {
                    case 2 :
                        if (argent >= 5 && invPos < 4) {
                            inventaire[invPos].nom = "Epée";
                            inventaire[invPos].pris = VRAI;
                            inventaire[invPos].type = epee;
                            invPos++;
                            argent = argent-5;
                            AfficherRuby(argent,renderer,0);
                            afficherImage ( 650, 250, renderer, "asset/ui/MenuShop11.bmp");
                            SDL_RenderPresent(renderer);
                            SDL_Delay(100);
                        } else {
                            afficherImage ( 650, 250, renderer, "asset/ui/MenuShop12.bmp");
                            if (invPos == 4)afficherImage ( 980, 0, renderer, "asset/ui/IndicInv5.bmp");
                            if (argent < 10)AfficherRuby(argent,renderer,1);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(100);
                        }
                        break;
                    case 3 :
                        if (argent >= 2 && invPos < 4) {
                            inventaire[invPos].nom = "Potion Soin";
                            inventaire[invPos].pris = VRAI;
                            inventaire[invPos].type = pot;
                            invPos++;
                            argent = argent-2;
                            AfficherRuby(argent,renderer,0);
                            afficherImage ( 650, 250, renderer, "asset/ui/MenuShop21.bmp");
                            SDL_RenderPresent(renderer);
                            SDL_Delay(100);
                        } else {
                            afficherImage ( 650, 250, renderer, "asset/ui/MenuShop22.bmp");
                            if (invPos == 4)afficherImage ( 980, 0, renderer, "asset/ui/IndicInv5.bmp");
                            if (argent < 2)AfficherRuby(argent,renderer,1);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(100);
                        }
                        break;
                    case 4 :
                        if (argent >= 10 && invPos < 4) {
                            inventaire[invPos].nom = "Bouclier";
                            inventaire[invPos].pris = VRAI;
                            inventaire[invPos].type = armure;
                            invPos++;
                            argent = argent-10;
                            AfficherRuby(argent,renderer,0);
                            afficherImage ( 650, 250, renderer, "asset/ui/MenuShop31.bmp");
                            SDL_RenderPresent(renderer);
                            SDL_Delay(100);
                        } else {
                            afficherImage ( 650, 250, renderer, "asset/ui/MenuShop32.bmp");
                            if (invPos == 4)afficherImage ( 980, 0, renderer, "asset/ui/IndicInv5.bmp");
                            if (argent < 10)AfficherRuby(argent,renderer,1);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(100);
                        }
                        break;
                    }
                }
            }
            break;
//                                          Partie Marchand fin  //
//                                          Partie Inventaire Début  //
        case 2:
            afficherImage ( 0, 661, renderer, "asset/ui/CommandeInventaire.bmp");
            switch(invDial) {
            case 1 :
                afficherImage ( 620, 180, renderer, "asset/ui/Inv1.bmp");
                break;
            case 2 :
                afficherImage ( 620, 180, renderer, "asset/ui/Inv2.bmp");
                break;
            case 3 :
                afficherImage ( 620, 180, renderer, "asset/ui/Inv3.bmp");
                break;
            case 4 :
                afficherImage ( 620, 180, renderer, "asset/ui/Inv4.bmp");
                break;
            }

            AfficherInventaire(inventaire,renderer);

            SDL_PollEvent(&event);

            switch(event.type) {
            case SDL_KEYDOWN:
                switch ( event.key.keysym.sym ) {
                case SDLK_z :
                    if (invDial > 1) invDial--;
                    break;
                case SDLK_s :
                    if (invDial < 4) invDial++;
                    break;
                case SDLK_i :
                    fix = 0;
                    AfficherNiveau(labyrinthe,inventaire,Joueur,numLaby,argent,clignotant,renderer,persoBas,sol,mur,vieSpecial,invPos);
                    break;
                case SDLK_f :
                    if (inventaire[invDial-1].pris == VRAI) {
                        switch (inventaire[invDial-1].type) {
                        case pot:
                            if (Joueur.vie < vieMax) {
                                Joueur.vie = Joueur.vie + 2;
                                if (Joueur.vie > vieMax) {
                                    Joueur.vie = vieMax;
                                }
                                inventaire[invDial-1].pris = FAUX;
                                invPos--;
                                triInventaire(inventaire);
                                AfficherVie(Joueur,vieSpecial,renderer);
                            }
                            break;
                        case armure:
                            if (vieSpecial < vieSpecialMax) {
                                vieSpecial = vieSpecial + 5;
                                if (vieSpecial > vieSpecialMax) {
                                    vieSpecial = vieSpecialMax;
                                }
                                inventaire[invDial-1].pris = FAUX;
                                invPos--;
                                triInventaire(inventaire);
                                AfficherVie(Joueur,vieSpecial,renderer);
                            }
                            break;
                        case epee:
                            Joueur.atck = Joueur.atck + 5;
                            inventaire[invDial-1].pris = FAUX;
                            invPos--;
                            triInventaire(inventaire);
                            break;
                        }
                    }
                    break;
                }
                break;
//                                          Partie Inventaire Fin  //
            }
            break;

        case 3 :
            AfficherMenuPause(renderer,menuP);

            SDL_PollEvent(&event);

            switch(event.type) {
            case SDL_KEYDOWN:
                switch ( event.key.keysym.sym ) {
                case SDLK_z :
                    menuP = 0;
                    break;
                case SDLK_s :
                    menuP = 1;
                    break;
                case SDLK_f :
                    if (menuP == 1)fin = 1;
                    if (menuP == 0){
                            fix = 0;
                            AfficherNiveau(labyrinthe,inventaire,Joueur,numLaby,argent,clignotant,renderer,persoBas,sol,mur,vieSpecial,invPos);
                    }
                    break;
                case SDLK_p :
                    fix = 0;
                    AfficherNiveau(labyrinthe,inventaire,Joueur,numLaby,argent,clignotant,renderer,persoBas,sol,mur,vieSpecial,invPos);
                    break;
                }
            }
            break;

        }

//                                          Partie Interaction Début  //

        switch (labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x]) {
        case '.' :
            argent++;
            labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x] = ' ';
            AfficherRuby(argent,renderer,0);
            break;
        case ':' :
            argent = argent + 5;
            labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x] = ' ';
            AfficherRuby(argent,renderer,0);
            break;
        case '_' :
            fix = 1;
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/SolB.bmp");
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+175, renderer, persoBas);
            switch(Joueur.coord.x) {
            case 6 :
                afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/Table1.bmp");
                break;
            case 7 :
                afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/Table2.bmp");
                break;
            case 8 :
                afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/Table3.bmp");
                break;
            }
            break;
        case 'S' :
            fin = 3;
            break;
        case 'H' :
            Joueur.vie = 0;
            break;
        case 'D' :
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/SolB.bmp");
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/character/shop/Dummies.bmp");
            Joueur.coord.x = Dummies[numLaby].coord.x-1;
            Joueur.coord.y = Dummies[numLaby].coord.y;
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/SolB.bmp");
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoDroite);
            if (clignotant == 0) {
                if (vieSpecial <= 0) {
                    Joueur.vie = Joueur.vie - Dummies[numLaby].atck;
                } else {
                    vieSpecial = vieSpecial - Dummies[numLaby].atck;
                }
                clignotant = 1;
            }
            break;
        case 'G' :
            if (clignotant == 0) {
                if (vieSpecial <= 0) {
                    Joueur.vie = Joueur.vie - Dummies[numLaby].atck;
                } else {
                    vieSpecial = vieSpecial - Dummies[numLaby].atck;
                }
                clignotant = 1;
            }
            break;
//                                        Debut passage niveau//
        case 'T' :
            switch (numLaby) {
            case Ville :
                Joueur.coord.x = PorteT[Auberge].x;
                Joueur.coord.y = PorteT[Auberge].y+1;
                numLaby = Auberge;
                sol = "asset/map/SolB.bmp";
                mur = "asset/map/MurB.bmp";
                AfficherNiveau(labyrinthe,inventaire,Joueur,numLaby,argent,clignotant,renderer,persoBas,sol,mur,vieSpecial,invPos);
                if (ennemie[numLaby]) {
                    AfficherVieEnnemie(Dummies,numLaby,renderer);
                } else {
                    afficherImage ( 60, 100, renderer, "asset/ui/FondVie.bmp");
                }
                break;

            case Auberge :
                Joueur.coord.x = PorteT[Ville].x;
                Joueur.coord.y = PorteT[Ville].y+1;
                numLaby = Ville;
                sol = "asset/map/SolV.bmp";
                mur = "asset/map/MurV.bmp";
                AfficherNiveau(labyrinthe,inventaire,Joueur,numLaby,argent,clignotant,renderer,persoBas,sol,mur,vieSpecial,invPos);
                if (ennemie[numLaby]) {
                    AfficherVieEnnemie(Dummies,numLaby,renderer);
                } else {
                    afficherImage ( 60, 100, renderer, "asset/ui/FondVie.bmp");
                }
                break;
            }
            break;
        case 'P' :
            switch (numLaby) {
            case Ville :
                Joueur.coord.x = PorteP[Prison].x;
                Joueur.coord.y = PorteP[Prison].y+1;
                numLaby = Prison;
                sol = "asset/map/SolP.bmp";
                mur = "asset/map/MurP.bmp";
                AfficherNiveau(labyrinthe,inventaire,Joueur,numLaby,argent,clignotant,renderer,persoBas,sol,mur,vieSpecial,invPos);
                AfficherPosition(numLaby,renderer);
                if (ennemie[numLaby]) {
                    AfficherVieEnnemie(Dummies,numLaby,renderer);
                } else {
                    afficherImage ( 60, 100, renderer, "asset/ui/FondVie.bmp");
                }
                break;

            case Prison :
                Joueur.coord.x = PorteP[Ville].x;
                Joueur.coord.y = PorteP[Ville].y-1;
                numLaby = Ville;
                sol = "asset/map/SolV.bmp";
                mur = "asset/map/MurV.bmp";
                AfficherNiveau(labyrinthe,inventaire,Joueur,numLaby,argent,clignotant,renderer,persoBas,sol,mur,vieSpecial,invPos);
                AfficherPosition(numLaby,renderer);
                if (ennemie[numLaby]) {
                    AfficherVieEnnemie(Dummies,numLaby,renderer);
                } else {
                    afficherImage ( 60, 100, renderer, "asset/ui/FondVie.bmp");
                }
                break;
            }
            break;

        }

        if ( labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x] == '-' && Joueur.coord.y == 2) {
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/SolP.bmp");
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/Grille.bmp");
            Joueur.coord.y++;
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/SolP.bmp");
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoHaut);
        }
        if ( labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x] == '-' && Joueur.coord.y == 5) {
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/SolP.bmp");
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/Grille.bmp");
            Joueur.coord.y--;
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/SolP.bmp");
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoBas);
        }
//                                        Gestion vie ennemie//
        if (ennemie[numLaby] == VRAI) {
            if ( Dummies[numLaby].vie <= 0) {
                labyrinthe[numLaby][Dummies[numLaby].coord.y][Dummies[numLaby].coord.x] = ' ';
                afficherImage ( 60, 100, renderer, "asset/ui/FondVie.bmp");
                afficherImage ( Dummies[numLaby].coord.x*60+75, Dummies[numLaby].coord.y*60+190, renderer, sol);
                if (numLaby == 2) {
                    labyrinthe[numLaby][Dummies[numLaby].coord.y][Dummies[numLaby].coord.x] = ':';
                    afficherImage ( Dummies[numLaby].coord.x*60+75, Dummies[numLaby].coord.y*60+190, renderer, "asset/map/coin1.bmp");
                }
                ennemie[numLaby] = FAUX;
            }
        }
//                                        Gestion vie ennemie//
        if ( labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x] == 'p' && invPos < 4) {
            inventaire[invPos].nom = "Clefs de la cellule";
            inventaire[invPos].pris = VRAI;
            inventaire[invPos].type = 0;
            possClefC = 1;
            invPos++;
            labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x] = ' ';
            AfficherEtatInventaire (renderer,invPos);
        } else if ( labyrinthe[numLaby][Joueur.coord.y-1][Joueur.coord.x] == 'p' || labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x+1] == 'p') {
            afficherImage ( 6*60+75, 1*60+190, renderer, sol);
            afficherImage ( 6*60+75, 1*60+190, renderer, "asset/map/ClefC.bmp");
        }

        if ( labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x] == 'C' && possClefC == 1) {
            switch (numLaby) {
            case Prison :
                Joueur.coord.x = Cell[Cellule].x;
                Joueur.coord.y = Cell[Cellule].y+1;
                numLaby = Cellule;
                if (describ == 1) {
                    describ = 2;
                }
                sol = "asset/map/SolC.bmp";
                mur = "asset/map/MurC.bmp";
                AfficherNiveau(labyrinthe,inventaire,Joueur,numLaby,argent,clignotant,renderer,persoBas,sol,mur,vieSpecial,invPos);
                AfficherPosition(numLaby,renderer);
                if (ennemie[numLaby]) {
                    AfficherVieEnnemie(Dummies,numLaby,renderer);
                } else {
                    afficherImage ( 60, 100, renderer, "asset/ui/FondVie.bmp");
                    afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoBas);
                }
                break;

            case Cellule :
                Joueur.coord.x = Cell[Prison].x;
                Joueur.coord.y = Cell[Prison].y-1;
                numLaby = Prison;
                sol = "asset/map/SolP.bmp";
                mur = "asset/map/MurP.bmp";
                AfficherNiveau(labyrinthe,inventaire,Joueur,numLaby,argent,clignotant,renderer,persoBas,sol,mur,vieSpecial,invPos);
                AfficherPosition(numLaby,renderer);
                if (ennemie[numLaby]) {
                    AfficherVieEnnemie(Dummies,numLaby,renderer);
                } else {
                    afficherImage ( 60, 100, renderer, "asset/ui/FondVie.bmp");
                }
                break;
            }
        } else if (labyrinthe[numLaby][Joueur.coord.y][Joueur.coord.x] == 'C') {
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/SolP.bmp");
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/Grille.bmp");
            Joueur.coord.y--;
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, "asset/map/SolP.bmp");
            afficherImage ( Joueur.coord.x*60+75, Joueur.coord.y*60+190, renderer, persoBas);
        }

//                                        Fin passage niveau//
        if (ennemie[2] == VRAI) {
            if (numLaby == Prison) {

                if (moduloGard == 1400) {

                    switch (inverserGardeP) {
                    case 0 :
                        if ((Dummies[Prison].coord.y == Joueur.coord.y && Dummies[Prison].coord.x+1 == Joueur.coord.x) || (Dummies[Prison].coord.y == Joueur.coord.y && Dummies[Prison].coord.x == Joueur.coord.x)) {
                            if (clignotant == 0) {
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = ' ';
                                Dummies[Prison].coord.x++;
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = 'G';
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/character/guard/GardeDroite.bmp");
                            } else {
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = ' ';
                                Dummies[Prison].coord.x--;
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = 'G';
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/character/guard/GardeDroite.bmp");
                            }
                        } else {
                            afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                            labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = ' ';
                            Dummies[Prison].coord.x++;
                            labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = 'G';
                            afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                            afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/character/guard/GardeDroite.bmp");
                            if (labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x+1] == '#') {
                                inverserGardeP = 1;
                            }
                        }
                        break;
                    case 1 :
                        if ((Dummies[Prison].coord.y-1 == Joueur.coord.y && Dummies[Prison].coord.x == Joueur.coord.x) || (Dummies[Prison].coord.y == Joueur.coord.y && Dummies[Prison].coord.x == Joueur.coord.x)) {
                            if (clignotant == 0) {
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = ' ';
                                Dummies[Prison].coord.y--;
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = 'G';
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/character/guard/GardeHaut.bmp");
                            } else {
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = ' ';
                                Dummies[Prison].coord.y++;
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = 'G';
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/character/guard/GardeHaut.bmp");
                            }
                        } else {
                            afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                            labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = ' ';
                            Dummies[Prison].coord.y--;
                            labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = 'G';
                            afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                            afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/character/guard/GardeHaut.bmp");
                            if (labyrinthe[numLaby][Dummies[Prison].coord.y-1][Dummies[Prison].coord.x] == '#') {
                                inverserGardeP = 2;
                            }
                        }
                        break;
                    case 2 :
                        if ((Dummies[Prison].coord.y == Joueur.coord.y && Dummies[Prison].coord.x-1 == Joueur.coord.x) || (Dummies[Prison].coord.y == Joueur.coord.y && Dummies[Prison].coord.x == Joueur.coord.x)) {
                            if (clignotant == 0) {
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = ' ';
                                Dummies[Prison].coord.x--;
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = 'G';
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/character/guard/GardeGauche.bmp");
                            } else {
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = ' ';
                                Dummies[Prison].coord.x++;
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = 'G';
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/character/guard/GardeGauche.bmp");
                            }
                        } else {
                            afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                            labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = ' ';
                            Dummies[Prison].coord.x--;
                            labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = 'G';
                            afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                            afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/character/guard/GardeGauche.bmp");
                            if (labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x-1] == '#') {
                                inverserGardeP = 3;
                            }
                        }
                        break;
                    case 3 :
                        if ((Dummies[Prison].coord.y+1 == Joueur.coord.y && Dummies[Prison].coord.x == Joueur.coord.x) || (Dummies[Prison].coord.y == Joueur.coord.y && Dummies[Prison].coord.x == Joueur.coord.x)) {
                            if (clignotant == 0) {
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = ' ';
                                Dummies[Prison].coord.y++;
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = 'G';
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/character/guard/GardeBas.bmp");
                            } else {
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = ' ';
                                Dummies[Prison].coord.y--;
                                labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = 'G';
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                                afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/character/guard/GardeBas.bmp");
                            }
                        } else {
                            afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                            labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = ' ';
                            Dummies[Prison].coord.y++;
                            labyrinthe[numLaby][Dummies[Prison].coord.y][Dummies[Prison].coord.x] = 'G';
                            afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/map/SolP.bmp");
                            afficherImage ( Dummies[Prison].coord.x*60+75, Dummies[Prison].coord.y*60+190, renderer, "asset/character/guard/GardeBas.bmp");
                            if (labyrinthe[numLaby][Dummies[Prison].coord.y+1][Dummies[Prison].coord.x] == '#') {
                                inverserGardeP = 0;
                            }
                        }
                        break;
                    }
                    moduloGard = 0;
                } else {
                    moduloGard++;
                }
            }
        }
        //                                          Partie Interaction Fin  //
    } while ( fin == 0 );

    switch (fin) {
    case 2 :
        afficherImage ( 0, 0, renderer, "asset/ui/YouDied.bmp");
        SDL_RenderPresent(renderer);
        SDL_Delay(5000);
        break;
    case 3 :
        afficherImage ( 0, 0, renderer, "asset/ui/YouWin.bmp");
        SDL_RenderPresent(renderer);
        SDL_Delay(5000);
        break;
    }
    return 0;
}
