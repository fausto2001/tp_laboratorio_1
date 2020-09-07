#include "Funciones.h"
#include "FuncionesMatematicas.h"
#include <stdio.h>

/*
* La funcion menu presenta un menu de opciones programado con un switch en el cual
* el usuario puede ingresar los numeros que desee con las opciones 1 y 2, calcular
* las operaciones con la opcion 3, e informar los resultados a traves de la opcion
* 4. Esta funcion contempla errores tales como informar los resultados previo a la
* realizacion de las operaciones.
*/

void menu()
{
	int operacionesRealizadas = 0;
	int opcion = 0;
	int primerNumero = 0;
	int segundoNumero = 0;
	int suma = 0;
	int resta = 0;
	int multiplicacion = 0;
	float division = 0;
	int primerFactorial = 0;
	int segundoFactorial = 0;
	int opcionCase4 = 0;
	int opcionCase3 = 0;
	while (opcion != 5)
	{
		system("clear");
		printf("Bienvenido/a al programa!");
		printf("\n 1. Ingresar 1er operando: %d", primerNumero);
		printf("\n 2. Ingresar 2do operando: %d", segundoNumero);
		printf("\n 3. Calcular las operaciones.");
		printf("\n 4. Informar resultados.");
		printf("\n 5. Salir.");
		printf("\n Elija una opcion: ");
		scanf("%d", &opcion);
		switch (opcion)
		{
			case 1:
				system("clear");
				printf("Escriba el primer operando: ");
				scanf("%d", &primerNumero);
				operacionesRealizadas = 0;
				break;
			case 2:
				system("clear");
				printf("Escriba el segundo operando: ");
				scanf("%d", &segundoNumero);
				operacionesRealizadas = 0;
				break;
			case 3:
				opcionCase3 = 0;
				suma = calcularSuma(primerNumero, segundoNumero);
				resta = calcularResta(primerNumero, segundoNumero);
				division = calcularDivision((float)primerNumero, (float)segundoNumero);
				multiplicacion = calcularMultiplicacion(primerNumero, segundoNumero);
				primerFactorial = calcularFactorial(primerNumero);
				segundoFactorial = calcularFactorial(segundoNumero);
				operacionesRealizadas = 1;
				printf("Las operaciones fueron realizadas con exito!");
				while (opcionCase3 != 1)
				{
					printf("\nPresione 1 para continuar: ");
					scanf("%d", &opcionCase3);
				}
				break;
			case 4:
				opcionCase4 = 0;
				if(!operacionesRealizadas)
				{
					system("clear");
					printf("\nLas operaciones  de los operandos actuales aun no fueron realizadas. Por favor, realize las operaciones de los operandos actuales para continuar");
					while (opcionCase4 != 1)
					{
						printf("\nPresione 1 para continuar: ");
						scanf("%d", &opcionCase4);
					}
					break;
				}
				else
				{
					resultados(suma, resta, division, multiplicacion, primerFactorial, segundoFactorial, primerNumero, segundoNumero);
				}
				break;
			case 5:
				printf("Gracias por usar el programa!");
				break;
			default:
				system("clear");
				printf("Eligió una opcion equivocada. Por favor, elija una opcion entre 1 y 5 para continuar.");
				break;
		}
	}
}

/*La funcion resultados informa los resultados de las operaciones, y contempla casos de
 *errores tales como los de la division por 0, o factoriales negativos.
 */

void resultados(int suma, int resta, float division, int multiplicacion, int primerFactorial, int segundoFactorial, int primerNumero, int segundoNumero)
{
	int opcion = 0;
	system("clear");
	printf("Los resultados de los numeros %d y %d son: ", primerNumero, segundoNumero);

	printf("\nSuma de %d + %d: %d", primerNumero, segundoNumero, suma);
	printf("\nResta de %d - %d: %d", primerNumero, segundoNumero, resta);
	if(segundoNumero != 0)
	{
		printf("\nDivision: %.2f", division);
	}
	else
	{
		printf("\nNo se puede dividir por 0.");
	}
	printf("\nMultiplicacion de %d * %d: %d", primerNumero, segundoNumero, multiplicacion);
	if (primerNumero < 0)
	{
		printf("\nNo existe el factorial de un numero negativo.");
	}
	else
	{
		if (primerFactorial <= 0)
		{
			printf("\nDesbordamiento del factorial de %d", primerNumero);
		}
		else
		{
			printf("\nFactorial de %d!: %d", primerNumero, primerFactorial);
		}
	}
	if(segundoNumero < 0)
	{
		printf("\nNo existe el factorial de un numero negativo.");
	}
	else
	{
		if (segundoFactorial <= 0)
		{
			printf("\nDesbordamiento del factorial de %d", segundoNumero);
		}
		else
		{
			printf("\nFactorial de %d!: %d", segundoNumero, segundoFactorial);
		}
	}

	while (opcion != 1)
	{
		printf("\nPresione 1 para continuar: ");
		scanf("%d", &opcion);
	}
}
