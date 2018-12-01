#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"

int hashFunction(int key, int hashSize){
	return key % hashSize;
}
