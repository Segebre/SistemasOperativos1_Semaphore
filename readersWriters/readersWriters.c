#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define ARRAY_SIZE 20
#define READERS 1
#define WRITERS 3

void* read(void* var);
void* write(void* var);
pthread_mutex_t mutexRead, mutexWrite;
int numbers[ARRAY_SIZE];
int readingCount, status;

int main(int argc, char const *argv[])
{
  int i;
  readingCount, status = 0;
  pthread_mutex_init(&mutexRead, NULL);
  pthread_mutex_init(&mutexWrite, NULL);
  pthread_t tidRead[READERS], tidWrite[WRITERS];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  for(i=0; i<WRITERS; i++)
    pthread_create(&tidWrite[i], &attr, write, NULL);
  for(i=0; i<READERS; i++)
    pthread_create(&tidRead[i], &attr, read, NULL);

  for(i=0; i<WRITERS; i++)
    pthread_join(tidRead[i], NULL);
  for(i=0; i<READERS; i++)
    pthread_join(tidWrite[i], NULL);
  return 0;
}

void* read(void* var){
    int i;
  while(1){
    pthread_mutex_lock(&mutexRead);
    if(++readingCount==1)
      pthread_mutex_lock(&mutexWrite);
    pthread_mutex_unlock(&mutexRead);
    for(i=0; i<ARRAY_SIZE; i++)
      printf("%d", numbers[i]);
    printf("\n");
    pthread_mutex_lock(&mutexRead);
    if(--readingCount==0)
      pthread_mutex_unlock(&mutexWrite);
    pthread_mutex_unlock(&mutexRead);
  }
  pthread_exit(0);
}

void* write(void* var){
    int i;
  while(1){
    pthread_mutex_lock(&mutexWrite);
    for(i=0; i<ARRAY_SIZE; i++)
      numbers[i] = status;
    status = status?0:1;
    pthread_mutex_unlock(&mutexWrite);
  }
  pthread_exit(0);
}