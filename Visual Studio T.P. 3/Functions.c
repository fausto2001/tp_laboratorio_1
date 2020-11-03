#include <stdio.h>
#include "LinkedList.h"
#include "Functions.h"
#include "Employee.h"
#include "Controller.h"
#include <string.h>
#include <stdlib.h>

void start()
{
	LinkedList* employeeList = ll_newLinkedList();
	menu(employeeList);
}

/****************************************************
	Menu:
	 (1). Cargar los datos de los empleados desde el archivo data.csv (modo texto).
	 (2). Cargar los datos de los empleados desde el archivo data.csv (modo binario).
	 (3). Alta de empleado
	 (4). Modificar datos de empleado
	 (5). Baja de empleado
	 (6). Listar empleados
	 (7). Ordenar empleados
	 (8). Guardar los datos de los empleados en el archivo data.csv (modo texto).
	 9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
	(10). Salir
*****************************************************/

void menu(LinkedList* employeeList)
{	
	int opcion = 0;
	int r[10];
	while(opcion < 1 || opcion > 10)
	{
		system("cls");
		printf("Bienvenido!");
		printf("\n1. Cargar empleados desde el archivo data.csv MODO TEXTO");
		printf("\n2. Cargar empleados desde el archivo data.csv MODO BINARIO");
		printf("\n3. Alta de empleado");
		printf("\n4. Modificar empleado");
		printf("\n5. Baja de empleado");
		printf("\n6. Listar empleados");
		printf("\n7. Ordenar empleados");
		printf("\n8. Guardar los datos de los empleados en el archivo data.csv MODO TEXTO");
		printf("\n9. Guardar los datos de los empleados en el archivo data.csv MODO BINARIO");
		printf("\n10. Salir");
		printf("\nElija una opcion: ");
		scanf("%d", &opcion);
	}
	switch (opcion)
	{
	case 1:
		r[1] = controller_loadFromText("data.csv", employeeList);
		if (r[1])
		{
			printf("\nEmpleados cargados!\n");
			system("pause");
			menu(employeeList);
		}
		else
		{
			printf("\nHubo un error al cargar los empleados.\n");
			system("pause");
			menu(employeeList);
		}
		break;
	case 2:
		r[2] = controller_loadFromBinary("data.bin", employeeList);
		if (r[2])
		{
			printf("\nEmpleados cargados!\n");
			system("pause");
			menu(employeeList);
		}
		else
		{
			printf("\nHubo un error al cargar los empleados.\n");
			system("pause");
			menu(employeeList);
		}
		break;
	case 3:
		r[3] = controller_addEmployee(employeeList);
		if (r[3])
		{
			printf("\nNuevo empleado agregado!\n");
			system("pause");
			menu(employeeList);
		}
		else
		{
			printf("\nHubo un error al agregar nuevo empleado\n");
			system("pause");
			menu(employeeList);
		}
		break;
	case 4:
		r[4] = controller_editEmployee(employeeList);
		if (r[4])
		{
			menu(employeeList);
		}
		else
		{
			printf("\nHubo un error!\n");
			system("pause");
			menu(employeeList);
		}
		break;
	case 5:
		r[5] = controller_removeEmployee(employeeList);
		if (r[5])
		{
			menu(employeeList);
		}
		else
		{
			printf("\nHubo un error!\n");
			system("pause");
			menu(employeeList);
		}
	case 6:
		r[6] = controller_ListEmployee(employeeList);
		if (r[6])
		{
			system("pause");
			menu(employeeList);
		}
		else
		{
			printf("Hubo un error.");
			system("pause");
			menu(employeeList);
		}
		break;
	case 7:
		r[7] = controller_sortEmployee(employeeList);
		if (r[7])
		{
			printf("\nEmpleados ordenados correctamente!\n");
			system("pause");
			menu(employeeList);
		}
		else
		{
			printf("Hubo un error.");
			system("pause");
			menu(employeeList);
		}
		break;
	case 8:
		r[8] = controller_saveAsText("data.csv", employeeList);
		if (r[8])
		{
			printf("Empleados guardados!\n");
			system("pause");
			menu(employeeList);
		}
		else
		{
			printf("Hubo un error.\n");
			system("pause");
			menu(employeeList);
		}
		break;
	case 9:
		r[9] = controller_saveAsBinary("data.bin", employeeList);
		if (r[9])
		{
			printf("Empleados guardados!\n");
			system("pause");
			menu(employeeList);
		}
		else
		{
			printf("Hubo un error.\n");
			system("pause");
			menu(employeeList);
		}
	case 10:
		exit(0);
	}
}


/** \brief Looks for new employee ID as close to 0 as possible.
 *
 * Function gets linkedlist length with ll_len. After that, newEmployeeId looks for every single employee until the
 * end of the list while saving current employee's ID value if it's bigger than the previous max number.
 * This functions returns the biggest number found + 1, so as not to give two employees the same ID (biggest number found
 * is actually an employee's ID after all).
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int newEmployeeId(LinkedList* employees)
{
	int employeeId = 0;
	int maxEmployeeId = 0;
	Employee* auxEmployee;

	for (int i = 0; i < ll_len(employees); i++)
	{
		auxEmployee = ll_get(employees, i);
		employee_getId(auxEmployee, &employeeId);
		if (employeeId > maxEmployeeId)
		{
			maxEmployeeId = employeeId;
		}
	}

	return maxEmployeeId + 1;
}


/** \brief Gets a string of 128 characters.
 *
 * Function asks the user for a name, and checks if it's 128 characters or less.
 *
 * \param char name
 * \return char* (returns string)
 *
 */
char* getEmployeeName(char name[128])
{
	char buffer[128];
	my_fflush();
	printf("\nIngrese nombre de empleado: ");
	scanf("%[^\n]", buffer);
	while (strlen(buffer) > 128)
	{
		printf("\nPor favor, reingrese nombre de empleado.");
		my_fflush();
		scanf("%[^\n]", buffer);
	}

	strcpy(name, buffer);
	
	return name;
}

/** \brief Gets a valid int.
 *
 * Function asks the user for an integer.
 *
 * \param no parameters.
 * \return int
 *
 */
int getInt()
{
	int num = -1;
	scanf("%d", &num);
	while (num < 0)
	{
		printf("Reingrese el numero: ");
		scanf("%d", &num);
	}
	return num;
}


/** \brief works just like fflush.
 *
 * Function clears buffer. I created it because I code in visual studio 2019 and fflush doesn't work there.
 *
 * \param no parameters
 * \return void
 *
 */
void my_fflush()
{
	int c;
	do
	{
		c = getchar();
	} while (c != '\n');
}

/** \brief Function returns employee index from Id.
 *
 * This function uses a while from 0 until the length of the list (thanks to ll_len) to look for an employee
 * with the same id as the one given. This is simple to do thanks to ll_get function, where I can momentarily store
 * an employee to check whether the id matches with the one given or not. If the index wasn't found, function returns -1.
 *
 * \param LinkedList* employees, int givenId
 * \return int index
 *
 */

int getEmployeeIndex(LinkedList* employees, int givenId)
{
	Employee* auxEmployee;
	int auxId = givenId;
	int index = -1;
	int i = 0;
	int flag = 0;
	while (i < ll_len(employees) && !flag)
	{
		auxEmployee = ll_get(employees, i);
		employee_getId(auxEmployee, &givenId);
		if (auxId == givenId)
		{
			flag = 1;
			index = i;
		}
		else
		{
			i++;
		}
	}

	return index;
}

/*sortById(LinkedList* employees)
{
	int r = 0;
	Employee* auxEmployee;
	Employee* auxEmployee2;
	int auxInt;
	char auxStr[128];

	if (employees != NULL)
	{
		for (int i = 0; i < ll_len(employees); i++)
		{
			printf("\nOrdenando empleado %d de %d", i, ll_len(employees));
			auxEmployee = ll_get(employees, i);
			for (int j = i + 1; j < ll_len(employees); j++)
			{
				auxEmployee2 = ll_get(employees, j);
				if (auxEmployee->id > auxEmployee2->id)
				{
					auxInt = auxEmployee->id;
					auxEmployee->id = auxEmployee2->id;
					auxEmployee2->id = auxInt;
					auxInt = auxEmployee->sueldo;
					auxEmployee->sueldo = auxEmployee2->sueldo;
					auxEmployee2->sueldo = auxInt;
					auxInt = auxEmployee->horasTrabajadas;
					auxEmployee->horasTrabajadas = auxEmployee2->horasTrabajadas;
					auxEmployee2->horasTrabajadas = auxInt;
					strcpy(auxStr, auxEmployee->nombre);
					strcpy(auxEmployee->nombre, auxEmployee2->nombre);
					strcpy(auxEmployee2->nombre, auxStr);
				}
			}
		}
		r = 1;
	}
	return r;
}

sortByWorktime(LinkedList* employees)
{
	int r = 0;
	Employee* auxEmployee;
	Employee* auxEmployee2;
	int auxInt;
	char auxStr[128];

	if (employees != NULL)
	{
		for (int i = 0; i < ll_len(employees); i++)
		{
			printf("\nOrdenando empleado %d de %d", i, ll_len(employees));
			auxEmployee = ll_get(employees, i);
			for (int j = i + 1; j < ll_len(employees); j++)
			{
				auxEmployee2 = ll_get(employees, j);
				if (auxEmployee->horasTrabajadas > auxEmployee2->horasTrabajadas)
				{
					auxInt = auxEmployee->id;
					auxEmployee->id = auxEmployee2->id;
					auxEmployee2->id = auxInt;
					auxInt = auxEmployee->sueldo;
					auxEmployee->sueldo = auxEmployee2->sueldo;
					auxEmployee2->sueldo = auxInt;
					auxInt = auxEmployee->horasTrabajadas;
					auxEmployee->horasTrabajadas = auxEmployee2->horasTrabajadas;
					auxEmployee2->horasTrabajadas = auxInt;
					strcpy(auxStr, auxEmployee->nombre);
					strcpy(auxEmployee->nombre, auxEmployee2->nombre);
					strcpy(auxEmployee2->nombre, auxStr);
				}
			}
		}
		r = 1;
	}
	return r;
}

sortBySalary(LinkedList* employees)
{
	int r = 0;
	Employee* auxEmployee;
	Employee* auxEmployee2;
	int auxInt;
	char auxStr[128];

	if (employees != NULL)
	{
		for (int i = 0; i < ll_len(employees); i++)
		{
			printf("\nOrdenando empleado %d de %d", i, ll_len(employees));
			auxEmployee = ll_get(employees, i);
			for (int j = i + 1; j < ll_len(employees); j++)
			{
				auxEmployee2 = ll_get(employees, j);
				if (auxEmployee->sueldo > auxEmployee2->sueldo)
				{
					auxInt = auxEmployee->id;
					auxEmployee->id = auxEmployee2->id;
					auxEmployee2->id = auxInt;
					auxInt = auxEmployee->sueldo;
					auxEmployee->sueldo = auxEmployee2->sueldo;
					auxEmployee2->sueldo = auxInt;
					auxInt = auxEmployee->horasTrabajadas;
					auxEmployee->horasTrabajadas = auxEmployee2->horasTrabajadas;
					auxEmployee2->horasTrabajadas = auxInt;
					strcpy(auxStr, auxEmployee->nombre);
					strcpy(auxEmployee->nombre, auxEmployee2->nombre);
					strcpy(auxEmployee2->nombre, auxStr);
				}
			}
		}
		r = 1;
	}
	return r;
}

sortByName(LinkedList* employees)
{
	int r = 0;
	Employee* auxEmployee;
	Employee* auxEmployee2;
	int auxInt;
	char auxStr[128];

	if (employees != NULL)
	{
		for (int i = 0; i < ll_len(employees); i++)
		{
			printf("\nOrdenando empleado %d de %d", i, ll_len(employees));
			auxEmployee = ll_get(employees, i);
			for (int j = i + 1; j < ll_len(employees); j++)
			{
				auxEmployee2 = ll_get(employees, j);
				if (strcmp(auxEmployee->nombre, auxEmployee2->nombre) >= 1)
				{
					auxInt = auxEmployee->id;
					auxEmployee->id = auxEmployee2->id;
					auxEmployee2->id = auxInt;
					auxInt = auxEmployee->sueldo;
					auxEmployee->sueldo = auxEmployee2->sueldo;
					auxEmployee2->sueldo = auxInt;
					auxInt = auxEmployee->horasTrabajadas;
					auxEmployee->horasTrabajadas = auxEmployee2->horasTrabajadas;
					auxEmployee2->horasTrabajadas = auxInt;
					strcpy(auxStr, auxEmployee->nombre);
					strcpy(auxEmployee->nombre, auxEmployee2->nombre);
					strcpy(auxEmployee2->nombre, auxStr);
				}
			}
		}
		r = 1;
	}
	return r;
}*/