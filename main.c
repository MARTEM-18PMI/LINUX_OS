#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
int counter_sigterm = 0;

void sigterm_handler(int signum){
    counter_sigterm += 1;
}
int main() {
    pid_t pid = fork();
    if(pid == 0){
        signal(SIGTERM, sigterm_handler);
        char buf1[] = "MYTEXT1111\n";
        char buf2[] = "MYTEXT2222\n";
        int fd = open("log.txt", O_CREAT|O_RDWR, S_IRWXU);
        while(1){
            if(counter_sigterm == 0){
                write(fd, buf1, 11);
                sleep(3);
            }
            if(counter_sigterm == 1){
                write(fd, buf2, 11);
                sleep(5);
            }
            if(counter_sigterm == 2){
                break;
            }
        }
        close(fd);
    }
    else if(pid < 0 ){
         printf("ferror\n");
         exit(1);
    }
    return 0;
}