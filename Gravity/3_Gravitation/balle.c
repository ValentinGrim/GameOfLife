//
//  balle.c
//  CSV
//
//  Created by Valentin Monnot / Josselin Pichereau on 15/01/2018.
//  Evalution TP Final
//

#include "balle.h"
#include "vecteur.h"
#include <stdlib.h>
#include <stdio.h>
#include "decl.h"

Balle chargerBalle(char * chemin)
{
  Balle Balle_v;       			// Déclaration de la balle principale
  FILE *pFichier = NULL; 		// Initialisation du pointeur sur fichier à NULL
  pFichier = fopen(chemin, "r"); 	// Ouverture fichier texte

  if(!pFichier)
  {

    printf("Problème lors de l'ouverture du fichier de configuration.\n");
    exit(EXIT_FAILURE);
    
  } 

  fscanf(pFichier, "masse %f\n", &Balle_v.masse); 					// Récupération de la valeur de la masse
  fscanf(pFichier, "fCoef %f\n", &Balle_v.coeffriction); 				// Récupération de la valeur du coef.friction
  fscanf(pFichier, "position %f %f\n", &Balle_v.position.x, &Balle_v.position.y); 	// Récupéreration de la valeur position en x et y
  fscanf(pFichier, "vitesse %f %f", &Balle_v.vitesse.x, &Balle_v.vitesse.y); 		// Récupéreration de la valeur vitesse en x et y
  fclose(pFichier);

  return Balle_v;
}


int majPosition(Balle * Balle_v, AttracteurList * pAttrList , float dt)          // Mise à jour de la position de la balle en appliquant le PFD et retourne -1 si balle est NULL (sécurité)
{

  if (!Balle_v) return -1;

  else
  {

    Vecteur S;
    S = creerVect(0,0);                               // Le vecteur de la somme des forces de gravitation

    int i=0;
    if(i < NB_ATTRACTEURS) // Sécurité tableau
    {

      for(i = 0; pAttrList->utiliseMoi[i]!=0; i++) // Boucle pour calculer toute les forces d'attraction des attracteurs.
      {

          Vecteur direction = subVect(pAttrList->positionAttracteur[i],Balle_v->position); 	// Calcule Vecteur direction
          float distance = normVect(direction);						 	// Calcule norme du vecteur direction
          direction = normaliseVect(direction);						 	// Normalise le vecteur direction

	         float magnitude =(0.1/(distance * distance));		// Calcule la magnitude de la force de Gravitation
	         if (magnitude > 1)					// Restreint la magnitude quand elle est supérieur à 1
	           {

		             magnitude = 0.5;

	           }

          Vecteur F = multScalVect(magnitude,direction);		// Calcule la force de gravitation
          Vecteur F2 = multScalVect(pAttrList->utiliseMoi[i],F);	// Sécurité si il n'y a pas d'attracteur

          S = addVect(S,F2);	// Vecteur de la somme des forces

      }
    

    Balle_v->acceleration = multScalVect(((float)1/Balle_v->masse),S);      			// Calcul de l’accélération courante grâce à l’équation (1)
    Balle_v->vitesse = addVect(Balle_v->vitesse,(multScalVect(dt , Balle_v->acceleration)));  	// Calcul de la nouvelle vitesse grâce à l'équation (2)
    Balle_v->position = addVect(Balle_v->position,(multScalVect(dt , Balle_v->vitesse)));     	// Calcul de la nouvelle position grâce a l'équation (3)

    return 0;

   }
  }
    return 0;
}

void initAttracteurList(AttracteurList * pAttrList)	// Initialisation des attracteurs à 0
{

	int i;
	for(i = 0; i < 5; i++)
	{

		pAttrList->positionAttracteur[i].x = 0;
		pAttrList->positionAttracteur[i].y = 0;
		pAttrList->utiliseMoi[i] = 0;

	}

}
