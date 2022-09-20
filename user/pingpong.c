#include "kernel/types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        printf("Pingpong needs only one argument!\n"); //检查参数数量是否正确
        exit(-1);
    }
    int pid, pid_child, pid_father;
    int p1[2], p2[2];
    char *buf = malloc(sizeof(char) * 4);
    pipe(p1);
    pipe(p2);
    if ((pid = fork()) < 0) {
        printf("Fork ERROR!\n");
    }
    if (pid == 0) {
        pid_child = getpid();
        read(p1[0], buf, 4);
        printf("%d: received %s\n",pid_child,buf);
        write(p2[1], "pong", 4);
        exit(0);
    }
    else {        
        pid_father = getpid();
        write(p1[1], "ping", 4);
        read(p2[0], buf, 4);
        
        printf("%d: received %s\n", pid_father, buf);
        wait(0);
        exit(0);
    }
    exit(0); //确保进程退出
}