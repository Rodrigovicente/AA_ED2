#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Register {
    int rowCode;
    char name[100];
    int age;
} Register;

int registerSize() {
    return sizeof(int)  // clientCode
    + sizeof(char) * 100 //clientName
    + sizeof(int); // status
}

int readLine(Register * row, FILE *fileName){
    return (fread(&row->rowCode, sizeof(int), 1, fileName) &&
    fread(row->name, sizeof(char), sizeof(row->name), fileName) &&
    fread(&row->age, sizeof(int), 1, fileName));
}

void printRow(Register * row){
  printf("Code: %d\n", row->rowCode);
  printf("Name: %s\n", row->name);
  printf("Age: %d\n", row->age);
  printf("------------------------------\n");

}

void writeRegister(Register *row, FILE *fileName){
    fwrite(&row->rowCode, sizeof(int), 1, fileName);
    fwrite(row->name, sizeof(char), sizeof(row->name), fileName);
    fwrite(&row->age, sizeof(int), 1, fileName);
}

int createA2File(Register * row, FILE* input, FILE *output){
  int fileAddress = 0;
  while(readLine(row, input)){
    fwrite(&fileAddress, sizeof(int),1,output);
    //printRow(row);
    writeRegister(row, output);
    fileAddress++;
  }
}

int createA3File(Register * row, FILE* input, FILE *output){
  int fileAddress;
  rewind(input);
  while(fread(&fileAddress, sizeof(int), 1, input) && readLine(row,input)){
    fwrite(&fileAddress, sizeof(int),1,output);
    fwrite(&row->rowCode, sizeof(int), 1, output);
    fwrite(&row->age, sizeof(int), 1, output);
  }
}

int createA4File(Register * row, FILE* input, FILE *output){
  int fileAddress, minorAddress, rowCode, minorCode, age;
  int minorAge = 999;
  int maxAge = 999;
  int written = 1;
  while(1){
    rewind(input);
    minorAge = 999;
    while(fread(&fileAddress, sizeof(int), 1, input) && fread(&rowCode, sizeof(int), 1, input) && fread(&age, sizeof(int), 1, input)){
      if(age < minorAge){
        minorAddress = fileAddress;
        minorAge = age;
        minorCode = rowCode;
      }
    }
    if(minorAge == 999)
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

int createA6File(Register * row, FILE* input, FILE *output){
  int fileAddress, clientCode, age, singleReg = -1;
  int chosenAddress, chosenCode, chosenAge;
  int j = 0;
  int equal = 0;
  while(fread(&chosenAddress, sizeof(int), 1, input) && fread(&chosenCode, sizeof(int), 1, input) && fread(&chosenAge, sizeof(int), 1, input))
  {
    while(fread(&fileAddress, sizeof(int), 1, input) && fread(&clientCode, sizeof(int), 1, input) && fread(&age, sizeof(int), 1, input))
    {
      if(chosenAge == age){
        fwrite(&chosenAddress, sizeof(int), 1, output);
        fwrite(&chosenCode, sizeof(int), 1, output);
        fwrite(&chosenAge, sizeof(int), 1, output);
        fwrite(&fileAddress, sizeof(int), 1, output);
        equal = 1;
        break;
      }
    }
    if(equal != 1){
      fwrite(&chosenAddress, sizeof(int), 1, output);
      fwrite(&chosenCode, sizeof(int), 1, output);
      fwrite(&chosenAge, sizeof(int), 1, output);
      fwrite(&singleReg, sizeof(int), 1, output);
    }
    j++;
    fseek(input, j * sizeof(int) * 3, SEEK_SET);
    equal = 0;
  }
}

int createA7File(Register * row, FILE* input, FILE *output){
  int fileAddress, minorAddress, rowCode, minorCode, age, minorAge, pointer, minorPointer;
  int minRowCode = 99999, i = 0, j;
  while(1){
    rewind(input);
    while(fread(&fileAddress, sizeof(int), 1, input) && fread(&rowCode, sizeof(int), 1, input) && fread(&age, sizeof(int), 1, input) && fread(&pointer, sizeof(int), 1, input)){
      if(rowCode < minRowCode){
        minRowCode = rowCode;
        minorAddress = fileAddress;
        minorCode = rowCode;
        minorAge = age;
        minorPointer = pointer;
        j = i;
      }
      i++;
    }
    if(minRowCode == 99999)
      break;
    minRowCode = 99999;
    i = 0;
    fseek(input, (j * (sizeof(int) *4)) + (sizeof(int)), SEEK_SET);
    fwrite(&minRowCode, sizeof(int), 1, input);
    fwrite(&minorAddress, sizeof(int), 1, output);
    fwrite(&minorCode, sizeof(int),1,output);
    fwrite(&minorAge, sizeof(int), 1, output);
    fwrite(&minorPointer, sizeof(int), 1, output);

  }

}
typedef struct RegisterA7 {
    int address,rowCode, age, pointer;
} RegisterA7;


int readLineA7(RegisterA7 * row, FILE *fileName){
    return (fread(&row->address, sizeof(int), 1, fileName) &&
    fread(&row->rowCode, sizeof(int), 1, fileName) &&
    fread(&row->age, sizeof(int), 1, fileName)&&
    fread(&row->pointer, sizeof(int), 1, fileName));
}

int createA8File(Register * row,RegisterA7 * rowA7, FILE* a1, FILE* a7, FILE *output){
  while(readLine(row,a1) && readLineA7(rowA7, a7)){
    fwrite(&row->rowCode, sizeof(int), 1, output);
    fwrite(row->name, sizeof(char), sizeof(row->name), output);
    fwrite(&row->age, sizeof(int),1,output);
    fwrite(&rowA7->pointer, sizeof(int), 1, output);

  }

}
