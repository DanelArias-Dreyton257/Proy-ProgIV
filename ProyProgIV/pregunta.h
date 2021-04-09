/*
 * pregunta.h
 *
 *  Created on: 15 mar. 2021
 *      Author: jon ander y danel
 */

#ifndef PREGUNTA_H_
#define PREGUNTA_H_

#define N_LISTA_PREG 7
#define N_OPCS 4

typedef struct {
	char *cat;
	char *preg;
	char **ops;
	int res;

} Pregunta;

void printPregunta(Pregunta *p);
void printPreguntaJuego(Pregunta *p);
Pregunta crearPregunta(char *list[]);
void freeRespuestas(Pregunta *p);
char* generarCodigo(Pregunta p);
Pregunta generarPreguntaPrueba();

int comprobarCategoria(char* cat);
int comprobarPregunta(char* preg);
int comprobarOpcion(char* opc);
int comprobarCodOpcion(int codRes);
int comprobarPreguntaEntera(Pregunta *p);

int esRespuestaCorrecta(Pregunta *p, int res);

#endif /* PREGUNTA_H_ */
