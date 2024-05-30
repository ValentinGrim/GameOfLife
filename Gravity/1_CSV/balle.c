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
  fscanf(pFichier, "position %f %f\n", &Balle_v.position.x, &Balle_v.position.y); 	// Récupération de la valeur position en x et y
  fscanf(pFichier, "vitesse %f %f", &Balle_v.vitesse.x, &Balle_v.vitesse.y); 		// Récupération de la valeur vitesse en x et y
  fclose(pFichier);

  return Balle_v;
}

int majPosition(Balle * Balle_v, float dt)          // Mise à jour de la position de la balle en appliquant le PFD et retourne -1 si balle est NULL (sécurité)
{

  if (!Balle_v) return -1;

  else
  {

    Vecteur P = creerVect(0,-9.81);                  // Création du vecteur poids
    P = multScalVect(Balle_v->masse,P);

    Vecteur f = multScalVect(-Balle_v->coeffriction,Balle_v->vitesse);      // Création du vecteur des forces de frottements visqueux

    Vecteur S = addVect(P,f);                        // Le vecteur de la somme des forces

    Balle_v->acceleration = multScalVect(((float)1/Balle_v->masse),S);      			// Calcul de l’accélération courante grâce à l’équation (1)
    Balle_v->vitesse = addVect(Balle_v->vitesse,(multScalVect(dt , Balle_v->acceleration)));  	// Calcul de la nouvelle vitesse grâce à l'équation (2)
    Balle_v->position = addVect(Balle_v->position,(multScalVect(dt , Balle_v->vitesse)));     	// Calcul de la nouvelle position grâce a l'équation (3)

    return 0;

  }

}
