#include "balle.h"
#include "vecteur.h"
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "sdl_stuff.h"
#include "decl.h"
#include "fpstimer.h"

Balle gBalleTab[NB_BALLES]; // Création du tableau de balle

void dragSouris(float x, float y)
{
    gBalleTab[0].position.x = x; // Récupération de la position x de la souris pour la position de la première balle
    gBalleTab[0].position.y = y; // Récupération de la position y de la souris pour la position de la première balle
}

int main(int argc, char **argv)
{
    // Test du nombre minimum d'arguments d'entrée en console, quitte si il n'y en a pas assez.
    if (argc < 2) {
        printf("Il manque un ou plusieurs arguments.");
        return EXIT_FAILURE; // On quitte le programme
    }

    if (!sdl_startup()) {
        return -1;
    }

    fpsInit();

    float dt; // Déclaration de la variable delta
    int i;
    for (i = 0; i < NB_BALLES; i++) // Boucle pour créer le nombre de balle NB_BALLES
    {
        // Créer chaque balle du tableau avec les caractéristique du fichier balle.txt utilisé avec la fonction chargerBalle
        gBalleTab[i] = chargerBalle(argv[1]);

        gBalleTab[0].ballePrecedente = NULL;        // Initialisation de la balle précèdant la première balle à NULL puisqu'elle n'existe pas
        gBalleTab[0].balleSuivante = &gBalleTab[1]; // Relie la première balle à la balle suivante

        gBalleTab[i].ballePrecedente = &gBalleTab[i - 1]; // Initialise chaque balle précèdante avec la balle précèdante dans le tableau
        gBalleTab[i].balleSuivante = &gBalleTab[i + 1];   // Initialise chaque balle suivante avec la balle suivante dans le tableau

        gBalleTab[NB_BALLES - 1].ballePrecedente = &gBalleTab[NB_BALLES - 2]; // Relie la dernière balle à l'avant dernière balle
        gBalleTab[NB_BALLES - 1].balleSuivante = NULL; // Initialisation de la balle suivant la dernière balle à NULL puisqu'elle n'existe pas
    }
    // program main loop
    do {

        fpsStep();

        dt = fpsGetDeltaTime();         // Assigne le temps entre deux frames à la variable dt
        for (i = 0; i < NB_BALLES; i++) // Boucle qui met à jour la position de chaque balle, qui limite ses déplacement à la fenêtre et affiche la balle
        {

            majPosition(&gBalleTab[i], dt); // Mise à jour de la position de chaque balle en fonction de dt

            if (gBalleTab[i].position.x < BALL_RADIUS) // Condition si la balle touche le bord gauche
            {
                // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
                gBalleTab[i].vitesse.x = (-gBalleTab[i].vitesse.x) * 0.9;
                gBalleTab[i].position.x = BALL_RADIUS; // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran
            }

            if (gBalleTab[i].position.x > 1 - BALL_RADIUS) // Condition si la balle touche le bord droit
            {
                // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
                gBalleTab[i].vitesse.x = (-gBalleTab[i].vitesse.x) * 0.9;
                gBalleTab[i].position.x = 1 - BALL_RADIUS; // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran
            }

            if (gBalleTab[i].position.y < BALL_RADIUS) // Condition si la balle touche le bord du haut
            {
                // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
                gBalleTab[i].vitesse.y = (-gBalleTab[i].vitesse.y) * 0.9;
                gBalleTab[i].position.y = BALL_RADIUS; // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran
            }

            if (gBalleTab[i].position.y > 1 - BALL_RADIUS) // Condition si la balle touche le bord du bas
            {
                // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
                gBalleTab[i].vitesse.y = (-gBalleTab[i].vitesse.y) * 0.9;
                gBalleTab[i].position.y = 1 - BALL_RADIUS; // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran
            }

            sdl_setBallPosition(i, gBalleTab[i].position.x, gBalleTab[i].position.y); // Affichage de la balle
        }

    } while (sdl_loop());
    // end main loop

    sdl_clean();
    return 0;
}
