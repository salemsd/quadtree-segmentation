#ifndef __MENU_H
#define __MENU_H

#define SIZE_X 800
#define SIZE_Y 800

/////////////////////////////////
// Fonctions fenêtre et dessin //
/////////////////////////////////

/**
 * @brief Ouvre le menu principal du programme
 * 
 * @param mode Mode du programme (aléatoire ou clic-souris)
 * @param forme Forme de la génération aléatoire si mode aléatoire (carré ou cercle)
 * @param deroulement Mode d'affichage si aléatoire (Point par point ou terminal)
 */
void menu(int *mode);

/**
 * @brief Renvoie si la souris est sur un bouton ou non
 * 
 * @param x Coordonnée x de la souris
 * @param y Coordonnée y de la souris
 * @param x_button Coordonnée x du coin supérieur gauche du bouton
 * @param y_button Coordonnée y du coin supérieur gauche du bouton
 * @param widthButton Largeur du bouton
 * @param heightButton Hauteur du bouton
 * @return 1 si la souris est sur le bouton, 0 sinon
 */
int mouseOnButton(int x, int y, int x_button, int y_button, int widthButton, int heightButton);

#endif