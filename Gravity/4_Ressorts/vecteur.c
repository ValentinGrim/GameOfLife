//
//  vecteur.c
//  CSV
//
//  Created by Valentin Monnot / Josselin Pichereau on 15/01/2018.
//  Evalution TP Final
//

#include "balle.h"
#include "vecteur.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Vecteur creerVect(float x,float y) // Retourne une structure Vecteur initialisée à (x,y)
{
	Vecteur v;
	v.x=x;
	v.y=y;

	return v;
}

Vecteur multScalVect(float s,Vecteur v) // Multiplie un scalaire avec un vecteur et retourne le résultat
{
	Vecteur v1;
	v1.x=s*v.x;
	v1.y=s*v.y;

	return v1;
}

Vecteur addVect(Vecteur v1,Vecteur v2) // Additionne 2 vecteurs et retourne le résultat
{
	Vecteur v3;
	v3.x=v1.x+v2.x;
	v3.y=v1.y+v2.y;

	return v3;
}

Vecteur normaliseVect (Vecteur v) // Normalise un vecteur et retourne le résultat
{

	float norme = normVect(v);
	if (norme == 0)
	{

		v.x = 0;
		v.y = 0;

		return v;

	}

	v.x /= norme;
	v.y /= norme;

	return v;

}

float normVect(Vecteur v) // Calcule la norme d'un vecteur et retourne le résultat
{

	float norme;
	norme = sqrt((v.x * v.x) + (v.y * v.y));

	return norme;

}
Vecteur subVect(Vecteur v1, Vecteur v2) // Soustrait 2 vecteurs et retourne le résultat
{

	Vecteur v3;
	v3.x=v1.x-v2.x;
	v3.y=v1.y-v2.y;

	return v3;

}
