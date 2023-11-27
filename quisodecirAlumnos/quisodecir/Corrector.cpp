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

void	Diccionario			(char *szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int &iNumElementos)
{

	FILE* fpDicc;
	char linea;
	int indicePD = 0;
	char palabraDetectada[TAMTOKEN];
	fopen_s(&fpDicc, szNombre, "r");
	iNumElementos = 0;

	if (fpDicc != NULL) {

		while ((linea = fgetc(fpDicc)) != EOF) {
			if ((linea == ' ' || linea == '\n' || linea == '\t' || linea == '\r' || linea == '.' || linea == ';' || linea == '(' || linea == ')' || linea == ',' || linea == '\0')) {

				int f = 1;
				if (indicePD != 0) {
					palabraDetectada[indicePD] = '\0';
					for (int pd = 0; pd < iNumElementos; pd++) {
						if (strcmp(palabraDetectada, szPalabras[pd]) == 0) {
							f = 0;
							indicePD = 0;
							iEstadisticas[pd]++;
							break;

						}
					}
					if (f == 1) {
						strcpy_s(szPalabras[iNumElementos], sizeof(palabraDetectada), palabraDetectada);
						iEstadisticas[iNumElementos] = 1;
						
						indicePD = 0;
						iNumElementos++;
					}

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
	

	for ( int k = 0; k < iNumElementos - 1; k++) {
		for (int l = 0; l < iNumElementos - k - 1; l++) {
			if (strcmp(szPalabras[l], szPalabras[l + 1]) > 0) {

				char auxPalabras[TAMTOKEN];
				int auxEstadistica;
				strcpy_s(auxPalabras, szPalabras[l]);
				auxEstadistica = iEstadisticas[l];
				strcpy_s(szPalabras[l], szPalabras[l + 1]);
				iEstadisticas[l] = iEstadisticas[l + 1];
				strcpy_s(szPalabras[l + 1], auxPalabras);
				iEstadisticas[l + 1] = auxEstadistica;

			}
		}
	}
	


	

}


void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int&	iNumLista)							//Numero de elementos en la szListaFinal
{
	iNumLista = 0;
	for (int i = 0; i < iNumSugeridas; i++) {
		for (int j = 0; j < iNumElementos; j++) {
			int f  = 1;

			for (int d = 0; d < iNumElementos; d++) {
				if (strcmp(szListaFinal[d], szPalabrasSugeridas[i]) == 0)
				{
					f = 0;
					break;
				}
			}
			/*Comparar de Lista del diccionario con la Lista de palabras clonadas */
			if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0 && f == 1) {
				
				strcpy_s(szListaFinal[iNumLista], szPalabrasSugeridas[i]);
				iPeso[iNumLista++] = iEstadisticas[j];
			}
		}
	}

	for ( int i = 0; i < iNumLista - 1; i++) {
		for (int j = 0; j < iNumLista - i - 1; j++) {
			if (iPeso[j] < iPeso[j + 1]) {

				char auxPalabras[TAMTOKEN];
				int auxEstadistica;
				strcpy_s(auxPalabras, szListaFinal[j]);
				auxEstadistica = iPeso[j];
				strcpy_s(szListaFinal[j], szListaFinal[j + 1]);
				iPeso[j] = iPeso[j + 1];
				strcpy_s(szListaFinal[j + 1], auxPalabras);
				iPeso[j + 1] = auxEstadistica;

			}
		}
	}

}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
******************************************************************************************************************/
void	ClonaPalabras(
	char* szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int& iNumSugeridas)						//Numero de elementos en la lista
{
	iNumSugeridas = 0;
	char abcd[] = "abcdefghijklmnñopqrstuvwxyzáéíóú";
	char auxclonada[TAMTOKEN];
	
	
	strcpy_s(szPalabrasSugeridas[iNumSugeridas++], szPalabraLeida);
	/*pasar el abc por el palabra*/
	strcpy_s(auxclonada, szPalabraLeida);
	for (int i = 0; i < strlen(szPalabraLeida); i++) {
		for (int k = 0; k < strlen(abcd); k++) {
			auxclonada[i] = abcd[k];
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], auxclonada);
			strcpy_s(auxclonada, szPalabraLeida);


		}

	}
	int e;
	/* aumentar el tamaño de la palabra para meter carcteres en medio*/
	for ( e = 1; e < strlen(szPalabraLeida) + 1; e++) {
		auxclonada[e] = szPalabraLeida[e - 1];
	}	auxclonada[e] = '\0';
	for ( int t = 0; t < strlen(szPalabraLeida) + 1; t++) {

		for (int j = 0; j < 32; j++) {
			auxclonada[t] = abcd[j];
			
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], auxclonada);
		}
		auxclonada[t] = szPalabraLeida[t];
	}

	if (strlen(szPalabraLeida) != 1) {
		/*quitar caracteres*/
		strcpy_s(auxclonada, szPalabraLeida);
		char l = auxclonada[strlen(szPalabraLeida) - 1];
		auxclonada[strlen(szPalabraLeida) + 1] = l;
		auxclonada[strlen(szPalabraLeida) - 1] = '\0';

		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], auxclonada);
		char temp;
		for (int quitar = strlen(auxclonada) - 1; quitar >= 0; quitar--) {
			temp = l;
			l = auxclonada[quitar];
			auxclonada[quitar] = temp;
			auxclonada[strlen(auxclonada) + 2] = l;
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], auxclonada);
		}
	}

	strcpy_s(auxclonada, szPalabraLeida);
	/* cambiar el orden de las palabras*/
	for (int orden = 0; orden < strlen(szPalabraLeida) - 1; orden++) {
		auxclonada[orden] = szPalabraLeida[orden + 1];
		auxclonada[orden + 1] = szPalabraLeida[orden];
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], auxclonada);
		strcpy_s(auxclonada, szPalabraLeida);
	}
	

	
	for (int v = 0; v < iNumSugeridas - 1 ; v++) {

		for (int b = v + 1; b < iNumSugeridas; b++) {

			if (strcmp(szPalabrasSugeridas[v], szPalabrasSugeridas[b]) > 0) {
				strcpy_s(auxclonada, szPalabrasSugeridas[v]);
				strcpy_s(szPalabrasSugeridas[v], szPalabrasSugeridas[b]);
				strcpy_s(szPalabrasSugeridas[b], auxclonada);
			}
		}
	}
}

