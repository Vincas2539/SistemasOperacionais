#include <iostream>
#include <unistd.h>
#include <time.h>
#include "filosofo.h"

using namespace std;

int d = 1; // altera o tempo em segundos dos sleep


// cria filosofo
Filosofo::Filosofo(int id){

  // signals (utilizado para a comunicação entre processos)
  comendo = false;
  pensando = true;
  faminto = false;

  // talheres
  talherEsq = false;
  talherDir = false;

  this->id = id; // id do filosofo
  
  srand(time(NULL) + id); // seed para o timer para variar com o id e com o tempo do computador
  this->timer = (rand() % 9) + 1; // timer de iterações necessárias para ele fazer uma ação

  if (id >= 5)
    idGarfoDir = 0; // id do garfo a direita para o ultimo filosofo
  else
    idGarfoDir = id; // id do garfo a direita do filosofo

  idGarfoEsq = id - 1; // id do carfo a esquerda do filosofo
}


// retorna se o filosofo está comendo, pensando ou com fome. (signal)
char Filosofo::getStatus(){
  if (comendo == true)
    return 'c';
  if (pensando == true)
    return 'p';
  if (faminto == true)
    return 'f';
  return 'e'; // se der algum problema ele retorna e (não sei se é possivel dar erro... rs)
}


// indica se o filosofo esta comendo, pensando ou com fome. (signal)
void Filosofo::setStatus(char id){
  if (id == 'c'){ 
    comendo = true; // indica que está comendo
    pensando = false;
    faminto = false;
  } else if (id == 'p'){
    comendo = false;
    pensando = true; // indica que esta pensando
    faminto = false;
  } else if (id == 'f'){
    comendo = false;
    pensando = false;
    faminto = true; // indica que esta com fome
  }
}


// o C++ passa g[] como referencia, assim alterando o valor no main
bool Filosofo::getGarfoDir(int g[]){ 
  if (g[idGarfoDir] == 1){
    talherDir = true;
    g[idGarfoDir] = 0;
    return true;
  }
  else
    return false;
}


// tenta pegar o garfo a esquerda dele e retorna se conseguiu ou não
bool Filosofo::getGarfoEsq(int g[]){
  if (g[idGarfoEsq] == 1){
    talherEsq = true;
    g[idGarfoEsq] = 0;
    return true;
  }
  else
    return false;
}


// tenta pegar o garfo a direita dele e retorna se conseguiu ou não
void Filosofo::devolveGarfos(int g[]){
  if (talherDir == true){
    talherDir = false;
    g[idGarfoDir] = 1;
  }
  
  if (talherEsq == true){
    talherEsq = false;
    g[idGarfoEsq] = 1;
  }
}


void Filosofo::think(){
  cout << "Filosofo " << id << " está pensando!" << "\tTimer: " << getTimer() << endl;
  sleep(d); // sleep usado apenas para o print
}


void Filosofo::comer(){
  cout << "Filosofo " << id << " está comendo!" << "\tTimer: " << getTimer() << endl;
  sleep(d); // sleep usado apenas para o print
}


void Filosofo::fome(){
  cout << "Filosofo " << id << " está com fome!" << "\tTimer: " << getTimer() << endl;
  sleep(d); // sleep usado apenas para o print 
}


void Filosofo::morrer(){
  cout << "Filosofo " << id << " morreu de fome! (starvation)" << "\tTimer: " << getTimer() << endl;
  sleep(d); // sleep usado apenas para o print
}


// inicia o timer
void Filosofo::setTimer(int n){
  srand(time(NULL) + id);
  if (n == 0)
    this->timer = (rand() % 9) + 1; // timer de iterações necessárias para ele trocar de ação
  else
    this->timer = 10; // timer para quando o processo não conseguir acessar o recurso, ele tem 10 iterações até morrer
}


// função para verificar se há garfos disponiveis ao redor do filosofo
bool Filosofo::tentaComer(int garfos[]){
  bool t1, t2;
  t1 = getGarfoEsq(garfos);
  t2 = getGarfoDir(garfos);
  
  if (t1 == true && t2 == true){
    setStatus('c');
    setTimer(0);
    comer();
    t1 = false;
    t2 = false;
    return true;
  } 
  devolveGarfos(garfos);
  return false;
}


// função que faz o filosofo tentar realizar a ação que ele deseja
void Filosofo::rodar(int garfos[]){ 
  if (getTimer() > 0){
    runTimer();
    if (getStatus() == 'c')
      comer();
    else if (getStatus() == 'p'){
      think();
    } else if (getStatus() == 'f'){
      if (!tentaComer(garfos))
        fome();
    } else if(getStatus() == 'e'){
      cout << "Erro!" << endl;
    }

  }else {
    if (getStatus() == 'c'){
    devolveGarfos(garfos);
    setStatus('p');
    setTimer(0);
    think();
    } else if (getStatus() == 'f')
      morrer();
    else if (!tentaComer(garfos)){
      setStatus('f');
      setTimer(1);
      fome();
    }
  }
}