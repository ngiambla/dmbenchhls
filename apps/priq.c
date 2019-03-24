//===-- priq.c ----------------------------------------------------*- C -*-===//
//
// Implements a priority queue using dynamic memory calls.
//
//===----------------------------------------------------------------------===//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>

#define min_data INT_MIN

typedef struct PRIQ{
	unsigned int max_size;
	unsigned int size;
	int * elements;
} PRIQ;

PRIQ * createPriq(unsigned int max_size) {
	PRIQ * priq = (PRIQ *)malloc(sizeof(PRIQ));
	if(priq == NULL) {
		printf("Out of space\n");
		exit(1);
	}

	priq->elements = (int *) malloc(sizeof(int)*max_size);
	if (priq->elements == NULL) {
		printf("Out of space\n");
		free(priq);
		exit(1);	
	}
	priq->max_size = max_size;
	priq->size = 0;
	priq->elements[0] = min_data;
	return priq;
}

void destroyPriq(PRIQ * priq) {
	if (priq == NULL) {
		return;
	}

	if (priq->elements != NULL) {
		free(priq->elements);
	}
	free(priq);
}

int isFull(PRIQ * priq) {
	return priq->max_size == priq->size+1;
}

void insert(PRIQ * priq, int x) {
	unsigned int i;

	if (isFull(priq)) {
		printf("Binary Heap is full...\n");
		return;
	}
	i = ++priq->size;
	while (priq->elements[i>>1] > x) {
		priq->elements[i] = priq->elements[i>>1];
		i >>= 1;
	}
	priq->elements[i] = x;
}

int deleteMin(PRIQ * priq) {

	int min = priq->elements[1];
	int x = priq->elements[priq->size--];
	int i = 1;
	int tmp;
	int flag = 0;
	while ( i<<1 <= priq->size) {
		flag = 0;
		if (priq->elements[i<<1] < x) {
			tmp = x;
			priq->elements[i] = x = priq->elements[i<<1];
			priq->elements[i<<1] = tmp;
			flag = 0;
		}
		if ((i<<1)+1 <= priq->size && priq->elements[(i<<1)+1] < x) {
			tmp = x;
			priq->elements[i] = x = priq->elements[(i<<1)+1];
			priq->elements[(i<<1)+1] = tmp;
			flag = 1;
		}
		i = (i<<1) + flag;
		x = priq->elements[i];
	}
	return min;
}

void decreaseKey(PRIQ * priq, unsigned int pos, int delta) {
	if (pos > priq->size) {
		return;
	}

	int x = priq->elements[pos] - delta;
	unsigned int i = pos;
	while (priq->elements[i>>1] > x) {
		priq->elements[i] = priq->elements[i>>1];
		i >>= 1;
	}
	priq->elements[i] = x;
}

void increaseKey(PRIQ * priq, unsigned int pos, int delta) {
	if (pos > priq->size) {
		return;
	}
	int x = priq->elements[pos] + delta;
	unsigned int i = pos;
	unsigned int child;
	for (; i*2 < priq->size; i = child) {
		child = i * 2;
		if ((child != priq->size) && priq->elements[child+1] < priq->elements[child]) {
			child++;
		}
		if (x > priq->elements[child]) {
				priq->elements[i] = priq->elements[child];
			} else {
				break;
			}
	}
	priq->elements[i] = x;
}

void delete(PRIQ * q, unsigned int p) {
	decreaseKey(q, p, q->elements[p] - q->elements[1] -1);
	deleteMin(q);
}

int main() {

	int i;
	PRIQ * priq = createPriq(25);
	
	for (i = 0; i < 25; i++) {
		insert(priq, i);
	}

	assert(isFull(priq));
	assert(deleteMin(priq) == 1);
	for (i = 0; i <=priq->size; i++) {
		printf(" %d", priq->elements[i]);
	}	
	assert(!isFull(priq));
	decreaseKey(priq, 8, 8);
	increaseKey(priq, 1, 7);
	delete(priq, 7);
	destroyPriq(priq);

	printf("OK.\n");
	return 0;
}