#ifndef _help_
#define _help_

#define INF INT_MAX						/* Using maximum integer as infinity */
#define MIN(a,b) (((a)<=(b))?(a):(b))	/* Minimum of two numbers */
#define MAX(a,b) (((a)>(b))?(a):(b))	/* Maximum of two numbers */

int fw (int, int, int *, int);
int findNfl (int *, int);
int rec (int, int, int *, int);
int mem (int, int, int *, int, int **);
int dp (int, int, int *, int, int **, int **);
void findStops(int **, int, int);
int passengersCost (int, int *, int);
int solutionsCost (int *, int, int *, int);
void bf (int *, int, int, int *, int, int *, int, int *);
void combinationUtil (int *, int *, int, int, int, int, int *, int, int *, int, int *);

#endif