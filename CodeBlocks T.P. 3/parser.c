#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int r = 0;
    char id[20];
    char nombre[128];
    char horasTrabajadas[20];
    char sueldo[20];
    Employee* empleadoAuxiliar;

    do
    {
        fscanf(pFile, "%[^,], %[^,], %[^,], %[^\n]\n", id, nombre, horasTrabajadas, sueldo);
        empleadoAuxiliar = employee_newParametros(id, nombre, horasTrabajadas, sueldo);
        ll_add(pArrayListEmployee, empleadoAuxiliar);
    } while (!feof(pFile));

    r = 1;
    
    return r;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int r = 0;
    int size = 0;
    Employee* empleadoAuxiliar;

    empleadoAuxiliar = employee_new();
    fread(empleadoAuxiliar, sizeof(Employee), 1, pFile);

    while (!feof(pFile))
    {
        ll_add(pArrayListEmployee, empleadoAuxiliar);
        size = ll_len(pArrayListEmployee);
        r = 1;
        empleadoAuxiliar = employee_new();
        fread(empleadoAuxiliar, sizeof(Employee), 1, pFile);
    }

    /*do
    {
        empleadoAuxiliar = employee_new();
        if (fread(empleadoAuxiliar, sizeof(Employee), 1, pFile) == 1)
        {
            ll_add(pArrayListEmployee, empleadoAuxiliar);
            r = 1;
        }
        else
        {
            r = 0;
        }
    } while (!feof(pFile) && r != 0);*/

    return r;
}
