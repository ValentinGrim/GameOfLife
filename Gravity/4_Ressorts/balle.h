//
//  balle.h
//  CSV
//
//  Created by Valentin Monnot / Josselin Pichereau on 15/01/2018.
//  Evalution TP Final
//

#ifndef balle_h
#define balle_h

#include "vecteur.h"


typedef struct Balle_decl             // Définition de la structure Balle_decl
{

  float masse;              //Kilo
  float coeffriction;
  Vecteur position;         //m
  Vecteur vitesse;          // m/s
  Vecteur acceleration;     // m/s2
  struct Balle_decl * ballePrecedente;
  struct Balle_decl * balleSuivante;

} Balle;

Balle chargerBalle(char * argc);        // Prototype de la fonction chargerBalle

int majPosition(Balle * Balle ,float dt); // Prototype de la fonction majPosition

int normalVectnot(Vecteur v1);          // Prototype de la fonction normalVectnot

#endif 
