#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h> //access to POSIX API- ex: getpid(),getppid(),fork()

int main(int argc, char *argv[])
{
    printf("Main function !!");

    pid_t pid = fork();
    int retVal = 1;
    if (pid < 0)
    {
        printf("Unable to fork it !!");
        return 1;
    }
    else if (pid == 0)
    {
        printf("Inside child process !!\n");
        printf("Pid of the child process is %d\n", getpid());
        printf("Pid of the parent process is %d\n", getppid());
        execl("./linsearch", argv[1], NULL);
    }
    else
    {
        printf("Pid of the parent process %d\n", getpid());
        wait(&retVal);

        if (WIFEXITED(retVal) == 1)
        {
            printf("Child process ended noramlly !!\n");
        }
        else
        {
            printf("Child process ended abnormally !!\n");
        }
    }

    return 0;
}