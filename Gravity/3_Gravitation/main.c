#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "vecteur.h"
#include "sdl_stuff.h"
#include "balle.h"
#include "decl.h"
#include "fpstimer.h"

AttracteurList gAttractList; // Variable global du nombre et de la position des attracteurs

void clicSouris(float x, float y) // Fonction appellée lorsque l'on appuie avec le bouton gauche de la souris
{
    // NB : une variable locale declaree static ne perd pas sa valeur entre deux appels a la fonction
    // son initialisation est effectué au tout premier appel de la fonction
    // on s'en sert ici pour savoir quel attracteur on est en train de positioner

    static int attracteurCurrent = 0;

    gAttractList.utiliseMoi[attracteurCurrent] = 1; // Mettre la variable utiliseMoi à 1 si un attracteur a été posé (initialement a 0)
    gAttractList.positionAttracteur[attracteurCurrent] = creerVect(x, y); // Créer le vecteur positionAttracteur avec les valeurs x et y du clic souris

    sdl_setAttracteurPosition(attracteurCurrent, x, y);
    attracteurCurrent++;
    attracteurCurrent %= NB_ATTRACTEURS;
}

int main(int argc, char **argv)
{
    // Test du nombre d'arguments minimum d'entrée en console sinon quitte si il n'y en a pas assez.
    if (argc < 2) {
        printf("Il manque un ou plusieurs arguments.");
        return EXIT_FAILURE; // On quitte le programme
    }

    float dt;                              // Déclaration de la variable delta
    Balle Balle_v = chargerBalle(argv[1]); // Déclaration de la balle et chargement des paramètres du fichier texte.
    initAttracteurList(&gAttractList);     // Initialisation des attracteurs à 0

    if (!sdl_startup()) {
        return -1;
    }

    fpsInit();
    // program main loop
    do {
        fpsStep();

        dt = fpsGetDeltaTime();                   // Assigne le temps entre deux frames à la variable dt
        majPosition(&Balle_v, &gAttractList, dt); // Mise à jour de la position de la balle en fonction de dt et de la liste des attracteurs

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
    // end main loop

    sdl_clean();
    return 0;
}
