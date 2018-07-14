#include <pthread.h> 
#include <stdio.h>
#include "csapp.h"
#include <math.h>
#include <stdlib.h>

void *thread(int num);

static int value; 

int main(int argc, char *argv[]){

  value  = atoi(argv[1]);

  if(value == 1){
    printf("Thread 0 done\n");
    return 0;
  }
  else{
  pthread_t tid_1;
  pthread_t tid_2;

  pthread_create(&tid_1, NULL, thread, 1);
  pthread_create(&tid_2, NULL, thread, 2);
  pthread_join(tid_1, NULL);
  pthread_join(tid_2, NULL);
  }
  printf("Thread 0 done\n");
  exit(0);
}

void *thread(int num)
{
  if(num >= (pow(2,value) - 2)){
    return NULL; 
  }
  if((2*num + 1) >= (pow(2,value) - 2)){
    printf("Thread %d done\n", num);
    return NULL;
  }
  else{
    int num_1;//this is just to avoid using global variables
    int num_2;
    num_1 =2*num + 1;
    num_2 =2*num+ 2;
    pthread_t uno;
    pthread_t dos;
    pthread_create(&uno, NULL, thread, num_1);
    pthread_create(&dos, NULL, thread, num_2);
    pthread_join(uno, NULL);
    pthread_join(dos, NULL);
    
    printf("Thread %d done\n", num);
    return NULL;
  }
}


