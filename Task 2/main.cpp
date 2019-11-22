#include <bits/stdc++.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <fstream>

using namespace std;

void handler(int signum);

int main() {
	signal(SIGCHLD , handler);
	
	vector<int> numbers;
	vector<int> pids;
	
	ifstream fin;
	fin.open("file.txt");
	
	int num;
	while(fin >> num) numbers.push_back(num);
	
	int numChilds = 3;
	int block = (int) numbers.size() / numChilds;
	int pid = 1;
	int i = 0;
	while(pid && i++ < numChilds) {
		pid = fork();
		if(pid) pids.push_back(pid);	
	}
	
	int sum = 0;
	if (!pid) {
		int cnt = 0;
		for (int j = (i - 1) * block;
		 cnt++ < block && j < (int) numbers.size();
		 j++) {
			sum += numbers[j];
		}
		printf("Child number %d with pid = %d -> %d\n", i, getpid(), sum);
		pause();
	}
	else {
		int sleepDuration = 10;
		while(sleepDuration--) sleep(1);
		for(int j = 0; j < numChilds; ++j) {
			kill(pids[j], 9);
			for(int k = 0; k < 2; ++k) sleep(1);
		}
		printf("Good Bye World !\n");	
	}
	return 0;
}

void handler(int signum) {
	while (1) {  
      		int status;
      		int pid = waitpid(-1, &status, WNOHANG);
      		if (pid <= 0)  break;
     		printf("Child has sent a SIGCHLD signal #%d\n", signum);    
     		printf("A child with pid %d terminated with exit code %d\n", pid, status>>8);
  	}	
}
