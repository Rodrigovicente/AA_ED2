#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_common.c"

/*
typedef struct Employee {
	int code;
	char name[100];
	int age;
	float wage;
	int status; // 1 used, 0 free
	int pointer;
} Employee;

typedef struct Client {
	int code;
	char name[100];
	int status; // 1 used, 0 free
	int pointer;
} Client;
*/

int emp_sizeofEmployee() {
	return sizeof(int)  //code
	+ sizeof(char) * 100 //cname
	+ sizeof(int) //age
	+ sizeof(float) //wage
	+ sizeof(int) // status
	+ sizeof(int); //pointer
}

int emp_readEmployee(Employee * employee, FILE *fileName){
	return (fread(&employee->code, sizeof(int), 1, fileName) &&
			fread(employee->name, sizeof(char), sizeof(employee->name), fileName) &&
			fread(&employee->age, sizeof(int), 1, fileName) &&
			fread(&employee->wage, sizeof(float), 1, fileName) &&
			fread(&employee->status, sizeof(int), 1, fileName) &&
			fread(&employee->pointer, sizeof(int), 1, fileName));

}

void emp_writeEmployee(Employee *employee, FILE *fileName, int filePos, int size){
	fseek(fileName, filePos * size, SEEK_SET);
	fwrite(&employee->code, sizeof(int), 1, fileName);
	fwrite(employee->name, sizeof(char), sizeof(employee->name), fileName);
	fwrite(&employee->age, sizeof(int), 1, fileName);
	fwrite(&employee->wage, sizeof(float), 1, fileName);
	fwrite(&employee->status, sizeof(int), 1, fileName);
	fwrite(&employee->pointer, sizeof(int), 1, fileName);
}


int emp_findFreePosition(FILE *fileName, int mappedPos){
	Employee * employee = (Employee*) malloc(sizeof(Employee));
	int i = 0, j = mappedPos;

	while(i < HASH_SIZE){
		fseek(fileName, j*emp_sizeofEmployee(), SEEK_SET);
		emp_readEmployee(employee, fileName);

		if(employee->status == 0){
			return j;
		}
		j = (j + 1) % HASH_SIZE;
		i++;
	}
	printf(" - Overflow -");
	exit(0);
}

int emp_findEmployee(FILE *fileName, int key){
	int i = 0, j;
	Employee *tempEmp = (Employee *) malloc(sizeof(Employee));

	j = hashFunction(key, HASH_SIZE);

	while(i < HASH_SIZE){
		fseek(fileName, j*emp_sizeofEmployee(), SEEK_SET);
		emp_readEmployee(tempEmp, fileName);

		if(tempEmp->code == key){
			return j;//return client position
		}
		j = tempEmp->pointer;
		i++;
	}
	return -1;//client not found
}

void emp_insertEmployee(Employee *employee, FILE *fileName){
	int mappedPos, freePos;
	Employee *tempEmp = (Employee *) malloc(sizeof(Employee));

	mappedPos = hashFunction(employee->code, HASH_SIZE);
	employee->status = 1;


	if (emp_findEmployee(fileName, employee->code) != -1) {
		printf("Dumb user! Employee already exists.\n");
	} else {
		fseek(fileName, mappedPos*emp_sizeofEmployee(), SEEK_SET);
		emp_readEmployee(tempEmp, fileName);

		if (tempEmp->status == 0) { //Position is available
			fseek(fileName, mappedPos*emp_sizeofEmployee(), SEEK_SET);
			fwrite(&employee->code, sizeof(int), 1, fileName);
			fwrite(employee->name, sizeof(char), sizeof(employee->name), fileName);
			fwrite(&employee->age, sizeof(int), 1, fileName);
			fwrite(&employee->wage, sizeof(float), 1, fileName);
			fwrite(&employee->status, sizeof(int), 1, fileName);
		} else {
			int i, j = mappedPos;

			while(i < HASH_SIZE){
				fseek(fileName, j*emp_sizeofEmployee(), SEEK_SET);
				emp_readEmployee(tempEmp, fileName);

				if(tempEmp->status == 0 || tempEmp->pointer == -1){
					break;
				}
				j = tempEmp->pointer;
				i++;
			}

			if (tempEmp->status == 0) {
				fseek(fileName, j*emp_sizeofEmployee(), SEEK_SET);
				fwrite(&employee->code, sizeof(int), 1, fileName);
				fwrite(employee->name, sizeof(char), sizeof(employee->name), fileName);
				fwrite(&employee->age, sizeof(int), 1, fileName);
				fwrite(&employee->wage, sizeof(float), 1, fileName);
				fwrite(&employee->status, sizeof(int), 1, fileName);
			} else if (tempEmp->pointer == -1) {
				freePos = emp_findFreePosition(fileName, j);
				fseek(fileName, freePos*emp_sizeofEmployee(), SEEK_SET);
				fwrite(&employee->code, sizeof(int), 1, fileName);
				fwrite(employee->name, sizeof(char), sizeof(employee->name), fileName);
				fwrite(&employee->age, sizeof(int), 1, fileName);
				fwrite(&employee->wage, sizeof(float), 1, fileName);
				fwrite(&employee->status, sizeof(int), 1, fileName);

				//setting pointer of the last position of the chain. Now its gonna point to the recent added position
				fseek(fileName, j * emp_sizeofEmployee() + emp_sizeofEmployee() - sizeof(int), SEEK_SET);
				fwrite(&freePos, sizeof(int), 1, fileName);

			} else {
				printf(" - Overflow -\n");
				exit(0);
			}
		}
	}
}

void emp_removeEmployee(FILE *fileName, int key){
	int mappedPos,i=0,pos,j;
	Employee * tempEmp = (Employee*) malloc(sizeof(Employee));

	// mappedPos = hashFunction(key, HASH_SIZE);


	pos = emp_findEmployee(fileName, key);

	fseek(fileName, pos*emp_sizeofEmployee(), SEEK_SET);
	emp_readEmployee(tempEmp, fileName);

	if(tempEmp->code == key){
		int nextInChain = tempEmp->pointer;
		j = pos;

		while(i < HASH_SIZE){
			fseek(fileName, j*emp_sizeofEmployee(), SEEK_SET);
			emp_readEmployee(tempEmp, fileName);

			if(tempEmp->pointer == pos){
				fseek(fileName, j*emp_sizeofEmployee()+emp_sizeofEmployee()-sizeof(int), SEEK_SET);
				fwrite(&nextInChain, sizeof(int), 1, fileName);
				//i = 0;
			}//else{
				j = (j+1) % HASH_SIZE;
				i++;
			//}
		}
		int t = -1;
		tempEmp->status = 0;
		fseek(fileName, pos*emp_sizeofEmployee()+emp_sizeofEmployee()-sizeof(int)-sizeof(int), SEEK_SET);
		fwrite(&tempEmp->status, sizeof(int),1,fileName);
		// fwrite(&t, sizeof(int), 1, fileName);
	}else{
		printf("\nDumb user! Client does not exist!!!\n");
	}
}

void emp_updateEmployee(int key, char *name, FILE *fileName){
	int pos;

	pos = emp_findEmployee(fileName,key);

	if(pos == -1){
		printf("Dumb user! this client does not exist!!\n");
	}else{
		fseek(fileName, (pos * emp_sizeofEmployee()) + sizeof(int), SEEK_SET);
		fwrite(name, sizeof(char), sizeof(name), fileName);
	}
}

void emp_createHash(int size, FILE *hashfile){
	Employee *emp = (Employee *) malloc(sizeof(Employee));
	if (emp) memset(emp, 0, sizeof(Employee));

	emp->code = -1;
	emp->age = -1;
	emp->wage = -1.0;
	emp->status = 0;
	emp->pointer = -1;


	for(int i=0; i< HASH_SIZE;i++){
		emp_writeEmployee(emp, hashfile, i, emp_sizeofEmployee());
	}
}


void emp_printEmployees(FILE *empFile){
	Employee *emp = (Employee *) malloc(sizeof(Employee));
	rewind(empFile);
	while(emp_readEmployee(emp, empFile)){
		printf("\n-----------------\n");
		printf("Code: %d\n",emp->code);
		printf("Name: %s\n", emp->name);
		printf("Age: %d\n", emp->age);
		printf("Wage: %.2f\n", emp->wage );
		printf("Status: %d\n", emp->status );
		printf("Pointer: %d\n", emp->pointer );

	}
	free(emp);
}
