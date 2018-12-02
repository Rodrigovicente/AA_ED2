#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_employee.c"
// #include "hash_dependent.c"
#include "lefkowitz_employee.c"


int main(int argc, char const *argv[]) {

	FILE * hash = fopen("tabHash.dat", "w+b");
	// dep_createHash(HASH_SIZE, hash);
	emp_createHash(HASH_SIZE, hash);
	//fclose(hashfile);

	//hash = fopen("tabHash.dat", "r+b");

	//Employee ** added_employees = (Employee**) malloc(sizeof(Employee) * 2);

	Employee * teste1 = (Employee*) malloc(sizeof(Employee));
	Employee * teste2 = (Employee*) malloc(sizeof(Employee));
	Employee * teste3 = (Employee*) malloc(sizeof(Employee));
	Employee * teste4 = (Employee*) malloc(sizeof(Employee));
	Employee * teste5 = (Employee*) malloc(sizeof(Employee));
	Employee * teste6 = (Employee*) malloc(sizeof(Employee));
	Employee * teste7 = (Employee*) malloc(sizeof(Employee));

	// Dependent * teste1 = (Dependent*) malloc(sizeof(Dependent));
	// Dependent * teste2 = (Dependent*) malloc(sizeof(Dependent));
	// Dependent * teste3 = (Dependent*) malloc(sizeof(Dependent));
	// Dependent * teste4 = (Dependent*) malloc(sizeof(Dependent));
	// Dependent * teste5 = (Dependent*) malloc(sizeof(Dependent));
	// Dependent * teste6 = (Dependent*) malloc(sizeof(Dependent));
	// Dependent * teste7 = (Dependent*) malloc(sizeof(Dependent));

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
	strcpy(teste1->name, "Joao zao");
	teste1->age = 27;
	teste1->wage = 2000.5;
	// teste1->employee_code = 12;
	teste1->pointer = -1;
	teste1->status = 1;

	teste2->code = 9;
	strcpy(teste2->name, "Armando jorge");
	teste2->age = 200;
	teste2->wage = 5000.0;
	// teste2->employee_code = 0;
	teste2->pointer = -1;
	teste2->status = 1;

	teste3->code = 20;
	strcpy(teste3->name, "okokoko a");
	teste3->age = 29;
	teste3->wage = 800.9;
	// teste3->employee_code = 21;
	teste3->pointer = -1;
	teste3->status = 1;

	teste4->code = 14;
	strcpy(teste4->name, "oloco moco");
	teste4->age = 20;
	teste4->wage = 6700.9;
	// teste4->employee_code = 21;
	teste4->pointer = -1;
	teste4->status = 1;

	teste5->code = 40;
	strcpy(teste5->name, "pitui pitata");
	teste5->age = 32;
	teste5->wage = 4300.9;
	// teste5->employee_code = 0;
	teste5->pointer = -1;
	teste5->status = 1;

	teste6->code = 25;
	strcpy(teste6->name, "manga banga");
	teste6->age = 27;
	teste6->wage = 4200.2;
	// teste6->employee_code = 0;
	teste6->pointer = -1;
	teste6->status = 1;

	teste7->code = 34;
	strcpy(teste7->name, "loro molo");
	teste7->age = 23;
	teste7->wage = 900.9;
	// teste7->employee_code = 0;
	teste7->pointer = -1;
	teste7->status = 1;

	// insertEmployee(teste1, hash);

	// insertEmployee(teste2, hash);
	// printf("\n>>>>>>>>>>>>>>>>FICOU ASSIM<<<<<<<<<<<<<<<<<<<\n");
	// printEmployees(hash);

	// insertEmployee(teste3, hash);
	// printf("\n>>>>>>>>>>>>>>>>FICOU ASSIM<<<<<<<<<<<<<<<<<<<\n");
	// printEmployees(hash);


	emp_insertEmployee(teste1, hash);

	emp_insertEmployee(teste2, hash);

	emp_insertEmployee(teste3, hash);

	emp_insertEmployee(teste4, hash);

	emp_insertEmployee(teste5, hash);

	emp_insertEmployee(teste6, hash);

	emp_insertEmployee(teste7, hash);


	printf("\n>>>>>>>>>>>>>>>>FICOU ASSIM<<<<<<<<<<<<<<<<<<<\n");
	emp_printEmployees(hash);


	// updateEmployee(21, "test", hash);
	// dep_updateDependent(9, "test", hash);

	// printf("\n>>>>>>>>>>>>>>>>FICOU ASSIM<<<<<<<<<<<<<<<<<<<\n");
	// printEmployees(hash);

	// printf("\n>>>>>>>>>>>>>>>>FICOU ASSIM<<<<<<<<<<<<<<<<<<<\n");
	// dep_printDependents(hash);

	FILE * table_a2 = fopen("table_a2.dat", "w+b");

	FILE * table_a3_name = fopen("table_a3_name.dat", "w+b");
	FILE * table_a3_age = fopen("table_a3_age.dat", "w+b");
	FILE * table_a3_wage = fopen("table_a3_wage.dat", "w+b");

	FILE * table_a4_name = fopen("table_a4_name.dat", "w+b");
	FILE * table_a4_age = fopen("table_a4_age.dat", "w+b");
	FILE * table_a4_wage = fopen("table_a4_wage.dat", "w+b");

	FILE * table_a5_name = fopen("table_a5_name.dat", "w+b");
	FILE * table_a5_age = fopen("table_a5_age.dat", "w+b");
	FILE * table_a5_wage = fopen("table_a5_wage.dat", "w+b");

	rewind(hash);
	createA2File(hash, table_a2);
	printf("\n\n///////////// A2 \n");
	printTableA2(table_a2);

	createA3File(table_a2, table_a3_name, table_a3_age, table_a3_wage);
	printf("\n\n///////////// A3 \n");
	printTableA3(table_a3_name, 1);

	createA4File(table_a3_name, table_a3_age, table_a3_wage, table_a4_name, table_a4_age, table_a4_wage);
	printf("\n\n///////////// A4 \n");
	printTableA4(table_a4_name, 1);

	createA5File(table_a4_name, table_a4_age, table_a4_wage, table_a5_name, table_a5_age, table_a5_wage);
	printf("\n\n///////////// A5 \n");
	printTableA4(table_a5_name, 1);

	fclose(hash);
	fclose(table_a2);
	fclose(table_a3_name);
	fclose(table_a3_age);
	fclose(table_a3_wage);
	fclose(table_a4_name);
	fclose(table_a4_age);
	fclose(table_a4_wage);
	fclose(table_a5_name);
	fclose(table_a5_age);
	fclose(table_a5_wage);

	return 0;
}
