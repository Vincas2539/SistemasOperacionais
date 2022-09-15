#ifndef filosofo
#define filosofo
#include "Mesa.h"

#include <iostream>
using namespace std;

class Filosofo {
private:
  bool comendo, pensando, faminto;
  int id, talher;
  Filosofo *esq, *dir;

public:
  Filosofo(Mesa *mesa, int id, Filosofo *esq, Filosofo *dir);

  int getId(){return id;};
  Filosofo *getEsq(){return esq;};
  Filosofo *getDir(){return dir;};

  bool getGarfo(Mesa *mesa);
  bool putGarfo(Mesa *mesa);
  void think();

};


#endif