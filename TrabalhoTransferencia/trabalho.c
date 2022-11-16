#define _GNU_SOURCE
#include <malloc.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>

void *transferencia1(void *arg);
void *transferencia2(void *arg);

struct c {
  int saldo;
};

typedef struct c conta;
conta conta1, conta2;
int mais = 0;
int count = 0;
int thread_count = 100;

// The child thread will execute this function

void *transferencia1(void *arg) {
  long mltp = (long) arg;
  int valor = (mltp * rand())%250;
  int countT1 = 0;
  
  while(1){
    if (conta1.saldo >= valor) { // 2
      conta1.saldo -= valor;
      conta2.saldo += valor;
      printf("Transferência concluída com sucesso!\n");
      printf("Saldo de c1: %d\n", conta1.saldo);
      printf("Saldo de c2: %d\n", conta2.saldo);
      break;
    }else if (countT1 > (rand()%5)){
      pthread_t thread2;
      pthread_create(&thread2, NULL, transferencia2, (void *) mltp);
      pthread_join(thread2, NULL);
      mais++;
      countT1=0;
    }
    countT1++;
    sleep(1);
  }
  return 0;
}

void *transferencia2(void *arg) {
  long mltp = (long) arg;
  int valor = (mltp * rand())%250;
  int countT2 = 0;
  
  while(1){
    if (conta2.saldo >= valor) { // 2
      conta2.saldo -= valor;
      conta1.saldo += valor;
      printf("Transferência concluída com sucesso!\n");
      printf("Saldo de c1: %d\n", conta1.saldo);
      printf("Saldo de c2: %d\n", conta2.saldo);
      break;
    }else if (countT2 > (rand()%5)){
      pthread_t thread1;
      pthread_create(&thread1, NULL, transferencia1, (void *) mltp);
      pthread_join(thread1, NULL);

      mais++;
      countT2=0;
    }
    countT2++;
    sleep(1);
  }
  return 0;
}

int main() {
  long thread;
  int status;


  // Todas as contas começam com saldo 1000
  conta1.saldo = 1000;
  conta2.saldo = 1000;
  
  pthread_t* threads1 = (pthread_t*) malloc(thread_count * sizeof(pthread_t));
  pthread_t* threads2 = (pthread_t*) malloc(thread_count * sizeof(pthread_t));
  
  for (thread = 0; thread < thread_count; thread++) {
    status = pthread_create(&threads1[thread], NULL, transferencia1, (void *) thread);
    if (status != 0)
      printf("Deu BO na thread. Status: %d", status);
    count++;
    status = pthread_create(&threads2[thread], NULL, transferencia2, (void *) thread);
    if (status != 0)
      printf("Deu BO na thread. Status: %d", status);
    count++;
  }

  for (thread = 0; thread < thread_count; thread++) {
    pthread_join(threads1[thread], NULL);
    if (status != 0)
      printf("A thread morreu. Status: %d", status);
    pthread_join(threads2[thread], NULL);
    if (status != 0)
      printf("A thread morreu. Status: %d", status);
  }

  int tr = count + mais;
  printf("\n%d Transferencias Finalizadas!\n%d selecionadas e %d a mais.\n", tr, count, mais);
  return 0;
}

