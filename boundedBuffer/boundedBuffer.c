#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "fila.h"

#define ARRAY_SIZE 10
#define PRODUCERS 10
#define CONSUMERS 10

void* produce(void* var);
void* consume(void* var);
sem_t semaphoreProduce, semaphoreConsume;
pthread_mutex_t mutex;

int main(int argc, char const *argv[])
{
  int i;
  fila_init(ARRAY_SIZE);
  sem_init(&semaphoreProduce, 0, ARRAY_SIZE);
  sem_init(&semaphoreConsume, 0, 0);
  pthread_t tidProduce[PRODUCERS], tidConsume[CONSUMERS];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  for(i=0; i<PRODUCERS; i++)
    pthread_create(&tidProduce[i], &attr, produce, NULL);
  for(i=0; i<CONSUMERS; i++)
    pthread_create(&tidConsume[i], &attr, consume, NULL);
  for(i=0; i<PRODUCERS; i++)
    pthread_join(tidProduce[i], NULL);
  for(i=0; i<CONSUMERS; i++)
    pthread_join(tidConsume[i], NULL);
  return 0;
}

void* produce(void* var){
  int count=0;
  while(1){
    sem_wait(&semaphoreProduce);
    pthread_mutex_lock(&mutex);
    if(push(count++)==-1)
      printf("ERROR PUSH!");
    pthread_mutex_unlock(&mutex);
    sem_post(&semaphoreConsume);
  }
  pthread_exit(0);
}

void* consume(void* var){
  int temp;
  while(1){
    sem_wait(&semaphoreConsume);
    pthread_mutex_lock(&mutex);
    if(pop(&temp)==-1)
      printf("ERROR POP!");
    printf("%d, ", temp);
    pthread_mutex_unlock(&mutex);
    sem_post(&semaphoreProduce); //////////////////////Si comento esto, porque no funciona?//////////////////////////
  }
  pthread_exit(0);
}

//Fila test code
  // int size = 10;
  // int temp, i, status;
  // fila_init(size);
  // for(i=0; i<size+7; i++)
  //   printf("Status: %s, Pushed: %d\n", ((push(i+3)==-1)?"Failed":"Success"), i+3);
  // pop(&temp);
  // pop(&temp);
  // pop(&temp);
  // push(1);
  // push(2);
  // for(i=0; i<size+7; i++){
  //   status = pop(&temp);
  //   printf("Status: %s, Poped: %d\n", ((status==-1)?"Failed":"Success"), temp);
  // }