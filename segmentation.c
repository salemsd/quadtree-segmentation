#include "graphique.h"
#include "particule.h"
#include "zone.h"

void test(){
    Zone zone = init_zone(512, 8, 0, 10);

    QuadTree Q = init_quadtree(0, 0, zone.W_H, zone.W_H, zone.Np);
    
    init_fenetre(zone.W_H);

    for (int i = 0; i < 2000; i++){
        zone.tab_part[i] = getParticule(512);
        insert(&Q, zone.tab_part[i], zone);
        zone.Np++;
    }
    
    dessineParticules(&zone);
    dessineZones(Q);

    MLV_wait_seconds(10);
    MLV_free_window();
}

int main(void){
    test();
}