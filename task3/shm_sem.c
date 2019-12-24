#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define PERIOD		1000000


/* arg for semctl system calls. */
union semun {
    int val;               		/* value for SETVAL */
    struct semid_ds *buf;  	/* buffer for IPC_STAT & IPC_SET */
    ushort *array;          	/* array for GETALL & SETALL */
    struct seminfo *__buf;  	/* buffer for IPC_INFO */
    void *__pad;
};


down(int sem) {
  struct sembuf p_op;
  
  p_op.sem_num = 0;
  p_op.sem_op = -1;
  p_op.sem_flg = !IPC_NOWAIT;
  
  if(semop(sem, &p_op, 1) == -1) {	
  	perror("Error in p()");
  	exit(-1);
  }
}


up(int sem) {
  struct sembuf v_op;
  
  v_op.sem_num = 0;
  v_op.sem_op = 1;
  v_op.sem_flg = !IPC_NOWAIT;
  
  if(semop(sem, &v_op, 1) == -1) {	
  	perror("Error in v()");
  	exit(-1);
  }
}

int Incrementor(int shmid, int sem) {
  int *shmaddr, ReadValue;
  int i;
  char quit_message[5];
   
  shmaddr = (int*) shmat(shmid, (void *)0, 0);
  if(shmaddr == -1) {	
  	perror("Error in attach in Incrementor");
  	exit(-1);
  }
  else {
    down(sem); 
    for (i=0; i<PERIOD; i++){
      ReadValue = *shmaddr;
      *shmaddr = ReadValue + 1;
    }
    up(sem);   

    printf("Incrementor: Our shared value is %d now\n", *shmaddr);	    
  }  	 
}

int Decrementor(int shmid, int sem) {
  int *shmaddr, ReadValue, i;
  
  shmaddr = (int*) shmat(shmid, (void *)0, 0);
  if(shmaddr == -1) {	
  	perror("Error in attach in Decrementor");
  	exit(-1);
  }
  else {
    down(sem);  
    for(i=0; i<PERIOD; i++){
      ReadValue = *shmaddr;	    
      *shmaddr = ReadValue - 1;
    }
    up(sem); 

    printf("Decrementor: Our shared value is %d now\n", *shmaddr);

    shmdt(shmaddr);
  }
}

int main() {
  int shmid, pid, semid, *shmaddr;
  
  union semun Semun;
  
  // getting the shared memory
  shmid = shmget(IPC_PRIVATE, 10, IPC_CREAT|0644);
  
  if(shmid == -1) {
    perror("Error in create shm");
    exit(-1);
  }
  else {
   	printf("\nShared memory ID = %d\n", shmid);
  }

  // getting the semaphore (size = 1 because it's a binary semaphore)
  semid = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
  
  if(semid == -1)	{
    perror("Error in create sem");
    exit(-1);
  }
  	  
  Semun.val = 1;  	/* initial value of the semaphore, Binary semaphore */
  if(semctl(semid, 0, SETVAL, Semun) == -1) {
    perror("Error in semctl");
    exit(-1);
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
  	Decrementor(shmid, semid);
  }
  else if(pid != -1) {
  	Incrementor(shmid, semid);
    wait(NULL);
    printf("\nFinal Value is %d\n\n", *shmaddr);
    shmdt(shmaddr);
  }
  else {
    perror("Error in fork");
    exit(-1);
  }

}
