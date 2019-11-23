# Multiple-Tasks-On-OS-Course
Tasks On Operating Systems Cousre implemented with C/C++.

#### Tasks Run only on UNIX systems

### Implemented by:
[@AhmedEssamDakrory]( https://github.com/AhmedEssamDakrory )
[@karashily]( https://github.com/karashily )

## Task 1:
An Assignment on Signals and forking.

### Brief Description:
A C program that reads numbers from a file, forks a number of child
processes, and then each child sums a block of these numbers, prints
that sum and waits for the parent to send a SIGKILL signal.
When a child recieves a SIGKILL signal, it sends a SIGCHLD to the parent,
which we implemented a new handler for it that prints the pid of that 
child and its exit code.
