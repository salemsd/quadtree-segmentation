#include "graphique.h"
#include "particule.h"
#include "zone.h"
#include "menu.h"
#include <time.h>


void test(){
    int mode; /* Par défaut 0: Clic souris; 1: Aléatoire */
    int nbPoint;
    int vitesse;
    srand(time(NULL));
    Zone zone;
    int W_H, wmin, Kp;
    QuadNode *Q;
    ListeCell tab_plist;

    menu(&mode);

    get_zone_data(mode, &W_H, &wmin, &Kp, &nbPoint, &vitesse);

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






