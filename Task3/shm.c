#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/shm.h>


incrementor(int shmid)
{
  void *shmaddr;
  
  for(int i = 0; i < 1000000 ;i++) {
    shmaddr = shmat(shmid, (void *)0, 0);
    if(shmaddr == -1)
    {	
      perror("Error in attach in writer");
      exit(-1);
    }
    else
    {
      int* count = (int*) shmaddr;
      *count++;
      
      if (i == 999999)
      {
        printf("parent value = %d", *count);
      }
      
      shmdt(shmaddr);
    }  	
  }  
}

decrementor(int shmid)
{
  void *shmaddr;
  
  for(int i = 0; i < 1000000 ;i++) {
    shmaddr = shmat(shmid, (void *)0, 0);
    if(shmaddr == -1)
    {	
      perror("Error in attach in reader");
      exit(-1);
    }
    else
    {
      int* count = (int*) shmaddr;
      *count--;
      
      if (i == 999999)
      {
        printf("child value = %d", *count);
      }

      shmdt(shmaddr);
    }
  }
}

main()
{
  int shmid, pid;
  
  shmid = shmget(IPC_PRIVATE, 4096, IPC_CREAT|0644);
  
  if(shmid == -1)
  	{
  	  perror("Error in create");
  	  exit(-1);
  	}
  else
  	printf("\nShared memory ID = %d\n", shmid);
     	
  pid = fork();
  
  if(pid == 0)
  	decrementor(shmid);
  else if(pid != -1)
  	incrementor(shmid);
  else
    {
  	perror("Error in fork");
  	exit(-1);
    }
}
