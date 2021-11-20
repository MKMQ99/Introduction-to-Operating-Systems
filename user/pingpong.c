#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    if (argc!=1){
        fprintf(2, "Usage: pingpang\n");
    }

    int father[2],child[2];
    char buf[20];
    pipe(father);
    pipe(child);
    if(fork()==0){
        close(father[1]);
        close(child[0]);
        read(father[0], buf, sizeof(buf));
        printf("%d: received %s\n",getpid(), buf);
        write(child[1], "pong", 4);
        exit(0);
    }else{
        close(father[0]);
        close(child[1]);
        write(father[1], "ping", 4);
        read(child[0], buf, sizeof(buf));
        printf("%d: received %s\n",getpid(), buf);
        exit(0);
    }
}