/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Ponga su nombre y numero de cuenta aqui.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#define DEPURAR 1




//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario			(char *szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int &iNumElementos)
{

	FILE* fpDicc;
	char linea;
	int indicePD = 0;
	char palabraDetectada[TAMTOKEN];
	fopen_s(&fpDicc, szNombre, "r");
	iNumElementos = 0;
	int i = 0;


	if (fpDicc != NULL) {

		while ((linea = fgetc(fpDicc)) != EOF) {
			if ((linea == ' ' || linea == '\n' || linea == '\t' || linea == '\r' || linea == '.' || linea == ';' || linea == '(' || linea == ')' || linea == ',' || linea == '\0')) {

				if (indicePD != 0) {
					palabraDetectada[indicePD] = '\0';
					strcpy_s(szPalabras[iNumElementos], sizeof(palabraDetectada), palabraDetectada);
					iEstadisticas[iNumElementos] = 1;
				/*	printf("\np: %s", palabraDetectada);*/
					indicePD = 0;
					iNumElementos++;
				}


			}
			else  {
				if ((linea >= 65 && linea <= 90)) {
				    linea= towlower(linea);
										}
				palabraDetectada[indicePD] = linea;
				indicePD++;
			}


		}
	}
	else {
		printf("Error al abrir el archivo.\n");

		 /*o cualquier otro valor de error*/
	}
	

	 //Eliminar duplicados y ordenar las palabras
	for ( i = 0; i < iNumElementos; i++) {
		for (int j = i + 1; j < iNumElementos; j++) {
			if (strcmp(szPalabras[i], szPalabras[j]) == 0) {
				/*aumentar las estadisticas de las palabras que se repiten*/
				iEstadisticas[i]++;
			/*	 Eliminar duplicados moviendo los elementos restantes hacia arriba*/
				for (int k = j; k < iNumElementos - 1; k++) {
					strcpy_s(szPalabras[k], szPalabras[k + 1]);

				}
				iNumElementos--;
				j--;
			}
			
		}
	}




	for ( i = 0; i < iNumElementos - 1; i++) {
		for (int j = 0; j < iNumElementos - i - 1; j++) {
			if (strcmp(szPalabras[j], szPalabras[j + 1]) > 0) {

				char auxPalabras[TAMTOKEN];
				int auxEstadistica;


				strcpy_s(auxPalabras, szPalabras[j]);
				auxEstadistica = iEstadisticas[j];


				strcpy_s(szPalabras[j], szPalabras[j + 1]);
				iEstadisticas[j] = iEstadisticas[j + 1];


				strcpy_s(szPalabras[j + 1], auxPalabras);
				iEstadisticas[j + 1] = auxEstadistica;

			}
		}
	}
	
//printf("\nNumPalabras: %i\n", iNumElementos);
	//FILE* fpDicc;
	//char linea;
	//int indicePD = 0;
	//char palabraDetectada[TAMTOKEN];
	//fopen_s(&fpDicc, szNombre, "r");
	//iNumElementos = 0;
	//int i = 0;


	//if (fpDicc != NULL) {

	//	while ((linea = fgetc(fpDicc)) != EOF) {
	//		if ((linea == ' ' || linea == '\n' || linea == '\t' || linea == '\r' || linea == '.' || linea == ';' || linea == '(' || linea == ')' || linea == ',' || linea == '\0')) {

	//			if (indicePD != 0) {
	//				palabraDetectada[indicePD] = '\0';
	//				strcpy_s(szPalabras[iNumElementos], sizeof(palabraDetectada), palabraDetectada);
	//				iEstadisticas[iNumElementos] = 1;
	//				/*	printf("\np: %s", palabraDetectada);*/
	//				indicePD = 0;
	//				iNumElementos++;
	//			}


	//		}
	//		else {
	//			if ((linea >= 65 && linea <= 90) || linea == 'Á' || linea == 'É' || linea == 'Í' || linea == 'Ó' || linea == 'Ú') {
	//				linea = towlower(linea);
	//			}
	//			palabraDetectada[indicePD] = linea;
	//			indicePD++;
	//		}


	//	}
	//}
	//else {
	//	printf("Error al abrir el archivo.\n");

	//	/*o cualquier otro valor de error*/
	//}


	////Eliminar duplicados y ordenar las palabras
	//for (i = 0; i < iNumElementos; i++) {
	//	for (int j = i + 1; j < iNumElementos; j++) {
	//		if (strcmp(szPalabras[i], szPalabras[j]) == 0) {
	//			/*aumentar las estadisticas de las palabras que se repiten*/
	//			iEstadisticas[i]++;
	//			/*	 Eliminar duplicados moviendo los elementos restantes hacia arriba*/
	//			for (int k = j; k < iNumElementos - 1; k++) {
	//				strcpy_s(szPalabras[k], szPalabras[k + 1]);

	//			}
	//			iNumElementos--;
	//			j--;
	//		}

	//	}
	//}




	//for (i = 0; i < iNumElementos - 1; i++) {
	//	for (int j = 0; j < iNumElementos - i - 1; j++) {
	//		if (strcmp(szPalabras[j], szPalabras[j + 1]) > 0) {

	//			char auxPalabras[TAMTOKEN];
	//			int auxEstadistica;


	//			strcpy_s(auxPalabras, szPalabras[j]);
	//			auxEstadistica = iEstadisticas[j];


	//			strcpy_s(szPalabras[j], szPalabras[j + 1]);
	//			iEstadisticas[j] = iEstadisticas[j + 1];


	//			strcpy_s(szPalabras[j + 1], auxPalabras);
	//			iEstadisticas[j + 1] = auxEstadistica;

	//		}
	//	}
	//}

	

}




/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su código
	strcpy_s(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char* szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int& iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su código
	//strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	//iNumSugeridas = 0;							//Una sola palabra sugerida
	//char auxclonda[TAMTOKEN];
	//char auxcarater;
	//int longi;
	//int a = 0;
	//longi = strlen(szPalabraLeida);
	iNumSugeridas = 0;
	char abcd[] = "abcdefghijklmnñopqrstuvwxyzáéíóú";
	char auxclonada[TAMTOKEN];
	int e;


	//pasar el abc por el la palabra
	strcpy_s(auxclonada, szPalabraLeida);
	for (int i = 0; i < strlen(szPalabraLeida); i++) {
		for (int k = 0; k < strlen(abcd); k++) {
			auxclonada[i] = abcd[k];
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], auxclonada);
			strcpy_s(auxclonada, szPalabraLeida);


		}

	}
	// aumentar el tamaño de la palabra para meter carcteres en medio
	for ( e = 1; e < strlen(szPalabraLeida) + 1; e++) {
		auxclonada[e] = szPalabraLeida[e - 1];

	}	auxclonada[e] = '\0';
	

	for ( int i = 0; i < strlen(szPalabraLeida) + 1; i++) {

		for (int j = 0; j < 32; j++) {
			auxclonada[i] = abcd[j];
			
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], auxclonada);
		}
		auxclonada[i] = szPalabraLeida[i];
	}

	/*quitar caracteres*/
	strcpy_s(auxclonada, szPalabraLeida);

	char l = auxclonada[strlen(szPalabraLeida) - 1];
	auxclonada[strlen(szPalabraLeida) + 1] = l;
	auxclonada[strlen(szPalabraLeida) - 1] = '\0';
	strcpy_s(szPalabrasSugeridas[iNumSugeridas++], auxclonada);
	char aux;
	char temp;
	for (int quitar = strlen(auxclonada) - 1; quitar >= 0; quitar--) {
		temp = l;
		l = auxclonada[quitar];
		auxclonada[quitar] = temp;
		auxclonada[strlen(auxclonada) + 2] = l;
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], auxclonada);
	}
	strcpy_s(auxclonada, szPalabraLeida);

	// cambiar el orden de las palabras
	for (int i = 0; i < strlen(szPalabraLeida) - 1; i++) {
		auxclonada[i] = szPalabraLeida[i + 1];
		auxclonada[i + 1] = szPalabraLeida[i];

		/*Numero de elementos en la lista a la Lista de palabras clonadas*/
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], auxclonada);
		/*Palabra a clonar palabra al auxiliar*/
		strcpy_s(auxclonada, szPalabraLeida);
	}
	strcpy_s(szPalabrasSugeridas[iNumSugeridas++], szPalabraLeida);
}