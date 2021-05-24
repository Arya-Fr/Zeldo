#ifndef AFFICHAGE_C_INCLUDED
#define AFFICHAGE_C_INCLUDED

#include "affichage.h"

void afficherImage ( int x ,int y ,SDL_Renderer* renderer ,char* nomFichier )
{
     SDL_Surface* surface_image = SDL_LoadBMP (nomFichier);

     if ( surface_image )
     {
         SDL_Texture* image = SDL_CreateTextureFromSurface ( renderer , surface_image );

         if ( image )
         {
             SDL_SetRenderTarget ( renderer , image );

             SDL_Rect r;
             r.x = x;
             r.y = y;

             SDL_QueryTexture ( image, NULL, NULL, &(r.w), &(r.h));

             printf ("On rend l'image dans le rectangle %d %d %d %d\n", r.x, r.y, r.w, r.h);

             SDL_RenderCopy ( renderer , image , NULL , &r);
             SDL_SetRenderTarget ( renderer , NULL );
             SDL_DestroyTexture (image);
         }
         else {
            fprintf (stderr, "Erreur de création de la texture\n");
         }

         SDL_FreeSurface (surface_image);
     }
     else {
        fprintf (stderr, "Erreur de chargement de l'image %s\n", nomFichier);
     }
}

void AfficherBulleDialHist1 (){
    printf(" _____________________________________ \n");
    printf("/                                     |\n");
    printf("|C'est Ganan que vous cherchez ?      |\n");
    printf("|Il s'est enfuis par les ruines      ►|\n");
    printf("|_____________________________________/\n");
}

void AfficherInventaire (item inventaire[4],SDL_Renderer* renderer){
    int temp;
    for (int i = 0; i < 4; i++){
        if (inventaire[i].pris == TRUE){
            switch(i){
                case 1:temp = 342;break;
                case 3:temp = 350;break;
                default:temp = 345;break;
            }
            switch(inventaire[i].type){
                case 0 :
                    afficherImage(820,i*120+339,renderer,"asset/ui/icone/IconeClef.bmp");
                    afficherImage(937,i*120+temp,renderer,"asset/ui/icone/DescriClef.bmp");
                    break;
                case 1 :
                    afficherImage(820,i*120+339,renderer,"asset/ui/icone/IconePotion.bmp");
                    afficherImage(937,i*120+temp,renderer,"asset/ui/icone/DescriPotion.bmp");
                    break;
                case 2 :
                    afficherImage(820,i*120+339,renderer,"asset/ui/icone/IconeBouclier.bmp");
                    afficherImage(937,i*120+temp,renderer,"asset/ui/icone/DescriBouclier.bmp");
                    break;
                case 3 :
                    afficherImage(820,i*120+339,renderer,"asset/ui/icone/IconeEpee.bmp");
                    afficherImage(937,i*120+temp,renderer,"asset/ui/icone/DescriEpee.bmp");
                    break;
            }
        }
    }
}

void AfficherEtatInventaire (SDL_Renderer* renderer,int inv){
    switch(inv){
        case 0 :afficherImage ( 980, 0, renderer , "asset/ui/IndicInv0.bmp");break;
        case 1 :afficherImage ( 980, 0, renderer , "asset/ui/IndicInv1.bmp");break;
        case 2 :afficherImage ( 980, 0, renderer , "asset/ui/IndicInv2.bmp");break;
        case 3 :afficherImage ( 980, 0, renderer , "asset/ui/IndicInv3.bmp");break;
        case 4 :afficherImage ( 980, 0, renderer , "asset/ui/IndicInv4.bmp");break;
    }

}

void AfficherVie (Perso Joueur, int vieSpecial,SDL_Renderer* renderer){
    afficherImage ( 51, 0, renderer , "asset/ui/fond1.bmp");
    for (int i=0; i<Joueur.vie; i++) {
            afficherImage ( i*30+65, 45, renderer , "asset/ui/coeur.bmp");
        }
        for (int i=0; i<vieSpecial; i++) {
            afficherImage ( i*30+460, 45, renderer , "asset/ui/bouclier.bmp");
        }
}

void AfficherPosition (int numLaby, SDL_Renderer* renderer){
    switch(numLaby){
        case 0:afficherImage ( 1100 , 0, renderer , "asset/ui/SignV.bmp");break;
        case 1:afficherImage ( 1100 , 0, renderer , "asset/ui/SignB.bmp");break;
        case 2:afficherImage ( 1100 , 0, renderer , "asset/ui/SignP.bmp");break;
        case 3:afficherImage ( 1100 , 0, renderer , "asset/ui/SignC.bmp");break;
    }
}

void AfficherVieEnnemie (Perso Dummies[],int numLaby,SDL_Renderer* renderer){
    switch(numLaby){
        case 1:afficherImage ( 60 , 100, renderer , "asset/ui/VieMan.bmp");break;
        case 2:afficherImage ( 60 , 100, renderer , "asset/ui/VieGar.bmp");break;
        case 3:afficherImage ( 60 , 100, renderer , "asset/ui/VieMur.bmp");break;
    }
    for (int i=0; i<Dummies[numLaby].vie; i++) {
        afficherImage ( i*30+86, 128, renderer , "asset/ui/coeur.bmp");
    }
}

void AfficherRuby (int argent,SDL_Renderer* renderer,int etat){
    switch(etat){
        case 0:
            afficherImage ( 690 , 0, renderer , "asset/ui/FondChiffre.bmp");
            int temp;
            if (argent > 9 && argent < 20){
                temp = argent - 10;
                afficherImage ( 690 , 40, renderer , "asset/ui/Chiffre1.bmp");
                switch(temp){
                    case 0 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre0.bmp");break;
                    case 1 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre1.bmp");break;
                    case 2 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre2.bmp");break;
                    case 3 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre3.bmp");break;
                    case 4 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre4.bmp");break;
                    case 5 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre5.bmp");break;
                    case 6 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre6.bmp");break;
                    case 7 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre7.bmp");break;
                    case 8 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre8.bmp");break;
                    case 9 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre9.bmp");break;
                }
            }
            if (argent > 19 && argent < 29){
                temp = argent - 20;
                afficherImage ( 690 , 40, renderer , "asset/ui/Chiffre2.bmp");
                switch(temp){
                    case 0 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre0.bmp");break;
                    case 1 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre1.bmp");break;
                    case 2 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre2.bmp");break;
                    case 3 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre3.bmp");break;
                    case 4 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre4.bmp");break;
                    case 5 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre5.bmp");break;
                    case 6 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre6.bmp");break;
                    case 7 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre7.bmp");break;
                    case 8 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre8.bmp");break;
                    case 9 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre9.bmp");break;
                }
            }
            if (argent < 10){
                switch(argent){
                    case 0 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre0.bmp");break;
                    case 1 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre1.bmp");break;
                    case 2 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre2.bmp");break;
                    case 3 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre3.bmp");break;
                    case 4 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre4.bmp");break;
                    case 5 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre5.bmp");break;
                    case 6 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre6.bmp");break;
                    case 7 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre7.bmp");break;
                    case 8 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre8.bmp");break;
                    case 9 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre9.bmp");break;
                }
            }
            break;
        case 1:
            afficherImage ( 690 , 0, renderer , "asset/ui/FondChiffre.bmp");
            afficherImage ( 690+24 , 39, renderer , "asset/ui/FondChiffreR.bmp");
            if (argent < 10){
                switch(argent){
                    case 0 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre0.bmp");break;
                    case 1 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre1.bmp");break;
                    case 2 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre2.bmp");break;
                    case 3 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre3.bmp");break;
                    case 4 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre4.bmp");break;
                    case 5 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre5.bmp");break;
                    case 6 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre6.bmp");break;
                    case 7 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre7.bmp");break;
                    case 8 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre8.bmp");break;
                    case 9 : afficherImage ( 690+24 , 40, renderer , "asset/ui/Chiffre9.bmp");break;
                }
            }
            break;
    }

}

void AfficherNiveau (char labyrinthe [4][DIMY][DIMX+1], item inventaire[4],Perso Joueur,int numLaby,int argent,bool fond,char symbole[],int clignotant,SDL_Renderer* renderer, char* persoBas,char* sol,char* mur, int vieSpecial,int invPos){
    SDL_RenderClear(renderer);
    afficherImage ( 0, 0, renderer , "asset/ui/fond.bmp");
    AfficherVie(Joueur,vieSpecial,renderer);
    afficherImage ( 0 , 661, renderer , "asset/ui/CommandeBase.bmp");
    AfficherEtatInventaire (renderer,invPos);
    for ( int y = 0 ; y < DIMY; y++ ) {
            for ( int x = 0 ; x < DIMX; x++ ) {
                    switch (labyrinthe[numLaby][y][x]) {
                    case  '#' :
                        afficherImage ( x*60+75 , y*60+190, renderer , mur);
                        break;
                    case  '.' :
                        afficherImage ( x*60+75 , y*60+190, renderer , sol);
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/coin.bmp");
                        break;
                    case  ':' :
                        afficherImage ( x*60+75 , y*60+190, renderer , sol);
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/coin1.bmp");
                        break;
                    case  ' ' :
                        afficherImage ( x*60+75 , y*60+190, renderer , sol);
                        break;
                    case  'J' :
                        afficherImage ( x*60+75 , y*60+190, renderer , sol);
                        afficherImage ( Joueur.coord.x*60+75 , Joueur.coord.y*60+190, renderer , persoBas);
                        break;
                    case  'T' :
                        afficherImage ( x*60+75 , y*60+190, renderer , mur);
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/PorteB.bmp");
                        break;
                    case  'P' :
                        switch(numLaby){
                            case 0: afficherImage ( x*60+75 , y*60+190, renderer , mur);
                                    afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/PorteP1.bmp");
                                    break;
                            case 2: afficherImage ( x*60+75 , y*60+190, renderer , mur);
                                    afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/PorteP2.bmp");
                                    break;
                        }
                        break;
                    case  'p' :
                        afficherImage ( x*60+75 , y*60+190, renderer , sol);
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/ClefC.bmp");
                        break;
                    case  'V' :
                        afficherImage ( x*60+75 , y*60+190, renderer , sol);
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/character/shop/Marchand.bmp");
                        break;
                    case  '_' :
                        afficherImage ( x*60+75 , y*60+190, renderer , sol);
                        switch(x){
                            case 6:afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/Table1.bmp");break;
                            case 7:afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/Table2.bmp");break;
                            case 8:afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/Table3.bmp");break;
                        }
                        break;
                    case  'D' :
                        afficherImage ( x*60+75 , y*60+190, renderer , sol);
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/character/shop/Dummies.bmp");
                        break;
                    case  '|' :
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/SolC.bmp");
                        break;
                    case  '-' :
                        afficherImage ( x*60+75 , y*60+190, renderer , sol);
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/Grille.bmp");
                        break;
                    case  'C' :
                        afficherImage ( x*60+75 , y*60+190, renderer , sol);
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/Grille.bmp");
                        break;
                    case 'S' :
                        afficherImage ( x*60+75 , y*60+190, renderer , mur);
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/Sortie.bmp");
                        break;
                    case 'F' :
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/MurCc.bmp");
                        break;
                    case 'g' :
                        afficherImage ( x*60+75 , y*60+190, renderer , sol);
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/character/prisonner/Priso.bmp");
                        break;
                    case 'H' :
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/map/Trou.bmp");
                        break;
                    case 'G' :
                        afficherImage ( x*60+75 , y*60+190, renderer , sol);
                        afficherImage ( x*60+75 , y*60+190, renderer , "asset/character/guard/GardeDroite.bmp");
                        break;
                    }
            }
    }
    afficherImage ( Joueur.coord.x*60+75 , Joueur.coord.y*60+190, renderer , persoBas);
    AfficherPosition(numLaby,renderer);
    AfficherRuby(argent,renderer,0);
}

void AfficherMenu (SDL_Renderer* renderer, int posMenu, int actu){
    switch(posMenu){
        case 0:
            if (actu == 1)afficherImage ( 0 , 0, renderer , "asset/ui/actuMenu00.bmp");
            if (actu == 0)afficherImage ( 0 , 0, renderer , "asset/ui/actuMenu01.bmp");
            break;
        case 1:
            if (actu == 1)afficherImage ( 0 , 0, renderer , "asset/ui/actuMenu10.bmp");
            if (actu == 0)afficherImage ( 0 , 0, renderer , "asset/ui/actuMenu11.bmp");
            break;
        case 2:
            if (actu == 1)afficherImage ( 0 , 0, renderer , "asset/ui/actuMenu20.bmp");
            if (actu == 0)afficherImage ( 0 , 0, renderer , "asset/ui/actuMenu21.bmp");
            break;
        case 3:
            if (actu == 1)afficherImage ( 0 , 0, renderer , "asset/ui/actuMenu30.bmp");
            if (actu == 0)afficherImage ( 0 , 0, renderer , "asset/ui/actuMenu31.bmp");
            break;
    }

}

#endif // AFFICHAGE_C_INCLUDED
