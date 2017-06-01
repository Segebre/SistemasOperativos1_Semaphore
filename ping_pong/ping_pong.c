#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

void* printPing(void* var);
void* printPong(void* var);
sem_t semaphorePing, semaphorePong;

int main(int argc, char const *argv[])
{
  sem_init(&semaphorePing, 0, 1);
  sem_init(&semaphorePong, 0, 0);
  pthread_t tid1, tid2;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&tid1, &attr, printPing, NULL);
  pthread_create(&tid2, &attr, printPong, NULL);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  return 0;
}

void* printPing(void* var){
  while(1){
    sem_wait(&semaphorePing);
    printf("%s\n", "Ping!");
    sem_post(&semaphorePong);
  }
  pthread_exit(0);
}

void* printPong(void* var){
  while(1){
    sem_wait(&semaphorePong);
    printf("%s\n", "Pong!");
    sem_post(&semaphorePing);
  }
  pthread_exit(0);
}