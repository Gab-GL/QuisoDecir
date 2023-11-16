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
	char linea[4000];
	char palabraDetectada[TAMTOKEN];
	int i;
	int indicePD;
	iNumElementos = 0;
	// abrir el achivo
	if (DEPURAR == 1)
		printf("%s", szNombre);

	fopen_s(&fpDicc, szNombre, "r");
	if (fpDicc != NULL)
	{
		
		if (DEPURAR == 1)
			printf("\nSi lo pude abrir");

		indicePD = 0;
		while (!feof(fpDicc))
		{
			fgets(linea, sizeof(linea), fpDicc);
			if (DEPURAR == 1)
				printf("\n%s\n", linea);
			
			for (i = 0; i < strlen(linea); i++)
			{

				// Detectar una palabra
				if ((linea[i] == ' ' || linea[i] == '\n') && linea[i + 1] != ' ')
				{
					palabraDetectada[indicePD] = '\0';
					strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabraDetectada);
					iEstadisticas[iNumElementos] = 1;
					if (DEPURAR == 1)
						//printf("\np: %s", palabraDetectada);
					indicePD = 0;
					iNumElementos++;
					// eliminar los espacios en blanco
					// tabuladores y saltos de linea consecutivos				
			    }
				else
				{
		
					if ((linea[i] >= 65 && linea[i] <= 90) || (linea[i] >= 97 && linea[i] <= 122))
					{
						linea[i] = towlower(linea[i]);
						palabraDetectada[indicePD] = linea[i];
						indicePD++;
					}
				}
			}

		}


			if (DEPURAR == 1)
				//// PALABRAS EN EL DOCUMENTO printf("\nNumPalabras: %i\n", iNumElementos);
				
			//CONTAR CUANTAS VECES SE REPTIE LA MISMA PALABRA Y ELMINAR LAS REPETIDAS DE LA LISTA
			for (int i = 0; i < iNumElementos; i++) {
				for (int j = i + 1; j < iNumElementos; j++) {
					if (strcmp(szPalabras[i], szPalabras[j]) == 0) {
                        iEstadisticas[i] = iEstadisticas[i] + 1;
						// Eliminar duplicados moviendo los elementos restantes hacia arriba
						for (int k = j; k < iNumElementos - 1; k++) {
							strcpy_s(szPalabras[k], szPalabras[k + 1]);
							
						}
						iNumElementos--;
						j--;
					}
                    
				}
                 
			}

			printf("\nNumPalabras: %i\n", iNumElementos);
			// ORDENAR LAS PALABRAS POR ORDEN ALFABETICO
			for (int i = 0; i < iNumElementos - 1; i++) {
				for (int j = 0; j < iNumElementos - i ; j++) {
					if (strcmp(szPalabras[j], szPalabras[j + 1]) > 0) {
						// Intercambiar números de cuenta y calificaciones
						char auxPalabra[TAMTOKEN];
						int auxEstadistica;


						strcpy_s(auxPalabra, szPalabras[j]);
						auxEstadistica = iEstadisticas[j];


						strcpy_s(szPalabras[j], szPalabras[j + 1]);
						auxEstadistica = iEstadisticas[j + 1];


						strcpy_s(szPalabras[j + 1], auxPalabra);
						iEstadisticas[j + 1] = auxEstadistica;

					}
				}



			}
		fclose(fpDicc);
	}
	else
	{
		if (DEPURAR == 1)
			printf("\nNo lo pude abrir");
	}
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
	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
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
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su código
	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}
