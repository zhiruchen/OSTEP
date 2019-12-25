#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    printf("redirect ouput start.... (pid:%d)\n", (int)getpid());
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(1);
    } else if (rc == 0) {  // child (new process)

        /*
        when the child is created, before calling exec(), the shell closes
        standard output and opens the file newfile.txt. 
        By doing so, any output from the soon-to-be-running program wc are sent to the file instead
        of the screen
         */
        // redirect standard output to a file
        close(STDOUT_FILENO);
        open("./redirect.ouput",  O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("redirect_output.c");
        myargs[2] = NULL;
        execvp(myargs[0], myargs);  // run word count
    } else {
        // main goes down to this path
        int rc_wait = wait(NULL);
    }
    return 0;
}
