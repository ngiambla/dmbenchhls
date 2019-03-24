#include <stdio.h>
#include <stdlib.h>

#define SIZE 25

typedef struct BinTreeNode{
    int data;
    struct BinTreeNode * right;
    struct BinTreeNode* left;
} BinTreeNode; 

typedef struct Stack {
	BinTreeNode * dat[SIZE];
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

BinTreeNode * getTop(Stack * s) {
	return s->dat[s->top];
}


BinTreeNode * pop(Stack * s) {
	if (s->top > -1) {
		return s->dat[s->top--];
	} else {
		return NULL;
	}
}

void push(Stack * s, BinTreeNode * node) {
	if (s->top < SIZE - 1) {
		s->top++;
		s->dat[s->top] = node;
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

void dfs(BinTreeNode * root) {
	BinTreeNode * tmp = root;
	
	Stack * s = createStack();

	push(s, root);
	while(!isEmpty(s)) {
		while(tmp->left != 0) {
			tmp = tmp->left;
			push(s,tmp);
		}
		while(!isEmpty(s)) {
			tmp = getTop(s);
			pop(s);
			printf("%d ", tmp->data);
			if(tmp->right != 0) {
				tmp = tmp->right;
				push(s,tmp);
				break;
			}
		}
	}
	printf("\n");

	destroyStack(s);
}

int main(){
	BinTreeNode * b1= (BinTreeNode *)malloc(sizeof(BinTreeNode));
	b1->data =1;

	BinTreeNode * b2= (BinTreeNode *)malloc(sizeof(BinTreeNode));
	b2->data =2;

	BinTreeNode * b3= (BinTreeNode *)malloc(sizeof(BinTreeNode));
	b3->data =3;

	BinTreeNode * b4= (BinTreeNode *)malloc(sizeof(BinTreeNode));
	b4->data =4;

	BinTreeNode * b5= (BinTreeNode *)malloc(sizeof(BinTreeNode));
	b5->data =5;

	BinTreeNode * b6= (BinTreeNode *)malloc(sizeof(BinTreeNode));
	b6->data =6;

	BinTreeNode * b7= (BinTreeNode *)malloc(sizeof(BinTreeNode));
	b7->data =7;

	BinTreeNode * b8= (BinTreeNode *)malloc(sizeof(BinTreeNode));
	b8->data =8;

	BinTreeNode * b9= (BinTreeNode *)malloc(sizeof(BinTreeNode));
	b9->data =9;

	b2->left = b1;
	b2->right = b4;
	b6->left = b2;
	b4->left = b3;
	b4->right = b5;
	b7->left = b6;
	b7->right = b8;
	b8->right = b9;
	
	dfs(b7);

	free(b1);
	free(b2);
	free(b3);
	free(b4);
	free(b5);
	free(b6);
	free(b7);
	free(b8);
	free(b9);

	return (0);
} 