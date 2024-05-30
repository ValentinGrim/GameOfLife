//
//  vecteur.h
//  CSV
//
//  Created by Valentin Monnot / Josselin Pichereau on 15/01/2018.
//  Evalution TP Final
//

#ifndef vecteur_h
#define vecteur_h

typedef struct Vecteur_decl			// Définition de la structure Vecteur_decl
{
	float x;
	float y;
} Vecteur;

Vecteur creerVect(float x,float y);		// Prototype de la fonction creerVect
Vecteur multScalVect(float s, Vecteur v);	// Prototype de la fonction multScalVect
Vecteur addVect(Vecteur v1, Vecteur v2);	// Prototype de la fonction addvect

#endif 
