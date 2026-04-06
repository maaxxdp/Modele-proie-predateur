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
static int insert_poisson(t_liste_poissons* Liste_poisson, const t_animal* nouveau_poisson) {
  
  if(Liste_poisson->nb_poisson<MAX_POISSONS){

    Liste_poisson->liste[Liste_poisson->nb_poisson] = *nouveau_poisson;

    Liste_poisson->nb_poisson++; 

    return 1;   
  }

    return 0;   
}

/************************ NEW POISSON (fonction PRIV�E) **************************/
/* Re�oit la grille de la mer.                                                */
/* Va cr�er un nouveau poisson al�atoire dans une case libre de la mer.       */
/******************************************************************************/
static t_animal new_poisson(t_ocean mer) {
  
  t_animal nouveau;
  int x, y;

  do{

    x = rand() % LARGEUR;
    y = rand() % HAUTEUR;
    
  } while (get_contenu_ocean(mer, x, y) != VIDE);

  /* */
  init_animal(&nouveau, x, y, rand() % (MAX_AGE_POISSON +1), ENERGIE_INIT_POISSON, 0);

  return nouveau;
}


/******************************************************************************/
/*                     D�FINITIONS DES FONCTIONS PUBLIQUES                    */
/******************************************************************************/

/***************************** VIDER LISTE POISSON *******************************/
/* Va vider la liste des poissons (�tat initial).                             */
/******************************************************************************/
void vider_liste_poisson(t_liste_poissons* Liste_poisson) {
   
}

/************************** REMPLIR LISTE POISSON ********************************/
/* Re�oit la liste de poissons, un nombre de poissons et la grille de la mer. */
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
/* Re�oit un poisson, sa position dans la liste et la grille de la mer.       */
/* Va tenter de d�placer le poisson vers un case voisine vide.                */
/* Retourne 1 si le poisson a �t� d�plac�, 0 sinon.                           */
/******************************************************************************/
int  deplacer_poisson(t_animal *nemo, int no, t_ocean mer){
    
   return 0;   
}


/******************************* AJOUTER POISSON *********************************/
/* Re�oit la liste des poissons, un poisson-m�re et la grille de la mer.      */
/* Va tenter d'ajouter un nouveau b�b�-poisson dans une case voisine libre    */
/* du poisson re�u en param�tre.                                              */
/* Retourne 1 si le nouveau b�b�-poisson a �t� cr�e, 0 sinon.                 */
/******************************************************************************/
int  ajouter_poisson(t_liste_poissons *Liste_poisson, t_animal *mamaf, t_ocean mer){
   
   return 0;    
}

/******************************* TUER POISSON ************************************/
/* Va �liminer un poisson de la liste, on remplace l'�l�ment supprim� par le  */
/* dernier dans le tableau.                                                   */
/******************************************************************************/
void tuer_poisson(t_liste_poissons *Liste_poisson, int pos, t_ocean mer){
 
}

/********************************* GET POISSON ***********************************/
/* Re�oit la liste des poissons ainsi qu'un indice-position.                  */
/* Retourne le poisson se trouvant � cette position dans la liste.            */
/******************************************************************************/
t_animal get_poisson(const t_liste_poissons *Liste_poisson, int i){
  return 0;
}

/***************************** MODIFIER POISSON **********************************/
/* Re�oit la liste des poissons ainsi qu'un indice-position et un poisson.    */
/* Va �crire le contenu du poisson re�u � la position donn�e dans la liste.   */
/******************************************************************************/
void modifier_poisson(t_liste_poissons *Liste_poisson, int i, const t_animal *newf){
 
}

/******************************************************************************/
