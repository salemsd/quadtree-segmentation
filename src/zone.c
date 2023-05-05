#include <stdlib.h>
#include <stdio.h>

#include "zone.h"

Zone init_zone(int nbPoint, int W_H, int wmin, int Kp){
    Zone zone;
    
    zone.Np = 0;
    zone.Kp = Kp;
    zone.W_H = W_H;
    zone.wmin = wmin;
    zone.tab_part = (Particule *) malloc(nbPoint * sizeof(Particule));

    return zone;
}

void free_tab_part(Zone *zone){
    free(zone->tab_part);
    zone->tab_part = NULL;
    printf("Toutes les particules ont été libérées\n");
}

void init_tab_particule_rand(Zone *zone){
    for(int i = 0 ; i < zone->Np; i++){
        zone->tab_part[i] = getParticule(zone->W_H);
    }
}

void get_zone_data(int mode, int *W_H, int *wmin, int *Kp, int *nbPoint, int *vitesse){
    int lu = 0;

    do {
        int c;
        printf("Veuillez entrer la taille de la zone initiale(puissance de 4): ");
        lu = scanf("%d", W_H);
        while ( (c = getchar()) != '\n' && c != EOF && (*W_H) % 4 != 0);
    }while (lu == 0);
    
    lu = 0;
    do {
        int c;
        printf("Veuillez entrer wmin (puissance de 4): ");
        lu = scanf("%d", wmin);
        while ( (c = getchar()) != '\n' && c != EOF && (*wmin) % 4 != 0);
    }while (lu == 0);

    lu = 0;
    do {
        int c;
        printf("Veuillez entrer Kp: ");
        lu = scanf("%d", Kp);
        while ( (c = getchar()) != '\n' && c != EOF);
    }while (lu == 0);
    
    if (mode == 1){
        lu = 0;
        do {
            int c;
            printf("Veuillez entrer un nombre entier pour le nombre de points: ");
            lu = scanf("%d", nbPoint);
            while ( (c = getchar()) != '\n' && c != EOF);
        }while (lu == 0);
        
        lu = 0;
        do {
            int c;
            printf("Veuillez entrer un nombre entier pour la vitesse: ");
            lu = scanf("%d", vitesse);
            while ( (c = getchar()) != '\n' && c != EOF);
        }while (lu == 0);
    }
}