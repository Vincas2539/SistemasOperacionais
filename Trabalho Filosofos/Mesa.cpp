#include <iostream>
#include "filosofo.h"
#include "Mesa.h"

using namespace std;

Mesa::Mesa(){
  this->cabeca = nullptr;
	this->qtde = 0;
  this->garfos = 0;
  this->maxGarfos = 0;
}


void Mesa::mostraOrdemCrescente(){
  if (cabeca == nullptr) 
    cout << "Lista vazia!" << endl;
	else{
		cout << "Lista: [ ";
		Filosofo *pAnda = this->cabeca;
		while (pAnda->getDir() != this->cabeca){
			cout << pAnda->getId() << " ";
			pAnda= pAnda->getDir();
		}
		cout << pAnda->getId() << "]";
	}
}

bool Mesa::insereOrdemCrescente(int chave, int dado){
	// Cria um novo no
	Filosofo *novoNo = new Filosofo(chave, dado, nullptr, nullptr);
	
	if (isFull()) return false;

	// se lista vazia, insere o nó no ponteiro cabeça
	// e faz o nó apontar para ele mesmo
	if (cabeca == nullptr) {
		this->cabeca = novoNo;
		novoNo->setProx(novoNo);
		novoNo->setAnt(novoNo);
	} else { 
	    // Caso contrário, procura posição de inserção
	    // na ordem crescente de valores
		No *pAnda = this->cabeca, *pAnt = nullptr;
		while (pAnda->getProx() != cabeca && pAnda->getChave() < chave){
				pAnt = pAnda;
				pAnda = pAnda->getProx();
		}	
		// Se não andou na lista e a chave que pAnda aponta
	    // é maior que a chave a ser inserida, significa que a chave
		// a ser inserida é antes do cabeça
		// e cabeça precisa ser redefinido
		if (pAnt == nullptr && pAnda->getChave() > chave){
			novoNo->setAnt(this->cabeca->getAnt());
			this->cabeca->getAnt()->setProx(novoNo);
			this->cabeca->setAnt(novoNo);
			novoNo->setProx(this->cabeca);
			this->cabeca = novoNo;
		} else {
			// Caso pAnda tenha caminhado na lista e
			// a chave que o pAnda aponta é maior do que a chave a ser inserido
			// insere o nó depois do ponteiro anterior pAnt
		 	if (pAnda->getChave() > chave && pAnt != nullptr) {	 
				pAnt->getProx()->setAnt(novoNo);
				novoNo->setProx(pAnda);
				pAnt->setProx(novoNo);
				novoNo->setAnt(pAnt);
			} else {// Senão, insere a chave depois do pAnda
		    	pAnda->getProx()->setAnt(novoNo);
				novoNo->setProx(pAnda->getProx());
				pAnda->setProx(novoNo);
				novoNo->setAnt(pAnda);
			}
		}
	}
	this->qtde++;
	return true;
}


bool Mesa::getGarfo(){
  if (garfos > 0){
    this->garfos -= 1;
    return true;
  }
  return false;
}


bool Mesa::putGarfo(){
  if(garfos < maxGarfos){
    this->garfos += 1;
    return true;
  }
  return false;
}


void Mesa::criaGarfo(){
  this->garfos += 1;
  this->maxGarfos += 1;
}


