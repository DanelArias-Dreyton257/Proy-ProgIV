/*
 * menu.c
 *
 *  Created on: 8 mar. 2021
 *      Author: danel and jon ander
 */
#include "menu.h"
#include "ficheroPreguntas.h"
#include "pregunta.h"
#include <stdlib.h>
#include <stdio.h>

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
	char *titulo = "Menu Principal";
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
		limpiarConsola();
		menuGestion();
		break;
	case 2: //Si el usuario elige "2" se abre el modo de juego
		limpiarConsola();
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
	char *titulo = "Menu Gestion de Preguntas";
	char *ops[] = { "Crear preguntas", "Borrar preguntas",
			"Modificar Preguntas", "Ver preguntas creadas",
			"Volcar fichero de texto a BD (No disponible)", "Volver" };
	char *msg = "\nIntroduce tu seleccion (1-6):\n";

	printf("%s", titulo);
	printOpciones(ops, 6);
	printf("%s", msg);
	fflush(stdout);
	//Recoge la eleccion del usuario
	int s = getIntInput();

	//Segun la eleccion del usuario cambia el procedimiento
	switch (s) {
	default: //Si el usuario introduce algo no valido
		return;
	case 1: //Si el usuario elige "1" se abre el menu de creacion de preguntas
		limpiarConsola();
		menuCrearPregunta();
		limpiarConsola();
		menuGestion();
		break;
	case 2: //Si el usuario elige "2" se abre el menu de borrado de preguntas
		limpiarConsola();
		menuBorrarPregunta();
		limpiarConsola();
		menuGestion();
		break;
	case 3: //Si el usuario elige "3" se abre el menu de modificaci�n de preguntas
		limpiarConsola();
		menuModPregunta();
		limpiarConsola();
		menuGestion();
		break;
	case 4: //Si el usuario elige "4" se visualizaran las preguntas
		limpiarConsola();
		verPreguntas();
		limpiarConsola();
		menuGestion();
		break;
	case 5: //Si el usuario elige "5" se volcaran los datos del fichero a la BD
		limpiarConsola();
		volcarFicheroABD();
		limpiarConsola();
		menuGestion();
		break;
	case 6: //Si el usuario elige "6" se retorna al menu principal
		limpiarConsola();
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
			"Introduce codigo de respuesta correcta (1-4):" };

	char *lista[N_LISTA_PREG];

	for (int i = 0; i < N_LISTA_PREG; i++) {
		printf("\n%s\n", pasos[i]);
		fflush(stdout);
		lista[i] = getStringInput(NUM_C_STR);
	}
	(*(lista[N_LISTA_PREG - 1]))--; //reduce en 1 el valor de la respuesta correcta

	limpiarConsola();

	//Creacion de la pregunta
	Pregunta p = crearPregunta(lista);

	if (comprobarPreguntaEntera(&p) > 0) {

		printPregunta(&p);
		//Se le preguntara al usuario si quiere crear la pregunta
		char *mensajeAdv = "�Esta seguro de crear esta pregunta? (Y/n)";
		printf("\n%s\n", mensajeAdv);
		fflush(stdout);
		char respuesta = getCharInput();
		//El usuario dara una respuesta, si o no, estando si por defecto

		//Si se selecciona no, no se creara la pregunta
		if (respuesta == 'n') {
			printf("Pregunta no creada");
			fflush(stdout);
		}

		//Si se selecciona Y o otra tecla se inserta la pregunta
		else {
			insertarPregunta(p);
		}
	} else {
		printf(
				"La pregunta no cumple con los requisitos.\n Por favor pruebe otra vez");
		//fflush(stdout);
	}
}
/**
 * Incia el menu de borrado de preguntas
 * Pide al usuario el codigo de la pregunta a borrar y la elimina
 */
void menuBorrarPregunta() {

	//Introduce codigo
	char *mensaje = "Introduce codigo de la pregunta:";
	printf("\n%s\n", mensaje);
	fflush(stdout);
	char *codigo = getStringInput(NUM_C_STR);

	//Imprime para asegurar
	Pregunta *p = buscarPreguntaEnFichero(codigo);
	if (p != NULL) {
		printPregunta(p);

		//Se le preguntara al usuario si quiere borrar la pregunta
		char *mensajeAdv = "�Esta seguro de borrar esta pregunta? (Y/n)";
		printf("\n%s\n", mensajeAdv);
		fflush(stdout);
		//El usuario dara una respuesta, si o no, estando si por defecto
		char respuesta = getCharInput();

		//Si se selecciona no, no se borrara la pregunta
		if (respuesta == 'n') {
			printf("Pregunta no borrada");

			fflush(stdout);
		}
		//Si se selecciona Y o otra tecla se borrara la pregunta
		else {
			borrarPregunta(codigo);
		}

	} else {
		printf("Pregunta no encontrada");
		fflush(stdout);
	}
	//Libera el codigo
	free(codigo);
}
/**
 * Incia el menu de modificacion de preguntas
 * Pide al usuario el codigo de la pregunta a modificar
 * Tras buscarla va presentando al usaurio la informacion de la pregunta y como debe modificarla
 */
void menuModPregunta() {
	//Ocurre la busqueda
	printf("Introduce codigo de la pregunta:\n");
	fflush(stdout);
	char *codigo = getStringInput(NUM_C_STR);

	Pregunta *p = buscarPreguntaEnFichero(codigo);

	if (p == NULL) {
		printf("Pregunta no encontrada");
		fflush(stdout);
		//break;
	} else {

		printPregunta(p);
		printf("\n");

		free(codigo);

		char *ops[] = { "Cambiar codigo", "Cambiar pregunta",
				"Cambiar respuesta 1", "Cambiar respuesta 2",
				"Cambiar respuesta 3", "Cambiar respuesta 4",
				"Cambiar codigo respuesta correcta (0-3)" };
		char *mensajeAdv = "�Quiere modificar esta pregunta? Y/n";
		fflush(stdout);

		printf("\n%s\n", mensajeAdv);
		fflush(stdout);

		//El usuario dara una respuesta, si o no, estando si por defecto
		char respuesta = getCharInput();
		if (respuesta == 'n') {
			printf("La pregunta no se modificara");
			fflush(stdout);
		} else {

			printOpciones(ops, 7);
			printf("\nIntroduce tu seleccion (1-7):\n");
			fflush(stdout);
			int s = getIntInput();

			//Pedir al usuario la info para modificar (seguir el doc)
			//Segun la eleccion del usuario cambia el procedimiento
			switch (s) {
			default: //Si el usuario introduce algo no valido
				return;
			case 1: //cambiara la categoria
				printf("Intoduce la nueva categoria:\n");
				fflush(stdout);
				char *str1 = getStringInput(NUM_C_STR);
				if (comprobarCategoria(str1) > 0) {
					p->cat = str1;
				} else {
					printf(
							"La categoria introducida no es valida, no se hara el cambio.");
				}
				break;
			case 2: //cambiara la pregunta
				printf("Intoduce la nueva pregunta:\n");
				fflush(stdout);
				char *str2 = getStringInput(NUM_C_STR);
				if (comprobarPregunta(str2) > 0) {
					p->preg = str2;
				} else {
					printf(
							"La pregunta introducida no es valida, no se hara el cambio.");
				}
				break;
			case 3: //cambiara la respuesta 1
				printf("Intoduce la nueva respuesta 1:\n");
				fflush(stdout);
				char *str3 = getStringInput(NUM_C_STR);
				if (comprobarOpcion(str3) > 0) {
					p->ops[0] = str3;
				} else {
					printf(
							"La opcion introducida no es valida, no se hara el cambio.");
				}
				break;
			case 4: //cambiara la respuesta 2
				printf("Intoduce la nueva respuesta 2:\n");
				fflush(stdout);
				char *str4 = getStringInput(NUM_C_STR);
				if (comprobarOpcion(str4) > 0) {
					p->ops[1] = str4;
				} else {
					printf(
							"La opcion introducida no es valida, no se hara el cambio.");
				}
				break;
			case 5: //cambiara la respuesta 3
				printf("Intoduce la nueva respuesta 3:\n");
				fflush(stdout);
				char *str5 = getStringInput(NUM_C_STR);
				if (comprobarOpcion(str5) > 0) {
					p->ops[2] = str5;
				} else {
					printf(
							"La opcion introducida no es valida, no se hara el cambio.");
				}
				break;
			case 6: //cambiara la respuesta 4
				printf("Intoduce la nueva respuesta 4:\n");
				fflush(stdout);
				char *str6 = getStringInput(NUM_C_STR);
				if (comprobarOpcion(str6) > 0) {
					p->ops[3] = str6;
				} else {
					printf(
							"La opcion introducida no es valida, no se hara el cambio.");
				}
				break;
			case 7: //cambiara la respuesta correcta
				printf("Intoduce la nueva respuesta correcta (1-4):\n");
				fflush(stdout);
				int input = getIntInput() - 1;
				if (comprobarCodOpcion(input) > 0) {
					p->res = input;
				} else {
					printf(
							"El codigo de opcion introducido no es valido, no se hara el cambio.");
				}
				break;
			}

			//No hace falta borrar ni insertar ni nada pues se cambia automaticamente
		}
	}
}

/**
 * Imprime todas las preguntas almacenadas por consola
 */
void verPreguntas() {
	//Imprime TODAS las preguntas
	printTodasPreguntas();
	pausarConsola();
}
/**
 * Vuelca la informacion del fichero de texto a la base de datos
 */
void volcarFicheroABD() {
	printf("No disponible de momento");
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
	fflush(stdout);
}
/**
 * Limpia de texto la consola
 */
void limpiarConsola() {
	system("cls");
}
/**
 * Pausa la consola hasta el input del usuario
 */
void pausarConsola() {
	system("pause");
}

