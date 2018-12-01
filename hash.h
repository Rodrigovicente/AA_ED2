
#define HASH_SIZE 7

typedef struct Employee {
	int code;
	char name[100];
	int age;
	float wage;
	int status; // 1 used, 0 free
	int pointer;
} Employee;

typedef struct Dependent {
	int code;
	char name[100];
	int age;
	int employee_code;
	int status; // 1 used, 0 free
	int pointer;
} Dependent;

int hashFunction(int key, int hashSize);
