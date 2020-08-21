#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define NUM_THREADS 100
#define MAX_TRIES 10
#define MAXVAL 99999999999999999

/* Pthreads entry point */
void* randomFunc(void* arg)
{
    /*
    Create large random value,
    loop through to check if it is prime by finding 0 mod,
    return 0 if not prime, or the Prime Random number if it is prime.
    */

    unsigned long int to_test;
    arc4random_buf (&to_test , sizeof (to_test));
    to_test = to_test % MAXVAL ;

    int flag =1;
    for(int i =2; i <= sqrt(to_test); i++){
        if(to_test %i == 0) {     
            flag=0;
            break;
            }
    }
    if(flag==1){   return (void*)(long int)(to_test);}
    else{   return 0;}
     
}
int main(int argc, char *argv[])
{
    /* Stack-allocated thread id's and individual thread arguments */
    pthread_t tid[NUM_THREADS];
    int args[NUM_THREADS];
    for (int i=0; i< NUM_THREADS; i++)
    {
        args[i]=i;
        pthread_create(&tid[i], NULL, randomFunc, &args[i]);
    }
    for (int i=0; i< NUM_THREADS; i++)
    {
        void* ret;
        pthread_join(tid[i], &ret);
        if(ret == 0){   printf("thread %d reports no prime\n", i ); } 
        else printf("thread %d reports that %lu is prime\n", i, (unsigned long int) ret);

    }
    return 0;
}