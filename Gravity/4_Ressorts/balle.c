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
  pFichier = fopen(chemin, "r"); 	// Ouverture du fichier texte
  
  if(!pFichier)
  {

    printf("Problème lors de l'ouverture du fichier de configuration.\n");
    exit(EXIT_FAILURE);
    
  } 
  
  fscanf(pFichier, "masse %f\n", &Balle_v.masse); 				  // Récupération de la valeur de la masse
  fscanf(pFichier, "fCoef %f\n", &Balle_v.coeffriction); 			  // Récupération de la valeur du coef.friction
  fscanf(pFichier, "position %f %f\n", &Balle_v.position.x, &Balle_v.position.y); // Récupéreration de la valeur position en x et y
  fscanf(pFichier, "vitesse %f %f", &Balle_v.vitesse.x, &Balle_v.vitesse.y);	  // Récupéreration de la valeur vitesse en x et y
  fclose(pFichier);

  return Balle_v;

}

int normalVectnot(Vecteur v1)				// Fonction vérifiant si un vecteur n'est pas égal à 0
{
	if(v1.x == 0 && v1.y == 0)
	return 1;
	
	else
	return 0;
  
}

int majPosition(Balle * Balle_v, float dt)          // Mise à jour de la position de la balle en appliquant le PFD et retourne -1 si balle est NULL (securite)
{

  if (!Balle_v) return -1;

  else
  {

    Vecteur P = creerVect(0,-9.81);               			// Création du vecteur poids avec le vecteur g (gravité)
    P = multScalVect(Balle_v->masse,P);					// Calcule du poids

    Vecteur f = multScalVect(-Balle_v->coeffriction,Balle_v->vitesse);  // Création du vecteur des forces de frottements fisqueux

    float k=200 ,l ,lo=0.02 ,s ;	// Déclaration et initialisation des valeurs utilisée dans la force de rappel du ressort

    Vecteur I;				// Déclaration du vecteur normalisé (direction vers le point d'attache)
    Vecteur F= creerVect(0,0);		// Déclaration de la force de rappel du ressort et initialisation à 0
    Vecteur S = addVect(P,f);		// Déclaration de la somme des forces du poids et des forces de frottements
    int b;

    if(Balle_v->ballePrecedente != NULL)	// Vérifie si il y a une balle précédente
    {

      I= subVect(Balle_v->position,Balle_v->ballePrecedente->position);	// Soustrait le vecteur position de la balle avec le vecteur position de la balle précédente
      l= normVect(I);							// Calcule la norme du vecteur I
      s=-k*(l-lo);							// Calcule la première partie de la formule de la force de rappel du ressort
      I= normaliseVect(I);	  					// Normalise le vecteur I
      b= normalVectnot(I);						// Appel une fonction vérifiant si le vecteur normalisé n'égal pas 0
      	 
      	 if(b==0)
     	 {
     	 F=multScalVect( s, I);						// Calcule la force de rappel du ressort
     	 S = addVect(S,F);						// Calcule la somme des forces totales
    	 }
    }
    
    if(Balle_v->balleSuivante != NULL)		// Vérifie si il y a une balle suivante
    {
      I= subVect(Balle_v->position,Balle_v->balleSuivante->position);	// Soustrait le vecteur position de la balle avec le vecteur position de la balle suivanteante
      l= normVect(I);							// Calcule la norme du vecteur I
      s=-k*(l-lo);							// Calcule la première partie de la formule de la force de rappel du ressort
      I= normaliseVect(I);						// Normalise le vecteur I
      b= normalVectnot(I);						// Appel une fonction vérifiant si le vecteur normalisé n'égal pas 0
      	
      	if(b==0)
      	{
      	F=multScalVect( s, I);						// Calcule la force de rappel du ressort
      	S = addVect(S,F);						// Calcule la somme des forces totales
      	}
    }


    	Balle_v->acceleration = multScalVect(((float)1/Balle_v->masse),S);     // Calcul de l’accélération courante grâce à l’équation (1)

    	Balle_v->vitesse = addVect(Balle_v->vitesse,(multScalVect(dt , Balle_v->acceleration)));      // Calcul de la nouvelle vitesse grâce à l'équation (2)

   	Balle_v->position = addVect(Balle_v->position,(multScalVect(dt , Balle_v->vitesse)));    //Calcul de la nouvelle position grâce a l'équation (3)


    return 0;

  }

}
