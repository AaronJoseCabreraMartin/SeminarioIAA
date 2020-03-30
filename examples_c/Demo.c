
/* 
 * Demo.c
 *
 * Example use of Netica API Programmer's Library
 *
 * This is a combination of the first 2 examples in the Netica API
 * Reference Manual.  It can be used to test if the installation is successful.
 *
 * Copyright (C) 1992-2010 by Norsys Software Corp.
 * The software in this file may be copied, modified, and/or included in 
 * derivative works without charge or obligation.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "Netica.h"
#include "NeticaEx.h"

#define CHKERR  {if (GetError_ns (env, ERROR_ERR, NULL))  goto error;}

extern environ_ns *env;

int main (void) {
	net_bn *net;
	//node_bn *VisitAsia, *Tuberculosis, *Smoking, *Cancer, *TbOrCa, *XRay;
	node_bn *State, *StatePlusOne, *Health, *Weapon,  *NearWeapon;
	node_bn *HearNoise, *NearHealth, *NearEnemy, *EnemyWeapon;
	double belief;
	char mesg[MESG_LEN_ns];
	int res;
	
	printf ("\n¡Bienvenido a la API de Netica!\n");
	printf ("Este es el proyecto del seminario de inteligencia artificial en videojuegos ");
	printf ("de la asignatura Inteligencia Artificial Avanzada.\n");
	printf ("Autores: Grupo G4\n");
	printf ("	-Manuel Andrés Carrera Galafante\n");
	printf ("	-Aarón José Cabrera Martín\n");
	printf ("	-Rafael Cala González\n");
	printf ("--------------------------------------------------------------------\n\n");
	
	env = NewNeticaEnviron_ns (NULL, NULL, NULL);
	res = InitNetica2_bn (env, mesg);

	printf ("%s\n", mesg);
	if (res < 0)  return -1;
	
	net = NewNet_bn ("Our_Bot_on_Netica", env);
	CHKERR
	// CREAR EL ESQUEMA DE LA RED
	State = NewNode_bn ("State", 6, net);
	StatePlusOne = NewNode_bn ("StatePlusOne", 6, net);
	Health =      NewNode_bn ("Health", 2, net);
	Weapon =       NewNode_bn ("Weapon", 2, net);
	NearHealth =       NewNode_bn ("HealthPackClose", 2, net);
	NearEnemy =         NewNode_bn ("NearEnemy", 2, net);
	EnemyWeapon =				NewNode_bn ("EnemyWeapon", 2, net);
	NearWeapon = 				NewNode_bn ("NearWeapon", 2, net);
	HearNoise =  				NewNode_bn ("HearNoise", 2, net);
	CHKERR

	// DARLE LOS ESTADOS POSIBLES DE CADA NODO
	SetNodeStateNames_bn (State,   "RecogerArma, Atacar, RecogerEnergia, Explorar, Huir, DetectarPeligro");
	SetNodeStateNames_bn (StatePlusOne, "RecogerArma, Atacar, RecogerEnergia, Explorar, Huir, DetectarPeligro");
	SetNodeStateNames_bn (Health, "Alto, Bajo");
	SetNodeStateNames_bn (Weapon,      "Armado, Desarmado");
	SetNodeStateNames_bn (NearHealth,      "Si, No");
	SetNodeStateNames_bn (NearEnemy,        "Si, No");
	SetNodeStateNames_bn (EnemyWeapon,      "Armados, Desarmados");
	SetNodeStateNames_bn (NearWeapon,      "Si, No");
	SetNodeStateNames_bn (HearNoise,        "Si, No");
	
	// PONERLE NOMBRE A LA TABLA
	SetNodeTitle_bn (StatePlusOne, "St+1");
	CHKERR

	// AÑADIR LAS RELACIONES ENTRE NODOS (PADRE -> HIJO)
	AddLink_bn (State, StatePlusOne);
	AddLink_bn (StatePlusOne, Health);
	AddLink_bn (StatePlusOne, Weapon);
	AddLink_bn (StatePlusOne, NearHealth);
	AddLink_bn (StatePlusOne, NearEnemy);
	AddLink_bn (StatePlusOne, EnemyWeapon);
	AddLink_bn (StatePlusOne, NearWeapon);
	AddLink_bn (StatePlusOne, HearNoise);
	CHKERR
	
	// AÑADIR LAS PROBABILIDADES DE CADA NODO.

	// NODO ESTADO
	SetNodeProbs(State, 0.05, 0.20, 0.05, 0.25, 0.1, 0.35);
																									 
	//										       RecoA  Ata  RecoE Expl Huir  Detec
	SetNodeProbs (StatePlusOne, "RecogerArma",     0.001, 0.3,   0.03,   0.3,   0.03,  0.339);
	SetNodeProbs (StatePlusOne, "Atacar", 	       0.005, 0.6,   0.005,  0.23,  0.15,  0.01);
	SetNodeProbs (StatePlusOne, "RecogerEnergia",  0.1,   0.49,  0.001,  0.209, 0.1,   0.1);
	SetNodeProbs (StatePlusOne, "Explorar", 	   0.35,  0.09,  0.05,   0.20,  0.005, 0.305);
	SetNodeProbs (StatePlusOne, "Huir", 	       0.005, 0.005, 0.49,   0.005, 0.49,  0.005);
	SetNodeProbs (StatePlusOne, "DetectarPeligro", 0.2,   0.47,  0.015,  0.005, 0.30,  0.01);

	// H                                     Alto  Bajo
	SetNodeProbs (Health, "RecogerArma",     0.90, 0.10);
	SetNodeProbs (Health, "Atacar", 		     0.80, 0.20);
	SetNodeProbs (Health, "RecogerEnergia",  0.10, 0.90);
	SetNodeProbs (Health, "Explorar", 		   0.80, 0.20);
	SetNodeProbs (Health, "Huir", 			     0.05, 0.95);
	SetNodeProbs (Health, "DetectarPeligro", 0.55, 0.45);

  // W                                       Armado  Desarmado
	SetNodeProbs (Weapon, "RecogerArma",       0.01,   0.99);
	SetNodeProbs (Weapon, "Atacar", 		       0.999,  0.001);
	SetNodeProbs (Weapon, "RecogerEnergia",    0.80,   0.20);
	SetNodeProbs (Weapon, "Explorar", 		     0.80,   0.20);
	SetNodeProbs (Weapon, "Huir", 			       0.10,   0.90);
	SetNodeProbs (Weapon, "DetectarPeligro",   0.99,   0.01);

	// PH                                          Si      No  
	SetNodeProbs (NearHealth, "RecogerArma",       0.10,   0.90);
	SetNodeProbs (NearHealth, "Atacar", 		       0.10,   0.90);
	SetNodeProbs (NearHealth, "RecogerEnergia",    0.999,  0.001);
	SetNodeProbs (NearHealth, "Explorar", 		     0.10,   0.90);
	SetNodeProbs (NearHealth, "Huir", 			       0.10,   0.90);
	SetNodeProbs (NearHealth, "DetectarPeligro",   0.10,   0.90);

	// PW                                          Si      No  
	SetNodeProbs (NearWeapon, "RecogerArma",       0.99,   0.01);
	SetNodeProbs (NearWeapon, "Atacar", 		       0.10,   0.90);
	SetNodeProbs (NearWeapon, "RecogerEnergia",    0.10,   0.90);
	SetNodeProbs (NearWeapon, "Explorar", 		     0.10,   0.90);
	SetNodeProbs (NearWeapon, "Huir", 			       0.10,   0.90);
	SetNodeProbs (NearWeapon, "DetectarPeligro",   0.10,   0.90);

	// OW                                         Armado  Desarmado  
	SetNodeProbs (EnemyWeapon, "RecogerArma",     0.80,   0.20);
	SetNodeProbs (EnemyWeapon, "Atacar", 		      0.80,   0.20);
	SetNodeProbs (EnemyWeapon, "RecogerEnergia",  0.80,   0.20);
	SetNodeProbs (EnemyWeapon, "Explorar", 		    0.80,   0.20);
	SetNodeProbs (EnemyWeapon, "Huir", 			      0.95,   0.05);
	SetNodeProbs (EnemyWeapon, "DetectarPeligro", 0.80,   0.20);

	// HN                                       Si      No
	SetNodeProbs (HearNoise, "RecogerArma",     0.10,   0.90);
	SetNodeProbs (HearNoise, "Atacar", 		      0.90,   0.10);
	SetNodeProbs (HearNoise, "RecogerEnergia",  0.10,   0.90);
	SetNodeProbs (HearNoise, "Explorar", 		    0.10,   0.90);
	SetNodeProbs (HearNoise, "Huir", 			      0.95,   0.05);
	SetNodeProbs (HearNoise, "DetectarPeligro", 0.99,   0.01);

	// NE                                       Si      No
	SetNodeProbs (NearEnemy, "RecogerArma",     0.20,   0.80);
	SetNodeProbs (NearEnemy, "Atacar", 		      0.99,   0.01);
	SetNodeProbs (NearEnemy, "RecogerEnergia",  0.05,   0.95);
	SetNodeProbs (NearEnemy, "Explorar", 		    0.10,   0.90);
	SetNodeProbs (NearEnemy, "Huir", 			      0.90,   0.10);
	SetNodeProbs (NearEnemy, "DetectarPeligro", 0.10,   0.90);
	CHKERR


	// COMPILE NET OBLIGATORIO
	CompileNet_bn (net);
	CHKERR


	// SACAR EL VALOR AL NODO StatePlusOne
	belief = GetNodeBelief ("StatePlusOne", "Atacar", net);
	CHKERR

	printf ("La probabilidad de que inicialmente el bot ataque es %g\%\n\n", belief*100);


	// DARLE EL VALOR "Si" A LA VARIABLE "NearEnemy"
  	EnterFinding ("NearEnemy", "Si", net);

	// SACAR EL VALOR AL NODO STATE+1 AL ATRIBUTO ATACAR
  	belief = GetNodeBelief ("StatePlusOne", "Atacar", net);
	CHKERR

	//printf ("Given an abnormal X-ray, \n\
    //     the probability of tuberculosis is %g\n\n", belief);
	printf ("Si hay un enemigo cerca, \n\
          la probabilidad de atacar en el siguiente instante es %g\%\n\n", belief*100);

	// DARLE EL VALOR "Bajo" A LA VARIABLE "Health"
  	EnterFinding ("Health", "Bajo", net);

	// SACAR EL VALOR AL NODO STATE+1 AL ATRIBUTO ATACAR
  	belief = GetNodeBelief ("StatePlusOne", "Atacar", net);
	CHKERR

	printf ("Pero si además tenemos la vida baja, \n\
          la probabilidad de atacar en el siguiente instante es %g\%\n\n", belief*100);

end:
	DeleteNet_bn (net);
	res = CloseNetica_bn (env, mesg);
	printf ("%s\n", mesg);
	printf ("Press <enter> key to quit ", mesg);
	getchar();
	return (res < 0) ? -1 : 0;

error:
	fprintf (stderr, "NeticaDemo: Error in %s\n", 
	         ErrorMessage_ns (GetError_ns (env, ERROR_ERR, NULL)));
	goto end;
}

