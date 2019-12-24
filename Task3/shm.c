#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define PERIOD		1000000


int Incrementor(int shmid) {
  int *shmaddr, ReadValue;
  int i;
  char quit_message[5];
   
  shmaddr = (int*) shmat(shmid, (void *)0, 0);
  if(shmaddr == -1) {	
  	perror("Error in attach in Incrementor");
  	exit(-1);
  }
  else {
    for (i=0; i<PERIOD; i++){
      ReadValue = *shmaddr;
      *shmaddr = ReadValue + 1;
    }

    printf("Incrementor: Our shared value is %d now\n", *shmaddr);	    

    sleep(2);
    printf("\nFinal Value is %d\n", *shmaddr);
    
    shmdt(shmaddr);
  }  	 
}

int Decrementor(int shmid) {
  int *shmaddr, ReadValue, i;
  
  shmaddr = (int*) shmat(shmid, (void *)0, 0);
  if(shmaddr == -1) {	
  	perror("Error in attach in Decrementor");
  	exit(-1);
  }
  else {
    for(i=0; i<PERIOD; i++){
      ReadValue = *shmaddr;	    
      *shmaddr = ReadValue - 1;
    }

    printf("Decrementor: Our shared value is %d now\n", *shmaddr);

    shmdt(shmaddr);
  }
}

int main() {
  int shmid, pid, *shmaddr;
  
  // getting the shared memory
  shmid = shmget(IPC_PRIVATE, 10, IPC_CREAT|0644);
  
  if(shmid == -1) {
    perror("Error in create shm");
    exit(-1);
  }
  else {
   	printf("Shared memory ID = %d\n", shmid);
  }
  
  shmaddr = (int*) shmat(shmid, (void *)0, 0);
  if(shmaddr == -1) {	
  	perror("Error in attach in parent");
  	exit(-1);
  }
  else {	
   	*shmaddr = 0;		/* initialize shared memory */
   	shmdt(shmaddr);
  }
  
  pid = fork();
  
  if(pid == 0) {
  	Decrementor(shmid);
  }
  else if(pid != -1) {
  	Incrementor(shmid);
    wait(NULL);
  }
  else {
    perror("Error in fork");
    exit(-1);
  }
}
