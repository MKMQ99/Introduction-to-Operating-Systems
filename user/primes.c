#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void child(int p){
    int temp;
    int status;
    if(read(p, &temp, sizeof(temp))){
        if(temp > 800) exit(0);
        printf("prime %d\n", temp);
    }else{
        exit(0);
    }
    int pp[2];
    int num;
    pipe(pp);
    if(fork()==0){
        close(pp[1]);
        child(pp[0]);
        exit(0);
    }else{
        while(read(p, &num, sizeof(num))){
            if(num % temp || num == 888){
                write(pp[1], &num, sizeof(num));
            }
            if(num > 800) {
                close(p);
                wait(&status);
                exit(0);
            }
        }
    }
}

int main(int argc, char* argv[]){
    if (argc!=1){
        fprintf(2, "Usage: primes\n");
    }

    int p[2];
    int status;
    pipe(p);
    if(fork()==0){
        close(p[1]);
        child(p[0]);
        exit(0);
    }else{
        close(p[0]);
        for(int j=2; j<36; ++j){
            write(p[1], &j, sizeof(j));
        }
        int t = 888;
        write(p[1], &t, sizeof(int));
        close(p[1]);
        wait(&status);
        exit(0);
    }
    exit(0);
}

