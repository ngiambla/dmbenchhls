#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int * arr[128];

int main() {

	for(int i = 0; i < 128; ++i) {
		arr[i] = (int *) malloc(128);
	}

	for(int i = 0; i < 128; ++i) {
		free(arr[i]);
	}

	printf("OK.\n");

	return 0;
}
