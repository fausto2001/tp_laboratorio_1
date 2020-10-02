#define MAX_EMPLOYEES 1000 //Max employees is the amount of employees reserved in memory

struct
{
	int id;
	char name[51];
	char lastName[51];
	float salary;
	int sector;
	int isEmpty;
} typedef Employee;

int initEmployees(Employee* list, int len);
int addEmployee(Employee* list, int len, int id, char name[51], char lastName[51], float salary, int sector);
int removeEmployee(Employee* list, int len, int id);
int searchFreeEmployee(Employee* list, int len);
int searchExistingEmployee(Employee* list, int len);
int sortEmployees(Employee* list, int len, int order);
int printEmployees(Employee* list, int len);
int findEmployeeById(Employee* list, int len, int givenId);
