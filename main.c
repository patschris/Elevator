#include <stdio.h>
#include <stdlib.h>
#include "solve.h"

int main(void) {
	int nrid, nst, *dests;
	/* Reading input from stdin */
	scanf("%d %d", &nrid, &nst);
	if ((dests = (int*) malloc(nrid*sizeof(int))) == NULL) {
		perror("dests malloc failed");
		return -1;
	}
	for (int i=0; i < nrid; i++) { 
		if (i < nrid-1) scanf("%d ", &dests[i]);
		else scanf("%d", &dests[i]);
	}
	/* Calling solve function */
	printf("Cost is: %d\n", solve(nrid, nst, dests));
	free(dests);
	return 0;
}