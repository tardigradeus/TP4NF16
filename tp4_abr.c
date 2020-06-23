#include "tp4_abr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

T_Noeud* creer_noeud(int Id_entreprise, T_Inter intervalle){
    T_Noeud* node = malloc(sizeof(node));
    node->id = Id_entreprise;
    node->cle = intervalle;
    node->d = NULL;
    node->g = NULL;
    return node;
}

T_Inter* creer_inter(int b1, int b2){
    if(b1 > b2){
        printf("Intervalle invalide\n");
        return NULL;
    }
    T_Inter* inter = malloc(sizeof(inter));
    inter->b1 = b1;
    inter->b2 = b2;
    return inter;
}

void ajouter_noeud(T_Arbre* abr, T_Noeud* noeud){
    if(!*abr){
        *abr = noeud;
        return;
    }
    int greater = compare(noeud->cle, (*abr)->cle);
    // go to the right if the current node is greater
    if(greater > 0){
        ajouter_noeud(&(*abr)->d, noeud);
    } else if(greater == 0) {
    // go to the left
        ajouter_noeud(&(*abr)->g, noeud);
    } else {
        printf("Erreur: l'intervalle est deja reservee\n");
    }
}

T_Noeud* recherche(T_Arbre abr, T_Inter intervalle, int Id_entreprise ){
    if(!abr) return NULL;
    int greater = compare(intervalle, abr->cle);
    // if intervalle is smaller
    if(greater == 0) {
        return recherche(abr->g, intervalle, Id_entreprise);
    } // is greater
    else if(greater > 0) {
        return recherche(abr->d, intervalle, Id_entreprise);
    } // overlap
    else {
        // if is equal
        if(isEqual(abr->cle, intervalle) && abr->id == Id_entreprise){
            return abr;
        }
    }
    return NULL;
}

int Supp_noeud(T_Arbre * abr, T_Inter intervalle, int Id_entreprise){

    // get the node to remove
    T_Noeud* node = recherche(*abr, intervalle, Id_entreprise);
    if(!node) return 0;
    // get the node's parent
    T_Noeud* parent = getParent(*abr, intervalle, Id_entreprise);
    int fromLeft = 0;
    if(parent && isEqualNode(parent->g, node)){
        fromLeft = 1;
    }
    // two children
    if(node->d && node->g){
        T_Noeud* min = getMin(node->d);
        T_Noeud* minParent = getParent(abr, min->cle, Id_entreprise);
        minParent->g = min->d;
        min->d = node->d;
        if(parent){
            if(fromLeft){
                parent->g = min;
            } else {
                parent->d = min;
            }
        } else {
            *abr = min;
        }
    }
    // only right child
    else if(node->d){
        if(parent) {
            if(fromLeft){
                parent->g = node->d;
            } else {
                parent->d = node->d;
            }
        } else {
            *abr = node->d;
        }
    }
    // only left child
    else if(node->g){
        if(parent) {
            if(fromLeft){
                parent->g = node->g;
            } else {
                parent->d = node->g;
            }
        } else {
            *abr = node->d;
        }
    }
    // no children
    else {
        if(parent){
            if(fromLeft){
                parent->g = NULL;
            } else {
                parent->d = NULL;

            }
        } else {
            *abr = NULL;
        }
    }
    free(node);
    return 1;
}

int modif_noeud(T_Arbre abr, T_Inter intervalle, int Id_entreprise, T_Inter nouvelIntervalle){

        // if node is removed, add the new one
        if(Supp_noeud(&abr, intervalle, Id_entreprise) == 0){
            // if the new interval is already used, add the old one
            if(recherche(abr, nouvelIntervalle, Id_entreprise)){
                T_Noeud* exNode = creer_noeud(Id_entreprise, intervalle);
                ajouter_noeud(&abr, exNode);
                return 0;
            } // else, the new one can be added
            else {
                T_Noeud* node = creer_noeud(Id_entreprise, nouvelIntervalle);
                ajouter_noeud(&abr, node);
                return 1;
            }
        }
        // else, node is not found
        return 0;
}

void affiche_abr(T_Arbre abr){
    if(!abr) return NULL;
    affiche_abr(abr->g);
    printf("ID_Entr:%d -- [%d ; %d]\n", abr->id, abr->cle.b1, abr->cle.b2);
    affiche_abr(abr->d);
    return;
}

void affiche_entr( T_Arbre abr, int Id_entreprise){
    if(!abr) return;
    affiche_entr(abr->g, Id_entreprise);
    if(abr->id == Id_entreprise) printf("[%d,%d]\n", abr->cle.b1, abr->cle.b2);
    affiche_entr(abr->d, Id_entreprise);
}

void detruire_arbre(T_Arbre *abr){
    if(!*abr) return;
    detruire_arbre(&(*abr)->g);
    detruire_arbre(&(*abr)->d);
    free(*abr);
}

// secondary functions

int compare(T_Inter int1, T_Inter int2) {
    // greater
    if(int1.b1 > int2.b2) return 1;
    // smaller
    if(int2.b1 > int1.b2) return 0;
    // overlapped
    return -1;
}

int isEqual(T_Inter int1, T_Inter int2) {
    return int2.b2 == int1.b2 && int2.b1 == int1.b1;
}

int isEqualNode(T_Noeud* n1, T_Noeud* n2) {
    if(!n1 || !n2) return 0;
    return n1->id == n2->id && isEqual(n1->cle, n2->cle);
}

T_Noeud* getMin(T_Arbre abr){
    // if left not null, return left
    if(abr->g){
        return getMin(abr->g);
    } else {
        return abr;
    }
}

T_Noeud* getMax(T_Arbre abr){
    // if right not null, return left
    if(abr->d){
        return getMax(abr->d);
    } else {
        return abr;
    }
}

T_Noeud* getParent(T_Arbre abr, T_Inter intervalle, int Id_entreprise){
    // if one of the children = node, return root
    if(abr->d && isEqual(intervalle, abr->d->cle) && abr->d->id == Id_entreprise) {
        return abr;
    } else if(abr->g && isEqual(intervalle, abr->g->cle) && abr->g->id == Id_entreprise) {
        return abr;
    } else {
        int comparison = compare(intervalle, abr->cle);
        // if intervalle < root -> go to the left
        if(comparison == 0){
            return getParent(abr->g, intervalle, Id_entreprise);
        } else if (comparison == 1) {
            // if intervalle > root -> go to the right
            return getParent(abr->d, intervalle, Id_entreprise);
        } // else no parent or no corresponding child
    }
    return NULL;
}

T_Arbre creerABR(){
    int id, d1, d2;
    printf("Indiquez l'identifiant de l'entreprise\n");
    scanf("%d", &id);
    printf("Indiquez le debut de l'intervalle correspondant a votre reservation\n");
    scanf("%d", &d1);
    printf("Indiquez la fin de l'intervalle correspondant a votre reservation\n");
    scanf("%d", &d2);

    if(d2 < d1){
        printf("La reservation n'est pas valide\n");
        return NULL;
    }
    T_Inter* inter = creer_inter(d1, d2);
    T_Arbre abr = creer_noeud(id, *inter);
    printf("L'arbre a ete cree avec [%d-%d]\n", abr->cle.b1, abr->cle.b2);
    return abr;
}

void addReservation(T_Arbre ABR){
    int id, d1, d2;
    printf("Indiquez l'identifiant de l'entreprise\n");
    scanf("%d", &id);
    printf("Indiquez le debut de l'intervalle correspondant a votre reservation\n");
    scanf("%d", &d1);
    printf("Indiquez la fin de l'intervalle correspondant a votre reservation\n");

    scanf("%d", &d2);
    if(d2 < d1){
        printf("La reservation n'est pas valide\n");
        return;
    }
    T_Inter* intervalleReservation = creer_inter(d1, d2);
    //creation du noeud
    T_Noeud* nouveauNoeud = creer_noeud(id, *intervalleReservation);
    ajouter_noeud(&ABR, nouveauNoeud);
}

void updateReservation(T_Arbre ABR){
    int id, d1, d2, d11, d22;
    T_Inter ancienIntervalle;
    T_Inter* nouvelIntervalle;

    printf("identifiant de l'entreprise a modifier:\n");
    scanf("%d",&id);
    printf("debut de l'intervalle a modifier:\n");
    scanf("%d",&d1);
    printf("fin de l'intervalle a modifier:\n");
    scanf("%d",&d2);

    ancienIntervalle.b1=d1;
    ancienIntervalle.b2=d2;

    printf("debut de l'intervalle de la nouvelle reservation:\n");
    scanf("%d",&d11);
    printf("fin de l'intervalle de la nouvelle reservation:\n");
    scanf("%d",&d22);

    if(d22 < d11){
        printf("La reservation n'est pas valide\n");
        return;
    }

    nouvelIntervalle = creer_inter(d11, d22);

    if (modif_noeud(ABR, ancienIntervalle, id, *nouvelIntervalle) == 1){
         printf("L'intervalle a ete modifie.\n");
    } else {
        printf("L'intervalle n'a pas pu etre modifie.\n");
    }
}

void deleteReservation(T_Arbre ABR){
    int id, d1, d2;
    T_Inter intervalle;
    printf("nom de l'entreprise dont la reservation est a supprimer:\n");
    scanf("%d",&id);
    printf("date de debut de la reservation a supprimer:\n");
    scanf("%d",&d1);
    printf("date de fin de la reservation a supprimer:\n");
    scanf("%d",&d2);
    intervalle.b1=d1;
    intervalle.b2=d2;

    Supp_noeud(&ABR, intervalle,id);
}

void displayIDReservation(T_Arbre ABR){
    int id;
    printf("identifiant de l'entreprise dont les reservations sont a afficher:\n");
    scanf("%d",&id);
    affiche_entr(ABR, id);
}
