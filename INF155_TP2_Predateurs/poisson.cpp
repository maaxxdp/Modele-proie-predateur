/******************************************************************************/
/* POISSON.CPP                                                                   */
/* Librairie des ti-poissons.                                                 */
/******************************************************************************/
#include "poisson.h"
#include "util.h"
#include <stdlib.h>
#include <assert.h>

/******************************************************************************/
/*                      DÉFINITIONS DES FONCTIONS PRIVÉES                     */
/******************************************************************************/

/*************************** INSERT POISSON (fonction PRIVÉE) ********************/
/* Fonction PRIVÉE qui ajoutera un poisson a la fin de la liste des poissons. */
/* Retourne 1 si le poisson a pu etre ajouté, 0 sinon (plus de place).        */
/******************************************************************************/
static int insert_poisson(t_liste_poissons* Liste_poisson, const t_animal* nemo) {
  

    return 0;   
}

/************************ NEW POISSON (fonction PRIVÉE) **************************/
/* Reçoit la grille de la mer.                                                */
/* Va créer un nouveau poisson aléatoire dans une case libre de la mer.       */
/******************************************************************************/
static t_animal new_poisson(t_ocean mer) {
  

    return 0;
}


/******************************************************************************/
/*                     DÉFINITIONS DES FONCTIONS PUBLIQUES                    */
/******************************************************************************/

/***************************** VIDER LISTE POISSON *******************************/
/* Va vider la liste des poissons (état initial).                             */
/******************************************************************************/
void vider_liste_poisson(t_liste_poissons* Liste_poisson) {
   
}

/************************** REMPLIR LISTE POISSON ********************************/
/* Reçoit la liste de poissons, un nombre de poissons et la grille de la mer. */
/* Va remplir la liste avec les "nb_poisson" premiers poissons.                  */
/******************************************************************************/
void remplir_liste_poisson(t_liste_poissons * les_poisson, int nb_poisson, t_ocean la_Mer) {
   
}

/****************************** GET NB POISSON ***********************************/
/* Retoure le nombre actuel de poissons dans la liste.                        */
/******************************************************************************/
int  get_nb_poisson(const t_liste_poissons *Liste_poisson){
  return 0;
}

/***************************** DEPLACER POISSON **********************************/
/* Reçoit un poisson, sa position dans la liste et la grille de la mer.       */
/* Va tenter de déplacer le poisson vers un case voisine vide.                */
/* Retourne 1 si le poisson a été déplacé, 0 sinon.                           */
/******************************************************************************/
int  deplacer_poisson(t_animal *nemo, int no, t_ocean mer){
    
   return 0;   
}


/******************************* AJOUTER POISSON *********************************/
/* Reçoit la liste des poissons, un poisson-mère et la grille de la mer.      */
/* Va tenter d'ajouter un nouveau bébé-poisson dans une case voisine libre    */
/* du poisson reçu en paramètre.                                              */
/* Retourne 1 si le nouveau bébé-poisson a été crée, 0 sinon.                 */
/******************************************************************************/
int  ajouter_poisson(t_liste_poissons *Liste_poisson, t_animal *mamaf, t_ocean mer){
   
   return 0;    
}

/******************************* TUER POISSON ************************************/
/* Va éliminer un poisson de la liste, on remplace l'élément supprimé par le  */
/* dernier dans le tableau.                                                   */
/******************************************************************************/
void tuer_poisson(t_liste_poissons *Liste_poisson, int pos, t_ocean mer){
 
}

/********************************* GET POISSON ***********************************/
/* Reçoit la liste des poissons ainsi qu'un indice-position.                  */
/* Retourne le poisson se trouvant à cette position dans la liste.            */
/******************************************************************************/
t_animal get_poisson(const t_liste_poissons *Liste_poisson, int i){
  return 0;
}

/***************************** MODIFIER POISSON **********************************/
/* Reçoit la liste des poissons ainsi qu'un indice-position et un poisson.    */
/* Va écrire le contenu du poisson reçu à la position donnée dans la liste.   */
/******************************************************************************/
void modifier_poisson(t_liste_poissons *Liste_poisson, int i, const t_animal *newf){
 
}

/******************************************************************************/
