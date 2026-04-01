/******************************************************************************/
/* OCEAN.H                                                                    */ 
/* Librairie de la mer (grille).                                              */
/******************************************************************************/
#include "util.h"

#if (!defined(NEMO))  //va empêcher la double-compilation
#define NEMO 1        //pour savoir si on a deja compilé ce module ou non

//dimensions de la grille (et de l'écran d'affichage)
#define HAUTEUR  25
#define LARGEUR  110
#define RIEN     -1

/******************************************************************************/
/*                         DÉCLARATIONS DE TYPES                              */
/******************************************************************************/

/* type énuméré pour les 8 directions de déplacement */
typedef enum {HAUT, HAUT_DR, DROITE, BAS_DR, BAS, BAS_G, GAUCHE, HAUT_G} T_dir;

/* type énuméré pour le contenu d'une case */
typedef enum {VIDE, POISSON, REQUIN} t_contenu;

/* type structure pour le contenu d'une case de la grille */
typedef struct{
  t_contenu  c_quoi;    //Soit: VIDE, POISSON ou REQUIN
  int        c_qui;     //le numéro du poisson/requin a cet endroit, sinon -1
} t_case;

/* type-tableau de la grille de la mer */
typedef t_case t_ocean[HAUTEUR][LARGEUR];

/******************************************************************************/
/*                         DÉCLARATIONS DE FONCTIONS                          */
/******************************************************************************/

void vider_ocean(t_ocean);
/* Va vider le contenu de la grille */

void trouve_voisin_alea(t_ocean mer, int *posx, int *posy);
/* Reçoit la grille ainsi qu'une position [*posx, *posy].
   Va trouver une case-voisine qui est libre et va renvoyer
   la nouvelle coordonnée de cette case via *posx et *posy. */

int  nb_voisins_libre(const t_ocean, int px, int py);
/* Reçoit la grille ainsi qu'une position [px, py]. 
   Retourne le nombre de cases voisines qui sont libres */

t_contenu  contenu_case(const t_ocean, int px, int py);
/* Reçoit la grille ainsi qu'une position [px, py].
   Retourne le contenu (VIDE, FISH, SHARK) de cette case. */

int  numero_case(const t_ocean, int px, int py);
/* Reçoit la grille ainsi qu'une position [px, py].
   Retourne le numéro du poisson/requin associé a cette case. */

void vider_case(t_ocean, int px, int py);
/* Reçoit la grille ainsi qu'une position [px, py].
   Va vider le contenu de cette case = {VIDE, RIEN}. */

void remplir_case(t_ocean, int px, int py, t_contenu, int);
/* Reçoit la grille ainsi qu'une position [px, py] avec un
   type de contenu (FISH, SHARK) et un numéro d'identification.
   Va remplir cette case de la grille avec le contenu reçu.  */

void dessiner_ocean(const t_ocean, int* nbF, int* nbS);
/* Va dessiner le contenu complet de la mer dans la console texte. */

#endif

/******************************************************************************/