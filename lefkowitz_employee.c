#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define FLOAT_MAX 9999999.0

/*
Para funcionário:
	name (1)
	age (2)

Para dependente:
	employee_code (3, 4)
	name (5)
	age (6)


Extras:
	Para funcionário:
		wage - Quem ganha mais que um certo salário
		code - Nome do funcionario pelo codigo

	Para dependente:
		code = Nome do dependente pelo codigo

*/
 //


typedef struct Employee_lk {
	int code;
	char name[100];
	int age;
	float wage;
	int status;
	int pointer;
	int disc_addr;
	int a5_pt;
	int a5_q;
	int prox_1;
	int prox_2;
	int prox_3;
} Employee_lk;

int employee_lk_Size() {
	return sizeof(int)  // code
	+ sizeof(char) * 100 // anme
	+ sizeof(int) // age
	+ sizeof(float) // wage
	+ sizeof(int) // disc_addr
	+ sizeof(int) // a5_pt
	+ sizeof(int) // a5_q
	+ sizeof(int) // prox_1
	+ sizeof(int) // prox_2
	+ sizeof(int); // prox_3
}

int readLine(Employee_lk * row, FILE *fileName, int table_id){

	switch (table_id) {
		case 1:
			return (	fread(&row->code, sizeof(int), 1, fileName) &&
						fread(row->name, sizeof(char), sizeof(row->name), fileName) &&
						fread(&row->age, sizeof(int), 1, fileName) &&
						fread(&row->wage, sizeof(float), 1, fileName) &&
						fread(&row->status, sizeof(int), 1, fileName) &&
						fread(&row->pointer, sizeof(int), 1, fileName));
		case 2:
			return (	fread(&row->disc_addr, sizeof(int), 1, fileName) &&
						fread(&row->code, sizeof(int), 1, fileName) &&
						fread(row->name, sizeof(char), sizeof(row->name), fileName) &&
						fread(&row->age, sizeof(int), 1, fileName) &&
						fread(&row->wage, sizeof(float), 1, fileName));
		case 31:
			return (	fread(&row->disc_addr, sizeof(int), 1, fileName) &&
						fread(&row->code, sizeof(int), 1, fileName) &&
						fread(row->name, sizeof(char), sizeof(row->name), fileName));
		case 32:
			return (	fread(&row->disc_addr, sizeof(int), 1, fileName) &&
						fread(&row->code, sizeof(int), 1, fileName) &&
						fread(&row->age, sizeof(int), 1, fileName));
		case 33:
			return (	fread(&row->disc_addr, sizeof(int), 1, fileName) &&
						fread(&row->code, sizeof(int), 1, fileName) &&
						fread(&row->wage, sizeof(float), 1, fileName));
		case 41:
			return (	fread(&row->disc_addr, sizeof(int), 1, fileName) &&
						fread(&row->code, sizeof(int), 1, fileName) &&
						fread(row->name, sizeof(char), sizeof(row->name), fileName));
		case 42:
			return (	fread(&row->disc_addr, sizeof(int), 1, fileName) &&
						fread(&row->code, sizeof(int), 1, fileName) &&
						fread(&row->age, sizeof(int), 1, fileName));
		case 43:
			return (	fread(&row->disc_addr, sizeof(int), 1, fileName) &&
						fread(&row->code, sizeof(int), 1, fileName) &&
						fread(&row->wage, sizeof(float), 1, fileName));
		case 51:
			return (	fread(row->name, sizeof(char), sizeof(row->name), fileName) &&
						fread(&row->a5_q, sizeof(int), 1, fileName) &&
						fread(&row->a5_pt, sizeof(int), 1, fileName));
		case 52:
			return (	fread(&row->age, sizeof(int), 1, fileName) &&
						fread(&row->a5_q, sizeof(int), 1, fileName) &&
						fread(&row->a5_pt, sizeof(int), 1, fileName));
		case 53:
			return (	fread(&row->wage, sizeof(float), 1, fileName) &&
						fread(&row->a5_q, sizeof(int), 1, fileName) &&
						fread(&row->a5_pt, sizeof(int), 1, fileName));
		case 61:
			return (	fread(&row->disc_addr, sizeof(int), 1, fileName) &&
						fread(&row->code, sizeof(int), 1, fileName) &&
						fread(row->name, sizeof(char), sizeof(row->name), fileName) &&
						fread(&row->prox_1, sizeof(int), 1, fileName));
		case 62:
			return (	fread(&row->disc_addr, sizeof(int), 1, fileName) &&
						fread(&row->code, sizeof(int), 1, fileName) &&
						fread(&row->age, sizeof(int), 1, fileName) &&
						fread(&row->prox_1, sizeof(int), 1, fileName));
		case 63:
			return (	fread(&row->disc_addr, sizeof(int), 1, fileName) &&
						fread(&row->code, sizeof(int), 1, fileName) &&
						fread(&row->wage, sizeof(float), 1, fileName) &&
						fread(&row->prox_1, sizeof(int), 1, fileName));
		case 71:
			return (	fread(&row->disc_addr, sizeof(int), 1, fileName) &&
						fread(&row->code, sizeof(int), 1, fileName) &&
						fread(row->name, sizeof(char), sizeof(row->name), fileName) &&
						fread(&row->prox_1, sizeof(int), 1, fileName));
		case 72:
			return (	fread(&row->disc_addr, sizeof(int), 1, fileName) &&
						fread(&row->code, sizeof(int), 1, fileName) &&
						fread(&row->age, sizeof(int), 1, fileName) &&
						fread(&row->prox_2, sizeof(int), 1, fileName));
		case 73:
			return (	fread(&row->disc_addr, sizeof(int), 1, fileName) &&
						fread(&row->code, sizeof(int), 1, fileName) &&
						fread(&row->wage, sizeof(float), 1, fileName) &&
						fread(&row->prox_3, sizeof(int), 1, fileName));

		default:
			break;
	}
}

void writeLine(Employee_lk *row, FILE *fileName_1, FILE *fileName_2, FILE *fileName_3, int table_id){
	switch (table_id) {
		case 2:
			fwrite(&row->disc_addr, sizeof(int), 1, fileName_1);
			fwrite(&row->code, sizeof(int), 1, fileName_1);
			fwrite(row->name, sizeof(char), sizeof(row->name), fileName_1);
			fwrite(&row->age, sizeof(int), 1, fileName_1);
			fwrite(&row->wage, sizeof(float), 1, fileName_1);
			break;

		case 3:
			fwrite(&row->disc_addr, sizeof(int), 1, fileName_1);
			fwrite(&row->disc_addr, sizeof(int), 1, fileName_2);
			fwrite(&row->disc_addr, sizeof(int), 1, fileName_3);

			fwrite(&row->code, sizeof(int), 1, fileName_1);
			fwrite(&row->code, sizeof(int), 1, fileName_2);
			fwrite(&row->code, sizeof(int), 1, fileName_3);

			fwrite(row->name, sizeof(char), sizeof(row->name), fileName_1);
			fwrite(&row->age, sizeof(int), 1, fileName_2);
			fwrite(&row->wage, sizeof(float), 1, fileName_3);
			break;

		case 41:
			fwrite(&row->disc_addr, sizeof(int), 1, fileName_1);
			fwrite(&row->code, sizeof(int), 1, fileName_1);
			fwrite(row->name, sizeof(char), sizeof(row->name), fileName_1);
			break;

		case 42:
			fwrite(&row->disc_addr, sizeof(int), 1, fileName_1);
			fwrite(&row->code, sizeof(int), 1, fileName_1);
			fwrite(&row->age, sizeof(int), 1, fileName_1);
			break;

		case 43:
			fwrite(&row->disc_addr, sizeof(int), 1, fileName_1);
			fwrite(&row->code, sizeof(int), 1, fileName_1);
			fwrite(&row->wage, sizeof(float), 1, fileName_1);
			break;

		case 71:
			fwrite(&row->disc_addr, sizeof(int), 1, fileName_1);
			fwrite(&row->code, sizeof(int), 1, fileName_1);
			fwrite(row->name, sizeof(char), sizeof(row->name), fileName_1);
			fwrite(&row->prox_1, sizeof(int), 1, fileName_1);
			break;

		case 72:
			fwrite(&row->disc_addr, sizeof(int), 1, fileName_1);
			fwrite(&row->code, sizeof(int), 1, fileName_1);
			fwrite(&row->age, sizeof(int), 1, fileName_1);
			fwrite(&row->prox_1, sizeof(int), 1, fileName_1);
			break;

		case 73:
			fwrite(&row->disc_addr, sizeof(int), 1, fileName_1);
			fwrite(&row->code, sizeof(int), 1, fileName_1);
			fwrite(&row->wage, sizeof(float), 1, fileName_1);
			fwrite(&row->prox_1, sizeof(int), 1, fileName_1);
			break;

		case 8:
			fwrite(&row->code, sizeof(int), 1, fileName_1);
			fwrite(row->name, sizeof(char), sizeof(row->name), fileName_1);
			fwrite(&row->age, sizeof(int), 1, fileName_1);
			fwrite(&row->wage, sizeof(float), 1, fileName_1);
			fwrite(&row->prox_1, sizeof(int), 1, fileName_1);
			fwrite(&row->prox_2, sizeof(int), 1, fileName_1);
			fwrite(&row->prox_3, sizeof(int), 1, fileName_1);
			break;

		default:
			break;
	}
}



void createA2File(FILE* input, FILE *output){
	Employee_lk * row = (Employee_lk*) malloc(sizeof(Employee_lk));

	int discAddress = 0;
	while(readLine(row, input, 1)){
		// fwrite(&fileAddress, sizeof(int),1,output);
		row->disc_addr = discAddress;
		//printRow(row);
		writeLine(row, output, NULL, NULL, 2);
		discAddress++;
	}
	free(row);
}

void createA3File(FILE* input, FILE *output_name, FILE *output_age, FILE *output_wage){
	Employee_lk * row = (Employee_lk*) malloc(sizeof(Employee_lk));

	rewind(input);
	while (readLine(row, input, 2)) {
		writeLine(row, output_name, output_age, output_wage, 3);
	}
}

int createA4File(FILE* input_name, FILE* input_age, FILE* input_wage, FILE *output_name, FILE *output_age, FILE *output_wage){
	Employee_lk * row = (Employee_lk*) malloc(sizeof(Employee_lk));

	int sizeofRow;
	Employee_lk minEmployee;

	int maxAge = INT_MAX;
	//int minAge;

	char maxName[100] = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
	//char minName[100];

	float maxWage = FLOAT_MAX;
	//float minWage;

	strcpy(minEmployee.name, maxName);
	minEmployee.age = maxAge;
	minEmployee.wage = maxWage;
	// AGE
	sizeofRow = sizeof(int) * 2 + sizeof(int);
	while(1) {
		rewind(input_age);
		minEmployee.age = maxAge;
		while (readLine(row, input_age, 32)) {
			if(row->age < minEmployee.age) {
				minEmployee = *row;
			}
		}

		if(minEmployee.age == maxAge)
			break;
		fseek(input_age, (minEmployee.disc_addr * sizeofRow + (sizeof(int) * 2)), SEEK_SET);
		fwrite(&maxAge, sizeof(int), 1, input_age);
		writeLine(&minEmployee, output_age, NULL, NULL, 42);
	}
	// NAME
	sizeofRow = sizeof(int) * 2 + sizeof(char) * sizeof(row->name);
	while(1) {
		rewind(input_name);
		strcpy(minEmployee.name, maxName);
		while (readLine(row, input_name, 31)) {
			if(strcmp(row->name, minEmployee.name) < 0) {
				minEmployee = *row;
			}
		}

		if(strcmp(minEmployee.name, maxName) == 0)
			break;

		fseek(input_name, (minEmployee.disc_addr * sizeofRow + (sizeof(int) * 2)), SEEK_SET);
		fwrite(&maxName, sizeof(char), sizeof(row->name), input_name);
		writeLine(&minEmployee, output_name, NULL, NULL, 41);
	}
	// WAGE
	sizeofRow = sizeof(int) * 2 + sizeof(float);
	while(1) {
		rewind(input_wage);
		minEmployee.wage = maxWage;
		while (readLine(row, input_wage, 33)) {
			if(row->wage < minEmployee.wage) {
				minEmployee = *row;
			}
		}

		if(minEmployee.wage == maxWage)
			break;

		fseek(input_wage, (minEmployee.disc_addr * sizeofRow + (sizeof(int) * 2)), SEEK_SET);
		fwrite(&maxWage, sizeof(float), 1, input_wage);
		writeLine(&minEmployee, output_wage, NULL, NULL, 43);
	}

}

int createA5File(FILE* input_1, FILE* input_2, FILE* input_3, FILE *output_1, FILE *output_2, FILE *output_3){
	Employee_lk * row = (Employee_lk*) malloc(sizeof(Employee_lk));
	int fileAddress, code, age, usedAddress = -1, wage;
	int chosenAddress, chosenCode, chosenAge, chosenWage;
	char name[100];
	char chosenName[100];
	int i = 1, j = 0;
	int count = 1;

	rewind(input_1);
	rewind(input_2);
	rewind(input_3);

	while(readLine(row, input_1, 41)) {
		chosenAddress = row->a5_pt;
		chosenCode = row->code;
		strcpy(chosenName, row->name);
		while(readLine(row, input_1, 41))
		{
			fileAddress = row->a5_pt;
			code = row->code;
			strcpy(name, row->name);
			if(chosenAddress == -1)
				break;

			i++;
			if(strcmp(chosenName, name) == 0){
				fseek(input_1, - (sizeof(int) *2) - (sizeof(char) * 100), SEEK_CUR);
				fwrite(&usedAddress, sizeof(int), 1, input_1);
				fseek(input_1, sizeof(int) + (sizeof(char) * 100), SEEK_CUR);
				count++;
			}
		}
		if(chosenAddress != -1){
			fwrite(chosenName, sizeof(char) * 100, 1, output_1);
			fwrite(&chosenAddress, sizeof(int), 1, output_1);
			fwrite(&count, sizeof(int), 1, output_1);
		}
		count = 1;
		j++;
		fseek(input_1, j * (sizeof(int) *2) + (sizeof(char) * 100), SEEK_SET);
	}
	i = 1; j = 0;
	count = 1;
	while(readLine(row, input_2, 42))
	{
		chosenAddress = row->a5_pt;
		chosenCode = row->code;
		chosenAge = row->age;
		while(readLine(row, input_2, 42))
		{
			fileAddress = row->a5_pt;
			code = row->code;
			age = row->age;
			if(chosenAddress == -1)
				break;

			i++;
			if(chosenAge == age){
				fseek(input_2, - sizeof(int) * 3, SEEK_CUR);
				fwrite(&usedAddress, sizeof(int), 1, input_2);
				fseek(input_2, sizeof(int)*2, SEEK_CUR);
				count++;
			}
		}
		if(chosenAddress != -1){
			fwrite(&chosenAge, sizeof(int), 1, output_2);
			fwrite(&chosenAddress, sizeof(int), 1, output_2);
			fwrite(&count, sizeof(int), 1, output_2);
		}
		count = 1;
		j++;
		fseek(input_2, j * sizeof(int) *3, SEEK_SET);
	}

	i = 1; j = 0;
	count = 1;
	while(readLine(row, input_3, 43))
	{
		chosenAddress = row->a5_pt;
		chosenCode = row->code;
		chosenWage = row->wage;
		while(readLine(row, input_3, 43))
		{
			fileAddress = row->a5_pt;
			code = row->code;
			wage = row->wage;
			if(chosenAddress == -1)
				break;

			i++;
			if(wage == chosenWage){
				fseek(input_3, - sizeof(int) * 2 + sizeof(float), SEEK_CUR);
				fwrite(&usedAddress, sizeof(int), 1, input_3);
				fseek(input_3, sizeof(int) + sizeof(float), SEEK_CUR);
				count++;
			}
		}
		if(chosenAddress != -1){
			fwrite(&chosenWage, sizeof(float), 1, output_3);
			fwrite(&chosenAddress, sizeof(int), 1, output_3);
			fwrite(&count, sizeof(int), 1, output_3);
		}
		count = 1;
		j++;
		fseek(input_3, j * sizeof(int) *2 + sizeof(float), SEEK_SET);
	}
}

int createA6File(Employee_lk * row, FILE* input_1, FILE* input_2, FILE* input_3, FILE *output_1, FILE *output_2, FILE *output_3){
	int fileAddress, code, age, usedAddress = -1, wage;
	int chosenAddress, chosenCode, chosenAge, chosenWage;
	char name[100], chosenName[100];
	int j = 0;
    int equal = 0;

	while(readLine(row, input_1, 51))
	{
		chosenAddress = row->disc_addr;
		chosenCode = row->code;
		strcpy(chosenName, row->name);
		while(readLine(row, input_1, 51))
		{
			if(strcmp(chosenName, row->name) == 0){
		        fwrite(&chosenAddress, sizeof(int), 1, output_1);
		        fwrite(&chosenCode, sizeof(int), 1, output_1);
		        fwrite(chosenName, sizeof(char) * 100, 1, output_1);
		        fwrite(&fileAddress, sizeof(int), 1, output_1);
		        equal = 1;
		        break;
	        }
		}
		if(equal != 1){
			fwrite(&chosenAddress, sizeof(int), 1, output_1);
			fwrite(&chosenCode, sizeof(int), 1, output_1);
			fwrite(chosenName, sizeof(int), 1, output_1);
			fwrite(&usedAddress, sizeof(int), 1, output_1);
		}
		j++;
		fseek(input_1, j * (sizeof(int) * 2) + (sizeof(char) * 100), SEEK_SET);
		equal = 0;
	}
	j = 0;
	equal = 0;

	while(readLine(row, input_2, 52))
	{
		chosenAddress = row->disc_addr;
		chosenCode = row->code;
		chosenAge = row->age;
		while(readLine(row, input_2, 52))
		{
			if(chosenAge == row->age){
				fwrite(&chosenAddress, sizeof(int), 1, output_2);
				fwrite(&chosenCode, sizeof(int), 1, output_2);
				fwrite(&chosenAge, sizeof(int), 1, output_2);
				fwrite(&fileAddress, sizeof(int), 1, output_2);
				equal = 1;
				break;
			}
		}
		if(equal != 1){
			fwrite(&chosenAddress, sizeof(int), 1, output_2);
			fwrite(&chosenCode, sizeof(int), 1, output_2);
			fwrite(&chosenAge, sizeof(int), 1, output_2);
			fwrite(&usedAddress, sizeof(int), 1, output_2);
		}
		j++;
		fseek(input_2, j * sizeof(int) * 3, SEEK_SET);
		equal = 0;
	}
	j = 0;
	equal = 0;

	while(readLine(row, input_3, 53))
	{
		chosenAddress = row->disc_addr;
		chosenCode = row->code;
		chosenWage = row->wage;
		while(readLine(row, input_3, 53))
		{
			if(chosenWage == row->wage){
				fwrite(&chosenAddress, sizeof(int), 1, output_3);
				fwrite(&chosenCode, sizeof(int), 1, output_3);
				fwrite(&chosenWage, sizeof(float), 1, output_3);
				fwrite(&fileAddress, sizeof(int), 1, output_3);
				equal = 1;
				break;
			}
		}
		if(equal != 1){
			fwrite(&chosenAddress, sizeof(int), 1, output_3);
			fwrite(&chosenCode, sizeof(int), 1, output_3);
			fwrite(chosenName, sizeof(float), 1, output_3);
			fwrite(&usedAddress, sizeof(int), 1, output_3);
		}
		j++;
		fseek(input_3, j * sizeof(int) * 2 + sizeof(float), SEEK_SET);
		equal = 0;
	}
}

void createA7File(Employee_lk * row, FILE* input, FILE *output, int col){

		// col = 1 p/ name
		// col = 2 p/ age
		// col = 3 p/ wage

	Employee_lk minEmployee;
	int i, pos_min, sizeofRow;

	int maxCode = INT_MAX;
	minEmployee.code = maxCode;

	switch (col) {
		case 1:
			sizeofRow = sizeof(int) * 2 + sizeof(char) * sizeof(row->name);
			break;
		case 2:
			sizeofRow = sizeof(int) * 3 + sizeof(int);
			break;
		case 3:
			sizeofRow = sizeof(int) * 3 + sizeof(float);
			break;
		default:
			return ;
	}

	while (1) {
		rewind(input);
		minEmployee.code = maxCode;
		i = 0;
		while (readLine(row, input, (60 + col))) {
			if(row->code < minEmployee.code){
				minEmployee = *row;

				pos_min = i;
			}
			i++;
		}
		if(minEmployee.code == maxCode)
			break;
		fseek(input, (pos_min * sizeofRow + (sizeof(int))), SEEK_SET);
		fwrite(&maxCode, sizeof(int), 1, input);

		writeLine(&minEmployee, output, NULL, NULL, (70 + col));

	}
}

void createA8File(Employee_lk * row_a1, Employee_lk * row_a7_name, Employee_lk * row_a7_age, Employee_lk * row_a7_wage, FILE* a1, FILE* a7_name, FILE* a7_age, FILE* a7_wage, FILE *output){
	Employee_lk row_a8;

	while(readLine(row_a1, a1, 1) && readLine(row_a7_name, a7_name, 71) && readLine(row_a7_age, a7_age, 72) && readLine(row_a7_wage, a7_wage, 72)){
		row_a8 = *row_a1;
		row_a8.prox_1 = row_a7_name->prox_1;
		row_a8.prox_2 = row_a7_age->prox_2;
		row_a8.prox_3 = row_a7_wage->prox_3;

		writeLine(&row_a8, output, NULL, NULL, 8);

		// fwrite(&row_a1->code, sizeof(int), 1, output);
		// fwrite(row_a1->name, sizeof(char), sizeof(row->name), output);
		// fwrite(&row_a1->age, sizeof(int), 1,output);
		// fwrite(&row_a1->wage, sizeof(float), 1,output);
		// fwrite(&row_a7_name->prox_1, sizeof(int), 1, output);
		// fwrite(&row_a7_age->prox_2, sizeof(int), 1, output);
		// fwrite(&row_a7_wage->prox_3, sizeof(int), 1, output);
	}

}

void printTableA2(FILE *tableFile){
	Employee_lk *emp = (Employee_lk *) malloc(sizeof(Employee_lk));
	rewind(tableFile);
	while(readLine(emp, tableFile, 2)){
		printf("\n-----------------\n");
		printf("disc_addr: %d\n",emp->disc_addr);
		printf("code: %d\n", emp->code);
		printf("name: %s\n", emp->name);
		printf("age: %d\n", emp->age );
		printf("wage: %.2f\n", emp->wage );

	}
	free(emp);
}

void printTableA3(FILE *tableFile, int col) {
	Employee_lk *emp = (Employee_lk *) malloc(sizeof(Employee_lk));
	rewind(tableFile);
	switch (col) {
		case 1:
			while(readLine(emp, tableFile, 31)){
				printf("\n-----------------\n");
				printf("disc_addr: %d\n",emp->disc_addr);
				printf("code: %d\n", emp->code);
				printf("name: %s\n", emp->name);
			}
		break;
		case 2:
			while(readLine(emp, tableFile, 32)){
				printf("\n-----------------\n");
				printf("disc_addr: %d\n",emp->disc_addr);
				printf("code: %d\n", emp->code);
				printf("age: %d\n", emp->age );
			}
			break;
		case 3:
			while(readLine(emp, tableFile, 33)){
				printf("\n-----------------\n");
				printf("disc_addr: %d\n",emp->disc_addr);
				printf("code: %d\n", emp->code);
				printf("wage: %.2f\n", emp->wage );
			}
			break;

	}
	free(emp);
}

void printTableA4(FILE *tableFile, int col) {
	Employee_lk *emp = (Employee_lk *) malloc(sizeof(Employee_lk));
	rewind(tableFile);
	switch (col) {
		case 1:
			while(readLine(emp, tableFile, 41)){
				printf("\n-----------------\n");
				printf("disc_addr: %d\n",emp->disc_addr);
				printf("code: %d\n", emp->code);
				printf("name: %s\n", emp->name);
			}
		break;
		case 2:
			while(readLine(emp, tableFile, 42)){
				printf("\n-----------------\n");
				printf("disc_addr: %d\n",emp->disc_addr);
				printf("code: %d\n", emp->code);
				printf("age: %d\n", emp->age );
			}
			break;
		case 3:
			while(readLine(emp, tableFile, 43)){
				printf("\n-----------------\n");
				printf("disc_addr: %d\n",emp->disc_addr);
				printf("code: %d\n", emp->code);
				printf("wage: %.2f\n", emp->wage );
			}
			break;

	}
	free(emp);
}

void printTableA5(FILE *tableFile, int col) {
	Employee_lk *emp = (Employee_lk *) malloc(sizeof(Employee_lk));
	rewind(tableFile);
	switch (col) {
		case 1:
			while(readLine(emp, tableFile, 51)){
				printf("\n-----------------\n");
				printf("name: %s\n", emp->name);
				printf("a5_pt: %d\n", emp->a5_pt);
				printf("a5_q: %d\n", emp->a5_q);
			}
		break;
		case 2:
			while(readLine(emp, tableFile, 52)){
				printf("\n-----------------\n");
				printf("age: %d\n", emp->age );
				printf("a5_pt: %d\n", emp->a5_pt);
				printf("a5_q: %d\n", emp->a5_q);
			}
			break;
		case 3:
			while(readLine(emp, tableFile, 53)){
				printf("\n-----------------\n");
				printf("wage: %.2f\n", emp->wage );
				printf("a5_pt: %d\n", emp->a5_pt);
				printf("a5_q: %d\n", emp->a5_q);
			}
			break;

	}
	free(emp);
}
