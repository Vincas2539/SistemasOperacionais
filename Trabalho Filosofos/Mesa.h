#ifndef ____Mesa____
#define ____Mesa____

#include "filosofo.h"

// Classe de Lista Duplamente Encadeada
class Mesa{
	private:
		Filosofo *cabeca;
		int qtde, garfos, maxGarfos;
	public:
		Mesa();
		~Mesa() {};

		void setCabeca(Filosofo *cabeca){ this->cabeca = cabeca;	};
		Filosofo *getCabeca(){ return cabeca; };
		int getQtde(){ return qtde;	};
		void setQtde(int qtde) { this->qtde =  qtde; };

		bool insereOrdemCrescente(int chave, int dado);
		void mostraOrdemCrescente();

    bool getGarfo();
    bool putGarfo();
    void criaGarfo();
};

#endif