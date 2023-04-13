#include "graphique.h"
#include "particule.h"
#include "zone.h"
#include <time.h>

void test(){
    srand(time(NULL));

    Zone zone = init_zone(512, 8, 200, 10);

    QuadNode *Q = init_quadtree(zone);

    init_fenetre(zone.W_H);

    // for (int i = 0; i < zone.Np; i++){
    //     zone.tab_part[i] = getParticule(zone.W_H);
    //     insert_quadtree(&Q, zone.tab_part[i], &zone, Q->plist);
    //     zone.curlen++;
    // }
    
    gestion_clic(&Q, &zone);

    MLV_wait_seconds(100);

    free_tab_part(&zone);
    MLV_free_window();
}


int main(void){
    test();
}






