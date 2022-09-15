#include <iostream>
#include "filosofo.h"
#include "Mesa.h"

using namespace std;

Filosofo::Filosofo(Mesa *mesa, int id, Filosofo *esq, Filosofo *dir){
  comendo = false;
  pensando = false;
  faminto = true;
  this->id = id;
  mesa.criaGarfo();
}

bool Filosofo::getGarfo(Mesa *mesa){
  if (mesa.getgarfo()){
    this->garfo += 1;
    return true;
  }
  return false;
}

bool Filosofo::putGarfo(Mesa *mesa){
  mesa.putGarfo();
  this->garfo -= 1;
  return true
}

void Filosofo::think(){
  cout << "Filosofo " << id << "está pensando!" << endl;
}