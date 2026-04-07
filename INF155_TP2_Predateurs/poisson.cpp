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

  les_poisson->nb_poisson = 0; // S'assurer que la liste est vide au départ

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

  return Liste_poisson->nb_poisson;
}

/***************************** DEPLACER POISSON **********************************/
/* Re�oit un poisson, sa position dans la liste et la grille de la mer.       */
/* Va tenter de d�placer le poisson vers un case voisine vide.                */
/* Retourne 1 si le poisson a �t� d�plac�, 0 sinon.                           */
/******************************************************************************/
int  deplacer_poisson(t_animal *nemo, int no, t_ocean mer){
  
  int x, y, nx, ny;

  get_position(nemo, &x, &y); // Récupérer la position actuelle

  // Si aucune case voisine n'est libre, le poisson ne se déplace pas
  if (nb_voisins_libre(mer, x, y) == 0){

    return 0;
  }

    // Initialiser la nouvelles position avec la position en x et y actuelle
    nx = x;
    ny = y;

    // Trouver une case voisine libre aléatoirement
    trouve_voisin_alea(mer, &nx, &ny);

    // Vider l'ancienne position du poisson de ses informations
    remplir_case(mer, x, y, VIDE, RIEN);

    // Remplir la nouvelle case avec les informations du poisson
    remplir_case(mer, nx, ny, POISSON, no); 

    // Mettre à jour la nouvelle position du poisson
    set_position(nemo, nx, ny);

    return 1; // Déplacement réussi

}

/******************************* AJOUTER POISSON *********************************/
/* Re�oit la liste des poissons, un poisson-m�re et la grille de la mer.      */
/* Va tenter d'ajouter un nouveau b�b�-poisson dans une case voisine libre    */
/* du poisson re�u en param�tre.                                              */
/* Retourne 1 si le nouveau b�b�-poisson a �t� cr�e, 0 sinon.                 */
/******************************************************************************/
int  ajouter_poisson(t_liste_poissons *Liste_poisson, t_animal *mamaf, t_ocean mer){
  
  t_animal bebe;
  int x, y;

  get_position (mamaf, &x, &y); // Récupérer la position du poisson mère

  // Si aucune case voisine n'est libre, aucun bébé ne nait
  if (nb_voisins_libre (mer, x, y) == 0){

    return 0;
  }

  // Réinitialisation de la gestation du poisson-mère que le bébé soit né ou pas
  reset_gestation(mamaf, -NB_JRS_GEST_POISSON); 

  // Simulation d'une fausse couche (33%)
  if (alea(1, 3) == 1){

    return 0;
  }

  // Si la liste est pleine, on ne crée pas de nouveau poisson
  if (Liste_poisson->nb_poisson >= MAX_POISSONS){

    return 0;
  }
  
  // Choisir une case voisine libre pour le bébé
  trouve_voisin_alea(mer, &x, &y);

  // Initialiser le bébé-poisson
  init_animal(&bebe, x, y, 0, ENERGIE_INIT_POISSON, 0);

  // Ajouter un bébé à la fin de la liste
  if (insert_poisson(Liste_poisson, &bebe)){

    // Mettre le bébé dans la grille de l'océan
    remplir_case(mer, x, y, POISSON, Liste_poisson->nb_poisson-1);

    return 1; //Nouveau poisson créé
  }
  
   return 0; 
}

/******************************* TUER POISSON ************************************/
/* Va �liminer un poisson de la liste, on remplace l'�l�ment supprim� par le  */
/* dernier dans le tableau.                                                   */
/******************************************************************************/
void tuer_poisson(t_liste_poissons *Liste_poisson, int pos, t_ocean mer){
  
  int x, y, dernier = Liste_poisson->nb_poisson -1;

  // Enlever le poisson de la grille
  get_position(&Liste_poisson->Liste[pos], &x, &y);
  remplir_case(mer, x, y, VIDE, RIEN);

  // Si ce n'est pas le dernier poisson
  if (pos != dernier) {

    // Copier le dernier poisson à la place du poisson supprimé
    Liste_poisson->Liste[pos] = Liste_poisson->Liste[dernier];

    // Mettre à jour la nouvelle position du poisson
    get_position(&Liste_poisson->Liste[pos], &x, &y);
    remplir_case(mer, x, y, POISSON, pos);
  }

  Liste_poisson->nb_poisson--; // Enlever 1 au nombre de poisson
}

/********************************* GET POISSON ***********************************/
/* Re�oit la liste des poissons ainsi qu'un indice-position.                  */
/* Retourne le poisson se trouvant � cette position dans la liste.            */
/******************************************************************************/
t_animal get_poisson(const t_liste_poissons *Liste_poisson, int i){
  
  return Liste_poisson->Liste[i];
}

/***************************** MODIFIER POISSON **********************************/
/* Re�oit la liste des poissons ainsi qu'un indice-position et un poisson.    */
/* Va �crire le contenu du poisson re�u � la position donn�e dans la liste.   */
/******************************************************************************/
void modifier_poisson(t_liste_poissons *Liste_poisson, int i, const t_animal *newf){
 
  Liste_poisson->Liste[i] = *newf;
}

/******************************************************************************/
