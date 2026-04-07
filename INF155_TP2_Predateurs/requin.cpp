/******************************************************************************/
/* requin.CPP                                                                  */
/* Librairie des m�chants requins (pr�dateurs).                               */
/******************************************************************************/
#include "requin.h"
#include "util.h"
#include <stdlib.h>
#include <assert.h>


/******************************************************************************/
/*                      D�FINITIONS DES FONCTIONS PRIV�ES                     */
/******************************************************************************/

/************************** INSERT REQUIN (fonction PRIV�E) ********************/
/* Fonction PRIV�E qui ajoutera un requin a la fin de la liste des requins.   */
/* Retourne 1 si le requin a pu etre ajout�, 0 sinon (plus de place).         */
/******************************************************************************/
static int insert_requin(t_liste_requins * Liste_requin, const t_animal* jaws) {
     
    if(Liste_requin->nb_requin<MAX_REQUIN){

        // Écriture dans la prochaine case libre 
        Liste_requin->Liste[Liste_requin->nb_requin] = *jaws;

        // Ajout d'un nouveau requin dans le compteur du nombre de requin
        Liste_requin->nb_requin++; 

        return 1;   // Requin ajouté à la liste
    }

    return 0;   // Requin non ajouté à la liste car pleine
}

/************************ NEW REQUIN (fonction PRIV�E) *************************/
/* Re�oit la grille de la mer.                                                */
/* Va cr�er un nouveau requin al�atoire dans une case libre de la mer.        */
/******************************************************************************/
static t_animal new_requin(t_ocean mer) {
  
    t_animal nouveau;
    int x, y, age, energie, gestation;

    // Choix aléatoire d'une case dans la grille pour un nouveau requin
    do{

        x = alea(0, LARGEUR - 1) ; // Position en x
        y = alea(0, HAUTEUR - 1); // Position en y 

    } while (contenu_case(mer, x, y) != VIDE); // Tant que la case n'est pas vide

    age = alea(0, MAX_AGE_SHRK);
    energie = alea(JRS_DIGESTION, JRS_DIGESTION * 4);

    if (age >= NB_JRS_PUB_SHRK) {
        gestation = alea(1, NB_JRS_GEST_SHRK);
    } else{
        gestation = 0;
    }

    /* Initialisation du requin: position x & y trouvé ci-dessus, attribution d'un âge choisi
    aléatoirement entre [0, MAX_AGE_SHRK], une énergie aléatoire entre [JRS_DIGESTION, JRS_DIGESTION * 4] 
    et initialisation du nombre de jours de gestation selon l'âge.*/
    init_animal(&nouveau, x, y, age, energie, gestation);

    return nouveau;

}

/******************************************************************************/
/*                     D�FINITIONS DES FONCTIONS PUBLIQUES                    */
/******************************************************************************/

/***************************** VIDER LISTE REQUIN ******************************/
/* Va vider la liste des requins (�tat initial).                              */
/******************************************************************************/
void vider_liste_requin(t_liste_requins *Liste_requin){

    Liste_requin->nb_requin = 0;
}

/************************** REMPLIR LISTE REQUIN *******************************/
/* Re�oit la liste de requins, un nombre de requins et la grille de la mer.   */
/* Va remplir la liste avec les "nb_requins" premiers requins.                */
/******************************************************************************/
void remplir_liste_requin(t_liste_requins* les_requin, int nb_requins, t_ocean la_Mer) {
  
    t_animal nouveau;
    int i, x, y;

    les_requin->nb_requin = 0; // S'assurer que la liste est vide au départ

    for (i = 0; i < nb_requins; i++){

        nouveau = new_requin(la_Mer); // Création d'un nouveau requin

        // Ajout d'un requin dans la liste
        if(insert_requin(les_requin, &nouveau)){

            // Récupérer la position du nouveau requin créé dans var nouveau
            get_position (&nouveau, &x, &y);

            // Mettre le requin dans la grille de l'océan
            remplir_case(la_Mer, x, y, REQUIN, les_requin->nb_requin-1);
        }
    }
}

/****************************** GET NB REQUINS *********************************/
/* Retoure le nombre actuel de requins dans la liste.                         */
/******************************************************************************/
int  get_nb_requins(const t_liste_requins *Liste_requin){

    return Liste_requin->nb_requin;
}

/******************************* DEPLACER REQUIN *******************************/
/* Re�oit un requin, sa position dans la liste et la grille de la mer.        */
/* Va tenter de d�placer le requin vers un case voisine vide.                 */
/* Retourne 1 si le requin a �t� d�plac�, 0 sinon.                            */
/******************************************************************************/
int  deplacer_requin(t_animal *jaws, int no, t_ocean mer){

    int x, y, nx, ny;

    get_position(jaws, &x, &y); // Récupérer la position actuelle

    // Si aucune case voisine n'est libre, le requin ne se déplace pas
    if (nb_voisins_libre(mer, x, y) == 0){
      return 0;
    }

    // Initialiser la nouvelles position avec la position en x et y actuelle
    nx = x;
    ny = y;
  
    // Trouver une case voisine libre aléatoirement
    trouve_voisin_alea(mer, &nx, &ny);

    // Vider l'ancienne position du requin du requin
    remplir_case(mer, x, y, VIDE, RIEN);
  
    // Remplir la nouvelle case avec les informations du requin
    remplir_case(mer, nx, ny, REQUIN, no); 
  
    // Mettre à jour la nouvelle position du requin
    set_position(jaws, nx, ny);
  
    return 1; // Déplacement réussi    
}

/***************************** AJOUTER REQUIN **********************************/
/* Re�oit la liste des requins, un requin-m�re et la grille de la mer.        */
/* Va tenter d'ajouter un nouveau b�b�-requin dans une case voisine libre     */
/* du requin re�u en param�tre.                                               */
/* Retourne 1 si le nouveau b�b�-requin a �t� cr�e, 0 sinon.                  */
/******************************************************************************/
int  ajouter_requin(t_liste_requins *Liste_requin, t_animal *mamash, t_ocean mer){ 
    
    t_animal bebe;
    int x, y;

    get_position(mamash, &x, &y); // Récupérer la position du requin-parent

    // Si aucune case voisine n'est libre, aucun bébé ne naît
    if (nb_voisins_libre(mer, x, y) == 0) {
        return 0;
    }

    // Si la liste est pleine, on ne crée pas de nouveau requin
    if (Liste_requin->nb_requin >= MAX_REQUIN) {
        reset_gestation(mamash, -NB_JRS_GEST_SHRK);
        return 0;
    }

    // Choisir une case voisine libre pour le bébé
    trouve_voisin_alea(mer, &x, &y);

    // Initialiser le bébé-requin
    init_animal(&bebe, x, y, 0, JRS_DIGESTION * 3, 0);

    // Réinitialiser la gestation du parent
    reset_gestation(mamash, -NB_JRS_GEST_SHRK);

    // Ajouter le bébé à la fin de la liste
    if (insert_requin(Liste_requin, &bebe)) {

        // Inscrire le bébé dans la grille de l'océan
        remplir_case(mer, x, y, REQUIN, Liste_requin->nb_requin - 1);

        return 1; // Nouveau requin créé
    }

   return 0;      
}

/******************************* TUER REQUIN **********************************/
/* Va �liminer un requin de la liste, on remplace l'�l�ment supprim� par le   */
/* dernier dans le tableau.                                                   */
/******************************************************************************/
void tuer_requin(t_liste_requins *Liste_requin, int pos, t_ocean mer){
  
    int x, y, dernier = Liste_requin->nb_requin - 1;

    // Enlever le requin de la grille
    get_position(&Liste_requin->Liste[pos], &x, &y);
    remplir_case(mer, x, y, VIDE, RIEN);

    // Si ce n'est pas le dernier requin
    if (pos != dernier) {

        // Copier le dernier requin à la place du requin supprimé
        Liste_requin->Liste[pos] = Liste_requin->Liste[dernier];

        // Mettre à jour l'indice du requin déplacé dans la grille
        get_position(&Liste_requin->Liste[pos], &x, &y);
        remplir_case(mer, x, y, REQUIN, pos);
    }

    Liste_requin->nb_requin--; // Enlever 1 au nombre de requins
}

/******************************* GET REQUIN ************************************/
/* Re�oit la liste des requins ainsi qu'un indice-position.                   */
/* Retourne le requin se trouvant � cette position dans la liste.             */
/******************************************************************************/
t_animal get_requin(const t_liste_requins *Liste_requin, int pos){

    return Liste_requin->Liste[pos];
}

/***************************** MODIFIER REQUIN *********************************/
/* Re�oit la liste des requins ainsi qu'un indice-position et un requin.      */
/* Va �crire le contenu du requin re�u � la position donn�e dans la liste.    */
/******************************************************************************/
void modifier_requin(t_liste_requins *Liste_requin, int pos, const t_animal *jaws){
    
    Liste_requin->Liste[pos] = *jaws;
}

/******************************************************************************/