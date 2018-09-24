# Elevator
An elevator is on the ground floor and has to trasport nrid passengers to their destinations. Elevator can make at most nst 
stops. Every passenger should depart at the closer floor to his destination. The cost for a passenger to take the stairs equals
to 1 per floor. We should find the solution with the minimum cost. Between solutions with the same cost, we prefer solutions 
with lower floor.<br /><br />
In order to solve the above mentioned task we use the following equations:<br />
M<sub>i,0</sub> = fw(0,∞), 0 ≤ i ≤ nfl<br />
M<sub>i,j</sub> = min<sup>i</sup><sub>k=0</sub>{M<sub>k,j-1</sub> - fw(k,∞) + fw(k,i) + fw(i,∞)}, 0 ≤ i ≤ nfl, 1 ≤ j ≤ nst<br />
If d is the destination of a passenger, then fw(a,b) = min{d-a, b-d}, if a < d ≤ b, else fw(a,b)=0.
The cost of the optimal solution equal to : MinCost = min<sub>i=0</sub><sup>nfl</sup>{M<sub>i,nst</sub>}
<br /><br />
We use four methods to achieve this goal: recursion (REC), recursion with memoization (MEM), dynamic programming (DP) and 
brute force (BF). In order to use one of these methods, you have to change the value of the variable VERSION in the Makefile,
clean and re-compile the program.
