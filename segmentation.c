#include "graphique.h"
#include "particule.h"
#include "zone.h"
#include <time.h>

void test(){
    srand(time(NULL));

    Zone zone = init_zone(512, 8, 4);
    // ListeCell tab_plist = init_plist(zone);

    QuadNode *Q = init_quadtree(zone);

    for (int i = 0; i < 15; i++){
        printf("x1 %d y1 %d x2 %d y2 %d\n", Q[i].x1, Q[i].y1, Q[i].x2, Q[i].y2);
    }

    init_fenetre(zone.W_H);
    
    gestion_clic(&Q, &zone);

    MLV_wait_seconds(100);

    free_tab_part(&zone);
    MLV_free_window();
}


int main(void){
    test();
}






