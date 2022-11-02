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

struct c {
  int saldo;
};

typedef struct c conta;
conta conta1, conta2;
int erros = 0;

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
      printf("ERRO! Saldo insuficiente, transferencia cancelada.\n");
      erros++;
      break;
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
      printf("ERRO! Saldo insuficiente, transferencia cancelada.\n");
      erros++;
      break;
    }
    countT2++;
    sleep(1);
  }
  return 0;
}

int main(int argc, char *argv[]) {
  long thread;
  int thread_count;
  int status;
  
  if (argc != 2){
    printf("Inserir apenas a quantidade de transferencias por conta que deseja executar!\n");
    return EXIT_FAILURE;
  }else
    thread_count = atoi(argv[1]);

  // Todas as contas começam com saldo 500
  conta1.saldo = 1000;
  conta2.saldo = 1000;
  
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

  int tr = count - erros;
  printf("\n%d Transferencias Finalizadas!\n%d bem sucedidas e %d com erro.\n", count, tr, erros);
  return 0;
}

