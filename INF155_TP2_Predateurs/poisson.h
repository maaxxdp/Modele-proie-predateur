/******************************************************************************/
/* poisson.H                                                                     */
/* Librairie des ti-poissons.                                                 */
/******************************************************************************/
#include"animal.h"
#include"ocean.h"

#define MAX_POISSONS       500    //nombre maximal de poissons
#define MAX_AGE_POISSON     60    //age maximal du poisson 
#define NB_JRS_PUB_POISSON  10    //nombre de jours avant la puberté
#define NB_JRS_GEST_POISSON  5    //nombre de jours de gestation
#define ENERGIE_INIT_POISSON 3    //valeur initiale d'énergie

/******************************************************************************/
/*                         DÉCLARATIONS DE TYPES                              */
/******************************************************************************/

/* Type-structure pour la liste des poissons */
typedef struct{
  t_animal* Liste;     // tableau dynamique
  int nb_poisson;      // nombre actuel de poissons
  int taille_liste;    // taille maximale du tableau
} t_liste_poissons;

/******************************************************************************/
/*                         DÉCLARATIONS DE FONCTIONS                          */
/******************************************************************************/
void remplir_liste_poisson(t_liste_poissons * les_poisson, int nb_poisson, t_ocean la_Mer);
/* Va remplir la liste avec les "nb_poisson" premiers poissons. */

void vider_liste_poisson(t_liste_poissons *);
/* Va vider la liste des poissons (état initial). */

int  get_nb_poisson(const t_liste_poissons *);
/* Retoure le nombre actuel de poissons dans la liste. */

int  deplacer_poisson(t_animal *, int, t_ocean);
/* Reçoit un poisson, sa position dans la liste et la grille de la mer.
   Va tenter de déplacer le poisson vers un case voisine vide.
   Retourne 1 si le poisson a été déplacé, 0 sinon.    */

int  ajouter_poisson(t_liste_poissons *, t_animal *, t_ocean);
/* Reçoit la liste des poissons, un poisson-mère et la grille de la mer.
   Va tenter d'ajouter un nouveau bébé-poisson dans une case voisine libre
   du poisson reçu en paramètre.
   Retourne 1 si le nouveau bébé-poisson a été crée, 0 sinon.   */

void tuer_poisson(t_liste_poissons *, int pos, t_ocean);
/* Va éliminer un poisson de la liste, on remplace l'élément supprimé par le 
   dernier dans le tableau.  */

t_animal get_poisson(const t_liste_poissons *, int i);
/* Reçoit la liste des poissons ainsi qu'un indice-position.
   Retourne le poisson se trouvant à cette position dans la liste. */

void modifier_poisson(t_liste_poissons *, int i, const t_animal *);
/* Reçoit la liste des poissons ainsi qu'un indice-position et un poisson.
   Va écrire le contenu du poisson reçu à la position donnée dans la liste. */

/******************************************************************************/
