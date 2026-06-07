#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int N;

/* Signal Handler */
void handle_sigint(int sig)
{
    printf("\nSIGINT received. Program continues execution.\n");
}

/* Prime Check Function */
int isPrime(int num)
{
    if(num < 2)
        return 0;

    for(int i = 2; i * i <= num; i++)
    {
        if(num % i == 0)
            return 0;
    }
    return 1;
}

/* Thread A Function */
void *primeSum(void *arg)
{
    clock_t start = clock();

    int count = 0, num = 2;
    long long sum = 0;

    while(count < N)
    {
        if(isPrime(num))
        {
            sum += num;
            count++;
        }
        num++;
    }

    clock_t end = clock();

    printf("\nThread A Result = %lld\n", sum);
    printf("Thread A Time = %.6f seconds\n",
           (double)(end - start)/CLOCKS_PER_SEC);

    pthread_exit(NULL);
}

/* Thread B Function */
void *thread1(void *arg)
{
    time_t start = time(NULL);

    while(time(NULL) - start < 100)
    {
        printf("Thread 1 running\n");
        sleep(2);
    }

    printf("Thread 1 completed\n");
    pthread_exit(NULL);
}

/* Thread C Function */
void *thread2(void *arg)
{
    time_t start = time(NULL);

    while(time(NULL) - start < 100)
    {
        printf("Thread 2 running\n");
        sleep(3);
    }

    printf("Thread 2 completed\n");
    pthread_exit(NULL);
}

int main()
{
    pthread_t A, B, C;

    signal(SIGINT, handle_sigint);

    printf("Enter N: ");
    scanf("%d", &N);

    pthread_create(&A, NULL, primeSum, NULL);
    pthread_create(&B, NULL, thread1, NULL);
    pthread_create(&C, NULL, thread2, NULL);

    pthread_join(A, NULL);
    pthread_join(B, NULL);
    pthread_join(C, NULL);

    printf("All threads completed.\n");

    return 0;
}
