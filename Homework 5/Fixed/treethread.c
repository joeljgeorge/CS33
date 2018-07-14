#include <pthread.h> 
#include <stdio.h>
#include "csapp.h"
#include <math.h>
#include <stdlib.h>

void *thread(void *vargp);

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
  int a = 1;
  int b = 2;
  int* intptr1 = (int*)malloc(sizeof(a));
  int* intptr2 = (int*)malloc(sizeof(b));
  *intptr1 = a;
  *intptr2 = b;
  pthread_create(&tid_1, NULL, thread, intptr1);
  pthread_create(&tid_2, NULL, thread, intptr2);
  pthread_join(tid_1, NULL);
  pthread_join(tid_2, NULL);
  }
  printf("Thread 0 done\n");
  exit(0);
}

void *thread(void *vargp)
{
  int* local_ptr = (int*)vargp;
  int num = *local_ptr;
  free(local_ptr); 

  if(num > (pow(2,value) - 2)){
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
    int* ptr1 = malloc(sizeof(num_1));
    int* ptr2 = malloc(sizeof(num_2));
    pthread_t uno;
    pthread_t dos;
    *ptr1 = num_1;
    *ptr2 = num_2;
    pthread_create(&uno, NULL, thread, ptr1);
    pthread_create(&dos, NULL, thread, ptr2);
    pthread_join(uno, NULL);
    pthread_join(dos, NULL);
    
    printf("Thread %d done\n", num);
    return NULL;
  }
}


