#ifndef __GRAPHIQUE_H
#define __GRAPHIQUE_H

#include <MLV/MLV_all.h>

#include "particule.h"
#include "quadtree.h"
#include "zone.h"

void init_fenetre(int W_H);

MLV_Color couleur_transparente(MLV_Color couleur, int alpha);

void gestion_clic(QuadTree *Q, Zone *zone);

void dessineZones(QuadTree Q);

void dessineParticules(Zone *zone);

#endif