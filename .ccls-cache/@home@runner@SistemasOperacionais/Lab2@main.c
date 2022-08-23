#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void primeiroEX();
void segundoEX();
// Exercício 1
void primeiroEx() {
  char nomeArquivo[50], linha;
  int x, b;
  FILE *entrada;

  printf("Digite o nome do arquivo desejado: ");
  scanf("%s", nomeArquivo);

  entrada = fopen(nomeArquivo, "r");
  if (entrada == NULL)
    printf("Arquivo não encontrado");
  while (true) {
    b = fscanf(entrada, "%s", &linha);
    printf("%s\n", &linha);
    if (b != 1)
      break;
  }
  fclose(entrada);
}

// Exercício 2

int main(void) {
  char nomeArquivo[50], linha;
  int x, b;
  FILE *entrada;

  printf("Digite o nome do arquivo desejado: ");
  scanf("%s", nomeArquivo);

  entrada = fopen(nomeArquivo, "r");
  if (entrada == NULL)
    printf("Arquivo não encontrado");
  while (true) {
    b = fscanf(entrada, "%s", &linha);
    printf("%s\n", &linha);
    if (b != 1)
      break;
  }
  fclose(entrada);
  return 0;
}
