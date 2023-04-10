#include "graphique.h"
#include "particule.h"
#include "zone.h"

void test(){
    MLV_create_window("test", "t", 512, 512);
    MLV_clear_window(MLV_COLOR_WHITE);

    Zone zone;
    zone.Np = 0;

    Particule part;
    while(zone.Np != 20){
        part = getParticule(512);
        zone.Np++;
        MLV_draw_filled_circle(part.x, part.y, 2, MLV_COLOR_BLACK);
        MLV_actualise_window();
    }

    MLV_wait_seconds(10);
    MLV_free_window();
}

int main(void){
    test();
}