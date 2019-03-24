#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int * arr[128];

int main() {

	for(int i = 0; i < 128; ++i) {
		arr[i] = (int *) malloc(i);
		if(i%16 == 0) {
			printf("[%d] ", (uint32_t)arr[i]);
		}
		free(arr[i]);
	}
	printf("\nOK.\n");

	return 0;
}
