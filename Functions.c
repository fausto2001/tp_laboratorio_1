#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MY_EMPLOYEES 10 //MY_EMPLOYEES is the amount of employees to be used and loaded when executing the program

/** \brief starts program through function "initEmployees"
 *
 * \param no parameters
 * \return void function, no return
 */
void initialize()
{
	int error = 0;
	Employee employeeList[MY_EMPLOYEES];
	error = initEmployees(employeeList, MY_EMPLOYEES);
	if (error == 0)
	{
		menu(employeeList);
	}
	else
	{
		printf("Error al inicializar empleados.");
	}
}

/** \brief displays menu and lets user choose option between 1 and 5.
 *
 * \param pointer to array of employees
 * \return void function, no return
 */
void menu(Employee* employeeList)
{
	int option = 0;
	while (option < 1 || option > 5)
	{
		system("clear");

		printf("Bienvenido al programa!");
		printf("\n1. ALTAS: Agregar un empleado");
		printf("\n2. MODIFICAR: Modificar el nombre, apellido, salario, o sector de un empleado");
		printf("\n3. BAJAS: Eliminar un empleado");
		printf("\n4. Informar");
		printf("\n5. Salir");
		printf("\n\nElija una opcion para continuar: ");
		scanf("%d", &option);
	}
	switch (option)
	{
		case 1:
			addMenu(employeeList, MY_EMPLOYEES);
			break;
		case 2:
			modifyMenu(employeeList, MY_EMPLOYEES);
			break;
		case 3:
			deleteMenu(employeeList, MY_EMPLOYEES);
			break;
		case 4:
			informMenu(employeeList, MY_EMPLOYEES);
			break;
		case 5:
			system("clear");
			printf("\nGracias por usar el programa!");
	}
}

/** \brief User is asked for employee name, surname, salary, and sector, and adds it to the database.
 *         Length of employee names is checked every time user inputs it, and the first letter of
 *		   every name is capitalized too, thanks to function "capitalize".
 *
 * \param pointer to array of employees.
 * \param maximum amount of employees loaded or to load.
 * \return void function, no return
 */
void addMenu(Employee* list, int len)
{
	int r = -1;
	char name[51] = "";
	char lastName[51] = "";
	float salary = 0;
	int sector = 0;
	char buffer[1000];
	int option = -1;
	int error = 0;

	system("clear");
	r = searchFreeEmployee(list, len);
	if (r == -1)
	{
		printf("No se pueden agregar nuevos empleados porque no hay espacio. Elimine un empleado para agregar uno nuevo.");
		confirm();
		menu(list);
	}
	else
	{
		printf(" -- Agregar nuevo empleado ID #%d --", r);
		printf("\nEscriba el nombre del nuevo empleado: ");
		my_fflush();
		scanf("%[^\n]", buffer);
		while (strlen(buffer) > 50)
		{
			system("clear");
			printf(" -- Agregar nuevo empleado ID #%d --", r);
			printf("\nEl nombre del empleado solo puede tener hasta 50 letras.\nPor favor, reingrese el nombre del nuevo empleado: ");
			my_fflush();
			scanf("%[^\n]", buffer);
		}
		strcpy(name, buffer);
		capitalize(name);
		printf("\nEl nombre (%s) fue ingresado correctamente.", name);
		confirm();
		system("clear");
		printf(" -- Agregar nuevo empleado ID #%d --", r);
		printf("\nEscriba el apellido del nuevo empleado: ");
		scanf("%[^\n]", buffer);
		while (strlen(buffer) > 50)
		{
			system("clear");
			printf(" -- Agregar nuevo empleado ID #%d --", r);
			printf("\nEl apellido del empleado solo puede tener hasta 50 letras. \nPor favor, reingrese el nombre del nuevo empleado: ");
			my_fflush();
			scanf("%[^\n]", buffer);
		}
		strcpy(lastName, buffer);
		capitalize(lastName);
		printf("\nEl apellido (%s) fue ingresado correctamente.", lastName);
		confirm();
		system("clear");
		printf(" -- Agregar nuevo empleado ID #%d --", r);
		printf("\nIngrese salario del empleado: ");
		scanf("%f", &salary);
		system("clear");
		printf(" -- Agregar nuevo empleado ID #%d --", r);
		printf("\nIngrese sector del empleado: ");
		my_fflush();
		scanf("%d", &sector);
		system("clear");
		printf(" -- Agregar nuevo empleado ID #%d --", r);
		printf("\nNombre: %s", name);
		printf("\nApellido: %s", lastName);
		printf("\nSalario: %.2f", salary);
		printf("\nSector: %d", sector);
		printf("\n\nEsta seguro que desea agregar este nuevo empleado? ");
		while(option != 1 && option != 0)
		{
			printf("\n[1] para CONFIRMAR   [0] para CANCELAR y REGRESAR AL MENU\n");
			scanf("%d", &option);
			switch(option)
			{
				case 0:
					menu(list);
					break;
				case 1:
					system("clear");
					error = addEmployee(list, len, r, name, lastName, salary, sector);
					if(!error)
					{
						printf("El empleado fue agregado satisfactoriamente!");
						confirm();
						menu(list);
					}
					else
					{
						printf("No se pudo agregar el empleado. Verifique si hay espacio.");
						confirm();
						menu(list);
					}
					break;
			}
		}
	}
}


/** \brief User is asked for employee ID, and if such ID is available, the user can change the employee's name, surname
 *		   salary, and sector. Just like in addMenu function, the length of the employees' names is checked every time
 *		   it's inputted, as well as its first letters capitalized.
 *
 * \param pointer to array of employees.
 * \param maximum amount of employees loaded or to load.
 * \return void function, no return
 */
void modifyMenu(Employee* list, int len)
{
	system("clear");
	int r = 0;
	int option = -1;
	int id = 0;
	int modifyOption = 1;
	int order = 1;
	char buffer[1000];
	r = searchExistingEmployee(list, len);
	if (!r)
	{
		printf("\nAun no ha sido agregado ningun empleado a la base de datos. Por favor, agregue un empleado previo a intentar modificar. ");
		confirm();
		menu(list);
	}
	else
	{
		sortEmployees(list, len, order);
		my_fflush();
		printf("Ingrese el ID del empleado a modificar: ");
		scanf("%d", &r);
		id = findEmployeeById(list, len, r);
		if (id == -1)
		{
			printf("El empleado ID #%d no ha sido encontrado.\n", r);
			printf("Desea reintentar con un nuevo ID o regresar al menu?");
			while (option != 0 && option != 1)
			{
				printf("\n[1] para REINTENTAR		[0] para REGRESAR al MENU\n");
				scanf("\n%d", &option);
				switch (option)
				{
				case 0:
					menu(list);
					break;
				case 1:
					modifyMenu(list, len);
					break;
				}
			}
		}
		else
		{
			system("clear");
			printf(" -- Modificar empleado ID #%d -- ", list[id].id);
			printf("\n1. Nombre: %s", list[id].name);
			printf("\n2. Apellido: %s", list[id].lastName);
			printf("\n3. Salario: %f", list[id].salary);
			printf("\n4. Sector: %d", list[id].sector);
			printf("\n5. Volver al menu");
			printf("\nElija una opcion: ");
			scanf("%d", &modifyOption);
			switch (modifyOption)
			{
			case 1:
				system("clear");
				printf(" -- Modificar empleado ID #%d -- ", list[id].id);
				printf("\nNombre actual: %s", list[id].name);
				printf("\nIngrese nuevo nombre: ");
				my_fflush();
				scanf("%[^\n]", buffer);
				while (strlen(buffer) > 50)
				{
					system("clear");
					printf(" -- Modificar empleado ID #%d -- ", list[id].id);
					printf("\nEl nombre del empleado solo puede tener hasta 50 letras.\nPor favor, reingrese el nombre del empleado: ");
					my_fflush();
					scanf("%[^\n]", buffer);
				}
				strcpy(list[id].name, buffer);
				capitalize(list[id].name);
				system("clear");
				printf(" -- Modificar empleado ID #%d -- ", list[id].id);
				printf("\nEl nuevo nombre del empleado es %s.", list[id].name);
				confirm();
				menu(list);
				break;
			case 2:
				system("clear");
				printf(" -- Modificar empleado ID #%d -- ", list[id].id);
				printf("\nApellido actual: %s", list[id].lastName);
				printf("\nIngrese nuevo apellido: ");
				my_fflush();
				scanf("%[^\n]", buffer);
				while (strlen(buffer) > 50)
				{
					system("clear");
					printf(" -- Modificar empleado ID #%d -- ", list[id].id);
					printf("\nEl nombre del apellido solo puede tener hasta 50 letras.\nPor favor, reingrese el nombre del empleado: ");
					my_fflush();
					scanf("%[^\n]", buffer);
				}
				strcpy(list[id].lastName, buffer);
				capitalize(list[id].lastName);
				system("clear");
				printf(" -- Modificar empleado ID #%d -- ", list[id].id);
				printf("\nEl nuevo apellido del empleado es %s.", list[id].lastName);
				confirm();
				menu(list);
				break;
			case 3:
				system("clear");
				printf(" -- Modificar empleado ID #%d -- ", list[id].id);
				printf("\nSalario actual: %f", list[id].salary);
				printf("\nIngrese nuevo salario: ");
				scanf("%f", &list[id].salary);
				system("clear");
				printf(" -- Modificar empleado ID #%d -- ", list[id].id);
				printf("\nEl nuevo salario del empleado es %f.", list[id].salary);
				confirm();
				menu(list);
				break;
			case 4:
				system("clear");
				printf(" -- Modificar empleado ID #%d -- ", list[id].id);
				printf("\nSector actual: %d", list[id].sector);
				printf("\nIngrese nuevo sector: ");
				scanf("%d", &list[id].sector);
				system("clear");
				printf(" -- Modificar empleado ID #%d -- ", list[id].id);
				printf("\nEl nuevo salario del empleado es %d.", list[id].sector);
				confirm();
				menu(list);
				break;
			case 5:
				menu(list);
				break;
			}
		}
	}
}

/** \brief User is asked for employee ID, and if it exists, the employee is deleted from the database by setting its
 *		   isEmpty value to 0.
 *
 * \param pointer to array of employees.
 * \param maximum amount of employees loaded or to load.
 * \return void function, no return
 */
void deleteMenu(Employee* list, int len)
{
	int id = 0;
	int exist = searchExistingEmployee(list, len);
	int r = 0;
	int option = -1;
	int delete = -1;
	int finalDelete = -1;
	int error = 0;

	if (!exist)
	{
		printf("\nAun no ha sido agregado ningun empleado a la base de datos. Por favor, agregue un empleado previo a intentar eliminar. ");
		confirm();
		menu(list);
	}
	else
	{
		my_fflush();
		printf("Ingrese el ID del empleado a eliminar: ");
		scanf("%d", &r);
		id = findEmployeeById(list, len, r);
		if (id == -1)
		{
			printf("El empleado ID #%d no ha sido encontrado.\n", r);
			printf("Desea reintentar con un nuevo ID o regresar al menu?");
			while (option != 0 && option != 1)
			{
				printf("\n[1] para REINTENTAR		[0] para REGRESAR al MENU\n");
				scanf("\n%d", &option);
				switch (option)
				{
				case 0:
					menu(list);
					break;
				case 1:
					deleteMenu(list, len);
					break;
				}
			}
		}
		else
		{
			while(delete != 0 && delete != 1)
			{
				system("clear");
				printf(" -- Eliminar empleado ID #%d -- ", list[id].id);
				printf("\nNombre: %s", list[id].name);
				printf("\nApellido: %s", list[id].lastName);
				printf("\nSalario: %f", list[id].salary);
				printf("\nSector: %d", list[id].sector);
				printf("\n1. Eliminar empleado");
				printf("\n0. Volver al menu");
				printf("\nEscriba 1 para eliminar, 0 para volver al menu.");
				scanf("%d", &delete);
				switch (delete)
				{
				case 1:
					printf("Esta seguro que desea eliminar este empleado?! La accion es irreversible: ");
					while (finalDelete != 1 && finalDelete != 0)
					{
						printf("\n[1] para CONFIRMAR   [0] para CANCELAR y REGRESAR AL MENU\n");
						scanf("%d", &finalDelete);
						switch (finalDelete)
						{
						case 0:
							menu(list);
							break;
						case 1:
							system("clear");
							error = removeEmployee(list, len, id);
							if (!error)
							{
								printf("El empleado fue eliminado satisfactoriamente!");
								confirm();
								menu(list);
							}
							else
							{
								printf("No se pudo eliminar el empleado.");
								confirm();
								menu(list);
							}
							break;
						}
					}
					break;
                case 0:
                    menu(list);
                    break;
				}
			}
		}
	}
}

/** \brief User can see every single employee loaded into the database, ordered by name from A-Z. User can't set order
 *		   since it's not stated in TP2.pdf: "1. Listado de los empleados ordenados alfabéticamente por Apellido y Sector.
 *		   2. Total y promedio de los salarios, y cuántos empleados superan el salario promedio."
 *
 * \param pointer to array of employees.
 * \param maximum amount of employees loaded or to load.
 * \return void function, no return
 */
void informMenu(Employee* list, int len)
{
	int exist = searchExistingEmployee(list, len);
	int order = 1;
	float totalSalary = 0;
	int totalEmployees = 0;
	float avg = 0;
	system("clear");
	if (!exist)
	{
		printf("\nAun no ha sido agregado ningun empleado a la base de datos. Por favor, agregue un empleado previo a intentar eliminar. ");
	}
	else
	{
		sortEmployees(list, len, order);
		printEmployees(list, len);
		for (int i = 0; i < MY_EMPLOYEES; i++)
		{
			if (!list[i].isEmpty)
			{
				totalEmployees++;
				totalSalary += list[i].salary;
			}
		}
		avg = totalSalary / totalEmployees;
		printf("\nTotal de salarios: %.2f", totalSalary);
		printf("\nPromedio de salarios: %.2f", avg);
	}
	confirm();
	menu(list);
}

/** \brief isEmpty wasn't quite working in my PC, so I decided to create this little function which gets the '\0' in the
 *         buffer, thus rendering the buffer clean.
 * \param no parameters given
 * \return void function, no return
 */
void my_fflush()
{
	int c;
	do
	{
		c = getchar();
	}
	while (c != '\n');
}


/** \brief Capitalize function receives a char string and uppercases the first letter and every letter after a space
 *		   as well as lowercasing all the other letters.
 *
 * \param  string
 * \return returns string
 */
char capitalize(char name[])
{
	int len = strlen(name);
	int skip = 0;

	if (name[0] > 96 && name[0] <= 122)
	{
		name[0] -= 32;
	}

	for(int i = 1; i < len; i++)
	{
		if(i != skip)
		{
			if (name[i] > 64 && name[i] < 91)
			{
				name[i] += 32;
			}
			if (name[i] == 32 && name[i + 1] != '\0')
			{
				skip = i + 1;
				if (name[i + 1] > 96 && name[i + 1] < 122)
				{
					name[i + 1] -= 32;
				}
			}
		}
	}
	return name;
}


/** \brief Confirm function works just like system("pause"), and lets the user take their time to see what's on the screen,
 *		   prior to inputting a key to advance.
 *
 * \param  no parameters given
 * \return void function, no returns.
 */
void confirm()
{
	char cont = '\0';
	my_fflush();
	while (cont == '\0')
	{
		printf("\nIngrese una tecla para continuar: ");
		scanf("%c", &cont);
		my_fflush();
	}
}
