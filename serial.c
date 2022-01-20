#include <stdio.h>

// 10000になるまで1を足すだけの関数
void function(int *cnt_p)
{
    int *cnt;

    cnt = cnt_p;
    for (int i = 0; i < 10000; i++)
        (*cnt) += 1;
}

int main()
{
    int cnt;

    function(&cnt);
    // cnt: 10000と表示される
    printf("cnt: %d\n", cnt);
}