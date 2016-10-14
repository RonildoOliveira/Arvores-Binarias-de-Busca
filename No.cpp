#include <iostream>
#include "No.h"

No::No(int elem)
{
    this->elemento = elem;

    this->setNoDir(NULL);
    this->setNoEsq(NULL);
    this->setNoPai(NULL);

    this->balanceamento = 0;
    this->altura = 0;
    this->vermelho = false;
}

No *No::getNoDir()
{
   return this->noDir;
}

void No::setNoDir(No *no)
{
    this->noDir = no;
}

No *No::getNoEsq()
{
    return this->noEsq;
}

void No::setNoEsq(No *no)
{
    this->noEsq = no;
}

int No::getElemNo()
{
    if (this == NULL) {
        return -1;
    }else{
        return this->elemento;
    }

}

void No::setElemNo(int novoElem)
{
    this->elemento = novoElem;
}

No *No::getNoPai()
{
    return this->noPai;
}

void No::setNoPai(No *no)
{
    this->noPai = no;
}

int No::getBalanceamento()
{
    if (this != NULL) {
        return this->balanceamento;
    }else{
        return 0;
    }
}

void No::setBalanceamento(int bal)
{
    this->balanceamento = bal;
}

void No::setAltura(int novaAltura)
{
    this->altura = novaAltura;
}

bool No::ehVermelho()
{
    if (this != NULL) {
        return this->vermelho;
    }else{
        return false;
    }

}

void No::setVermelho(bool cor)
{
    this->vermelho = cor;
}

No::~No()
{
    //dtor
}
