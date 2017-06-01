#include "fila.h"
#include <stdlib.h>

int* fila;
int currentCount;  //Cantidad de valores actuales
int totalCount;    //Cantidad de valores agregados
int filaSize; //Tamaño del arreglo

int fila_init(int n){
  free(fila);//////////////////////Puede tronar////////////////////////
  fila = (int*)malloc(n*sizeof(int));
  currentCount, totalCount = 0;
  filaSize = n;
}

int pop(int* popTo){
  if(currentCount<=0)
    return -1;
  *popTo = fila[(totalCount-currentCount)%filaSize];
  return --currentCount;
}

int push(int toPush){
  if(currentCount==filaSize)
    return -1;
  fila[totalCount++%filaSize] = toPush;
  return ++currentCount;
}

int getCount(){
  return currentCount;
}