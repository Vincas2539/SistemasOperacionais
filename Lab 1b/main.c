#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void primeiroEX();
void segundoEX();

// Exercício 1
void primeiroEx() {
  char nomeArquivo[50], b, *linha;
  int x;
  FILE *entrada;

  printf("Digite o nome do arquivo desejado: ");
  scanf("%s", nomeArquivo);

  entrada = fopen(nomeArquivo, "r");
  if (entrada == NULL)
    printf("Arquivo não encontrado"); // mão está funcionando
  
  while (true) {
    linha = fgets(&b, 100, entrada);
    
    if (linha == NULL)
      break;
    else printf("%s", linha);
  }
  fclose(entrada);
}

// Exercício 2
void segundoEX(){
  char nomeArquivoEntrada[50], nomeArquivoSaida[50], *linha, b;
  int x;
  FILE *entrada, *saida;

  printf("Digite o nome do arquivo que deseja ler: ");
  scanf("%s", nomeArquivoEntrada);

  entrada = fopen(nomeArquivoEntrada, "r");
  if (entrada == NULL) printf("Arquivo não encontrado"); // não está funcionando

  printf("Digite o nome do arquivo que deseja escrever: ");
  scanf("%s", nomeArquivoSaida);
  saida = fopen(nomeArquivoSaida, "w");
  if (saida == NULL) printf("Não foi possível criar arquivo"); // não está funcionando
  
  while (true) {
    linha = fgets(&b, 100, entrada);
    
    if (linha != NULL){
      printf("%s", linha);
      fputs(linha, saida);
    } else break;
  }
  fclose(entrada);
  fclose(saida);
}

int main(void) {
  int a;
  

  while(a != 0){
    printf("\nEscolha o exercício a ser executado (0 para finalizar execução): ");
    scanf("%d", &a);
    if(a == 1){
      primeiroEx();
    } else if(a == 2){
      segundoEX();
    } else{
      printf("Escolha valores entre 1 e 2");
    }
  }
  return 0;
}
