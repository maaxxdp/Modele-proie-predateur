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

    // Écriture dans la prochaine case libre 
    Liste_poisson->Liste[Liste_poisson->nb_poisson] = *nouveau_poisson;

    // Ajout d'un nouveau poisson dans le compteur du nombre de poisson
    Liste_poisson->nb_poisson++; 

    return 1;   // Poisson ajouté à la liste
  }

    return 0;   // Poisson non ajouté à la liste car pleine
}

/************************ NEW POISSON (fonction PRIV�E) **************************/
/* Re�oit la grille de la mer.                                                */
/* Va cr�er un nouveau poisson al�atoire dans une case libre de la mer.       */
/******************************************************************************/
static t_animal new_poisson(t_ocean mer) {
  
  t_animal nouveau;
  int x, y;

// Choix aléatoire d'une case dans la grille pour un nouveau poisson
  do{

    x = alea(0, LARGEUR - 1) ; // Position en x
    y = alea(0, HAUTEUR - 1); // Position en y 

  } while (contenu_case(mer, x, y) != VIDE); // Tant que la case n'est pas vide

  /* Initialisation du poisson: position x & y trouvé ci-dessus, attribution d'un âge choisi
   aléatoirement entre [0, MAX_AGE_POISSON], une énergie de départ équivalent à 
   ENERGIE_INIT_POISSON, et initialisation à 0 jours de gestation.*/
  init_animal(&nouveau, x, y, alea(0, MAX_AGE_POISSON), ENERGIE_INIT_POISSON, 0);

  return nouveau;
}

/******************************************************************************/
/*                     D�FINITIONS DES FONCTIONS PUBLIQUES                    */
/******************************************************************************/

/***************************** VIDER LISTE POISSON *******************************/
/* Va vider la liste des poissons (�tat initial).                             */
/******************************************************************************/
void vider_liste_poisson(t_liste_poissons* Liste_poisson) {
   
  Liste_poisson->nb_poisson = 0;

}

/************************** REMPLIR LISTE POISSON ********************************/
/* Re�oit la liste de poissons, un nombre de poissons et la grille de la mer. */
/* Va remplir la liste avec les "nb_poisson" premiers poissons.                  */
/******************************************************************************/
void remplir_liste_poisson(t_liste_poissons * les_poisson, int nb_poisson, t_ocean la_Mer) {
   
  t_animal nouveau;
  int i, x, y;

  les_poisson -> nb_poisson = 0; // S'assurer que la liste est vide au départ

  for (i = 0; i < nb_poisson; i++){

      nouveau = new_poisson(la_Mer); // Création d'un nouveau poisson

      // Ajout d'un poisson dans la liste
      if(insert_poisson(les_poisson, &nouveau)){

        // Récupérer la position du nouveau poisson créé dans var nouveau
        get_position (&nouveau, &x, &y);

        // Mettre le poisson dans la grille de l'océan
        remplir_case(la_Mer, x, y, POISSON, les_poisson -> nb_poisson-1);
      }
  }
}

/****************************** GET NB POISSON ***********************************/
/* Retoure le nombre actuel de poissons dans la liste.                        */
/******************************************************************************/
int  get_nb_poisson(const t_liste_poissons *Liste_poisson){

  return Liste_poisson-> nb_poisson;
}

/***************************** DEPLACER POISSON **********************************/
/* Re�oit un poisson, sa position dans la liste et la grille de la mer.       */
/* Va tenter de d�placer le poisson vers un case voisine vide.                */
/* Retourne 1 si le poisson a �t� d�plac�, 0 sinon.                           */
/******************************************************************************/
int  deplacer_poisson(t_animal *nemo, int no, t_ocean mer){
  
  int x, y, nx, ny;

  get_position(nemo, &x, &y); // Récupérer la position actuelle

  // 0- droite (1,0), 1- gauche(-1,0), 2- bas (0,1) et 3- haut (0,-1)
  int dx[4] ={1, -1, 0, 0};
  int dy[4] ={0, 0, 1, -1};

  for (int i = 0; i < 4; i++) {

    // Calcul des nouvelles positions en x et y
    nx = x + dx[i];
    ny = y + dy[i];

    // Faire traverser le poisson de l'autre coté de l'écran horizontalement
    if (nx < 0){
      nx = LARGEUR - 1;
    } else if (nx >= LARGEUR){
      nx = 0;
    }

    // Vérifier que la position verticale est dans les limites de la grille océan
    if(ny >= 0 && ny < HAUTEUR){
      
      // Vérifier si la case est vide
      if (contenu_case(mer, nx, ny) == VIDE) {

        // Vider l'ancienne position du poisson de ses informations
        remplir_case(mer, x, y, VIDE, RIEN);

        // Remplir la nouvelle case avec les informations du poisson
        remplir_case(mer, nx, ny, POISSON, no); 

        // Mettre à jour la nouvelle position du poisson
        set_position(nemo, nx, ny);

        return 1; // Déplacement réussi
      }
    }

  }

  return 0; // Aucun déplacement possible
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
