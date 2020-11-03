#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include <string.h>

Employee* employee_newParametros(char* idStr, char* nombreStr, char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* newEmployee;
	newEmployee = employee_new();
	int r = 0;
	
	employee_setId(newEmployee, atoi(idStr));
    employee_setNombre(newEmployee, nombreStr);
	employee_setHorasTrabajadas(newEmployee, atoi(horasTrabajadasStr));
	employee_setSueldo(newEmployee, atoi(sueldoStr));

	return newEmployee;
}

Employee* employee_new()
{
	Employee* newEmployee;
	newEmployee = (Employee*)malloc(sizeof(Employee));
	return newEmployee;
}




/****************			SETTERS				**********************/		

int employee_setNombre(Employee* this, char* nombre)
{
	int r = 0;

	if (this != NULL && nombre != NULL && strlen(nombre))
	{
		strcpy(this->nombre, nombre);
		r = 1;
	}

	return r;
}

int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas)
{
	int r = 0;
	if (this != NULL && horasTrabajadas != NULL)
	{
		this->horasTrabajadas = horasTrabajadas;
		r = 1;
	}

	return r;
}

int employee_setSueldo(Employee* this, int sueldo)
{
	int r = 0;
	if (this != NULL && sueldo != NULL && sueldo > 0)
	{
		this->sueldo = sueldo;
		r = 1;
	}

	return r;
}

int employee_setId(Employee* this, int id)
{
	int r = 0;
	if (this != NULL && id != NULL)
	{
		this->id = id;
		r = 1;
	}

	return id;
}

/****************			SETTERS				**********************/



/****************			GETTERS				**********************/

int employee_getId(Employee* this, int* id)
{
	int r = 0;
	if (this != NULL && id != NULL)
	{
		*id = this->id;
		r = 1;
	}

	return r;
}

int employee_getSueldo(Employee* this, int* sueldo)
{
	int r = 0;
	if (this != NULL && sueldo != NULL)
	{
		*sueldo = this->sueldo;
		r = 1;
	}

	return r;
}

int employee_getHorasTrabajadas(Employee* this, int* horasTrabajadas)
{
	int r = 0;
	if (this != NULL && horasTrabajadas != NULL)
	{
		*horasTrabajadas = this->horasTrabajadas;
		r = 1;
	}

	return r;
}

int employee_getNombre(Employee* this, char* nombre)
{
	int r = 0;

	if (this != NULL && nombre != NULL)
	{
		strcpy(nombre, this->nombre);
		r = 1;
	}

	return r;
}

/****************			GETTERS				**********************/


int compareByName(Employee* auxEmployee, Employee* auxEmployee2)
{
	int r = strcmp(auxEmployee->nombre, auxEmployee2->nombre);

	return r;
}

int compareById(Employee* auxEmployee, Employee* auxEmployee2)
{
	int r = 0;

	if (auxEmployee->id > auxEmployee2->id)
	{
		r = 1;
	}

	return r;
}

int compareBySueldo(Employee* auxEmployee, Employee* auxEmployee2)
{
	int r = 0;

	if (auxEmployee->sueldo > auxEmployee2->sueldo)
	{
		r = 1;
	}

	return r;
}

int compareByHoras(Employee* auxEmployee, Employee* auxEmployee2)
{
	int r = 0;

	if (auxEmployee->horasTrabajadas > auxEmployee2->horasTrabajadas)
	{
		r = 1;
	}

	return r;
}