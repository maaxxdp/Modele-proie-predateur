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
	//HAUT, HAUT_DR, DROITE, BAS_DR, BAS, BAS_G, GAUCHE, HAUT_G
	switch(dir)
		case HAUT:
			(*py)++;
			break;

		case HAUT_DR:
			(*px)++;
			(*py)++;
			break;

		case DROITE:
			(*px)++;
			break;

		case BAS_DR:
			(*px)++;
			(*py)--;
			break;

		case BAS:
			(*py)--;
			break;

		case BAS_G:
			(*px)--;
			(*py)--;
			break;

		case GAUCHE:
			(*px)--;
			break;

		case HAUT_G:
			(*px)--;
			(*py)++;
			break;
 
}

/******************************************************************************/
/*                         DÉFINITIONS DE FONCTIONS                           */
/******************************************************************************/

/******************************* VIDER OCEAN **********************************/
/* Va vider le contenu de la grille.                                          */
/******************************************************************************/
void vider_ocean(t_ocean mer){
   // On utilise nested for loops pour mettre toutes les cases a zéro
	for (int i = 0; i < HAUTEUR; i++) {
		for (int j = 0; j < LARGEUR; j++) {
			mer[i][j].c_quoi = VIDE;
		}
	}
}

/*************************** TROUVE VOISIN ALEA *******************************/
/* Reçoit la grille ainsi qu'une position [*posx, *posy].                     */
/* Va trouver une case-voisine qui est libre et va renvoyer                   */
/* la nouvelle coordonnée de cette case via *posx et *posy.                   */
/******************************************************************************/
void trouve_voisin_alea(t_ocean mer, int *posx, int *posy){
	
	}
}

/***************************** NB VOISINS LIBRE *******************************/
/* Reçoit la grille ainsi qu'une position [px, py].                           */
/* Retourne le nombre de cases voisines qui sont libres.                      */
/******************************************************************************/
int  nb_voisins_libre(const t_ocean mer, int px, int py) {
	int total = 0;
	int* place_libres = &total;
	// Haut
	if (mer[px][py + 1] == VIDE) {
		*place_libres += 1;
	}
	// Haut-droite
	else if (mer[px + 1][py + 1]==VIDE) {
		*place_libres += 1;
	}
	// Droite
	else if (mer[px + 1][py] == VIDE) {
		*place_libres += 1;
	}
	// Bas-droite
	else if (mer[px + 1][py - 1] == VIDE) {
		*place_libres += 1;
	}
	// Bas
	else if (mer[px - 1][py] == VIDE) {
		*place_libres += 1;
	}
	// Bas-gauche
	else if (mer[px - 1][py - 1] == VIDE) {
		*place_libres += 1;
	}
	// Gauche
	else if (mer[px - 1][py] == VIDE) {
		*place_libres += 1;
	}
	// Haut-gauche
	else if (mer[px - 1][py + 1] == VIDE) {
		*place_libres += 1;
	}
  return total;
}

/****************************** CONTENU CASE **********************************/
/* Reçoit la grille ainsi qu'une position [px, py].                           */
/* Retourne le contenu (VIDE, POISSON, REQUIN) de cette case.                 */
/******************************************************************************/
t_contenu  contenu_case(const t_ocean mer, int px, int py){
	return mer[px][py].c_quoi;
}

/**************************** NUMERO CASE *************************************/
/* Reçoit la grille ainsi qu'une position [px, py].                           */
/* Retourne le numéro du poisson/requin associé a cette case.                 */
/******************************************************************************/
int  numero_case(const t_ocean mer, int px, int py){
  return  mer[px][py].c_qui;
}

/****************************** VIDER CASE ************************************/
/* Reçoit la grille ainsi qu'une position [px, py].                           */
/* Va vider le contenu de cette case = {VIDE, RIEN}.                          */
/******************************************************************************/
void vider_case(t_ocean mer, int px, int py){
	mer[px][py] = VIDE;
}

/****************************** REMPLIR CASE **********************************/
/* Reçoit la grille ainsi qu'une position [px, py] avec un                    */
/* type de contenu (POISSON, REQUIN) et un numéro d'identification.           */
/* Va remplir cette case de la grille avec le contenu reçu.                   */
/******************************************************************************/
void remplir_case(t_ocean mer, int px, int py, t_contenu chose, int no){
	mer[px][py].contenu = chose;
	mer[px][py].id = no;
}

/***************************** DESSINER OCEAN *********************************/
/* Va dessiner le contenu complet de la mer dans la console texte.            */
/******************************************************************************/
void dessiner_ocean(const t_ocean mer, int * nbF, int * nbS){
 
}

/******************************************************************************/
