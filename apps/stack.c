//===-- stack.c ---------------------------------------------------*- C -*-===//
//
// Implements a stack using dynamic memory calls.
//
//===----------------------------------------------------------------------===//


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define SUCCESS 1
#define SIZE 100

typedef struct Stack {
	int dat[SIZE];
	int top;
} Stack;


Stack * createStack() {
	Stack * s = (Stack *)malloc(sizeof(Stack));
	if(s == NULL) {
		printf("\n");
		exit(1);
	}
	s->top = -1;
	return s;
}

void destroyStack(Stack * s) {
	if (s != NULL){
		free(s);
	}
}

int getTop(Stack * s) {
	return s->dat[s->top];
}


int pop(Stack * s) {
	if (s->top > -1) {
		return s->dat[s->top--];
	} else {
		return NULL;
	}
}

void push(Stack * s, int val) {
	if (s->top < SIZE - 1) {
		s->top++;
		s->dat[s->top] = val;
	} else {
		printf("Stack Overflow!\n");
		exit(1);
	}
}

int getSize(Stack * s) {
	return s->top + 1;
}

int isEmpty(Stack * s) {
	return s->top == -1;
}


int main() {
	uint8_t status = SUCCESS;
	int numsFwd[50], numsRev[50];
	Stack * s;

	// Create the stack;
	s = createStack();
	assert(isEmpty(s));

	// initialize list
	for(int i = 0; i < 50; ++i) {
		numsFwd[i] = i;
	}

	// push onto list;
	for(int i = 0; i < 50; ++i) {
		push(s, numsFwd[i]);
	}

	assert(getSize(s) == 50);

	// pop off into list;
	for(int i = 0; i < 50; ++i) {
		numsRev[i]=pop(s);
	}

	for(int i = 0; i < 50; ++i) {
		assert(numsRev[49-i] == numsFwd[i]);
	}

	assert(getSize(s) == 0);
	destroyStack(s);

	printf("OK.\n");

	return (status);
}
