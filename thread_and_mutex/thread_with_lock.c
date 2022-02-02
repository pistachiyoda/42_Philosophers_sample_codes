#include <stdio.h>
#include <pthread.h>

// threadに渡す情報は一つの変数にまとめないといけないので、
// mutexとcntを保持する構造体を作っておく。
typedef struct {
    pthread_mutex_t *mutex;
    int             *cnt_p;
}   info_t;

// 10000になるまで1を足すだけの関数
void *function(void *info_p)
{
    int     *cnt;
    info_t  *info;

    info = info_p;
    cnt = info->cnt_p;
    for (int i = 0; i < 10000; i++)
    {
        // ②mutexのlockとunlock
        // クリティカルセクション（
        // 複数のスレッドから同時に実行されるとデータの不整合が発生する一連の処理部分）
        // をmutex_lock, mutex_unlockで囲む。
        pthread_mutex_lock(info->mutex);
        (*cnt) += 1;
        pthread_mutex_unlock(info->mutex);
    }
    return (NULL);
}

int main()
{
    int cnt;
    pthread_t thread_1;
    pthread_t thread_2;
    info_t info;

    // ①mutexオブジェクトの生成
    /*
    int pthread_mutex_init(
	    pthread_mutex_t *mutex,               // mutexオブジェクト
	    const pthread_mutexattr_t *mutexattr　// mutexオブジェクト生成時の属性
    );
    */
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    cnt = 0;

    info.cnt_p = &cnt;
    info.mutex = &mutex;

    pthread_create(&thread_1, NULL, &function, &info);
    pthread_create(&thread_2, NULL, &function, &info);

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

    // cnt: 20000と出力される
    printf("cnt: %d\n", cnt);
}