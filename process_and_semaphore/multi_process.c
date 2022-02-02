#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#define VAL 5

void sleep_random()
{
	srandom(getpid());
	unsigned int sleep_sec = random() % 5;
	sleep(sleep_sec);
}

int	main ()
{
	pid_t pid[VAL];
    int status;
    int i;

    i = 0;
    while (i < VAL)
    {
	    pid[i] = fork();
        if (pid[i] == 0)
        {
            printf("[CHILD]process(pid[%d] = %d) start.\n", i, pid[i]);
            printf("[CHILD]getpid() in pid[%d]: %d\n", i, getpid()); 
            sleep_random();
            printf("[CHILD]process(pid[%d] = %d) end.\n", i, pid[i]);
            exit(0);  //mainの中なのでreturnでも可
        }
        else
        {
            printf("[PARENT]getpid() in pid[%d]: %d\n", i, getpid()); 
            printf("[PARENT]pid[%d] = %d\n", i, pid[i]); 
        }
        i++;
    }

    printf("=====END OF FORK ROOP=====\n");

    // ①か②、どちらかをコメントアウトして実行
    // ①全ての子プロセスの終了を待つ場合
    // i = 0;
    // while (i < VAL)
    // {
    //     waitpid(pid[i], &status, 0); 
    //     printf("[PARENT]pid[%d] end\n", i);
    //     i++;
    // }

    // ②子プロセスの中のどれかが終了するのを待つ場合
    int finished_pid = waitpid(-1, &status, 0); 
    printf("finished_child_pid: %d\n", finished_pid);
    i = 0;
    while (i < VAL)
    {
        if (pid[i] != finished_pid)
        {
            kill(pid[i], SIGKILL);
            printf("pid[%d](%d) killed\n", i, pid[i]);
        }
        i++;
    }

    printf("=====END OF PROGRAM=====.\n");
    return (0);
}
