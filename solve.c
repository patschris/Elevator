#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "help.h"

#ifdef REC /* recursive */

int solve (int nrid, int nst, int *dests) {
	
	int cost, stop;

	int nfl = findNfl(dests, nrid); /* Find the maximum destination floor */
	/* Searching for the minimum cost and the last stop of the elevator */
	int minfl = INF; 
	for (int i=nfl; i>=0; i--) {
		cost = rec(i,nst,dests,nrid);
		if (cost <= minfl) {
			minfl = cost;
			stop = i;
		}
	}
	/* For the optimal solution, print the last stop and return the cost of this solution */
	if (stop) printf("Last stop at floor %d\n", stop);
	else printf("No elevator stops\n");
	return minfl;
}
#endif


#ifdef MEM /* recursive with memoization */

int solve (int nrid, int nst, int *dests) {
	int cost, stop, **M;
	int nfl = findNfl(dests, nrid); /* Find the maximum destination floor */
	/* Array M is used for memoization */
	if ((M = (int **) malloc((nfl+1)*sizeof(int *))) == NULL) {
		perror("M malloc failed");
		exit(-1);
	}
	for (int i=0; i<nfl+1; i++) {
		if ((M[i] = (int *)malloc((nst+1) * sizeof(int))) == NULL) {
			perror("M malloc failed");
			exit(-1);
		}
		for (int j=0; j<nst+1; j++) M[i][j] = -1;
	}
	/* Searching for the minimum cost and the last stop of the elevator */
	int minfl = INF;
	for (int i=nfl; i>=0; i--) {
		cost = mem(i,nst,dests,nrid, M);
		if (cost <= minfl){
			minfl = cost;
			stop = i;
		}
	}
	/* For the optimal solution, print the last stop and return the cost of this solution */
	if (stop) printf("Last stop at floor %d\n", stop);
	else printf("No elevator stops\n");
	for (int i=0; i<nfl+1; i++) free(M[i]);
	free(M);
	return minfl;
}

#endif


#ifdef DP /* dynamic programming */

int solve (int nrid, int nst, int *dests) {
	int cost, lastStop, **stop, **M;
	int nfl = findNfl(dests, nrid); /* Find the maximum destination floor */
	/* Array M is used for saving the cost */
	if ((M = (int **) malloc((nfl+1)*sizeof(int *))) == NULL) {
		perror("M malloc failed");
		exit(-1);
	}
	/* Array stop is used for saving value k in stop j-1 that leads to minimum M(i,j) */
	if ((stop = (int **) malloc((nfl+1)*sizeof(int *))) == NULL) {
		perror("stop malloc failed");
		exit(-1);
	}
	for (int i=0; i<nfl+1; i++) {
		if ((M[i] = (int *)malloc((nst+1) * sizeof(int))) == NULL) {
			perror("M malloc failed");
			exit(-1);
		}
		if ((stop[i] = (int *)malloc((nst+1) * sizeof(int))) == NULL) {
			perror("stop malloc failed");
			exit(-1);
		}
		for (int j=0; j<nst+1; j++) {
			M[i][j] = -1;
			stop[i][j] = 0;
		}
	}
	/* Searching for the minimum cost and the last stop of the elevator */
	int minfl = INF;
	for (int j=0; j<nst+1; j++) {
		printf(" ");
		for (int i=0; i<nfl+1; i++) {
			cost = dp (i, j, dests, nrid, stop, M);
			if (cost < minfl){
				minfl = cost;
				lastStop = i;
			}
			printf("%d ", cost);
			if (cost < 10) printf(" ");
		}
		printf("\n");
	}
	/* For the optimal solution, print all the stops and return the cost of this solution */
	if (lastStop<=0) {
		printf("No elevator stops\n");
	}
	else {
		printf("Elevator stops are: ");
		findStops(stop, lastStop, nst);
		printf("%d\n", lastStop);
	}
	for (int i=0; i<nfl+1; i++) {
		free(M[i]);
		free(stop[i]);
	}
	free(M);
	free(stop);
	return minfl;
}
#endif


#ifdef BF /* brute force */

int solve (int nrid, int nst, int *dests) {
	int i, nfl, min, *floors, *stop;
	nfl = findNfl(dests, nrid); /* Find the maximum destination floor */
	/* Array stop is used for saving the floors that elevator stoped in the optimal solution */
	if ((stop = (int *)malloc(nst * sizeof(int))) == NULL) {
		perror("stop malloc failed");
		exit(-1);
	}
	/* Array floors is used for saving all the possible floors that elevator can stops (1-nfl) */
	if ((floors = (int *)malloc(nfl * sizeof(int))) == NULL) {
		perror("floors malloc failed");
		exit(-1);
	}
	for (i=0; i<nfl; i++) floors[i] = i+1;
	/* Initial minimum value proposes the solution in which all passengers use the stairs in order to go to their destinations */
	min = fw(0, INF, dests, nrid);
	/* Function bf updates values of min and stop */
    for (i=1; i<nst+1; i++) bf(floors, nfl, i, dests, nrid, stop, nst, &min);
  	/* For the optimal solution, print all the stops and return the cost of this solution */
    if (stop[0]) {
		printf("Elevator stops are:");
		for (i=0; i<nst; i++) 
			if (stop[i]) printf(" %d", stop[i]);
		printf("\n");
	}
	else {
		printf("No elevator stops\n");
	}
	free(stop);
	free(floors);
	return min;
}
#endif