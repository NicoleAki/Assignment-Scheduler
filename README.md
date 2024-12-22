# Assignment-Scheduler
The Assignment Scheduler submits assignments to the central server according to the weightages and the deadlines.
Each assignment has a weightage (integer), a deadline, and an expected execution time. The scheduler,
taking into consideration the weightages and execution times, submits the assignments
to the central server. It has to follow the following properties:
•Highest Weightage First: Assignments with higher weightages (numerically larger)
should be executed before assignments with lower weightages. If two assignments
have the same weightage, the one with the nearest deadline should be executed first.
•No Overdue Assignments: An assignment can only be scheduled if its deadline has
not yet passed. If an assignment cannot be scheduled, it is discarded and logged.
•Efficiency Matters: The scheduling system must be optimized using a heap to ensure
efficient assignment insertion and retrieval.

Each assignment is represented as an object with:
•Assignment ID (string)
•Weightage (integer, higher is better)
•Deadline (integer, represents time units)
•Execution Time (integer, represents how long the assignment takes to execute)
