#include <iostream>
#include <unistd.h>
#include <time.h>
#include "filosofo.h"

using namespace std;

int main() {
  // cria filosofos
  Filosofo *F1 = new Filosofo(1);
  Filosofo *F2 = new Filosofo(2);
  Filosofo *F3 = new Filosofo(3);
  Filosofo *F4 = new Filosofo(4);
  Filosofo *F5 = new Filosofo(5);

  // adiciona os filosofos em uma lista
  Filosofo *filosofos[5] {F1, F2, F3, F4, F5};

  // cria um indice para cada garfo de cada filosofo (funciona como um sinal, indicando se o recurso está disponível para a thread utilizar ou não)
  int garfos[5] {1, 1, 1, 1, 1};

  int c = 1; // contador de iterações
  
  Filosofo *F; // ponteiro para percorrer a lista de filosofos

  // iteração infinita
  while(true){
    cout << "Iteração " << c << endl;
    for(int a = 0; a < 5; a++){ // iteração para percorrer a lista de filosofos
      F = filosofos[a];
      F->rodar(garfos); // rodar a função de tentar comer ou pensar por filosofo
    }
    cout << endl;
    c++;
  }
  return 0;
}