#include <stdlib.h>
#include <stdio.h>
#include "vecteur.h"
#include "balle.h"
#include "sdl_stuff.h"
#include "fpstimer.h"
#include <math.h>

int main(int argc, char **argv)
{
    // Test du nombre d'arguments minimum d'entrée en console sinon quitte si il n'y en a pas assez.
    if (argc < 2) {
        printf("Il manque un ou plusieurs arguments.");
        return EXIT_FAILURE; // On quitte le programme
    }

    float dt;                              // Déclaration de la variable delta
    Balle Balle_v = chargerBalle(argv[1]); // Déclaration de la balle et chargement des paramètres du fichier texte.

    if (!sdl_startup()) {
        return -1;
    }

    fpsInit(); // boucle pour mettre à jour en continue la simulation

    do {
        fpsStep();

        dt = fpsGetDeltaTime();    // Assigne le temps entre deux frames à la variable dt
        majPosition(&Balle_v, dt); // Mise à jour de la position de la balle en fonction de dt

        if (Balle_v.position.x < BALL_RADIUS) // Condition si la balle touche le bord gauche
        {
            // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
            Balle_v.vitesse.x = (-Balle_v.vitesse.x) * 0.9;
            Balle_v.position.x = BALL_RADIUS; // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran
        }

        if (Balle_v.position.x > 1 - BALL_RADIUS) // Condition si balle touche le bord droit
        {
            // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
            Balle_v.vitesse.x = (-Balle_v.vitesse.x) * 0.9;
            Balle_v.position.x = 1 - BALL_RADIUS; // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran
        }

        if (Balle_v.position.y < BALL_RADIUS) // Condition si balle touche le bord haut
        {
            // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
            Balle_v.vitesse.y = (-Balle_v.vitesse.y) * 0.9;
            Balle_v.position.y = BALL_RADIUS; // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran
        }

        if (Balle_v.position.y > 1 - BALL_RADIUS) // Condition si balle touche le bord bas
        {
            // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
            Balle_v.vitesse.y = (-Balle_v.vitesse.y) * 0.9;
            Balle_v.position.y = 1 - BALL_RADIUS; // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran
        }

        sdl_setBallPosition(Balle_v.position.x, Balle_v.position.y); // Permet d'afficher la balle avec sa nouvelle position.

    } while (sdl_loop());

    sdl_clean();
    return 0;
}
