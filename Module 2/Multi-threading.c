#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int N;

/* Function to check whether a number is prime */
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

/* Thread A */
void *primeSum(void *arg)
{
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

    printf("Sum of first %d prime numbers = %lld\n", N, sum);
    pthread_exit(NULL);
}

/* Thread B */
void *thread1(void *arg)
{
    time_t start = time(NULL);

    while(time(NULL) - start < 100)
    {
        printf("Thread 1 running\n");
        sleep(2);
    }

    pthread_exit(NULL);
}

/* Thread C */
void *thread2(void *arg)
{
    time_t start = time(NULL);

    while(time(NULL) - start < 100)
    {
        printf("Thread 2 running\n");
        sleep(3);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t t1, t2, t3;

    printf("Enter N: ");
    scanf("%d", &N);

    pthread_create(&t1, NULL, primeSum, NULL);
    pthread_create(&t2, NULL, thread1, NULL);
    pthread_create(&t3, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}
