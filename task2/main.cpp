#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

using namespace std;

int main(int argc, char* argv[]) {
    printf("Hello!\n");
    int mode;
    bool modeSelected = false;
    while (!modeSelected) {
        printf("What Do You Want to use now?\n\t1- Generator\n\t2- Schedular\n>>> ");
        cin >> mode;
        if (mode == 1 || mode == 2) {
            modeSelected == true;
            break;
        }
        else {
            printf("Wrong Answer!\n");
        }
    }
    if(mode == 1) {
        int pid = fork();
        if(pid == -1) {
            printf("FATAL ERROR: Fork failed\n");
        }
        else if(!pid) {
            printf("\nStarting generator....\n");
            char* args[2];
            args[0] = "python";
            args[1] = "generator.py";
            args[2] = NULL;

            execvp(args[0], args);
            printf("FATAL ERROR: Failed to start generator.\n");
            exit(1);
        }
        else { 
            int stat; 
            wait(&stat);
            if (WIFEXITED(stat) && WEXITSTATUS(stat) == 1) 
                return 1;
            printf("Generator finished.....\n\n");
        }
    }
    else {
        int pid = fork();

        if(pid == -1) {
            printf("FATAL ERROR: Fork failed\n");
        }
        else if(!pid) {
            printf("\nStarting schedular....\n");
            char* args[1];
            args[0] = "./schedular.out";
            args[1] = NULL;

            execvp(args[0], args);
            printf("FATAL ERROR: Failed to start schedular.\n");
            exit(2);
        }
        else {
            int stat; 
            wait(&stat);
            if (WIFEXITED(stat) && WEXITSTATUS(stat) == 2) 
                return 2;
                
            printf("Schedular finished....\n\n");
            pid = fork();

            if(pid == -1) {
            printf("FATAL ERROR: Fork failed\n");
            }
            else if(!pid) {
                printf("Plotting data....\n");
                char* args[2];
                args[0] = "python";
                args[1] = "plot.py";
                args[2] = NULL;

                execvp(args[0], args);
                printf("FATAL ERROR: Failed to start plotter.\n");
                exit(3); 
            }
            else {
                int stat; 
                wait(&stat);
                if (WIFEXITED(stat) && WEXITSTATUS(stat) == 3) 
                    return 3; 

                printf("Plotter finished...\n\n");
            }
        }
    }
    return 0;
}
