#include "balle.h"
#include "vecteur.h"
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include"sdl_stuff.h"
#include "decl.h"
#include "fpstimer.h"


Balle gBalleTab[NB_BALLES]; 		// Création du tableau de balle

void dragSouris(float x, float y)
{
    gBalleTab[0].position.x=x; 		//Récupération de la position x de la souris pour la position de la première balle
    gBalleTab[0].position.y=y; 		//Récupération de la position y de la souris pour la position de la première balle
}



int main ( int argc, char** argv )
{

    if (argc < 3) 		// Test du nombre minimum d'arguments d'entrée en console, quitte si il n'y en a pas assez.
    {

      printf("Il manque un ou plusieurs arguments.");
      return EXIT_FAILURE; 				// On quitte le programme

    }

    if(!sdl_startup())
        return -1;

    fpsInit();

    float dt; 			// Déclaration de la variable delta
    int i;
    printf("coucou");
        gBalleTab[0] = chargerBalle(argv[1]); // Créer chaque balle du tableau avec les caractéristique du fichier balle.txt utilisé avec la fonction chargerBalle
	gBalleTab[1] = chargerBalle(argv[2]);
  	
    
    // program main loop
    do
    {

        fpsStep();

        dt=fpsGetDeltaTime();  		// Assigne le temps entre deux frames à la variable dt
    for(i=0; i<NB_BALLES; i++) 		// Boucle qui met à jour la position de chaque balle, qui limite ses déplacement à la fenêtre et affiche la balle
    {

        majPosition(&gBalleTab[i], dt); 	// Mise à jour de la position de chaque balle en fonction de dt

        if(gBalleTab[i].position.x < BALL_RADIUS) 	// Condition si la balle touche le bord gauche
        {

            gBalleTab[i].vitesse.x = (-gBalleTab[i].vitesse.x) * 1; // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
            gBalleTab[i].position.x = BALL_RADIUS; 		      // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran

        }

        if(gBalleTab[i].position.x > 1 - BALL_RADIUS) 	// Condition si la balle touche le bord droit
        {

            gBalleTab[i].vitesse.x = (-gBalleTab[i].vitesse.x) * 1; // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
            gBalleTab[i].position.x = 1 - BALL_RADIUS; 		      // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran

        }

        if(gBalleTab[i].position.y < BALL_RADIUS) // Condition si la balle touche le bord du haut
        {

           gBalleTab[i].vitesse.y = (-gBalleTab[i].vitesse.y) * 1; // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
           gBalleTab[i].position.y = BALL_RADIUS; 		     // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran
        }

        if(gBalleTab[i].position.y > 1 - BALL_RADIUS) // Condition si la balle touche le bord du bas
        {

            gBalleTab[i].vitesse.y = (-gBalleTab[i].vitesse.y) * 1; // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
            gBalleTab[i].position.y = 1 - BALL_RADIUS; 		      // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran

        }


        sdl_setBallPosition(i,gBalleTab[i].position.x,gBalleTab[i].position.y); // Affichage de la balle

    }

    }
    while(sdl_loop());
    // end main loop

    sdl_clean();
    return 0;
}
