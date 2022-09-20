#include "kernel/param.h"
#include "kernel/types.h"

#include "user.h"


void xargs(int argc, char *argv[])
{
    char *new_args[MAXARG];
    char line_buff[512];
    char * start;


    for (int i = 1; i < argc; i++)
    {
        new_args[i - 1] = argv[i];
    }

    while (gets(line_buff,512))
    {
        if(line_buff[0] == '\0') {
            break;
        }
        // read args
        int arg_cnt = argc-1;
        int j = 0;
        while(line_buff[j] == ' ') {
            j++;
        }
        start = &line_buff[j];
        for(int i=j; i<512;i++){
            if(line_buff[i] == '\n') {

                line_buff[i] = '\0';
                new_args[arg_cnt] = start;
                arg_cnt++;
                break;
            }
            if((i!=j) & (line_buff[i] == ' ')) {
                line_buff[i] = '\0';
                i++;

                new_args[arg_cnt] = start;
                arg_cnt++;
                if(arg_cnt == MAXARG) {
                    break;
                }
                while (line_buff[i] == ' ')
                {
                    i++;
                }
                if(line_buff[i] == '\n') {
                    break;
                }
                start = &line_buff[i];
                i--;  
            }
            else {
                continue;

            }
        }

        new_args[arg_cnt] = 0;
        arg_cnt++;

        int pid;
        if ((pid = fork()) < 0)
        {
            printf("Fork ERROR!\n");
        }
        if (pid == 0)
        {
            exec(argv[1], new_args);
            exit(0);
        }
        else
        {
            wait(0);
        }
    }
    // printf("xargs finished\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("xargs needs more than 1 argument!\n"); //检查参数数量是否正确
        exit(-1);
    }
    xargs(argc,argv);
    
    exit(0); //确保进程退出
}

