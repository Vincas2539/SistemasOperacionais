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

// 64kb stack
#define FIBER_STACK 1024 * 64

struct c {
  int saldo;
};

typedef struct c conta;

conta conta1, conta2;

// The child thread will execute this function

void *transferencia1(void *arg) {
  long mltp = (long) arg;
  int valor = mltp * rand()%500;
  if (conta1.saldo >= valor) { // 2
    conta1.saldo -= valor;
    conta2.saldo += valor;
    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", conta1.saldo);
    printf("Saldo de c2: %d\n", conta2.saldo);
  }else
    printf("ERRO! Saldo insuficiente, transferencia cancelada.\n");
  return 0;
}

void *transferencia2(void *arg) {
  long mltp = (long) arg;
  int valor = mltp * rand()%500;
  if (conta2.saldo >= valor) { // 2
    conta2.saldo -= valor;
    conta1.saldo += valor;
    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", conta1.saldo);
    printf("Saldo de c2: %d\n", conta2.saldo);
  }else
    printf("ERRO! Saldo insuficiente, transferencia cancelada.\n");
  return 0;
}

int main() {
  long thread;
  int thread_count = 20;
  int status;
  
  // Todas as contas começam com saldo 500
  conta1.saldo = 500;
  conta2.saldo = 500;
  
  int count = 0;
  
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

  printf("\n%d Transferencias Finalizadas!!\n", count);
  return 0;
}

