#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char *ball = "ball";
    int p1[2];
    int p2[2];
    int cnt = 100;
    int ballsize = strlen(ball) + 1;

    pipe(p1);
    pipe(p2);

    if (fork() == 0)
    {
        for (int i = 0; i < cnt; i++)
        {
            char buff[ballsize];

            // recieve

            // close(p1[1]);
            read(p1[0], buff, ballsize);
            // close(p1[0]);
            printf("child process:");
            printf(buff);
            printf("\n");

            // send
            // close(p2[0]);
            write(p2[1], buff, ballsize);
            // close(p2[1]);
        }
    }
    else
    {
        for (int j = 0; j < cnt; j++)
        {
            // send

            // close(p1[0]);
            write(p1[1], ball, ballsize);
            // close(p1[1]);

            char buff2[ballsize];
            // recieve
            // close(p2[1]);
            read(p2[0], buff2, ballsize);
            // close(p2[0]);
            printf("parent process:");
            printf(buff2);
            printf("\n");
        }
    }

    exit(0);
}
