/*
 * baseDatos.h
 *
 *  Created on: 2 may. 2021
 *      Author: danel
 */

#ifndef BASEDATOS_H_
#define BASEDATOS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "pregunta.h"

int almacenarCategorias(Categoria *categorias, int numCategorias);
int almacenarCategoria(Categoria *cat);
int almacenarPregunta(Pregunta *preg);
int abrirBaseDatos();
int cerrarBaseDatos();
int getPreguntasCategoria(char *cat, Pregunta **pArray, int *numPreguntas);

#ifdef __cplusplus
}
#endif

#endif /* BASEDATOS_H_ */
