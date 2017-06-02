#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define ARRAY_SIZE 20

void* read(void* var);
void* write(void* var);
sem_t semaphoreRead, semaphoreWrite;
int numbers[ARRAY_SIZE];
int status;

int main(int argc, char const *argv[])
{
  status = 0;
  sem_init(&semaphoreRead, 0, 0);
  sem_init(&semaphoreWrite, 0, 1);
  pthread_t tidRead, tidWrite;
  pthread_t tidRead2, tidWrite2;
  pthread_t tidRead3, tidWrite3;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&tidRead, &attr, read, NULL);
  pthread_create(&tidRead2, &attr, read, NULL);
  pthread_create(&tidRead3, &attr, read, NULL);
  pthread_create(&tidWrite, &attr, write, NULL);
  pthread_create(&tidWrite2, &attr, write, NULL);
  pthread_create(&tidWrite3, &attr, write, NULL);
  pthread_join(tidRead, NULL);
  pthread_join(tidWrite, NULL);
  pthread_join(tidRead2, NULL);
  pthread_join(tidWrite2, NULL);
  pthread_join(tidRead3, NULL);
  pthread_join(tidWrite3, NULL);
  return 0;
  return 0;
}

void* read(void* var){
  while(1){
    int i, writing;
    do
      sem_getvalue(&semaphoreWrite, &writing);
    while(writing==0);
    sem_post(&semaphoreRead);
    for(i=0; i<ARRAY_SIZE; i++)
      printf("%d", numbers[i]);
    // printf("R");
    // printf("R");
    // printf("R");
    // printf("R");
    // printf("R");
    // printf("R");
    // printf("R");
    // printf("R");
    // printf("R");
    // printf("R");
    printf("\n");
    sem_wait(&semaphoreRead);
  }
  pthread_exit(0);
}

void* write(void* var){
  while(1){
    int i, reading;
    sem_wait(&semaphoreWrite);
    do
      sem_getvalue(&semaphoreRead, &reading);
    while(reading!=0);
    for(i=0; i<ARRAY_SIZE; i++)
      numbers[i] = status;
    // printf("WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    status = status?0:1;
    sem_post(&semaphoreWrite);
  }
  pthread_exit(0);
}