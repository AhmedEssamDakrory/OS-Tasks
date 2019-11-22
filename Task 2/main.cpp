/**
* A C program that reads numbers from a file, forks a number of child
* processes, and then each child sums a block of these numbers, prints
* that sum and waits for the parent to send a SIGKILL signal.
*
* When a child recieves a SIGKILL signal, it sends a SIGCHLD to the parent,
* which we implemented a new handler for it that prints the pid of that 
* child and its exit code.
*
* - implemented by:
* 	Ahmed Essam Eldeen
* 	Ahmed Elkarashily
*/

#include <bits/stdc++.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <fstream>

using namespace std;

void handler(int signum);

int main() {
	// changing the handler for SIGCHLD signal
	signal(SIGCHLD, handler);
	
	// vector to read numbers into
	vector<int> numbers;

	// vector to add the pids of the child processes to it
	vector<int> pids;


	/** reading numbers  into the numbers vector */
	
	// the file stream to read the numbers from a file
	ifstream fin;
	fin.open("file.txt");
	
	// reading numbers from the file
	int num;
	while(fin >> num) numbers.push_back(num);
	
	
	/**	forking child processes from the parent */

	// number of child processes to fork
	int numChilds = 3;

	// number of numbers per process
	int block = (int) numbers.size() / numChilds;
	
	// a variable to store the pid of the child in it. 
	// intialized to 1 to pass the loop condition in the first time.
	int pid = 1;
	
	// loop counter and a flag for forking 
	int i = 0;

	while(pid && i++ < numChilds) {
		pid = fork();
		if(pid) pids.push_back(pid);	
	}

	/** 
	* each child sums numbers in it's block and waits for the parent,
	* and the parent waits for a duration for the child processes to finish,
	* then sends SIGKILL to each child.
	*/

	if (!pid) { // if pid == 0 then this is a child

		// a sum variable which is created for every process
		int sum = 0;
		
		// looping on numbers and summing this child's block
		int cnt = 0;
		for (int j = (i - 1) * block;
		 cnt++ < block && j < (int) numbers.size();
		 j++) {
			sum += numbers[j];
		}

		// priting the sum of the this child process
		printf("Child number %d with pid = %d -> %d\n", i, getpid(), sum);
		
		// pause to wait for the SIGKILL from the parent
		pause();
	}

	else { // the parent
		
		// sleep for a sleepDuration
		// a while loop to avoid a signal from waking up the process
		int sleepDuration = 10;
		while(sleepDuration--) sleep(1);
		
		// send signal 9 (SIGKILL) to all child processes 
		for(int j = 0; j < numChilds; ++j) {
			kill(pids[j], 9);
			for(int k = 0; k < 2; ++k) sleep(1);
		}
		printf("Good Bye World !\n");	
	}
	return 0;
}

/** the custom handler for SIGCHLD */ 
void handler(int signum) {
	while (1) {
		// a variable to hold the exit status of the child process
      	int status;
		
      	int pid = waitpid(-1, &status, WNOHANG);
      	
		if (pid <= 0)  break;
     	
		printf("Child has sent a SIGCHLD signal #%d\n", signum);    
     	printf("A child with pid %d terminated with exit code %d\n", pid, status>>8);
  	}	
}
