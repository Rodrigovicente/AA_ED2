#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "hash.h"

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
	int a6_prox
} Employee;

int registerSize() {
	return sizeof(int)  // code
	+ sizeof(char) * 100 // anme
	+ sizeof(int) // age
	+ sizeof(float) // wage
	+ sizeof(int) // disc_addr
	+ sizeof(int) // a5_pt
	+ sizeof(int) // a5_q
	+ sizeof(int); // a6_prox
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

		default:
			break;
	}
}

void writeLine(Employee_lk *row, FILE *fileName_1, FILE *fileName_2, FILE *fileName_3, int table_id){
	switch (table_id) {
		case 2:
			fwrite(&row->disc_addr, sizeof(int), 1, fileName);
			fwrite(&row->code, sizeof(int), 1, fileName);
			fwrite(row->name, sizeof(char), sizeof(row->name), fileName);
			fwrite(&row->age, sizeof(int), 1, fileName);
			fwrite(&row->wage, sizeof(float), 1, fileName);
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
			fwrite(&row->code, sizeof(int), 1, fileName_1);;
			fwrite(&row->age, sizeof(int), 1, fileName_1);
			break;

		case 43:
			fwrite(&row->disc_addr, sizeof(int), 1, fileName_1);
			fwrite(&row->code, sizeof(int), 1, fileName_1);;
			fwrite(&row->wage, sizeof(float), 1, fileName_1);
			break;


		default:
			break;
	}
}



void createA2File(Employee_lk * row, FILE* input, FILE *output){
	int discAddress = 0;
	while(readLine(row, input, 1)){
		// fwrite(&fileAddress, sizeof(int),1,output);
		row.disc_addr = discAddress;
		//printRow(row);
		writeLine(row, output, NULL, NULL, 2);
		discAddress++;
	}
}

void createA3File(Employee_lk * row, FILE* input, FILE *output_name, FILE *output_age, FILE *output_wage){
	rewind(input);
	while (readLine(row, input, 2)) {
		writeLine(row, output_name, output_age, output_wage, 3);
	}
}

int createA4File(Register * row, FILE* input, FILE *output_name, FILE *output_age, FILE *output_wage){
	int fileAddress, minorAddress, rowCode, minorCode, age;
	int minorAge = INT_MAX;
	int maxAge = INT_MAX;
	int written = 1;
	while(1) {
		rewind(input);
		minorAge = INT_MAX;
		while (fread(&fileAddress, sizeof(int), 1, input) && fread(&rowCode, sizeof(int), 1, input) && fread(&age, sizeof(int), 1, input)) {
			if(age < minorAge) {
				minorAddress = fileAddress;
				minorAge = age;
				minorCode = rowCode;
			}
		}

		if(minorAge == INT_MAX)
			break;
		fseek(input, (minorAddress * (sizeof(int) *3)) + (sizeof(int) *2), SEEK_SET);
		fwrite(&maxAge, sizeof(int), 1, input);
		fwrite(&minorAddress, sizeof(int),1,output);
		fwrite(&minorCode, sizeof(int), 1, output);
		fwrite(&minorAge, sizeof(int), 1, output);
	}

}

int createA5File(Register * row, FILE* input, FILE *output){
	int fileAddress, clientCode, age, usedAddress = -1;
	int chosenAddress, chosenCode, chosenAge;
	int i = 1, j = 0;
	int count = 1;
	while(fread(&chosenAddress, sizeof(int), 1, input) && fread(&chosenCode, sizeof(int), 1, input) && fread(&chosenAge, sizeof(int), 1, input))
	{
		while(fread(&fileAddress, sizeof(int), 1, input) && fread(&clientCode, sizeof(int), 1, input) && fread(&age, sizeof(int), 1, input))
		{
		  if(chosenAddress == -1)
		    break;
		  i++;
		  if(chosenAge == age){
		    fseek(input, - sizeof(int) *3, SEEK_CUR);
		    fwrite(&usedAddress, sizeof(int), 1, input);
		    fseek(input, sizeof(int) *2, SEEK_CUR);
		    count++;
		  }
		}
		if(chosenAddress != -1){
		  fwrite(&chosenAge, sizeof(int), 1, output);
		  fwrite(&chosenAddress, sizeof(int), 1, output);
		  fwrite(&count, sizeof(int), 1, output);
		}
		count = 1;
		j++;
		fseek(input, j * sizeof(int) * 3, SEEK_SET);

	}
	}
