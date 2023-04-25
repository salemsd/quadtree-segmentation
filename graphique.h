#ifndef __GRAPHIQUE_H
#define __GRAPHIQUE_H

#include <MLV/MLV_all.h>

#include "particule.h"
#include "quadtree.h"
#include "zone.h"

void init_fenetre(int W_H);

MLV_Color couleur_transparente(MLV_Color couleur, int alpha);

void gestion_clic(QuadTree Q, ListeCell tab_plist, Zone *zone);

void gestion_aleatoire(QuadTree Q, ListeCell tab_plist, Zone *zone, int nbPoint);

int touche_bord(Zone zone, int i);

void dessineZones(QuadTree Q, Zone zone, int indice);

void dessineParticules(Zone *zone);

#endif