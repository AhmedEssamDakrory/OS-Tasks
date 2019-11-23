## Task 1
An Assignment on Signals and forking.

### Brief Description:
A C program that reads numbers from a file, forks a number of child
processes, and then each child sums a block of these numbers, prints
that sum and waits for the parent to send a SIGKILL signal.
When a child recieves a SIGKILL signal, it sends a SIGCHLD to the parent,
which we implemented a new handler for it that prints the pid of that 
child and its exit code.

### Implemented by:
[@AhmedEssamDakrory]( https://github.com/AhmedEssamDakrory )
[@karashily]( https://github.com/karashily )

### Prerequisites

* g++
```sh
apt-get install g++
```

### Usage

1. Build the file using the makefile by simply opening the shell and typing:
```sh
make
```
  or Build using g++ by typing:
```sh
g++ task1.cpp -o task1.out
```
2. Run the program
```sh
./task1
```
