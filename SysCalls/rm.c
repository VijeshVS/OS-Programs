#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc,char *argv[]){
    int output_fd = unlink(argv[1]);

    if(output_fd == -1){
        perror("Unlink error !!");
        return 3;
    }
}