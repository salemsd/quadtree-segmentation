#include "graphique.h"
#include "particule.h"
#include "zone.h"
#include "menu.h"
#include <time.h>

void test(){
    int mode; /* Par défaut 0: Clic souris; 1: Aléatoire */
    int nbPoint;
    int vitesse;
    int lu = 0;
    srand(time(NULL));
    Zone zone;
    int W_H, wmin, Kp;
    QuadNode *Q;
    ListeCell tab_plist;

    menu(&mode);
    do {
        int c;
        printf("Veuillez entrer la taille de la zone initiale(puissance de 4): ");
        lu = scanf("%d", &W_H);
        while ( (c = getchar()) != '\n' && c != EOF && W_H % 4 != 0);
    }while (lu == 0);
    
    lu = 0;
    do {
        int c;
        printf("Veuillez entrer wmin (puissance de 4): ");
        lu = scanf("%d", &wmin);
        while ( (c = getchar()) != '\n' && c != EOF && wmin % 4 != 0);
    }while (lu == 0);

    lu = 0;
    do {
        int c;
        printf("Veuillez entrer Kp: ");
        lu = scanf("%d", &Kp);
        while ( (c = getchar()) != '\n' && c != EOF);
    }while (lu == 0);
    
    if (mode == 1){
        lu = 0;
        do {
            int c;
            printf("Veuillez entrer un nombre entier pour le nombre de points: ");
            lu = scanf("%d", &nbPoint);
            while ( (c = getchar()) != '\n' && c != EOF);
        }while (lu == 0);
        
        lu = 0;
        do {
            int c;
            printf("Veuillez entrer un nombre entier pour la vitesse: ");
            lu = scanf("%d", &vitesse);
            while ( (c = getchar()) != '\n' && c != EOF);
        }while (lu == 0);
    }

    MLV_execute_at_exit(exit_function, &arret);

    /* Clic souris */
    if (mode == 0){
        zone = init_zone(NMAX, W_H, wmin, Kp);
        tab_plist = init_plist(zone, NMAX);
        Q = init_quadtree(zone);

        init_fenetre(zone.W_H);

        gestion_clic(Q, tab_plist, &zone);
    }
    /* Aléatoire */
    else{
        zone = init_zone(nbPoint, W_H, wmin, Kp);
        tab_plist = init_plist(zone, nbPoint);
        Q = init_quadtree(zone);

        init_fenetre(zone.W_H);

        fill_tabs(&zone, tab_plist, nbPoint, vitesse);
        gestion_aleatoire(Q, tab_plist, &zone, nbPoint);
    }


    free_tab_part(&zone);
    free_plist(tab_plist);
    free_quadtree(Q, zone);
    MLV_free_window();
}


int main(void){
    test();
}






