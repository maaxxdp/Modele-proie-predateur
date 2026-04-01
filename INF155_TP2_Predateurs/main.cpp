/******************************************************************************/
/* MAIN.CPP                                                                   */
/*                                                                            */
/* Programme qui implémente la dynamique proie-prédateur de façon itérative.  */
/* Notre modèle va afficher des ti-poissons et des requins dans une "mer" de  */
/* dimension limitée.  Les poissons ont une source infinie de nourriture et   */
/* vont donc procréer automatiquement sans contrainte (sauf la taille max. de */
/* la liste des poissons).  Les requins ont besoin de manger des ti-poissons  */
/* pour survivre.  La maturité des requins sera plus lente et la reproduction */
/* des requins sera moins fréquente. Chaque itération représente 1 "jour" de  */
/* vie.  Le programme boucle jusqu'a l'extinction des poissons ou requins.    */
/* Un mode sans affichage est offert ou les données après chaque itération    */
/* sont inscrites dans un fichier texte pour analyse.                         */
/******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<ctype.h>
#include"poisson.h"
#include"requin.h"

/******************************************************************************/
/*                        DÉCLARATIONS DES CONSTANTES                         */
/******************************************************************************/

#define NB_POISSONS_INIT 200  //nombre initial de poissons
#define NB_REQUINS_INIT   50  //nombre initial de requins
#define MAX_TEMPS       5000  //presque 15 ans
#define TEMPS_DELAI      50  //delai d'affichage en millisecondes
#define TOUCHE_FIN        27  //touche-clavier (ESC) pour terminer le programme

#define NOM_FICHIER  "stats.txt"

/******************************************************************************/
/*                         DÉCLARATIONS DE FONCTIONS                          */
/******************************************************************************/

int  getmode();
/* Demande et valide le mode d'affichage. */

void chasser_poissons(t_liste_poissons *, t_liste_requins *, t_ocean);
/* Reçoit la liste des poissons, la liste des requins et la mer.
   On identifie les poissons qui seront mangés par les requins. */

void requins_morts(t_liste_requins *, t_ocean);
/* Reçoit la liste de requins et la mer.  
   On identifie les requins qui vont mourir de faim. */

void deplacer_requins(t_liste_requins *, t_ocean);
/* Reçoit la liste de requins et la mer. 
   On ajoute des bébé-requins a la liste s'il y a lieu.
   On déplace les requins qui restent de une position-écran. */

void deplacer_poissons(t_liste_poissons *, t_ocean);
/* Reçoit la liste de poissons et la mer. 
   On ajoute des bébé-poissons a la liste s'il y a lieu.
   On déplace les poissons qui restent de une position-écran. */

/******************************************************************************/
/*                             PROGRAMME PRINCIPAL                            */
/******************************************************************************/
int main(){
  t_ocean  la_mer;                //La grille de la mer
  t_liste_poissons  les_poissons; //la liste des ti-poissons
  t_liste_requins   les_requins;  //la liste des requins
  int nb_poisson, nb_requin;      //nombre de poissons et requins
  int stop=0, iter=0;             //pour contrôler et compter les itérations
  int MODE_AFF = getmode();       //le mode d'affichage (= 0/1)

  /* Variable-fichier pour écriture de données. Sera ouvert SI MODE_AFF = 0 */
 
  /* on établit les conditions initiales */

  /* on vide toutes les structures de données */
 
  /* on génere tous les ti-poissons */
  

  /* on génere tous les requins */
 

  //on déssine l'état initial de la mer

  /* Boucle principale de simulation */
 
      //prochaine iteration

	/* identifier les poissons mangés */

	/* identifier les requins morts */


	/* traiter les requins restants */


	/* traiter les poissons restants */

	/* mise-a-jour du nombre de poissons et requins */

	/* Si le mode d'affichage est allumé.. */
	
  //sinon, on écrit le nombre de poissons/requins dans le fichier texte
      
    /* si l'utilisateur appuye sur <ESC> on arrête le programme */
	
   //tant qui reste des requins et poissons

  /* dessiner l'état final de la mer */
  

  /* on confirme la raison de la fin du programme */
 
  return EXIT_SUCCESS;
}

/******************************************************************************/
/*                         DÉFINITIONS DE FONCTIONS                           */
/******************************************************************************/

/********************************* GETMODE ************************************/
/* Fonction qui permet de demander le mode d'affichage.                       */
/******************************************************************************/
int getmode()
{  char c;

     /* On demande et valide le mode désiré */
	 do {
		 printf("\nVoulez-vous avec affichage (O)ui/(N)on ? ");
		 fflush(stdin);
		 scanf("%c",&c);
		 c = toupper(c);
	 } while ((c != 'O') && (c != 'N'));   //doit être soit 'O' ou 'N'!!
	 
	 system("cls");
	 return (c == 'O') ? 1 : 0;   //on retourne soit 0/1 selon le choix
}

/**************************** chasser_poissons ********************************/
/* Reçoit la liste des poissons, la liste des requins et la mer.              */
/* On identifie les poissons qui seront mangés par les requins.               */
/******************************************************************************/
void chasser_poissons(t_liste_poissons *les_poissons, t_liste_requins *les_requins, 
	                  t_ocean la_mer){
  t_animal nemo;      //poisson temporaire
  t_animal jaws;      //requin temporaire
  int i, pos, mange,
	  px, vx, py, vy;  //pos. temporaires: (px, py)= poisson, (vx, vy)= requin
  
  /* Pour tous les poissons (on doit re-vérifier à chaque fois!!).. */
  for (i=0; i < get_nb_poisson(les_poissons); i++){
    nemo = get_poisson(les_poissons, i);    //obtenir CE poisson
	get_position(&nemo, &px, &py);   //..et sa position

	//si un de ses 8 voisins (1 case plus loin) est un requin..
	mange = 0;
	for (vy=py-1; vy <= py+1; vy++)
	  for (vx=px-1; vx <= px+1; vx++)
	    if ((vy >= 0 && vx >= 0 && vy < HAUTEUR && vx < LARGEUR) &&  //limites!
  		    (vx!=px || vy!=py) && contenu_case(la_mer, vx, vy) == REQUIN){
		  /* on va tuer ce poisson et l'effacer de la mer */
		  tuer_poisson(les_poissons, i, la_mer);
		  mange = 1;

		  /* on récupère l'indice du requin qui vient de manger ce poisson */
		  pos = numero_case(la_mer, vx, vy);
          jaws = get_requin(les_requins, pos);   //obtenir CE requin
		  ajout_energie(&jaws, JRS_DIGESTION);  //..et on augmente son indice d'énergie

		  /* remettre le requin modifié dans la liste */
	      modifier_requin(les_requins, pos, &jaws);  

		  vy = py+1;  vx = px+1;    //pour quitter les 2 boucles For
		  i--;         //pour rester au MEME endroit dans la liste des poissons!
	    }

	//si le poisson n'a pas été mangé, on vérifie si il meurt de viellesse
	if (!mange) {
		if (est_mort(&nemo, MAX_AGE_POISSON)) {
			tuer_poisson(les_poissons, i, la_mer);
			i--;         //pour rester au MEME endroit dans la liste des poissons!
		}
	}
  }
}

/****************************** requins_morts *********************************/
/* Reçoit la liste de requins et la mer.                                      */
/* On identifie les requins qui vont mourir de faim.                          */
/******************************************************************************/
void requins_morts(t_liste_requins *les_requins, t_ocean la_mer){
  t_animal jaws;   //requin temporaire
 
  /* Pour tous les requins (on doit re-vérifier à chaque fois!!).. */
  for (int i=0; i < get_nb_requins(les_requins); i++){
    jaws = get_requin(les_requins, i);   //obtenir CE requin

	/* si il doit mourir on l'efface de la liste et aussi de la mer */
	if (est_mort(&jaws, MAX_AGE_SHRK)){
	  tuer_requin(les_requins, i, la_mer);
 	  i--;        //pour rester au MEME endroit dans la liste des requins!
	}
  }
}

/**************************** deplacer_requins ********************************/
/* Reçoit la liste de requins et la mer.                                      */
/* On ajoute des bébé-requins a la liste s'il y a lieu.                       */
/* On déplace les requins qui restent de une position-écran.                  */
/******************************************************************************/
void deplacer_requins(t_liste_requins *les_requins, t_ocean la_mer){
  t_animal jaws;    //requin temporaire
  int i, nb_requins = get_nb_requins(les_requins);  //le nombre de requins

  /* Pour tous les requins restants.. */
  for (i=0; i < nb_requins; i++){
    jaws = get_requin(les_requins, i);   //obtenir CE requin
	inc_age(&jaws, NB_JRS_PUB_SHRK);              //..et incrémenter son age
	dec_energie(&jaws);

	/* SI il est pret a procréer on ajoute un bébé-requin a la liste */
	if (puberte_atteinte(&jaws, NB_JRS_PUB_SHRK, NB_JRS_GEST_SHRK))
	  ajouter_requin(les_requins, &jaws, la_mer);
	else 
	  /* sinon on le déplace */
	  deplacer_requin(&jaws, i, la_mer);

	/* remettre le requin modifié dans la liste */
	modifier_requin(les_requins, i, &jaws);  
  }
}

/*************************** deplacer_poissons ********************************/
/* Reçoit la liste de poissons et la mer.                                     */
/* On ajoute des bébé-poissons a la liste s'il y a lieu.                      */
/* On déplace les poissons qui restent de une position-écran.                 */
/******************************************************************************/
void deplacer_poissons(t_liste_poissons *les_poissons, t_ocean la_mer){
  t_animal nemo;         //poisson temporaire
  int i, nb_poisson = get_nb_poisson(les_poissons);  //le nombre de poissons

  /* Pour tous les poissons restants.. */
  for (i=0; i < nb_poisson; i++){
    nemo = get_poisson(les_poissons, i);   //obtenir CE poisson
	inc_age(&nemo, NB_JRS_PUB_POISSON);            //..et incrémenter son age

	/* SI il est pret a procréer on ajoute un bébé-poisson a la liste */
	if (puberte_atteinte(&nemo, NB_JRS_PUB_POISSON, NB_JRS_GEST_POISSON)) {
		if (ajouter_poisson(les_poissons, &nemo, la_mer))    //si il a réussi a procréer..
			dec_energie(&nemo);                         //perte d'énergie si il a accouché
	}
	else 
	    /* sinon on le déplace */
	    deplacer_poisson(&nemo, i, la_mer);
		  
	/* remettre le poisson modifié dans la liste */
    modifier_poisson(les_poissons, i, &nemo);
  }
}

/******************************************************************************/
