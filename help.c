#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "help.h"

/* 
 * If the destination of the passenger is betweeen fststop and sndstop, then the cost
 * is equal to the minimum distance of his destination and this two stops
 */
int fw (int fststop, int sndstop, int *dests, int size) {
	int cost = 0;
	for (int i=0; i<size; i++)
		if (dests[i] > fststop && dests[i] <= sndstop)
			cost += MIN(dests[i]-fststop, sndstop-dests[i]);	
	return cost;
}

/* 
 * Find the maximum destination floor 
 */
int findNfl (int *dests, int size) {
	int nfl = -1;
	if (size > 0) {
		nfl = dests[0];
		for (int i = 1; i < size; i++) nfl = MAX(nfl, dests[i]);
	}
	return nfl;
}

/*
 * Applies the following recursion:
 * M(i,0) = fw(0,∞), 0 <= i <= nfl
 * M(i,j) = min k {M(k,j-1)-fw(0,∞)+fw(k,i)+ fw(i,∞)}, 0 <= i <= nfl AND 1 <= j <= nst
 */
int rec (int i, int j, int *dests, int size) {
	int min =  INF;
	if(i && j) {
		for(int k=0; k<=i; k++) {
			int Mij = rec(k,j-1,dests,size)-fw(k,INF,dests,size)+fw(k,i,dests,size)+fw(i,INF,dests,size);
			if (Mij < min) min = Mij;
		}
		return min;
	}
	else {
		return fw(0, INF, dests, size);
	}
}

/*
 * Applies the above mentioned recursion, but uses array M to avoid multiple computations of the same value 
 */
int mem (int i, int j, int *dests, int size, int **M) {
	int min =  INF;
	if (M[i][j] == -1) { // M[i][j] is empty
		if(i && j) {
			for(int k=0; k<=i; k++) {
				int Mij = mem(k,j-1,dests,size,M)-fw(k,INF,dests,size)+fw(k,i,dests,size)+fw(i,INF,dests,size);
				if (Mij < min) min = Mij;
			}
			M[i][j] = min;
		}
		else {
			M[i][j] = fw(0, INF, dests, size);
		}
	}
	return M[i][j];
}

/*
 * Applies the above mentioned recursion logic for the dynamic programming method
 * Instead of top-down approach used in recursion, dynamic programmic uses bottom-up aproach
 * Using array stop in order to find all the stops contributes in the optimal solution
 */
int dp (int i, int j, int *dests, int size, int **stop, int **M) {
	int min =  INF;
	if (i && j) {
		for(int k=0; k<=i; k++) {
			int Mij = M[k][j-1]-fw(k,INF,dests,size)+fw(k,i,dests,size)+fw(i,INF,dests,size);
			if (Mij < min) {
				min = Mij;
				stop[i][j] = k;
			}
		}
		M[i][j] = min;
	}
	else {
		M[i][j] = fw(0, INF, dests, size);
	}
	return M[i][j];
}

/*
 * Print the stop in the dynamic programming method
 */
void findStops(int **stops, int i, int j) {
	if(stops[i][j]>0) {
		findStops(stops,stops[i][j],j-1);
		printf("%d ",stops[i][j]);
	}
}

/*
 * We compute the passenger's cost as the closer floor to his destination floor
 */
int passengersCost (int dest, int *stop, int size) {
	int cost = dest;
	for (int i=0; i<size; i++) cost = MIN(cost,abs(stop[i]-dest));
	return cost;
}

/*
 * A possible's solution cost equals to the sum of each passenger's cost
 */
int solutionsCost (int *dest, int sizeOfDest, int *stop, int size) {
	int cost = 0;
	for (int i=0; i<sizeOfDest; i++) cost += passengersCost(dest[i], stop, size);
	return cost;
}

/*
 * Calls the recursive function compilationUtil which produces and checks every solution set with size r 
 */
void bf (int *arr, int n, int r, int *dest, int sizeOfDest, int *stop, int sizeOfStop, int *min) {
	int *data; 
	if ((data = (int *)malloc(r * sizeof(int)))==NULL) {
		perror("data malloc failed");
		exit(-1);
	}
	combinationUtil(arr, data, 0, n-1, 0, r, dest, sizeOfDest, stop, sizeOfStop, min);
	free(data);
}

/*
 * Produces every solution set with size r and finds the optimal solution for this size
 * Source : https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
 */
void combinationUtil (int *arr, int *data, int start, int end, int index, int r, int *dest, int sizeOfDest, int *stop, int sizeOfStop, int *min) {
	if (index == r) {
		int cost = solutionsCost (dest, sizeOfDest, data, r);
 		if (cost < *min) {
 			*min = cost;
 			for (int j=0; j < r; j++) stop[j] = data[j];
 			for (int j=r; j < sizeOfStop; j++) stop[j] = 0;
 		}
		return;
	}
	for (int i=start; i<=end && end-i+1 >= r-index; i++) {
		data[index] = arr[i];
		combinationUtil(arr, data, i+1, end, index+1, r, dest, sizeOfDest, stop, sizeOfStop, min);
	}
}