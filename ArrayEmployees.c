#include "ArrayEmployees.h"
#include <string.h>


/** \brief To indicate that all positions in the array are empty,
 * this function puts the flag (isEmpty) in TRUE in all
 * positions of the array
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int initEmployees(Employee* list, int len)
{
    int r = 0;

    if (len > MAX_EMPLOYEES)
    {
        r = -1;
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            list[i].isEmpty = 1;
            list[i].id = i;
            printf("\nCargando empleado %d de %d", i, len);
        }
    }

    return r;
}

/**brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param list employee*
 * \param len int
 * \param id int
 * \param name[] char
 * \param lastName[] char
 * \param salary float
 * \param sector int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 */
int addEmployee(Employee* list, int len, int id, char name[51], char lastName[51], float salary, int sector)
{
    int r = 0;
    if(list[id].isEmpty == 1)
    {
        strcpy(list[id].name, name);
        strcpy(list[id].lastName, lastName);
        list[id].salary = salary;
        list[id].sector = sector;
        list[id].isEmpty = 0;
    }
    else
    {
        r = -1;
    }

    return r;
}

/** \brief find an Employee by Id and returns the index position in array.
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
 *
 */
int findEmployeeById(Employee* list, int len, int givenId)
{
    int r = -1;
    int flag = 0;
    int i = 0;
    while(i < len && !flag)
    {
        if(givenId == list[i].id && !list[i].isEmpty)
        {
            r = i;
            flag = 1;
        }
        else
        {
            i++;
        }
    }
    return r;
}

int searchFreeEmployee(Employee* list, int len)
{
    int i = 0;
    int flag = 0;
    int r = -1;

    while (i < len && !flag)
    {
        if (list[i].isEmpty == 1)
        {
            r = list[i].id;
            flag = 1;
        }
        else
        {
            i++;
        }
    }
    return r;
}

/** \brief looks for existing employees in the list.
 *
 * \param list Employee*
 * \param length int
 * \return returns 1 if any employee with the value 'isEmpty' equal to 0 is found,
 * \returns 0 if no employees currently have the value 'isEmpty' equal to 0 in the list.
 */
int searchExistingEmployee(Employee* list, int len)
{
    int i = 0;
    int flag = 0;
    int r = 0;

    while (i < len && !flag)
    {
        if (list[i].isEmpty == 0)
        {
            r = 1;
            flag = 1;
        }
        else
        {
            i++;
        }
    }
    return r;
}

/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
 *
 */

int removeEmployee(Employee* list, int len, int id)
{
    int r = 0;
    list[id].isEmpty = 1;
    if (!list[id].isEmpty)
    {
        r = -1;
    }
    return r;
}

/** \brief Sort the elements in the array of employees, the argument order
indicate UP or DOWN order
 *
 * \param list Employee*
 * \param len int
 * \param order int [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int sortEmployees(Employee* list, int len, int order)
{
    char auxStr[51];
    int auxInt;
    float auxFlo;

    if (order == 1)
    {
        for (int i = 0; i < len - 1; i++)
        {
            for (int j = 0; j < len; j++)
            {
                if(!list[i].isEmpty && !list[j].isEmpty)
                {
                    if(strcmp(list[i].name, list[j].name) != 0)
                    {
                        if (strcmp(list[i].name, list[j].name) < 0)
                        {
                            strcpy(auxStr, list[i].name);
                            strcpy(list[i].name, list[j].name);
                            strcpy(list[j].name, auxStr);
                            strcpy(auxStr, list[i].lastName);
                            strcpy(list[i].lastName, list[j].lastName);
                            strcpy(list[j].lastName, auxStr);
                            auxInt = list[i].sector;
                            list[i].sector = list[j].sector;
                            list[j].sector = auxInt;
                            auxFlo = list[i].salary;
                            list[i].salary = list[j].salary;
                            list[j].salary = auxFlo;
                            auxInt = list[i].id;
                            list[i].id = list[j].id;
                            list[j].id = auxInt;
                        }
                    }
                    else
                    {
                        if (list[i].sector < list[j].sector)
                        {
                            strcpy(auxStr, list[i].name);
                            strcpy(list[i].name, list[j].name);
                            strcpy(list[j].name, auxStr);
                            strcpy(auxStr, list[i].lastName);
                            strcpy(list[i].lastName, list[j].lastName);
                            strcpy(list[j].lastName, auxStr);
                            auxInt = list[i].sector;
                            list[i].sector = list[j].sector;
                            list[j].sector = auxInt;
                            auxFlo = list[i].salary;
                            list[i].salary = list[j].salary;
                            list[j].salary = auxFlo;
                            auxInt = list[i].id;
                            list[i].id = list[j].id;
                            list[j].id = auxInt;
                        }
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < len - 1; i++)
        {
            for (int j = 0; j < len; j++)
            {
                if (!list[i].isEmpty && !list[j].isEmpty)
                {
                    if (strcmp(list[i].name, list[j].name) != 0)
                    {
                        if (strcmp(list[i].name, list[j].name) > 0)
                        {
                            strcpy(auxStr, list[i].name);
                            strcpy(list[i].name, list[j].name);
                            strcpy(list[j].name, auxStr);
                            strcpy(auxStr, list[i].lastName);
                            strcpy(list[i].lastName, list[j].lastName);
                            strcpy(list[j].lastName, auxStr);
                            auxInt = list[i].sector;
                            list[i].sector = list[j].sector;
                            list[j].sector = auxInt;
                            auxFlo = list[i].salary;
                            list[i].salary = list[j].salary;
                            list[j].salary = auxFlo;
                            auxInt = list[i].id;
                            list[i].id = list[j].id;
                            list[j].id = auxInt;
                        }
                    }
                    else
                    {
                        if (list[i].sector > list[j].sector)
                        {
                            strcpy(auxStr, list[i].name);
                            strcpy(list[i].name, list[j].name);
                            strcpy(list[j].name, auxStr);
                            strcpy(auxStr, list[i].lastName);
                            strcpy(list[i].lastName, list[j].lastName);
                            strcpy(list[j].lastName, auxStr);
                            auxInt = list[i].sector;
                            list[i].sector = list[j].sector;
                            list[j].sector = auxInt;
                            auxFlo = list[i].salary;
                            list[i].salary = list[j].salary;
                            list[j].salary = auxFlo;
                            auxInt = list[i].id;
                            list[i].id = list[j].id;
                            list[j].id = auxInt;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

/** \brief print the content of employees array
 *
 * \param list Employee*
 * \param length int
 * \return int
 *
 */
int printEmployees(Employee* list, int len)
{
    //name  lastName    salary  sector
    printf("--- LISTA DE EMPLEADOS ---");
    printf("\nID\t\t\t   Nombre\t\t\t   Apellido\t\tSalario\t\tSector");
    for (int i = 0; i < len; i++)
    {
        if(!list[i].isEmpty)
        {
            printf("\n%3d%30s%30s%20.2f%12d", list[i].id, list[i].name, list[i].lastName, list[i].salary, list[i].sector);
        }
    }
    return 0;
}

