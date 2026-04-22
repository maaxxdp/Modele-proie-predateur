/******************************************************************************/
/*  ANIMAL.CPP                                                                */         
/*  Module utilitaire qui permet de g�rer un type "t_animal"                  */
/*  Conception : Eric Th�                                                     */
/******************************************************************************/

#include "animal.h"

/****************************** INIT ANIMAL ***********************************/
/* Re�oit un animal et ses valeurs initiales, va initialiser l'animal re�u.   */
/******************************************************************************/
void init_animal(t_animal *animal, int px, int py, int age, int energie, int gest){
    animal->posx = px;//initialise position en x
    animal->posy = py;//initialise position en y
    animal->age = age;//initialise age
    animal->energie_sante = energie;//inititalise energie
    animal->jrs_gest = gest;//initialise jours de gestatiojn
}

/****************************** GET POSITION **********************************/
/* Re�oit un animal et retourne sa position via [*px, *py].                   */
/******************************************************************************/
void get_position(const t_animal *animal, int *px, int *py){  
    *px = animal->posx;//retourne dans le pointeur la valeur de posx de l'animal
    *py = animal->posy;//retourne dans le pointeur la valeur de posy de l'animal
}

/****************************** SET POSITION **********************************/
/* Re�oit un animal et une position et va inscrire cette position � l'animal. */
/******************************************************************************/
void set_position(t_animal *animal, int px, int py){  
    animal->posx = px;//position x est egal a position x de l'animal
    animal->posy = py;//position y est egal a position y de l'animal
}

/**************************** PUBERTE ATTEINTE ********************************/
/* Re�oit un animal et retourne 1 si le poisson a attient l'age de            */
/* pubert� ET a termin� sa p�riode de gestation (donc, il va procr�er),       */
/* retourne 0 sinon.                                                          */
/******************************************************************************/
int  puberte_atteinte(const t_animal *animal, int puberte, int gestation){
    if (animal->age >= puberte && animal->jrs_gest >= gestation) {
        return 1;//si plus vieux que puberte ET jrs_gest plus grand ou egal a gestation, retourne 1
    } else {
        return 0;//sinon, retourne 0
    }
}

/****************************** INC AGE ***************************************/
/* Re�oit un animal et va incr�menter son age ainsi que le nombre de jours    */
/* en gestation de +1 jour si il est assez vieux pour procr�er.               */
/******************************************************************************/
void inc_age(t_animal *animal, int age_puberte){
    animal->age++;//augmente l'age de 1
    if (animal->age >= age_puberte){//si plus vieux que puberte
        animal->jrs_gest++;//augmente jrs_gest de 1
    }
}

/************************** RESET GESTATION ***********************************/
/* Re�oit un animal et va r�initialiser les jours de gestation � "val".       */
/******************************************************************************/
void reset_gestation(t_animal *animal, int val){       
    animal->jrs_gest = val;//jrs_gest va etre egal a val
}

/**************************** AJOUT ENERGIE ***********************************/
/* Re�oit un animal et va incr�menter son niveau d'�nergie de la valeur re�ue */
/******************************************************************************/
void ajout_energie(t_animal *animal, int energie){
    animal->energie_sante += energie;//ajoute energie a energie_sante
}

/**************************** DEC ENERGIE *************************************/
/* Re�oit un animal et va d�cr�menter son niveau d'�nergie de -1.             */
/******************************************************************************/
void dec_energie(t_animal *animal){   
    animal->energie_sante--;//reduis de 1 la valeur energie_sante
}

/**************************** GET ENERGIE *************************************/
/* Re�oit un animal et va retourner son niveau d'�nergie.                     */
/******************************************************************************/
int  get_energie(t_animal *animal){
	return animal->energie_sante;//retourne la valeur qui se trouve dans animal sous eergie_sante
}

/***************************** EST MORT ***************************************/
/* Retourne 1 si l'animal re�u vient de mourir de faim (plus d'�nergie)       */
/* OU si il a atteint son �ge maximal (age_max). On retourne 0 sinon.         */
/******************************************************************************/
int  est_mort(const t_animal *animal, int age_max){   
    if (animal->energie_sante <= 0 || animal->age > age_max) {
        return 1;//si energie plus petit ou egal 0 OU age plus grand qu'age_max, retourne 1
    } else {
        return 0;//retourne 0 dans le cas contraire
    }
}
