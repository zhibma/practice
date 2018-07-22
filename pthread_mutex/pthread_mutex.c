/* 编写一个包含两个线程的程序，在主线程中接收键盘输入，并把
 * 输入字符放入缓冲区中；待缓冲区满后，由另一线程输出缓冲区
 * 的内容，用户斥锁实现两者间的同步。*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

typedef struct
{
    int len;
    char data[1];
}buf_t;

typedef struct
{
    void *argv[2];
}thread_arg_t;

#define LOOP_TIMES          3
#define SLEEP_SECONDS       1
#define MAX_BUF_DATA_LEN    10

int getnchar(char *buf, size_t len);
void print_buffer(thread_arg_t *arg);

int main()
{
    int iCount = 0;
    buf_t *p_buf = NULL;
    pthread_t thread;
    thread_arg_t args;
    void *ret_val = NULL;
    pthread_mutex_t mutex;
    pthread_mutex_t *p_mutex = &mutex;

    p_buf = (buf_t *)malloc(sizeof(buf_t) + MAX_BUF_DATA_LEN);
    if(NULL == p_buf)
    {
        printf("call malloc failure, exit...\n");
        return 0;
    }
    memset(p_buf, 0, sizeof(buf_t) + MAX_BUF_DATA_LEN);

    pthread_mutex_init(p_mutex, NULL);

    args.argv[0] = (void *)p_buf;
    args.argv[1] = (void *)p_mutex;
    pthread_create(&thread, NULL, (void *)(&print_buffer), (void *)(&args));

    while(LOOP_TIMES > iCount)
    {
        pthread_mutex_lock(p_mutex);
        if(MAX_BUF_DATA_LEN > p_buf->len)
        {
            printf("[main thread] lack of %d characters, please input.\n", MAX_BUF_DATA_LEN - p_buf->len);
            getnchar(p_buf->data + p_buf->len, MAX_BUF_DATA_LEN - p_buf->len);
            p_buf->len = strlen(p_buf->data);
            if(p_buf->len == MAX_BUF_DATA_LEN)iCount++;
        }
        else
        {
            printf("[main thread] buffer is full, wait for output.\n");
            pthread_mutex_unlock(p_mutex);
            sleep(SLEEP_SECONDS);
            continue;
        }
        pthread_mutex_unlock(p_mutex);
    }

    pthread_join(thread, &ret_val);
    pthread_mutex_destroy(p_mutex);
    free(p_buf);

    return EXIT_SUCCESS;
}

int getnchar(char *buf, size_t len)
{
    char c = '\0';
    unsigned i = 0;
    int iTotal = 0;

    while((i < len) && ('\n' != (c = getchar())))
    {
        buf[i] = c;
        i++;
    }

    while('\n' != c)
    {
        c = getchar();
    }

    iTotal = i;
    return iTotal;
}

void print_buffer(thread_arg_t *arg)
{
    int iCount = 0;
    buf_t *p_buf = arg->argv[0];
    pthread_mutex_t *p_mutex = arg->argv[1];

    while(LOOP_TIMES > iCount)
    {
        pthread_mutex_lock(p_mutex);
        if(MAX_BUF_DATA_LEN > p_buf->len)
        {
            printf("[sub thread] buffer not full, wait for input.\n");
            pthread_mutex_unlock(p_mutex);
            sleep(SLEEP_SECONDS);
            continue;
        }
        else
        {
            printf("[sub thread] output: %s\n", p_buf->data);
            memset(p_buf, 0, sizeof(buf_t) + MAX_BUF_DATA_LEN);
            iCount++;
        }
        pthread_mutex_unlock(p_mutex);
    }
}
