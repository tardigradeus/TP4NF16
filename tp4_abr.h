#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED

typedef struct Intervalle {
    int b1;
    int b2;
} T_Inter;

typedef struct Noeud {
    T_Inter cle;
    struct Noeud* g;
    struct Noeud* d;
    int id;
} T_Noeud;

typedef T_Noeud* T_Arbre;

T_Noeud* creer_noeud(int Id_entreprise,T_Inter intervalle);
T_Inter* creer_inter(int b1, int b2);
void ajouter_noeud(T_Arbre* abr, T_Noeud* noeud);
T_Noeud* recherche(T_Arbre abr, T_Inter intervalle, int Id_entreprise );
int Supp_noeud(T_Arbre * abr, T_Inter intervalle, int Id_entreprise);
int modif_noeud(T_Arbre abr, T_Inter intervalle, int Id_entreprise,T_Inter Nouvelntervalle);
void affiche_abr(T_Arbre abr);
void affiche_entr( T_Arbre abr, int Id_entreprise);
void detruire_arbre(T_Arbre *abr);

// others

// 0 if int1 < int2, 1 if int1 > int2, -1 else
int compare(T_Inter int1, T_Inter int2);
int isEqual(T_Inter int1, T_Inter int2);
int isEqualNode(T_Noeud* n1, T_Noeud* n2);
// return the parent node
T_Noeud* getParent(T_Arbre abr, T_Inter intervalle, int Id_entreprise);
T_Noeud* getMin(T_Arbre abr);
T_Noeud* getMax(T_Arbre abr);
T_Arbre creerABR();
void addReservation(T_Arbre ABR);
void updateReservation(T_Arbre ABR);
void deleteReservation(T_Arbre ABR);
void displayIDReservation(T_Arbre ABR);

#endif // TP4_H_INCLUDED
