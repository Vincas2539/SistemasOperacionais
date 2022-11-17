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

// Definição das funções que geram as transações
void *transferencia1(void *arg); //definição das funções para poder consumi-las depois, senão da erro 
void *transferencia2(void *arg);

// Definição da Struct Conta 
struct c {
  int saldo;
};

// Criação das Contas 
typedef struct c conta;
conta conta1, conta2;
// Variável que conta quantidade de threads criadas a mais
int mais = 0;
// Variável que conta quantidade de threads criadas
int count = 0;
// Variável que armazena quantidade de threads(transferênicas) a serem criadas em cada conta
int thread_count = 100;

// Função que gera as transações da conta 1 
void *transferencia1(void *arg) {
  // Variável que garante que os valores de tranferência sejam diferentes entre cada transação
  long mltp = (long) arg;
  // Variável que recebe o valor a ser transferido
  int valor = (mltp * rand())%250;
  // Contador de tempo que a função aguarda para que a conta receber dinheiro o suficiente para relizar a transação
  int countT1 = 0;

  // Age como a função signal
  while(1){
    // Verifica se a conta tem saldo suficiente para realizar a transação
    if (conta1.saldo >= valor) { 
      // Realiza a transação
      conta1.saldo -= valor;
      conta2.saldo += valor;
      printf("Transferência concluída com sucesso!\n");
      printf("Saldo de c1: %d\n", conta1.saldo);
      printf("Saldo de c2: %d\n", conta2.saldo);
      // Sai do laço infinito
      break; 
    
      // Verifica se a thread já aguardou tempo suficiente para a conta ter saldo
    }else if (countT1 > (rand()%5)){
      // Cria uma transação para a conta atual
      pthread_t thread2;
      pthread_create(&thread2, NULL, transferencia2, (void *) mltp);
      pthread_join(thread2, NULL);
      
      // Adiciona 1 na variável que conta as threads criadas a mais
      mais++;
      // Zera o contador para caso seja necessária a execução do else if novamente
      countT1=0;
    }
    // Adiciona 1 no contador e espera 1 segundo (período de espera para a conta ter saldo)
    countT1++;
    sleep(1);
  }
  return NULL;
}

// Função que gera as transações da conta 2
void *transferencia2(void *arg) {
   // Variável que garante que os valores de tranferência sejam diferentes entre cada transação
  long mltp = (long) arg;
  // Variável que recebe o valor a ser transferido
  int valor = (mltp * rand())%250;
  // Contador de tempo que a função aguarda para que a conta receber dinheiro o suficiente para relizar a transação
  int countT2 = 0;

  // Age como a função signal
  while(1){
    // Verifica se a conta tem saldo suficiente para realizar a transação
    if (conta2.saldo >= valor) { 
      // Realiza a transação
      conta2.saldo -= valor;
      conta1.saldo += valor;
      printf("Transferência concluída com sucesso!\n");
      printf("Saldo de c1: %d\n", conta1.saldo);
      printf("Saldo de c2: %d\n", conta2.saldo);
      // Sai do laço infinito
      break;
      
    // Verifica se a thread já aguardou tempo suficiente para a conta ter saldo
    }else if (countT2 > (rand()%5)){
      // Cria uma transação para a conta atual
      pthread_t thread1;
      pthread_create(&thread1, NULL, transferencia1, (void *) mltp);
      pthread_join(thread1, NULL);

      // Adiciona 1 na variável que conta as threads criadas a mais
      mais++;
       // Zera o contador para caso seja necessária a execução do else if novamente
      countT2=0;
    }
    // Adiciona 1 no contador e espera 1 segundo (período de espera para a conta ter saldo)
    countT2++;
    sleep(1);
  }
  return NULL;
}

int main() {
  // Contador para criação das threads | arg passado para thread (mltp)
  long thread;
  // Variável que indica se a thread foi criada com sucesso ou não
  int status;


  // Todas as contas começam com saldo 1000
  conta1.saldo = 1000;
  conta2.saldo = 1000;

  // Alocando o vetor que armazena as threads, dinamicamente, na memória  
  pthread_t* threads1 = (pthread_t*) malloc(thread_count * sizeof(pthread_t));
  pthread_t* threads2 = (pthread_t*) malloc(thread_count * sizeof(pthread_t));

  // Laço que cria as threads e armazena em seus respectivos vetores
  for (thread = 0; thread < thread_count; thread++) {
    
    status = pthread_create(&threads1[thread], NULL, transferencia1, (void *) thread);
    // Verifica se a thread foi criada com sucesso
    if (status != 0)
      printf("Deu BO na thread. Status: %d", status);
    // Adiciona 1 na variável que conta as threads criadas
    count++;
    
    status = pthread_create(&threads2[thread], NULL, transferencia2, (void *) thread);
    // Verifica se a thread foi criada com sucesso
    if (status != 0)
      printf("Deu BO na thread. Status: %d", status);
    // Adiciona 1 na variável que conta as threads criadas
    count++;
  }

  // Laço que permite a execução das threads 
  for (thread = 0; thread < thread_count; thread++) {
    pthread_join(threads1[thread], NULL);
    pthread_join(threads2[thread], NULL);
  }

  // Threads criadas no total
  int tr = count + mais;
  printf("\n%d Transferencias Finalizadas!\n%d selecionadas e %d a mais.\n", tr, count, mais);
  return 0;
}
