/*
 * Usuario.cpp
 *
 *  Created on: 9 may. 2021
 *      Author: danel
 */

#include "Usuario.h"
#include <string.h>

Usuario::Usuario(char *nombre, char *contrasena):Jugador(nombre, VIDA_BASE){
	this->contrasena = strdup(contrasena);
}

char* Usuario::getContrasena() const {
	return contrasena;
}

Usuario::Usuario(const Usuario &other):Jugador(other){
	this->contrasena = strdup(other.contrasena);
}

Usuario::~Usuario() {
	delete[] contrasena;
}

void Usuario::danyar(){
	vida-=DANYO;
}

const int Usuario::getVidaBase(){
	return VIDA_BASE;
}

void Usuario::revitalizar(){
	vida+=INC_RECU;
}

