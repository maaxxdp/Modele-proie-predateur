/******************************************************************************/
/* OCEAN.CPP                                                                  */ 
/* Librairie de la mer (grille).                                              */
/******************************************************************************/
#include "ocean.h"
#include <stdio.h>
#include <stdlib.h>
/*************************** FONCTION PRIVÉE ******************************/

/* Fonction qui renvoie la nouvelle coordonnée (*px, *py) voisine de la
   coordonnée (*px, *py) reçue selon le paramètre de direction "dir". */
static void voisin(int *px, int *py, T_dir dir){
	//HAUT, HAUT_DR, DROITE, BAS_DR, BAS, BAS_G, GAUCHE, HAUT_G
	switch(dir) {
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
			mer[i][j].c_qui = RIEN;
		}
	}
}

/*************************** TROUVE VOISIN ALEA *******************************/
/* Reçoit la grille ainsi qu'une position [*posx, *posy].                     */
/* Va trouver une case-voisine qui est libre et va renvoyer                   */
/* la nouvelle coordonnée de cette case via *posx et *posy.                   */
/******************************************************************************/
void trouve_voisin_alea(t_ocean mer, int *posx, int *posy){
		int voisins[8][2]; // max 8 voisins
		int nb = 0;

		int x = *posx;
		int y = *posy;

		// Tableau des 8 directions (dx, dy)
		int directions[8][2] = {
			{0, -1},  // haut
			{0, 1},   // bas
			{-1, 0},  // gauche
			{1, 0},   // droite
			{-1, -1}, // haut-gauche
			{1, -1},  // haut-droite
			{-1, 1},  // bas-gauche
			{1, 1}    // bas-droite
		};

		for (int i = 0; i < 8; i++) {
			int nx = x + directions[i][0];
			int ny = y + directions[i][1];

			// ⚠️ Vérifier les limites de la grille
			if (nx >= 0 && nx < HAUTEUR && ny >= 0 && ny < LARGEUR) {

				if (mer[nx][ny].c_quoi == VIDE && mer[nx][ny].c_qui == RIEN) {
					voisins[nb][0] = nx;
					voisins[nb][1] = ny;
					nb++;
				}
			}
		}

		// Choisir un voisin au hasard s'il y en a
		if (nb > 0) {
			int choix = rand() % nb;
			*posx = voisins[choix][0];
			*posy = voisins[choix][1];
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
	mer[px][py].c_qui = RIEN;
	mer[px][py].c_quoi = VIDE;
}

/****************************** REMPLIR CASE **********************************/
/* Reçoit la grille ainsi qu'une position [px, py] avec un                    */
/* type de contenu (POISSON, REQUIN) et un numéro d'identification.           */
/* Va remplir cette case de la grille avec le contenu reçu.                   */
/******************************************************************************/
void remplir_case(t_ocean mer, int px, int py, t_contenu chose, int no){
	mer[px][py].c_quoi = chose;
	mer[px][py].c_qui = no;
}

/***************************** DESSINER OCEAN *********************************/
/* Va dessiner le contenu complet de la mer dans la console texte.            */
/******************************************************************************/
void dessiner_ocean(const t_ocean mer, int * nbF, int * nbS){
 
}

/******************************************************************************/
