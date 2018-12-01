#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_common.c"

/*
typedef struct Dependent {
	int code;
	char name[100];
	int age;
	int employee_code;
	int status; // 1 used, 0 free
	int pointer;
} Dependent;

typedef struct Employee {
	int code;
	char name[100];
	int age;
	float wage;
	int status; // 1 used, 0 free
	int pointer;
} Employee;
*/

int dep_sizeofDependent() {
	return sizeof(int)  //code
	+ sizeof(char) * 100 //cname
	+ sizeof(int) //age
	+ sizeof(int) //wage
	+ sizeof(int) // status
	+ sizeof(int); //pointer
}
//feito
int dep_readDependent(Dependent * dependent, FILE *fileName){
	return (fread(&dependent->code, sizeof(int), 1, fileName) &&
	fread(dependent->name, sizeof(char), sizeof(dependent->name), fileName) &&
	fread(&dependent->age, sizeof(int), 1, fileName) &&
	fread(&dependent->employee_code, sizeof(int), 1, fileName) &&
	fread(&dependent->status, sizeof(int), 1, fileName) &&
	fread(&dependent->pointer, sizeof(int), 1, fileName));

}

void dep_writeDependent(Dependent *dependent, FILE *fileName, int filePos, int size){
	fseek(fileName, filePos * size, SEEK_SET);
	fwrite(&dependent->code, sizeof(int), 1, fileName);
	fwrite(dependent->name, sizeof(char), sizeof(dependent->name), fileName);
	fwrite(&dependent->age, sizeof(int), 1, fileName);
	fwrite(&dependent->employee_code, sizeof(int), 1, fileName);
	fwrite(&dependent->status, sizeof(int), 1, fileName);
	fwrite(&dependent->pointer, sizeof(int), 1, fileName);
}


int dep_findFreePosition(FILE *fileName, int mappedPos){
	Dependent * dependent = (Dependent*) malloc(sizeof(Dependent));
	int i = 0, j = mappedPos;

	while(i < HASH_SIZE){
		fseek(fileName, j*dep_sizeofDependent(), SEEK_SET);
		dep_readDependent(dependent, fileName);

		if(dependent->status == 0){
			return j;
		}
		j = (j + 1) % HASH_SIZE;
		i++;
	}
	printf(" - Overflow -");
	exit(0);
}
//feito
int dep_findDependent(FILE *fileName, int key){
	int i = 0, j;
	Dependent *tempDep = (Dependent *) malloc(sizeof(Dependent));

	j = hashFunction(key, HASH_SIZE);

	while(i < HASH_SIZE){
		fseek(fileName, j*dep_sizeofDependent(), SEEK_SET);
		dep_readDependent(tempDep, fileName);

		if(tempDep->code == key){
			return j;//return client position
		}
		j = tempDep->pointer;
		i++;
	}
	return -1;//client not found
}
//feito
void dep_insertDependent(Dependent *dependent, FILE *fileName){
	int mappedPos, freePos;
	Dependent *tempDep = (Dependent *) malloc(sizeof(Dependent));

	mappedPos = hashFunction(dependent->code, HASH_SIZE);
	dependent->status = 1;


	if (dep_findDependent(fileName, dependent->code) != -1) {
		printf("Dumb user! Dependent already exists.\n");
	} else {
		fseek(fileName, mappedPos*dep_sizeofDependent(), SEEK_SET);
		dep_readDependent(tempDep, fileName);

		if (tempDep->status == 0) { //Position is available
			fseek(fileName, mappedPos*dep_sizeofDependent(), SEEK_SET);
			fwrite(&dependent->code, sizeof(int), 1, fileName);
			fwrite(dependent->name, sizeof(char), sizeof(dependent->name), fileName);
			fwrite(&dependent->age, sizeof(int), 1, fileName);
			fwrite(&dependent->employee_code, sizeof(int), 1, fileName);
			fwrite(&dependent->status, sizeof(int), 1, fileName);
		} else {
			int i, j = mappedPos;

			while(i < HASH_SIZE){
				fseek(fileName, j*dep_sizeofDependent(), SEEK_SET);
				dep_readDependent(tempDep, fileName);

				if(tempDep->status == 0 || tempDep->pointer == -1){
					break;
				}
				j = tempDep->pointer;
				i++;
			}

			if (tempDep->status == 0) {
				fseek(fileName, j*dep_sizeofDependent(), SEEK_SET);
				fwrite(&dependent->code, sizeof(int), 1, fileName);
				fwrite(dependent->name, sizeof(char), sizeof(dependent->name), fileName);
				fwrite(&dependent->age, sizeof(int), 1, fileName);
				fwrite(&dependent->employee_code, sizeof(float), 1, fileName);
				fwrite(&dependent->status, sizeof(int), 1, fileName);
			} else if (tempDep->pointer == -1) {
				freePos = dep_findFreePosition(fileName, j);
				fseek(fileName, freePos*dep_sizeofDependent(), SEEK_SET);
				fwrite(&dependent->code, sizeof(int), 1, fileName);
				fwrite(dependent->name, sizeof(char), sizeof(dependent->name), fileName);
				fwrite(&dependent->age, sizeof(int), 1, fileName);
				fwrite(&dependent->employee_code, sizeof(int), 1, fileName);
				fwrite(&dependent->status, sizeof(int), 1, fileName);

				//setting pointer of the last position of the chain. Now its gonna point to the recent added position
				fseek(fileName, j * dep_sizeofDependent() + dep_sizeofDependent() - sizeof(int), SEEK_SET);
				fwrite(&freePos, sizeof(int), 1, fileName);

			} else {
				printf(" - Overflow -\n");
				exit(0);
			}
		}
	}
}
//feito
void dep_removeDependent(FILE *fileName, int key){
	int mappedPos,i=0,pos,j;
	Dependent * tempDep = (Dependent*) malloc(sizeof(Dependent));

	// mappedPos = hashFunction(key, HASH_SIZE);


	pos = dep_findDependent(fileName, key);

	fseek(fileName, pos*dep_sizeofDependent(), SEEK_SET);
	dep_readDependent(tempDep, fileName);

	if(tempDep->code == key){
		int nextInChain = tempDep->pointer;
		j = pos;

		while(i < HASH_SIZE){
			fseek(fileName, j*dep_sizeofDependent(), SEEK_SET);
			dep_readDependent(tempDep, fileName);

			if(tempDep->pointer == pos){
				fseek(fileName, j*dep_sizeofDependent()+dep_sizeofDependent()-sizeof(int), SEEK_SET);
				fwrite(&nextInChain, sizeof(int), 1, fileName);
				//i = 0;
			}//else{
				j = (j+1) % HASH_SIZE;
				i++;
			//}
		}
		int t = -1;
		tempDep->status = 0;
		fseek(fileName, pos*dep_sizeofDependent()+dep_sizeofDependent()-sizeof(int)-sizeof(int), SEEK_SET);
		fwrite(&tempDep->status, sizeof(int),1,fileName);
		// fwrite(&t, sizeof(int), 1, fileName);
	}else{
		printf("\nDumb user! Client does not exist!!!\n");
	}
}
//feito
void dep_updateDependent(int key, char *name, FILE *fileName){
	int pos;

	pos = dep_findDependent(fileName,key);

	if(pos == -1){
		printf("Dumb user! this client does not exist!!\n");
	}else{
		fseek(fileName, (pos * dep_sizeofDependent()) + sizeof(int), SEEK_SET);
		fwrite(name, sizeof(char), sizeof(name), fileName);
	}
}
//feito
void dep_createHash(int size, FILE *hashfile){
	Dependent *dep = (Dependent *) malloc(sizeof(Dependent));
	if (dep) memset(dep, 0, sizeof(Dependent));

	dep->code = -1;
	dep->age = -1;
	dep->employee_code = -1;
	dep->status = 0;
	dep->pointer = -1;


	for(int i=0; i< HASH_SIZE;i++){
		dep_writeDependent(dep, hashfile, i, dep_sizeofDependent());
	}
	fclose(hashfile);
}

/*
typedef struct Dependent {
	int code;
	char name[100];
	int age;
	int employee_code;
	int status; // 1 used, 0 free
	int pointer;
} Dependent;
*/
//feito
void dep_printDependents(FILE *depFile){
	Dependent *dep = (Dependent *) malloc(sizeof(Dependent));
	rewind(depFile);
	while(dep_readDependent(dep, depFile)){
		printf("\n-----------------\n");
		printf("Code: %d\n",dep->code);
		printf("Name: %s\n", dep->name);
		printf("Age: %d\n", dep->age );
		printf("Employee Code: %d\n", dep->employee_code);
		printf("Status: %d\n", dep->status );
		printf("Pointer: %d\n", dep->pointer );

	}
	free(dep);
}
