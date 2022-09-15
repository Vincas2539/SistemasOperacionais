#ifndef filosofo
#define filosofo

#include <iostream>
#include <unistd.h>

using namespace std;

class Filosofo { // declaração do objeto filosofo
private:
  bool comendo, pensando, faminto, talherEsq, talherDir;
  int id, timer, idGarfoDir, idGarfoEsq;

public:
  Filosofo(int id);

  int getId(){return id;};
  char getStatus();
  void setStatus(char id);

  bool tentaComer(int garfos[]);

  bool getGarfoDir(int g[]);
  bool getGarfoEsq(int g[]);
  void devolveGarfos(int g[]);

  void think();
  void fome();
  void comer();
  void morrer();

  int getTimer(){return timer;}
  void runTimer(){timer = timer-1;}
  void setTimer(int n);

  void rodar(int garfos[]);
};


#endif