//
//  main.c
//  CSV
//
//  Created by Valentin Monnot / Josselin Pichereau on 15/01/2018.
//  Evalution TP Final
//

#include <stdlib.h>
#include <stdio.h>
#include "vecteur.h"
#include "balle.h"

int main(int argc, char ** argv)
{

    if (argc < 3) 	// Test du nombre d'arguments minimum d'entrée en console sinon quitte si il n'y en a pas assez.
    {

      printf("Il manque un ou plusieurs arguments.");
      return EXIT_FAILURE; 	// On quitte le programme

    }

    Balle Balle_v = chargerBalle(argv[1]); 	// Déclaration de la balle et chargement des paramètres du fichier texte.

    FILE *pFichier = NULL; 			// Déclaration du pointeur sur fichier
    pFichier = fopen(argv[2], "w"); 		// Ouverture du fichier texte et assignation du pointeur sur fichier

    float t; 					// Variable du temps

    for(t = 0.0; t <= 3; t += 0.01) 		// Boucle de caclule de nouvelle position de la balle
    {

        fprintf(pFichier, "%f;%f;%f\n", t, Balle_v.position.x, Balle_v.position.y); 	// Ecriture de la position de la balle et du temps dans le csv
        int secu = majPosition(&Balle_v, 0.01); 	// Mise à jour avec les nouvelles coordonées, vitesses, ect... +  renvoi -1 à secu si la Balle est NULL
        if(secu == -1) return EXIT_FAILURE;     	//Sécurité

    }

    fclose(pFichier);
    return 0;
}
