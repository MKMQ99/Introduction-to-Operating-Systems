#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) 
{
  if (argc < 2) {
    fprintf(2, "Usage: xargs <command>\n");
    exit(1);
  }

  char *cmd = argv[1];
  char *params[MAXARG], buf[512];
  int i, status;

  if (argc + 1 > MAXARG) {
    fprintf(2, "Too many arguments\n");
    exit(1);
  }

  for (i = 1; i < argc; i++) {
    params[i-1] = argv[i];
  }
  params[argc] = 0;

  while (1) {
    i = 0;
    while (1) {
      int n = read(0, &buf[i], 1);
      if (n == 0 || buf[i] == '\n') 
        break;
      i++;
    }
    if (i == 0) 
      break;
    buf[i] = 0;
    params[argc-1] = buf;
    if (fork() == 0) {
      exec(cmd, params);
      exit(0);
    } else {
      wait(&status);
    }
  }

  exit(0);
}