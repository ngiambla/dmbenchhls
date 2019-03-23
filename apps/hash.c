//===-- hash.c ----------------------------------------------------*- C -*-===//
//
// Implements a hash table using dynamic memory calls.
//
//===----------------------------------------------------------------------===//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 11

enum STATUS { OK, FREE, DEL };

typedef struct Cell{
	int element;
	int info;
} Cell;

typedef struct HashTable {
	unsigned int size;
	Cell * cells;
} HashTable;



int hash(int e) {
	return e % 11; // using a prime number
}

HashTable * createHashTb(unsigned int size) {

	int i = 0;
	HashTable * ht = (HashTable *) malloc(sizeof(HashTable));
	if(ht == NULL) {
		printf("Out of space.\n");
		exit(1);
	}

	ht->cells = (Cell *)malloc(sizeof(Cell)*size);
	if(ht->cells == NULL){
		free(ht);
		exit(1);
	}
	
	ht->size = size;

	for(int i = 0; i < size; ++i) {
		ht->cells[i].info = FREE;
	}
	return ht;
}

void insertEntry(HashTable * ht, int val) {
	int pos = hash(val);
	
	while (ht->cells[pos].info != FREE) {
		pos = (pos+1) % ht->size;
	}

	ht->cells[pos].element = val;
	ht->cells[pos].info = OK;
}

int getIndexOfEntry(HashTable * ht, int val) {
	int idx = hash(val);


	for(int i = 0; i < ht->size; ++i) {
		if(ht->cells[idx].info == OK && val == ht->cells[idx].element){
			return idx;
		}
		idx = (idx+1) % ht->size;
	}

	return -1;
}

void deleteEntry(HashTable * ht, int val) {
	int pos = getIndexOfEntry(ht, val);
	if (pos != -1) {
		ht->cells[pos].info = DEL;
	}
}

void destroyHashTb(HashTable * ht) {
	if(ht == NULL){
		return;
	} 

	if(ht->cells != NULL) {
		free(ht->cells);
	}
	free(ht);
}

int main()
{
	int k = 0;
	int vals[] = {4789, 1209, 2137, 1679, 1583, 3945, 3293};
	
	HashTable * ht = createHashTb(SIZE);
	for (int i = 0; i < 7; i++) {
		insertEntry(ht, vals[i]);
	}
	int pos1 = getIndexOfEntry(ht, 1209);
	int pos2 = getIndexOfEntry(ht, 1679);
	assert(pos1 != -1);
	assert(pos1 != pos2);
	assert(ht->cells[pos1].element == 1209);

	deleteEntry(ht, 2137);
	pos1 = getIndexOfEntry(ht, 2137);
	assert(pos1 == -1);
	for (int i = 0; i < SIZE; i++) {
		if (ht->cells[i].info == OK) {
			printf("%4d ", ht->cells[i].element);
		}
	}
	printf("\n");
	destroyHashTb(ht);
	return 0;
}