#include <MLV/MLV_all.h>
#include "menu.h"
#include "graphique.h"


int mouseOnButton(int x, int y, int x_button, int y_button, int widthButton, int heightButton){
    return (x >= x_button && x <= x_button + widthButton) && (y >= y_button && y <= y_button + heightButton);
}

void menu(int *mode){
    init_fenetre(SIZE_X);
    MLV_clear_window(MLV_COLOR_BLACK);

    int x, y;
    int widthButton1, heightButton1, widthButton2, heightButton2;
    
    MLV_draw_text(SIZE_X/2.3, 100, "QuadTree", MLV_COLOR_WHITE);
    MLV_draw_text(SIZE_X/2.8, 325, "Choisissez le mode du programme", MLV_COLOR_WHITE);

    int x_button1 = SIZE_X/4.2; 
    int x_button2 = SIZE_X/1.55; 
    int y_buttons = SIZE_Y/2; 

    MLV_draw_adapted_text_box(x_button1, y_buttons, "Souris", 10, MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    MLV_draw_adapted_text_box(x_button2, y_buttons, "Aléatoire", 10, MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    MLV_get_size_of_adapted_text_box("Souris", 10, &widthButton1, &heightButton1);
    MLV_get_size_of_adapted_text_box("Aléatoire", 10, &widthButton2, &heightButton2);

    MLV_actualise_window();

    // Choix souris et aléatoire
    int button1 = 0; int button2 = 0;
    do{
        MLV_wait_mouse(&x, &y);

        if (mouseOnButton(x, y, x_button1, y_buttons, widthButton1, heightButton1)){
            button1 = 1;
        }
        else if (mouseOnButton(x, y, x_button2, y_buttons, widthButton2, heightButton2)){
            button2 = 1;
        }
    } while (!button1 && !button2);

    
    // Modes:
    // Souris = 1
    // Aleatoire = 0
    if (button1){
        *mode = 0;
        MLV_free_window();
        return;
    }
    else if (button2){
        *mode = 1;
        MLV_free_window();
        return;
    }
}