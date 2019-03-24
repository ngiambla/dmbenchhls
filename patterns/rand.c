
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX___MOVES 10 		// Max number to move per iteration
#define MAX_MEM_OPS 20 		//Maximum number of pointers to remember for free


typedef struct MEM_OP {
	int * pointer;
	int lifetime;
	char ok;
} MEM_OP;

static unsigned long int next = 1;
static MEM_OP all_mem_ops [MAX_MEM_OPS];

int rand(void) {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
    next = seed;
}

void initalize() {
	for(int i =0; i < MAX_MEM_OPS; ++i) {
		all_mem_ops[i].ok = 'N';
	}
}


// This function performs a request to malloc() and generates a random lifetime for this event.
void add_mem_op(int bytes) {
	for(int i =0; i < MAX_MEM_OPS; ++i) {
		if(all_mem_ops[i].ok == 'N') {
			printf("[malloc]-[pre ]=%d\n", bytes);
			int * p = malloc(bytes);
			printf("[malloc]-[post]\n");
			all_mem_ops[i].pointer = p;
			all_mem_ops[i].lifetime = rand() % 32;
			all_mem_ops[i].ok = 'Y';
			return;
		}
	}
}


void draw_from_uniform() {

	for(int j = 0; j < 128; ++j) {
		if(rand() % 32 > 16) {
			add_mem_op(rand() % 128);
		}

		for(int i =0; i < MAX_MEM_OPS; ++i) {
			if(all_mem_ops[i].ok == 'Y' && all_mem_ops[i].lifetime == 0) {
				printf("[free]-[pre ]\n");
				free(all_mem_ops[i].pointer);
				printf("[free]-[post]\n");
				all_mem_ops[i].ok = 'N';
			}
			if(all_mem_ops[i].ok == 'Y') {
				--all_mem_ops[i].lifetime;
			}
		}
	}
	for(int j = 0; j < MAX_MEM_OPS; ++j) {
		if(all_mem_ops[j].ok == 'Y') {
			free(all_mem_ops[j].pointer);
		}
	}
}



int main() {
	printf("Monte Carlo Simulation - Uniform Distribution.\n");
	srand(0x82);

	initalize();
	draw_from_uniform();

	printf("End.\n");
	return 1;
}
