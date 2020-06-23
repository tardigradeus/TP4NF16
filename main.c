#include <stdio.h>
#include <stdlib.h>
#include "tp4_abr.h"

int main() {

    T_Arbre ABR;

    int choice = -1;
    while(choice != 8) {
        printf("Choisir l'option voulue:\n");
        printf("1. Creeer un ABR \n");
        printf("2. Afficher toutes les reservations \n");
        printf("3. Ajouter une reeservation \n");
        printf("4. Modifier une reservation \n");
        printf("5. Supprimer une reeservation \n");
        printf("6. Afficher les reservations d'une entreprise \n");
        printf("7. Supprimer l'arbre \n");
        printf("8. Quitter \n");


        scanf("%d", &choice);
        switch(choice){
            case 1: ABR = creerABR();
                break;
            case 2: affiche_abr(ABR);
                break;
            case 3: addReservation(ABR);
                break;
            case 4: updateReservation(ABR);
                break;
            case 5: deleteReservation(ABR);
                break;
            case 6: displayIDReservation(ABR);
                break;
            case 7: detruire_arbre(&ABR);
                break;
            case 8: break;
            default: printf("L'entrée est erronnée. Réessayez:\n");
        }
        if(choice == 8) break;
    }
}
