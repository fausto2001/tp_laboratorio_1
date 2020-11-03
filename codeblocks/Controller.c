#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "Functions.h"
#include <string.h>



/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    int r = 1;
    FILE* pFile = fopen(path, "r");

    if (pFile != NULL)
    {
        r = parser_EmployeeFromText(pFile, pArrayListEmployee);
    }
    else
    {
        r = 0;
    }

    fclose(pFile);

    return r;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
    int r = 0;
    FILE* pFile = NULL;

    if(pArrayListEmployee != NULL)
    {
        pFile = fopen(path, "rb");
        if (pFile != NULL)
        {
            r = parser_EmployeeFromBinary(pFile, pArrayListEmployee);
        }
        fclose(pFile);
    }

    return r;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int r = 0;
    char name[128] = "";

    if (pArrayListEmployee != NULL)
    {
        Employee* newEmployee;

        newEmployee = employee_new();

        newEmployee->id = newEmployeeId(pArrayListEmployee);
        strcpy(newEmployee->nombre, getEmployeeName(name));
        printf("\nIngrese horas trabajadas: ");
        newEmployee->horasTrabajadas = getInt();
        printf("\nIngrese salario: ");
        newEmployee->sueldo = getInt();

        ll_add(pArrayListEmployee, newEmployee);
        r = 1;
    }

    return r;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int id = -1;
    int r = 0;
    int employeeIndex = 0;
    int opcion = 0;
    char employeeName[128] = "";
    int salary = 0;
    int horasTrabajadas = 0;
    Employee* chosenEmployee;

    if (pArrayListEmployee != NULL)
    {
        printf("Ingrese el id del empleado a modificar o ingrese -1 para volver al menu: ");
        scanf("%d", &id);
        switch (id)
        {
        case -1:
            r = 1;
            return r;
            break;
        default:
            employeeIndex = getEmployeeIndex(pArrayListEmployee, id);
            if (employeeIndex == -1)
            {
                printf("\nEl empleado ID %d no ha sido encontrado.\n", id);
                r = 1;
                system("pause");
                return r;
                break;
            }
            else
            {
                chosenEmployee = ll_get(pArrayListEmployee, employeeIndex);
                printf("Que desea modificar?\n");
                printf("1. Nombre: %s\n", chosenEmployee->nombre);
                printf("2. Salario: %d\n", chosenEmployee->sueldo);
                printf("3. Horas: %d\n", chosenEmployee->horasTrabajadas);
                printf("4. Salir\n");
                while (opcion < 1 || opcion > 5)
                {
                    printf("Elija una opcion correcta: ");
                    scanf("%d", &opcion);
                }
                switch (opcion)
                {
                case 1:
                    strcpy(employeeName, getEmployeeName(employeeName));
                    r = employee_setNombre(chosenEmployee, employeeName);
                    if (!r)
                    {
                        printf("\nHubo un error al ingresar nombre. \n");
                        return r;
                    }
                    else
                    {
                        printf("\nNuevo nombre ingresado!\n");
                        system("pause");
                        return r;
                    }
                    break;
                case 2:
                    salary = getInt(salary);
                    r = employee_setSueldo(chosenEmployee, salary);
                    if (!r)
                    {
                        printf("\nHubo un error al ingresar salario. \n");
                        return r;
                    }
                    else
                    {
                        printf("\nNuevo salario ingresado!\n");
                        system("pause");
                        return r;
                    }
                case 3:
                    horasTrabajadas = getInt(horasTrabajadas);
                    r = employee_setHorasTrabajadas(chosenEmployee, horasTrabajadas);
                    if (!r)
                    {
                        printf("\nHubo un error al ingresar las horas trabajadas. \n");
                        return r;
                    }
                    else
                    {
                        printf("\nNuevas horas trabajadas ingresadas!\n");
                        system("pause");
                        return r;
                    }
                case 4:
                    r = 1;
                    menu(pArrayListEmployee);
                    break;
                }
            }
            break;
        }
    }
    return r;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int id = -1;
    int r = 0;
    int employeeIndex = 0;

    if (pArrayListEmployee != NULL)
    {
        printf("Ingrese el id del empleado a eliminar o ingrese -1 para volver al menu: ");
        scanf("%d", &id);
        switch (id)
        {
        case -1:
            r = 1;
            return r;
            break;
        default:
            employeeIndex = getEmployeeIndex(pArrayListEmployee, id);
            if (employeeIndex == -1)
            {
                printf("\nEl empleado ID %d no ha sido encontrado.\n", id);
                r = 1;
                system("pause");
                return r;
            }
            else
            {
                r = ll_remove(pArrayListEmployee, employeeIndex);
                if (!r)
                {
                    r = 1;
                    printf("Empleado eliminado satsifactoriamente!");
                    system("pause");
                }
                else
                {
                    r = 0;
                }
            }
            break;
        }
    }
    return r;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    system("cls");
    int r = 0;
    Employee* employee;
    int id;
    char name[128];
    int horasTrabajadas;
    int sueldo;

    if (pArrayListEmployee != NULL)
    {
        printf("\nid\t\t\t\tnombre\thoras trabajadas      sueldo\n");
        for (int i = 0; i < ll_len(pArrayListEmployee); i++)
        {
            employee = ll_get(pArrayListEmployee, i);
            employee_getId(employee, &id);
            printf("%d", id);
            employee_getNombre(employee, name);
            printf("%35s", name);
            employee_getHorasTrabajadas(employee, &horasTrabajadas);
            printf("%15d", horasTrabajadas);
            employee_getSueldo(employee, &sueldo);
            printf("%15d\n", sueldo);
        }
        r = 1;
    }

    return r;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int r = 0;
    int option = 0;
    if(pArrayListEmployee != NULL)
    {
        while (option < 1 || option > 5)
        {
            printf("\n1. Ordenar por ID.");
            printf("\n2. Ordenar por nombre.");
            printf("\n3. Ordenar por horas trabajadas.");
            printf("\n4. Ordenar por salario.");
            printf("\n5. Salir\n");
            printf("Elija una opcion: ");
            scanf("%d", &option);
            switch (option)
            {
            case 1:
                //r = sortById(pArrayListEmployee);
                printf("\nOrdenando por ID...");
                ll_sort(pArrayListEmployee, compareById, 1);
                break;
            case 2:
                printf("\nOrdenando por nombre...");
                ll_sort(pArrayListEmployee, compareByName, 1);
                break;
            case 3:
                printf("\nOrdenando por horas trabajadas...");
                ll_sort(pArrayListEmployee, compareByHoras, 1);
                break;
            case 4:
                printf("\nOrdenando por sueldo...");
                ll_sort(pArrayListEmployee, compareBySueldo, 1);
            case 5:
                r = 1;
                break;
            }
            r = 1;
        }
    }
    return r;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
    int r = 0;
    Employee* auxEmployee;

    if (pArrayListEmployee != NULL)
    {
        FILE* pFile;
        pFile = fopen(path, "w");
        for (int i = 0; i < ll_len(pArrayListEmployee); i++)
        {
            auxEmployee = ll_get(pArrayListEmployee, i);
            fprintf(pFile, "%d, %s, %d, %d\n", auxEmployee->id, auxEmployee->nombre, auxEmployee->horasTrabajadas, auxEmployee->sueldo);
        }
        r = 1;
        fclose(pFile);
    }

    return r;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    int r = 0;
    Employee* auxEmployee;

    if (pArrayListEmployee != NULL)
    {
        FILE* pFile;
        pFile = fopen(path, "wb");
        for (int i = 0; i < ll_len(pArrayListEmployee); i++)
        {
            auxEmployee = ll_get(pArrayListEmployee, i);
            fwrite(auxEmployee, sizeof(Employee), 1, pFile);
        }
        r = 1;
        fclose(pFile);
    }

    return r;
    return 1;
}

