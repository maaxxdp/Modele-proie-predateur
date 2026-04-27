/******************************************************************************/
/* MAIN.CPP                                                                   */
/*                                                                            */
/* Programme qui impl�mente la dynamique proie-pr�dateur de fa�on it�rative.  */
/* Notre mod�le va afficher des ti-poissons et des requins dans une "mer" de  */
/* dimension limit�e.  Les poissons ont une source infinie de nourriture et   */
/* vont donc procr�er automatiquement sans contrainte (sauf la taille max. de */
/* la liste des poissons).  Les requins ont besoin de manger des ti-poissons  */
/* pour survivre.  La maturit� des requins sera plus lente et la reproduction */
/* des requins sera moins fr�quente. Chaque it�ration repr�sente 1 "jour" de  */
/* vie.  Le programme boucle jusqu'a l'extinction des poissons ou requins.    */
/* Un mode sans affichage est offert ou les donn�es apr�s chaque it�ration    */
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
/*                        D�CLARATIONS DES CONSTANTES                         */
/******************************************************************************/

#define NB_POISSONS_INIT 200  //nombre initial de poissons
#define NB_REQUINS_INIT   50  //nombre initial de requins
#define MAX_TEMPS       5000  //presque 15 ans
#define TEMPS_DELAI      50  //delai d'affichage en millisecondes
#define TOUCHE_FIN        27  //touche-clavier (ESC) pour terminer le programme

#define NOM_FICHIER  "stats.txt"

/******************************************************************************/
/*                         D�CLARATIONS DE FONCTIONS                          */
/******************************************************************************/

int  getmode();
/* Demande et valide le mode d'affichage. */

void chasser_poissons(t_liste_poissons *, t_liste_requins *, t_ocean);
/* Re�oit la liste des poissons, la liste des requins et la mer.
   On identifie les poissons qui seront mang�s par les requins. */

void requins_morts(t_liste_requins *, t_ocean);
/* Re�oit la liste de requins et la mer.  
   On identifie les requins qui vont mourir de faim. */

void deplacer_requins(t_liste_requins *, t_ocean);
/* Re�oit la liste de requins et la mer. 
   On ajoute des b�b�-requins a la liste s'il y a lieu.
   On d�place les requins qui restent de une position-�cran. */

void deplacer_poissons(t_liste_poissons *, t_ocean);
/* Re�oit la liste de poissons et la mer. 
   On ajoute des b�b�-poissons a la liste s'il y a lieu.
   On d�place les poissons qui restent de une position-�cran. */

/******************************************************************************/
/*                             PROGRAMME PRINCIPAL                            */
/******************************************************************************/
int main(){
  t_ocean  la_mer;                //La grille de la mer
  t_liste_poissons  les_poissons; //la liste des ti-poissons
  t_liste_requins   les_requins;  //la liste des requins
  int nb_poisson, nb_requin;      //nombre de poissons et requins
  int stop=0, iter=0;             //pour contr�ler et compter les it�rations
  int MODE_AFF = getmode();       //le mode d'affichage (= 0/1)

  /* Variable-fichier pour �criture de donn�es. Sera ouvert SI MODE_AFF = 0 */
  FILE *fich = (MODE_AFF) ? NULL : fopen(NOM_FICHIER, "w");

  init_alea();     //initialiser le g�n�rateur al�atoire

  /* on �tablit les conditions initiales */
  nb_poisson = NB_POISSONS_INIT;
  nb_requin = NB_REQUINS_INIT;

  /* on vide toutes les structures de donn�es */
  vider_ocean(la_mer);
  vider_liste_poisson(&les_poissons);
  vider_liste_requin(&les_requins);

  /* on g�nere tous les ti-poissons */
  remplir_liste_poisson(&les_poissons, nb_poisson, la_mer);

  /* on g�nere tous les requins */
  remplir_liste_requin(&les_requins, nb_requin, la_mer);

  int nbF, nbS;
  dessiner_ocean(la_mer, &nbF, &nbS);    //on d�ssine l'�tat initial de la mer

  /* Boucle principale de simulation */
  do{
    iter++;    //prochaine iteration

	/* identifier les poissons mang�s */
	chasser_poissons(&les_poissons, &les_requins, la_mer);

	/* identifier les requins morts */
	requins_morts(&les_requins, la_mer);

	/* traiter les requins restants */
	deplacer_requins(&les_requins, la_mer);

	/* traiter les poissons restants */
	deplacer_poissons(&les_poissons, la_mer);

	/* mise-a-jour du nombre de poissons et requins */
	nb_poisson=get_nb_poisson(&les_poissons);
    nb_requin=get_nb_requins(&les_requins);
	
	/* Si le mode d'affichage est allum�.. */
	if (MODE_AFF) {
	  dessiner_ocean(la_mer, &nbF, &nbS);
      afficher_etat(iter, nb_poisson, nb_requin);
	  delai_ecran(TEMPS_DELAI);
	}
	else{  //sinon, on �crit le nombre de poissons/requins dans le fichier texte
      fprintf(fich, "%d  %d  %d\n", iter, nb_poisson, nb_requin);
	}

    /* si l'utilisateur appuye sur <ESC> on arr�te le programme */
	if (_kbhit()) 
	  stop = (_getch() == TOUCHE_FIN);
  }while(iter < MAX_TEMPS && !stop && nb_poisson && nb_requin); //tant qui reste des requins et poissons

  /* dessiner l'�tat final de la mer */
  dessiner_ocean(la_mer, &nbF, &nbS);
  afficher_etat(iter, nb_poisson, nb_requin);

  /* on confirme la raison de la fin du programme */
  if (!nb_poisson)  message("** Fin du programme due a l'extinction des POISSONS!");
  if (!nb_requin) message("** Fin du programme due a l'extinction des REQUINS!");
  
  if (!MODE_AFF) fclose(fich);  //fermer et sauvegarder le fichier de donn�es

  _getch();
  return EXIT_SUCCESS;
}

/******************************************************************************/
/*                         D�FINITIONS DE FONCTIONS                           */
/******************************************************************************/

/********************************* GETMODE ************************************/
/* Fonction qui permet de demander le mode d'affichage.                       */
/******************************************************************************/
int getmode()
{  char c;

     /* On demande et valide le mode d�sir� */
	 do {
		 printf("\nVoulez-vous avec affichage (O)ui/(N)on ? ");
		 fflush(stdin);
		 scanf("%c",&c);
		 c = toupper(c);
	 } while ((c != 'O') && (c != 'N'));   //doit �tre soit 'O' ou 'N'!!
	 
	 system("cls");
	 return (c == 'O') ? 1 : 0;   //on retourne soit 0/1 selon le choix
}

/**************************** chasser_poissons ********************************/
/* Re�oit la liste des poissons, la liste des requins et la mer.              */
/* On identifie les poissons qui seront mang�s par les requins.               */
/******************************************************************************/
void chasser_poissons(t_liste_poissons *les_poissons, t_liste_requins *les_requins, 
	                  t_ocean la_mer){
  t_animal nemo;      //poisson temporaire
  t_animal jaws;      //requin temporaire
  int i, pos, mange,
	  px, vx, py, vy;  //pos. temporaires: (px, py)= poisson, (vx, vy)= requin
  
  /* Pour tous les poissons (on doit re-v�rifier � chaque fois!!).. */
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

		  /* on r�cup�re l'indice du requin qui vient de manger ce poisson */
		  pos = numero_case(la_mer, vx, vy);
          jaws = get_requin(les_requins, pos);   //obtenir CE requin
		  ajout_energie(&jaws, JRS_DIGESTION);  //..et on augmente son indice d'�nergie

		  /* remettre le requin modifi� dans la liste */
	      modifier_requin(les_requins, pos, &jaws);  

		  vy = py+1;  vx = px+1;    //pour quitter les 2 boucles For
		  i--;         //pour rester au MEME endroit dans la liste des poissons!
	    }

	//si le poisson n'a pas �t� mang�, on v�rifie si il meurt de viellesse
	if (!mange) {
		if (est_mort(&nemo, MAX_AGE_POISSON)) {
			tuer_poisson(les_poissons, i, la_mer);
			i--;         //pour rester au MEME endroit dans la liste des poissons!
		}
	}
  }
}

/****************************** requins_morts *********************************/
/* Re�oit la liste de requins et la mer.                                      */
/* On identifie les requins qui vont mourir de faim.                          */
/******************************************************************************/
void requins_morts(t_liste_requins *les_requins, t_ocean la_mer){
  t_animal jaws;   //requin temporaire
 
  /* Pour tous les requins (on doit re-v�rifier � chaque fois!!).. */
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
/* Re�oit la liste de requins et la mer.                                      */
/* On ajoute des b�b�-requins a la liste s'il y a lieu.                       */
/* On d�place les requins qui restent de une position-�cran.                  */
/******************************************************************************/
void deplacer_requins(t_liste_requins *les_requins, t_ocean la_mer){
  t_animal jaws;    //requin temporaire
  int i, nb_requins = get_nb_requins(les_requins);  //le nombre de requins

  /* Pour tous les requins restants.. */
  for (i=0; i < nb_requins; i++){
    jaws = get_requin(les_requins, i);   //obtenir CE requin
	inc_age(&jaws, NB_JRS_PUB_SHRK);              //..et incr�menter son age
	dec_energie(&jaws);

	/* SI il est pret a procr�er on ajoute un b�b�-requin a la liste */
	if (puberte_atteinte(&jaws, NB_JRS_PUB_SHRK, NB_JRS_GEST_SHRK))
	  ajouter_requin(les_requins, &jaws, la_mer);
	else 
	  /* sinon on le d�place */
	  deplacer_requin(&jaws, i, la_mer);

	/* remettre le requin modifi� dans la liste */
	modifier_requin(les_requins, i, &jaws);  
  }
}

/*************************** deplacer_poissons ********************************/
/* Re�oit la liste de poissons et la mer.                                     */
/* On ajoute des b�b�-poissons a la liste s'il y a lieu.                      */
/* On d�place les poissons qui restent de une position-�cran.                 */
/******************************************************************************/
void deplacer_poissons(t_liste_poissons *les_poissons, t_ocean la_mer){
  t_animal nemo;         //poisson temporaire
  int i, nb_poisson = get_nb_poisson(les_poissons);  //le nombre de poissons

  /* Pour tous les poissons restants.. */
  for (i=0; i < nb_poisson; i++){
    nemo = get_poisson(les_poissons, i);   //obtenir CE poisson
	inc_age(&nemo, NB_JRS_PUB_POISSON);            //..et incr�menter son age

	/* SI il est pret a procr�er on ajoute un b�b�-poisson a la liste */
	if (puberte_atteinte(&nemo, NB_JRS_PUB_POISSON, NB_JRS_GEST_POISSON)) {
		if (ajouter_poisson(les_poissons, &nemo, la_mer))    //si il a r�ussi a procr�er..
			dec_energie(&nemo);                         //perte d'�nergie si il a accouch�
	}
	else 
	    /* sinon on le d�place */
	    deplacer_poisson(&nemo, i, la_mer);
		  
	/* remettre le poisson modifi� dans la liste */
    modifier_poisson(les_poissons, i, &nemo);
  }
}

/******************************************************************************/
