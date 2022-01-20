#include <stdio.h>
#include <pthread.h>

// 10000になるまで1を足すだけの関数
void *function(void *cnt_p)
{
    int *cnt;

    cnt = cnt_p;
    for (int i = 0; i < 10000; i++)
        (*cnt) += 1;
    return (NULL);
}

int main()
{
    int cnt;
    pthread_t thread_1;
    pthread_t thread_2;

    cnt = 0;

    // スレッドを２つ作成し、それぞれのスレッドの中でfunctionを処理させる。
    /*
    int
    pthread_create(
        pthread_t *thread,               // スレッド変数へのポインタ(スレッドを格納する配列)
        const pthread_attr_t *attr,      // スレッドの属性（例えばスレッドの優先度（仕事の優先度）など）へのポインタを指定
        void *(*start_routine)(void *),  // スレッドで実行する関数へのポインタ
        void *arg                        // スレッドを実行する上で参照するデータへのポインタを指定(スレッドを実行する上で必要な情報を格納する配列)
)   ;
    */
    pthread_create(&thread_1, NULL, &function, &cnt);
    pthread_create(&thread_2, NULL, &function, &cnt);

    // pthread_createで作成されたスレッドの処理終了を待つ。
    /*
    int
    pthread_join(
        pthread_t thread,   // スレッド変数へのポインタ
        void **value_ptr.   // スレッドの実行結果を格納するデータへのポインタ
    );
    */
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

    // 大体11000以上くらいになる。
    printf("cnt: %d\n", cnt);
}