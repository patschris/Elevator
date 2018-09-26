# Elevator

## Problem Description
An elevator is on the ground floor and has to trasport *nrid* passengers to their destinations. Elevator can make at most *nst* stops. Every passenger should depart at the closer floor to his destination. The cost for a passenger to take the stairs equals to 1 per floor. We should find the solution with the minimum cost. Between solutions with the same cost, we prefer solutions with lower floor.

## Recursive equation
In order to solve the above mentioned task we use the following equations:<br/>
M<sub>i,0</sub> = fw(0,∞), 0 ≤ i ≤ nfl<br/>
M<sub>i,j</sub> = min<sup>i</sup><sub>k=0</sub>{M<sub>k,j-1</sub> - f<sub>w</sub>(k,∞) + f<sub>w</sub>(k,i) + f<sub>w</sub>(i,∞)}, 0 ≤ i ≤ nfl, 1 ≤ j ≤ nst<br/>
If d is the destination of a passenger, then f<sub>w</sub>(a,b) = min{d-a, b-d}, if a < d ≤ b, else f<sub>w</sub>(a,b)=0.<br/>
The cost of the optimal solution equal to : MinCost = min<sub>i=0</sub><sup>nfl</sup>{M<sub>i,nst</sub>}<br/>

## Methods
- Recursion (REC)
- Recursion with memoization (MEM)
- Dynamic programming (DP) 
- Brute force (BF)
<br/>
In order to use one of these methods, you have to change the value of the variable VERSION in the Makefile, clean and re-compile the program.

## Makefile
 - `make` to compile
 - `make clean` to delete the object files and the executable
 - `make run` to execute the program
 - `make check` to run valgrind to check for memory leaks.
