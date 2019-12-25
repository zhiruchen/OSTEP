#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  printf("Hello World, (pid:%d)\n", (int)getpid());
  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "Fork Failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("Hello I am child, (pid:%d)\n", (int)getpid());
  } else {
    int rc_wait = wait(NULL);  // wait child proess to finish it's job
    printf("hello, I am parent of %d  (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int)getpid());
  }

  return 0;
}
