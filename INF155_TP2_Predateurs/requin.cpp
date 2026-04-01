/******************************************************************************/
/* requin.CPP                                                                  */
/* Librairie des méchants requins (prédateurs).                               */
/******************************************************************************/
#include "requin.h"
#include "util.h"
#include <stdlib.h>
#include <assert.h>


/******************************************************************************/
/*                      DÉFINITIONS DES FONCTIONS PRIVÉES                     */
/******************************************************************************/

/************************** INSERT REQUIN (fonction PRIVÉE) ********************/
/* Fonction PRIVÉE qui ajoutera un requin a la fin de la liste des requins.   */
/* Retourne 1 si le requin a pu etre ajouté, 0 sinon (plus de place).         */
/******************************************************************************/
static int insert_requin(t_liste_requins * Liste_requin, const t_animal* jaws) {
   

    return 0;   
}

/************************ NEW REQUIN (fonction PRIVÉE) *************************/
/* Reçoit la grille de la mer.                                                */
/* Va créer un nouveau requin aléatoire dans une case libre de la mer.        */
/******************************************************************************/
static t_animal new_requin(t_ocean mer) {
  
    return 0;
}


/******************************************************************************/
/*                     DÉFINITIONS DES FONCTIONS PUBLIQUES                    */
/******************************************************************************/

/***************************** VIDER LISTE REQUIN ******************************/
/* Va vider la liste des requins (état initial).                              */
/******************************************************************************/
void vider_liste_requin(t_liste_requins *Liste_requin){

}

/************************** REMPLIR LISTE REQUIN *******************************/
/* Reçoit la liste de requins, un nombre de requins et la grille de la mer.   */
/* Va remplir la liste avec les "nb_requins" premiers requins.                */
/******************************************************************************/
void remplir_liste_requin(t_liste_requins* les_requin, int nb_requins, t_ocean la_Mer) {
  
}

/****************************** GET NB REQUINS *********************************/
/* Retoure le nombre actuel de requins dans la liste.                         */
/******************************************************************************/
int  get_nb_requins(const t_liste_requins *Liste_requin){
  return 0;
}

/******************************* DEPLACER REQUIN *******************************/
/* Reçoit un requin, sa position dans la liste et la grille de la mer.        */
/* Va tenter de déplacer le requin vers un case voisine vide.                 */
/* Retourne 1 si le requin a été déplacé, 0 sinon.                            */
/******************************************************************************/
int  deplacer_requin(t_animal *jaws, int no, t_ocean mer){
    

   return 0;     
}

/***************************** AJOUTER REQUIN **********************************/
/* Reçoit la liste des requins, un requin-mère et la grille de la mer.        */
/* Va tenter d'ajouter un nouveau bébé-requin dans une case voisine libre     */
/* du requin reçu en paramètre.                                               */
/* Retourne 1 si le nouveau bébé-requin a été crée, 0 sinon.                  */
/******************************************************************************/
int  ajouter_requin(t_liste_requins *Liste_requin, t_animal *mamash, t_ocean mer){ 
   
   return 0;      
}

/******************************* TUER REQUIN **********************************/
/* Va éliminer un requin de la liste, on remplace l'élément supprimé par le   */
/* dernier dans le tableau.                                                   */
/******************************************************************************/
void tuer_requin(t_liste_requins *Liste_requin, int pos, t_ocean mer){
  
}

/******************************* GET REQUIN ************************************/
/* Reçoit la liste des requins ainsi qu'un indice-position.                   */
/* Retourne le requin se trouvant à cette position dans la liste.             */
/******************************************************************************/
t_animal get_requin(const t_liste_requins *Liste_requin, int pos){
	return 0;
}

/***************************** MODIFIER REQUIN *********************************/
/* Reçoit la liste des requins ainsi qu'un indice-position et un requin.      */
/* Va écrire le contenu du requin reçu à la position donnée dans la liste.    */
/******************************************************************************/
void modifier_requin(t_liste_requins *Liste_requin, int pos, const t_animal *jaws){

}

/******************************************************************************/
