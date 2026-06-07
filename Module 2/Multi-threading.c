#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

int N;

int isPrime(int n){
    if(n<2) return 0;
    for(int i=2; i*i<=n; i++)
        if(n%i==0) return 0;
    return 1;
}

void* sum_Prime(void* arg){
    int count=0, sum=0;
    for(int i=2; count<N; i++)
        if(isPrime(i)){ sum+=i; count++; }
    printf("Sum of first %d primes = %d\n", N, sum);
    pthread_exit(NULL);
}

void* thread_1(void* arg){
    time_t t = time(NULL);
    while(time(NULL)-t < 100){
        printf("Thread 1 running\n");
        sleep(2);
    }
    pthread_exit(NULL);
}

void* thread_2(void* arg){
    time_t t = time(NULL);
    while(time(NULL)-t < 100){
        printf("Thread 2 running\n");
        sleep(3);
    }
    pthread_exit(NULL);
}

void main(){
    pthread_t t1, t2, t3;
    printf("Enter N: "); scanf("%d", &N);

    pthread_create(&t1, NULL, sum_Prime, NULL);
    pthread_create(&t2, NULL, thread_1, NULL);
    pthread_create(&t3, NULL, thread_2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("All threads done!\n");
}
