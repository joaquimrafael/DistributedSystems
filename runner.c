/*Laboratorio de Computacao Distribuida
Joaquim Rafael Mariano Prieto Pereira - 10408805
Exercicio: Corrida de Threads com Sincronizacao*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NUM_RUNNERS 5
int position = 1;
sem_t semaphore;

void* corredor(void* arg) {
    int id = *(int*)arg;
    int time = (rand() % 5) + 1;

    printf("Runner %d started with the time: %d\n", id, time);

    sleep(time);
    sem_wait(&semaphore);

    int arrivalPosition = position;
    position++;
    printf("Runner %d finished in %dº place!\n", id, arrivalPosition);

    sem_post(&semaphore);

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t threads[NUM_RUNNERS];
    int thread_ids[NUM_RUNNERS] = {1,2,3,4,5};

    srand(time(NULL));

    if (sem_init(&semaphore, 0, 1) != 0) {
        fprintf(stderr, "semaphoreaphore start error\n");
        return 1;
    }

    printf("Run started!\n");

    for(int i = 0;i < NUM_RUNNERS;i++){
        if(pthread_create(&threads[i], NULL, corredor, (void*) &thread_ids[i])){
            fprintf(stderr, "Unable to create thread %d\n",i+1);
            return 1;
        }
    }

    for(int j=0;j<NUM_RUNNERS;j++){
        pthread_join(threads[j], NULL);
    }

    sem_destroy(&semaphore);

    printf("Finish RUN\n");
    return 0;
}
