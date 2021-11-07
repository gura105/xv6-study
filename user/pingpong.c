#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    // int p[2];
    // char *argv2[2];

    // argv2[0] = "wc";
    // argv2[1] = "0";

    // pipe(p);
    // if (fork() == 0)
    // {
    //     // child process

    //     // fd 0にパイプの読み込み側を割当てて、p[0]を開放する
    //     close(0);
    //     dup(p[0]);
    //     close(p[0]);

    //     // パイプの書き込み側を閉じる(最初から不要だから)
    //     close(p[1]);

    //     // fd 0がパイプの読み込み側の状態でexec実行
    //     // つまりwcでは0 -> パイプ(r), 1 -> stdout, 2 -> stderrとなっている
    //     exec("wc", argv2);
    // }
    // else
    // {
    //     // パイプの読み込み側を閉じる(最初から不要だから)
    //     close(p[0]);

    //     // パイプの書き込み側にraw dataを書き込み
    //     write(p[1], "hello world", 12);

    //     // パイプの書き込み側を閉じる
    //     close(p[1]);
    // }

    char ball = 'a';
    int p1[2];
    int p2[2];

    pipe(p1);
    pipe(p2);

    if (fork() == 0)
    {
        char buff[255];

        // recieve
        close(p1[1]);
        read(p1[0], buff, 1);
        close(p1[0]);
        printf("child process:");
        printf(buff);
        printf("\n");

        // send
        close(p2[0]);
        write(p2[1], buff, 1);
        close(p2[1]);
    }
    else
    {
        // send
        close(p1[0]);
        write(p1[1], &ball, 1);
        close(p1[1]);

        char buff2[255];
        // recieve
        close(p2[1]);
        read(p2[0], buff2, 1);
        close(p2[0]);
        printf("parent process:");
        printf(buff2);
        printf("\n");
    }

    exit(0);
}
