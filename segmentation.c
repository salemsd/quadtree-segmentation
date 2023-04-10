#include "graphique.h"
#include "particule.h"
#include "zone.h"
#include <time.h>

void test(){
    srand(time(NULL));

    Zone zone = init_zone(512, 8, 6, 4);

    QuadTree Q = init_quadtree(0, 0, zone.W_H, zone.W_H, 0);
    
    init_fenetre(zone.W_H);

    for (int i = 0; i < zone.Np; i++){
        zone.tab_part[i] = getParticule(zone.W_H);
        insert_quadtree(&Q, zone.tab_part[i], &zone, Q->plist);
        zone.curlen++;
    }
    
    dessineParticules(&zone);
    dessineZones(Q);

    MLV_wait_seconds(100);

    free_tab_part(&zone);
    MLV_free_window();
}

int main(void){
    test();
}