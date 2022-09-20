#include "kernel/types.h"
#include "user.h"

int filter_pipe(int fd_in)
{
    int *buf = malloc(sizeof(int));
    int res = read(fd_in, buf, sizeof(int));
    int first = *buf;
    if (res == 0)
    {
        exit(0);
    }
    printf("prime %d\n", first);
    int pid;
    int pipe_fd[2];
    pipe(pipe_fd);

    if ((pid = fork()) < 0)
    {
        printf("Fork ERROR!\n");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        exit(1);
    }
    if (pid == 0)
    {
        close(pipe_fd[1]);
        filter_pipe(pipe_fd[0]);
        exit(0);
    }
    else
    {
        close(pipe_fd[0]);
        while (read(fd_in, buf, sizeof(int)) != 0)
        {
            if (*buf % first != 0)
            {
                write(pipe_fd[1], buf, sizeof(int));
            }
        }
        close(pipe_fd[1]);
        wait(0);
        exit(0);
    }
    exit(0); //确保进程退出
}

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        printf("Primes needs only one argument!\n"); //检查参数数量是否正确
        exit(-1);
    }
    int * buf = malloc(sizeof(int));
    int pid;
    int pfd[2];
    pipe(pfd);
    if ((pid = fork()) < 0)
    {
        printf("Fork ERROR!\n");
        close(pfd[0]);
        close(pfd[1]);
        exit(1);
    }
    if (pid == 0) {
        close(pfd[1]);
        filter_pipe(pfd[0]);
        close(pfd[0]);
        exit(0);
    }
    else {
        close(pfd[0]);
        for(int i=2; i<=35; i++) {
            *buf = i;
            write(pfd[1],buf, sizeof(int));
        }
        close(pfd[1]);
        wait(0);
        exit(0);
    }
    exit(0); //确保进程退出
}


