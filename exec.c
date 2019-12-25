#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    printf("Hello World, (pid:%d)\n", (int)getpid());
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(1);
    } else if (rc == 0) {  // child (new process)
        printf("Hello I am child, (pid:%d)\n", (int)getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("exec.c");
        myargs[2] = NULL;

        // OS does not create a new process; rather, it transforms the currently running program
        // into a different running program (wc).
        execvp(myargs[0], myargs);  // run word count
        printf("this will not print");
    } else {
        int rc_wait = wait(NULL);  // wait child proess to finish it's job
        printf("hello, I am parent of %d  (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int)getpid());
    }
    return 0;
}
