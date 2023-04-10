#include <stdlib.h>

#include "quadtree.h"
#include "cellules.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

QuadTree init_quadtree(int x1, int y1, int x2, int y2, int nbp){
    QuadTree new_tree = (QuadTree) malloc(sizeof(QuadNode));
    if( new_tree){
        new_tree->n1 = new_tree->n2 = new_tree->n3 = new_tree->n4 = NULL;
        new_tree->plist = NULL;
        
        new_tree->nbp = nbp;
        new_tree->x1 = x1;
        new_tree->y1 = y1;
        new_tree->x2 = x2;
        new_tree->y2 = y2;
    }
    
    return new_tree ;
}

QuadTree find_node(QuadTree Q, Particule part) {
    if (Q->n1 && Q->n2 && Q->n3 && Q->n4 == NULL) {
        return Q;
    }
    else {
        int x_milieu = (Q->x1 + Q->x2) / 2;
        int y_milieu = (Q->y1 + Q->y2) / 2;

        if (part.x < x_milieu) {
            if (part.y < y_milieu) {
                return find_node(Q->n1, part);
            } 
            else {
                return find_node(Q->n2, part);
            }
        } 
        else {
            if (part.y < y_milieu) {
                return find_node(Q->n4, part);
            } 
            else {
                return find_node(Q->n3, part);
            }
        }
    }
}



void insert(QuadTree *qt, Particule p, Zone zone) {
    /* Recherche du noeud où insérer la particule */
    QuadTree node = find_node(*qt, p);


    double xmid = (node->x1 + node->x2) / 2.0;
    double ymid = (node->y1 + node->y2) / 2.0;



    if (node->nbp < zone.Kp) {
        zone.tab_part[zone.Np] = p ;
        node->plist = insere_queue(&node->plist, &p);
        node->nbp++;
        return;
    }
    else {
        double dist ;
        int min_child = 1 ;
        double min_dist = MAX (abs(p.x - (node->n1->x1 + node->n1->x2) / 2.0), abs(p.y - (node->n1->y1 + node->n1->y2) / 2.0));

        dist = MAX (abs(p.x - (node->n2->x1 + node->n2->x2) / 2.0), abs(p.y - (node->n2->y1 + node->n2->y2) / 2.0));

        if(dist < min_dist){
            min_dist = dist ;
            min_child = 2 ;
        }

        dist = MAX (abs(p.x - (node->n3->x1 + node->n3->x2) / 2.0), abs(p.y - (node->n3->y1 + node->n3->y2) / 2.0));

        if(dist < min_dist){
            min_dist = dist ;
            min_child = 3 ;
        }

        dist = MAX (abs(p.x - (node->n4->x1 + node->n4->x2) / 2.0), abs(p.y - (node->n4->y1 + node->n4->y2) / 2.0));
        if(dist < min_dist){
            min_dist = dist ;
            min_child = 4 ;
        }

        switch (min_child) {
            case 1:
                if (!node->n1) {
                    node->n1 = init_quadtree(node->x1, node->y1, xmid, ymid , 0);
                }
                insert(&(node->n1), p, zone);
                break;
            case 2:
                if (!node->n2) {
                    node->n2 = init_quadtree(node->x1, ymid, xmid, node->y2 , 0);
                }
                insert(&(node->n2), p, zone);
                break;
            case 3:
                if (!node->n3) {
                    node->n3 = init_quadtree(xmid, node->y1, node->x2, ymid, 0 );
                }
                insert(&(node->n3), p, zone);
                break;
            case 4:
                if (!node->n4) {
                    node->n4 = init_quadtree(xmid, ymid, node->x2, node->y2, 0 );
                }
                insert(&(node->n4), p, zone);
                break;
        }
    }
}


