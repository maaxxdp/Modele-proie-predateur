/******************************************************************************/
/* requin.H                                                                    */
/* Librairie des méchants requins (prédateurs).                               */
/******************************************************************************/
#include"animal.h"
#include"ocean.h"

#define MAX_REQUIN         100   //nombre maximum de requins dans la mer
#define MAX_AGE_SHRK     1200   //age maximal du requin 
#define NB_JRS_PUB_SHRK    90   //nombre de jours avant la puberté
#define NB_JRS_GEST_SHRK   21   //nombre de jours de gestation
#define JRS_DIGESTION       5   //valeur ajoutée à l'indice de santé après un repas

/******************************************************************************/
/*                         DÉCLARATIONS DE TYPES                              */
/******************************************************************************/

/* Type-structure pour la liste des requins */
typedef struct{
  t_animal* Liste;     // tableau dynamique
  int nb_requin;       // nombre actuel de requins
  int taille_liste;    // taille maximale du tableau
} t_liste_requins;

/******************************************************************************/
/*                         DÉCLARATIONS DE FONCTIONS                          */
/******************************************************************************/
void remplir_liste_requin(t_liste_requins * les_requin, int nb_requins, t_ocean la_Mer);
/* Va remplir la liste avec les "nb_requins" premiers requins. */

void vider_liste_requin(t_liste_requins *);
/* Va vider la liste des requins (état initial). */

int  get_nb_requins(const t_liste_requins *);
/* Retoure le nombre actuel de requins dans la liste. */

//void get_pos_requin(const t_animal*, int *px, int *py);
/* Reçoit un requin et retourne sa position via [*px, *py]. */

int  deplacer_requin(t_animal*, int, t_ocean);
/* Reçoit un requin, sa position dans la liste et la grille de la mer.
   Va tenter de déplacer le requin vers un case voisine vide.
   Retourne 1 si le requin a été déplacé, 0 sinon.    */

int  ajouter_requin(t_liste_requins *, t_animal *, t_ocean);
/* Reçoit la liste des requins, un requin-mère et la grille de la mer.
   Va tenter d'ajouter un nouveau bébé-requin dans une case voisine libre
   du requin reçu en paramètre.
   Retourne 1 si le nouveau bébé-requin a été crée, 0 sinon.   */

void tuer_requin(t_liste_requins *, int pos, t_ocean mer);
/* Va éliminer un requin de la liste, on remplace l'élément supprimé par le */
/* dernier dans le tableau.  */

t_animal get_requin(const t_liste_requins *, int pos);
/* Reçoit la liste des requins ainsi qu'un indice-position.
   Retourne le requin se trouvant à cette position dans la liste. */

void modifier_requin(t_liste_requins *, int pos, const t_animal *);
/* Reçoit la liste des requins ainsi qu'un indice-position et un requin.
   Va écrire le contenu du requin reçu à la position donnée dans la liste. */

void liberer_liste_requin(t_liste_requins *);
/* Libère la mémoire allouée dynamiquement pour la liste des requins.
   Remet les champs de la structure à zéro. */
