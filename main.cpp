#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "ThreadPool.h"
#include "ThreadPool.cpp"


void taskFunc(void* arg) {
    int num = *(int*)arg;
    printf("thread working,number = %d\n,tid = %ld\n", num, pthread_self());
    usleep(1000);
}

int main()
{
    ThreadPool<int> pool(4, 10);
    for (int i = 0; i < 100; ++i) {
        int* num = new int(i + 100);
        pool.addTask(Task<int>(taskFunc,num));
    }

    sleep(30);

    return 0;
}
