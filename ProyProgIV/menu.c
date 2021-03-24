/*
 * menu.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */
#include <stdio.h>
#include "menu.h"
#include "pregunta.h"
#include <stdlib.h>
#include "ficheroTexto.h"

#define NUM_C_STR 100 //Numero de caracteres maximo para char*

/**
 * Permite leer el input del usuario devolviendo el char introducido
 *
 * Usa scanf()
 *
 * @return char leido por consola
 */
char getCharInput() {
	fflush(stdin);
	char chr;
	scanf("%c", &chr);
	return chr;
}
/**
 * Permite leer el input del usuario devolviendo el entero introducido
 *
 * Usa scanf()
 *
 * @return int leido por consola
 */
int getIntInput() {
	fflush(stdin);
	int i;
	scanf("%i", &i);
	return i;
}
/**
 * Permite leer el input del usuario devolviendo el entero introducido
 *
 * @param numero de digitos maximo a leer
 * @return entero leido por consola
 */
int getLIntInput(int numDigs) {
	fflush(stdin);
	int n;
	char *str = malloc(sizeof(char) * (numDigs + 1));
	fgets(str, numDigs, stdin);
	sscanf(str, "%i", &n);
	return n;
}
/**
 * Permite leer el input del usuario devolviendo un puntero a los caracteres introducidos
 *
 * @param numero de caracteres maximo a leer
 * @return char* leido por consola
 */
char* getStringInput(int numChars) {
	fflush(stdin);
	char *str = malloc(sizeof(char) * (numChars + 1));
	fgets(str, numChars, stdin);
	sscanf(str, "%[^\n]", str); //Lee hasta que se encuentre un salto de linea
	return str;
}
/**
 * Inicia el menu principal
 * Imprimiendo todas sus opciones por consola y luego esperando a la respuesta del usuario
 * Segun la eleccion del usuario continuara la ejecucion del programa 
 */
void menuPrincipal() {

	//Define e imprime el menu
	char *titulo = "\nMenu Principal";
	char *ops[] = { "Gestion de preguntas y respuestas",
			"Jugar (No disponible)", "Salir" };
	char *msg = "\nIntroduce tu seleccion (1-3):\n";

	printf("%s", titulo);
	printOpciones(ops, 3);
	printf("%s", msg);

	//Recoge la eleccion del usuario
	int s = getIntInput();

	//Segun la eleccion del usuario cambia el procedimiento
	switch (s) {
	default: //Si el usuario introduce algo no valido
		return;
	case 1: //Si el usuario elige "1" se abre el menu de gestion
		menuGestion();
		break;
	case 2: //Si el usuario elige "2" se abre el modo de juego
		printf("Elegiste Jugar");
		break;
	case 3: //Si el usuario elige "3" se sale del programa
		return;
	}
}

/**
 * Inicia el menu de gestion
 * Imprimiendo todas sus opciones por consola y luego esperando a la respuesta del usuario
 * Segun la eleccion del usuario continuara la ejecucion del programa 
 */
void menuGestion() {

	//Define e imprime el menu
	char *titulo = "\nMenu Gestion de Preguntas";
	char *ops[] = { "Crear preguntas", "Borrar preguntas",
			"Modificar Preguntas", "Ver preguntas creadas",
			"Volcar fichero de texto a BD", "Volver" };
	char *msg = "\nIntroduce tu seleccion (1-6):\n";

	printf("%s", titulo);
	printOpciones(ops, 6);
	printf("%s", msg);

	//Recoge la eleccion del usuario
	int s = getIntInput();

	//Segun la eleccion del usuario cambia el procedimiento
	switch (s) {
	default: //Si el usuario introduce algo no valido
		return;
	case 1: //Si el usuario elige "1" se abre el menu de creacion de preguntas
		menuCrearPregunta();
		break;
	case 2: //Si el usuario elige "2" se abre el menu de borrado de preguntas
		menuBorrarPregunta();
		break;
	case 3: //Si el usuario elige "3" se abre el menu de modificaci�n de preguntas
		menuModPregunta();
		break;
	case 4: //Si el usuario elige "4" se visualizaran las preguntas
		verPreguntas();
		break;
	case 5: //Si el usuario elige "5" se volcaran los datos del fichero a la BD
		volcarFicheroABD();
		break;
	case 6: //Si el usuario elige "6" se retorna al menu principal
		menuPrincipal();
		break;
	}
}

/**
 * Inicia el menu de creacion de preguntas
 * Imprimiendo cada paso y esperando a la entrada del usuario tras cada paso
 * Recoge la informacion introducida por el usuario y crea una pregunta que luego se almacena
 */
void menuCrearPregunta() {

	char *pasos[] = { "Introduce codigo de categoria:",
			"Introduce la pregunta:", "Introduce respuesta 1:",
			"Introduce respuesta 2:", "Introduce respuesta 3:",
			"Introduce respuesta 4:",
			"Introduce codigo de respuesta correcta (0-3):" };

	char *lista[N_LISTA_PREG];

	for (int i = 0; i < N_LISTA_PREG; i++) {
		fflush(stdout);
		printf("\n%s\n", pasos[i]);
		//char s = getCharInput();
		lista[i] = getStringInput(NUM_C_STR); //FIXME
	}

	Pregunta p = crearPregunta(lista);
	//TODO guardar pregunta
	printPregunta(&p);

}
/**
 * Incia el menu de borrado de preguntas
 * Pide al usuario el codigo de la pregunta a borrar y la elimina
 */
void menuBorrarPregunta() {

	//Introduce codigo
	char *pasos =  "Introduce codigo de la pregunta:";
	printf("\n%s\n", pasos);
	char *codigo;
	codigo = getStringInput(NUM_C_STR);
	//Ocurre la busqueda
	//for (int i = 0; i < ListaDePreguntas; ++i) {
	//	if (ListaDePreguntas[1]=codigo) {
			//free(ListaDePreguntas[i]);
	//		}
	//}
	free(codigo);
	free(pasos);
	Pregunta p = buscarPreguntaEnFichero("prueba");

	//Prov: Imprimir la pregunta para confirmar

}
/**
 * Incia el menu de modificacion de preguntas
 * Pide al usuario el codigo de la pregunta a modificar
 * Tras buscarla va presentando al usaurio la informacion de la pregunta y como debe modificarla
 */
void menuModPregunta() {
	//Ocurre la busqueda
	char *pasos =  "Introduce codigo de la pregunta:";
	printf("%s", pasos);
	char *codigo;
	char *codigo1;
	codigo1 = getStringInput(NUM_C_STR);
	Pregunta p = buscarPreguntaEnFichero(codigo1);

	char *ops[] = { "Cambiar codigo", "Cambiar pregunta",
				"Cambiar respuesta 1", "Cambiar respuesta 2",
				"Cambiar respuesta 3", "Cambiar respuesta 4",
				"Cambiar respuesta correcta"};


	printOpciones(ops, 7);
	char *msg = "\nIntroduce tu seleccion (1-7):\n";
	printf("\n%s", msg);
	int s = getIntInput();

	//Pedir al usuario la info para modificar (seguir el doc)
		//Segun la eleccion del usuario cambia el procedimiento
		switch (s) {
		default: //Si el usuario introduce algo no valido
			return;
		case 1:
			free(p.cat);
			codigo = getStringInput(NUM_C_STR);
			p.cat=codigo;
			break;
		case 2:
			free(p.preg);
			codigo = getStringInput(NUM_C_STR);
			p.preg=codigo;


			break;
		case 3:
			free(p.ops[0]);
			codigo = getStringInput(NUM_C_STR);
			p.ops[0]=codigo;
			break;
		case 4:
			free(p.ops[1]);
			codigo = getStringInput(NUM_C_STR);
			p.ops[1]=codigo;
			break;
		case 5: //cambiara la respuesta 3
			free(p.ops[2]);
			codigo = getStringInput(NUM_C_STR);
			p.ops[2]=codigo;
			break;
		case 6: //cambiara la respuesta 4
			free(p.ops[3]);
			codigo = getStringInput(NUM_C_STR);
			p.ops[3]=codigo;
			break;
		case 7: //cambiara la respuesta correcta
			free(p.res);
			codigo = getStringInput(NUM_C_STR);
			p.res=codigo;
			break;
		}





	//Prov: Imprimir la pregunta para confirmar
		printPregunta(&p);

}
/**
 * Imprime todas las preguntas almacenadas por consola
 */
void verPreguntas() {
	//Imprime TODAS las preguntas
	//TODO
}
/**
 * Vuelca la informacion del fichero de texto a la base de datos
 */
void volcarFicheroABD() {
	//TODO
}
/**
 * Funcion util para lo menus
 * Formatea e imprime las opciones
 *
 * @param ops array de char* que son las opciones a mostrar
 * @param size tama�o de la array de char*
 */
void printOpciones(char *ops[], int size) {
	for (int i = 0; i < size; i++) {
		printf("\n\t%i.%s", i + 1, ops[i]);
	}
}

