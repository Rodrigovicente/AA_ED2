#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#include "hash_employee.c"
#include "hash_dependent.c"


int main(int argc, char const *argv[]) {

	FILE * hash = fopen("tabHash.dat", "w+b");
	dep_createHash(HASH_SIZE, hash);
	hash = fopen("tabHash.dat", "r+b");

	//Employee ** added_employees = (Employee**) malloc(sizeof(Employee) * 2);

	// Employee * teste1 = (Employee*) malloc(sizeof(Employee));
	// Employee * teste2 = (Employee*) malloc(sizeof(Employee));
	// Employee * teste3 = (Employee*) malloc(sizeof(Employee));

	Dependent * teste1 = (Dependent*) malloc(sizeof(Dependent));
	Dependent * teste2 = (Dependent*) malloc(sizeof(Dependent));
	Dependent * teste3 = (Dependent*) malloc(sizeof(Dependent));

/*
	added_employees[0]->code = 0;
	strcpy(added_employees[0]->name, "joaoalbino");
	added_employees[0]->age = 27;
	added_employees[0]->wage = 2000.5;
	added_employees[0]->pointer = -1;
	added_employees[0]->status = 1;

	added_employees[1]->code = 21;
	strcpy(added_employees[1]->name, "joaoalbi no2");
	added_employees[1]->age = 200;
	added_employees[1]->wage = 5000.0;
	added_employees[1]->pointer = -1;
	added_employees[1]->status = 1;
*/

	teste1->code = 2;
	strcpy(teste1->name, "joaoalbino");
	teste1->age = 27;
	// teste1->wage = 2000.5;
	teste1->employee_code = 12;
	teste1->pointer = -1;
	teste1->status = 1;

	teste2->code = 9;
	strcpy(teste2->name, "joaoalbi no2");
	teste2->age = 200;
	// teste2->wage = 5000.0;
	teste2->employee_code = 0;
	teste2->pointer = -1;
	teste2->status = 1;

	teste3->code = 20;
	strcpy(teste3->name, "okokoko a");
	teste3->age = 29;
	// teste3->wage = 800.9;
	teste3->employee_code = 21;
	teste3->pointer = -1;
	teste3->status = 1;

	// insertEmployee(teste1, hash);

	// insertEmployee(teste2, hash);
	// printf("\n>>>>>>>>>>>>>>>>FICOU ASSIM<<<<<<<<<<<<<<<<<<<\n");
	// printEmployees(hash);

	// insertEmployee(teste3, hash);
	// printf("\n>>>>>>>>>>>>>>>>FICOU ASSIM<<<<<<<<<<<<<<<<<<<\n");
	// printEmployees(hash);


	dep_insertDependent(teste1, hash);

	dep_insertDependent(teste2, hash);
		printf("\n>>>>>>>>>>>>>>>>FICOU ASSIM<<<<<<<<<<<<<<<<<<<\n");
	dep_printDependents(hash);

	dep_insertDependent(teste3, hash);
	printf("\n>>>>>>>>>>>>>>>>FICOU ASSIM<<<<<<<<<<<<<<<<<<<\n");
	dep_printDependents(hash);


	// updateEmployee(21, "test", hash);
	dep_updateDependent(9, "test", hash);

	// printf("\n>>>>>>>>>>>>>>>>FICOU ASSIM<<<<<<<<<<<<<<<<<<<\n");
	// printEmployees(hash);

	printf("\n>>>>>>>>>>>>>>>>FICOU ASSIM<<<<<<<<<<<<<<<<<<<\n");
	dep_printDependents(hash);


	fclose(hash);

	return 0;
}
