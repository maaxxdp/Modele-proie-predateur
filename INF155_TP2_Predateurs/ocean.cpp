/******************************************************************************/
/* OCEAN.CPP                                                                  */ 
/* Librairie de la mer (grille).                                              */
/******************************************************************************/
#include "ocean.h"
#include <stdio.h>

/*************************** FONCTION PRIVÉE ******************************/

/* Fonction qui renvoie la nouvelle coordonnée (*px, *py) voisine de la
   coordonnée (*px, *py) reçue selon le paramètre de direction "dir". */
static void voisin(int *px, int *py, T_dir dir){
 
}

/******************************************************************************/
/*                         DÉFINITIONS DE FONCTIONS                           */
/******************************************************************************/

/******************************* VIDER OCEAN **********************************/
/* Va vider le contenu de la grille.                                          */
/******************************************************************************/
void vider_ocean(t_ocean mer){
  
}

/*************************** TROUVE VOISIN ALEA *******************************/
/* Reçoit la grille ainsi qu'une position [*posx, *posy].                     */
/* Va trouver une case-voisine qui est libre et va renvoyer                   */
/* la nouvelle coordonnée de cette case via *posx et *posy.                   */
/******************************************************************************/
void trouve_voisin_alea(t_ocean mer, int *posx, int *posy){
  
}

/***************************** NB VOISINS LIBRE *******************************/
/* Reçoit la grille ainsi qu'une position [px, py].                           */
/* Retourne le nombre de cases voisines qui sont libres.                      */
/******************************************************************************/
int  nb_voisins_libre(const t_ocean mer, int px, int py){
  

  return 0;
}

/****************************** CONTENU CASE **********************************/
/* Reçoit la grille ainsi qu'une position [px, py].                           */
/* Retourne le contenu (VIDE, POISSON, REQUIN) de cette case.                 */
/******************************************************************************/
t_contenu  contenu_case(const t_ocean mer, int px, int py){
  return  0;
}

/**************************** NUMERO CASE *************************************/
/* Reçoit la grille ainsi qu'une position [px, py].                           */
/* Retourne le numéro du poisson/requin associé a cette case.                 */
/******************************************************************************/
int  numero_case(const t_ocean mer, int px, int py){
  return  0;
}

/****************************** VIDER CASE ************************************/
/* Reçoit la grille ainsi qu'une position [px, py].                           */
/* Va vider le contenu de cette case = {VIDE, RIEN}.                          */
/******************************************************************************/
void vider_case(t_ocean mer, int px, int py){
 
}

/****************************** REMPLIR CASE **********************************/
/* Reçoit la grille ainsi qu'une position [px, py] avec un                    */
/* type de contenu (POISSON, REQUIN) et un numéro d'identification.           */
/* Va remplir cette case de la grille avec le contenu reçu.                   */
/******************************************************************************/
void remplir_case(t_ocean mer, int px, int py, t_contenu chose, int no){

}

/***************************** DESSINER OCEAN *********************************/
/* Va dessiner le contenu complet de la mer dans la console texte.            */
/******************************************************************************/
void dessiner_ocean(const t_ocean mer, int * nbF, int * nbS){
 
}

/******************************************************************************/
