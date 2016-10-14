#include <iostream>
#include <iomanip>

#include "No.h"
#include "ArvoreBinaria.h"

using namespace std;

std::vector<No> lista;

ArvoreBinaria::ArvoreBinaria(No *no)
{
    this->noRaiz = no;
}

No *ArvoreBinaria::getRaiz()
{
    return this->noRaiz;
}

void ArvoreBinaria::setRaiz(No * no)
{
    this->noRaiz = no;
}

bool ArvoreBinaria::inserirAB(int elem)
{
    if (buscar(this->getRaiz(),elem) != NULL) {
        return false;
    }else{
        No *z = new No(elem);
        No *y = NULL;
        No *x = this->getRaiz();

        while (x!= NULL) {
            y = x;
            if (z->getElemNo() < x->getElemNo()) {
                x = x->getNoEsq();
            } else {
                x = x->getNoDir();
            }
        }
        if (y == NULL) {
            this->setRaiz(z);
        } else if(z->getElemNo() < y->getElemNo()){
            y->setNoEsq(z);
        }else{
            y->setNoDir(z);
        }
        return true;
    }
}

bool ArvoreBinaria::removerNo(No *no,int elem)
{
    if(no == NULL)
            return false;
        No* ant = NULL;
        No* atual = no;
        while(atual != NULL){
            if(elem == atual->getElemNo()){
                if(atual == no)
                    no = removeAtual(atual);
                else{
                    if(ant->getNoDir() == atual)
                        ant->setNoDir(removeAtual(atual));
                    else
                        ant->setNoEsq(removeAtual(atual));
                }
                return true;
            }

            ant = atual;

            if(elem > atual->getElemNo())
                atual = atual->getNoDir();
            else
                atual = atual->getNoEsq();
        }
        return false;
}

No *ArvoreBinaria::removeAtual(No *no)
{
    No *no1, *no2;

    if(no->getNoEsq() == NULL){
        no2 = no->getNoDir();
        return no2;
    }
    no1 = no;
    no2 = no->getNoEsq();

    while(no2->getNoDir() != NULL){
        no1 = no2;
        no2 = no2->getNoDir();
    }

    if(no1 != no){
        no1->setNoDir(no2->getNoEsq());
        no2->setNoEsq(no->getNoEsq());
    }

    no2->setNoDir(no->getNoDir());
    return no2;
}



int ArvoreBinaria::totalNos(No *no)
{
    if (no == NULL)
        return 0;
    int nos_esq = totalNos(no->getNoEsq());
    int nos_dir = totalNos(no->getNoDir());
    return(nos_esq + nos_dir + 1);
}

int ArvoreBinaria::altura(No *no)
{
    if (no == NULL) {
        return -1;
    }
    if (no->getNoEsq() == NULL && no->getNoDir() == NULL) {
        return 0;
    }else if (no->getNoEsq() == NULL){
        return 1 + altura(no->getNoDir());
    }else if(no->getNoDir() == NULL){
        return 1 + altura(no->getNoEsq());
    }else{
        return 1 + max(altura(no->getNoEsq()),altura(no->getNoDir()));
    }
}

int ArvoreBinaria::balanceamentoNo(No *no)
{
    int alturaDir = this->altura(no->getNoDir());
    int alturaEsq = this->altura(no->getNoEsq());
    return alturaDir - alturaEsq;
}

int ArvoreBinaria::sucNo(No *no)
{
    if (no->getNoDir() != NULL) {
        return minimo(no->getNoDir());
    }else{
        return -1;
    }
}

int ArvoreBinaria::antNo(No *no)
{
    if (no->getNoEsq() != NULL) {
        return maximo(no->getNoEsq());
    }else{
        return -1;
    }
}

No * ArvoreBinaria::buscar(No *no, int valor)
{
    if(no == NULL){
        return NULL;
    }
    if(no->getElemNo() == valor){
        return no;
    }
    if (valor < no->getElemNo()) {
        return buscar(no->getNoEsq(), valor);
    }else{
        return buscar(no->getNoDir(), valor);
    }
}

int ArvoreBinaria::minimo(No *no)
{
    while(no->getNoEsq() != NULL)
        no = no->getNoEsq();
    return no->getElemNo();
}

int ArvoreBinaria::maximo(No *no)
{
    while (no->getNoDir() != NULL)
        no = no->getNoDir();
    return no->getElemNo();
}

void ArvoreBinaria::emOrdem(No *no)
{
    if(no != NULL){
        emOrdem(no->getNoEsq());
        cout << " " << no->getElemNo() << " ";
        emOrdem(no->getNoDir());
    }
}

void ArvoreBinaria::preOrdem(No *no)
{
    if (no != NULL) {
        cout << " " << no->getElemNo() << " ";
        preOrdem(no->getNoEsq());
        preOrdem(no->getNoDir());
    }
}

void ArvoreBinaria::posOrdem(No *no)
{
    if (no != NULL) {
        posOrdem(no->getNoEsq());
        posOrdem(no->getNoDir());
        cout << " " << no->getElemNo() << " ";
    }
}

std::vector<No> ArvoreBinaria::vetorPosOrdem(No *no)
{
    if (no != NULL) {
        vetorPosOrdem(no->getNoEsq());
        vetorPosOrdem(no->getNoDir());
        lista.push_back(*no);
    }
    return lista;
}

ArvoreBinaria::~ArvoreBinaria()
{
    //dtor
}
