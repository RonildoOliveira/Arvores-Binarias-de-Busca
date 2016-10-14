#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "No.h"
#include "ArvoreBinaria.h"
#include "AVL.h"

using namespace std;

AVL::AVL(No *no):ArvoreBinaria(no)
{
    this->noRaiz = no;
}

void AVL::inserirAVL(int elem)
{
    No * no = new No(elem);
    inserirABAVL(this->getRaiz(), no);
}

void AVL::setBalanco(No * no) {
        no->setBalanceamento(altura(no->getNoDir())-altura(no->getNoEsq()));
    }


void AVL::verificarBalanceamento(No * noAtual) {
        setBalanco(noAtual);

        int balanceamento = noAtual->getBalanceamento();

        if (balanceamento == -2) {
            if (altura(noAtual->getNoEsq()->getNoEsq()) >= altura(noAtual->getNoEsq()->getNoDir())) {
                noAtual = rotacaoDireita(noAtual);
            } else {
                noAtual = duplaRotacaoEsquerdaDireita(noAtual);
            }
        } else if (balanceamento == 2) {
            if (altura(noAtual->getNoDir()->getNoDir()) >= altura(noAtual->getNoDir()->getNoEsq())) {
                noAtual = rotacaoEsquerda(noAtual);
            } else {
                noAtual = duplaRotacaoDireitaEsquerda(noAtual);
            }
        }

        if (noAtual->getNoPai() != NULL) {
            verificarBalanceamento(noAtual->getNoPai());
        } else {
            this->setRaiz(noAtual);
        }
    }

/** ROTAÇÕES **/
No * AVL::rotacaoEsquerda(No * inicial) {

    No * direita = inicial->getNoDir();
    direita->setNoPai(inicial->getNoPai());

    inicial->setNoDir(direita->getNoEsq());

    if (inicial->getNoDir() != NULL) {
        inicial->getNoDir()->setNoPai(inicial);
    }

    direita->setNoEsq(inicial);
    inicial->setNoPai(direita);

    if (direita->getNoPai() != NULL) {

        if (direita->getNoPai()->getNoDir() == inicial) {
            direita->getNoPai()->setNoDir(direita);

        } else if (direita->getNoPai()->getNoEsq() == inicial) {
            direita->getNoPai()->setNoEsq(direita);
        }
    }

    setBalanco(inicial);
    setBalanco(direita);

    return direita;
}

No * AVL::rotacaoDireita(No * inicial) {

    No * esquerda = inicial->getNoEsq();
    esquerda->setNoPai(inicial->getNoPai());

    inicial->setNoEsq(esquerda->getNoDir());

    if (inicial->getNoEsq() != NULL) {
        inicial->getNoEsq()->setNoPai(inicial);
    }

    esquerda->setNoDir(inicial);
    inicial->setNoPai(esquerda);

    if (esquerda->getNoPai() != NULL) {

        if (esquerda->getNoPai()->getNoDir() == inicial) {
            esquerda->getNoPai()->setNoDir(esquerda);

        } else if (esquerda->getNoPai()->getNoEsq() == inicial) {
            esquerda->getNoPai()->setNoEsq(esquerda);
        }
    }

    setBalanco(inicial);
    setBalanco(esquerda);

    return esquerda;
}

No * AVL::duplaRotacaoEsquerdaDireita(No * inicial) {
    inicial->setNoEsq(rotacaoEsquerda(inicial->getNoEsq()));
    return rotacaoDireita(inicial);
}

No * AVL::duplaRotacaoDireitaEsquerda(No * inicial) {
    inicial->setNoDir(rotacaoDireita(inicial->getNoDir()));
    return rotacaoEsquerda(inicial);
}

/** ROTAÇÕES **/

void AVL::inserirABAVL(No * aComparar, No * aInserir) {

    if (aComparar == NULL) {
        this->setRaiz(aInserir);
    } else {
        if ((aInserir->getElemNo()) < (aComparar->getElemNo())) {

            if (aComparar->getNoEsq() == NULL) {
                aComparar->setNoEsq(aInserir);
                aInserir->setNoPai(aComparar);

                verificarBalanceamento(aComparar);

            } else {
                inserirABAVL(aComparar->getNoEsq(), aInserir);
            }

        } else if ((aInserir->getElemNo()) > (aComparar->getElemNo())) {

            if (aComparar->getNoDir() == NULL) {
                aComparar->setNoDir(aInserir);
                aInserir->setNoPai(aComparar);

                verificarBalanceamento(aComparar);

            } else {
                inserirABAVL(aComparar->getNoDir(), aInserir);
            }

        } else {
            //cout << "Elemento já existe."<< endl;
        }
    }
}

int AVL::altura(No *atual)
{
    if (atual == NULL) {
        return -1;
    }
    if (atual->getNoEsq() == NULL && atual->getNoDir() == NULL) {
        return 0;
    }else if (atual->getNoEsq() == NULL){
        return 1 + altura(atual->getNoDir());
    }else if(atual->getNoDir() == NULL){
        return 1 + altura(atual->getNoEsq());
    }else{
        return 1 + max(altura(atual->getNoEsq()),altura(atual->getNoDir()));
    }
}

/** REMOÇÃO **/
void AVL::removerAVL(int valor) {
       removerABAVL(this->getRaiz(), valor);
}

void AVL::removerABAVL(No * atual, int valor) {
        if (atual == NULL) {
            return;
        } else {

            if (atual->getElemNo() > valor) {
                removerABAVL(atual->getNoEsq(), valor);

            } else if (atual->getElemNo() < valor) {
                removerABAVL(atual->getNoDir(), valor);

            } else if (atual->getElemNo() == valor) {
                removerNoEncontrado(atual);
            }
        }
    }

 void AVL::removerNoEncontrado(No * aRemover) {
        No * noTemp;

        if (aRemover->getNoEsq() == NULL || aRemover->getNoDir() == NULL) {

            if (aRemover->getNoPai() == NULL) {
                this->setRaiz(NULL);
                aRemover = NULL;
                return;
            }
            noTemp = aRemover;

        } else {
            noTemp = this->sucessor(aRemover);
            aRemover->setElemNo(noTemp->getElemNo());
        }

        No * noReordena;

        if (noTemp->getNoEsq() != NULL) {
            noReordena = noTemp->getNoEsq();
        } else {
            noReordena = noTemp->getNoDir();
        }

        if (noReordena != NULL) {
            noReordena->setNoPai(noTemp->getNoPai());
        }

        if (noTemp->getNoPai() == NULL) {
            this->setRaiz(noReordena);
        } else {
            if (noTemp == noTemp->getNoPai()->getNoEsq()) {
                noTemp->getNoPai()->setNoEsq(noReordena);
            } else {
                noTemp->getNoPai()->setNoDir(noReordena);
            }

            verificarBalanceamento(noTemp->getNoPai());
        }
        noTemp = NULL;
 }

 No *AVL::sucessor(No * no)
 {
     if (no->getNoDir() != NULL) {
         No * noR = no->getNoDir();
         while (noR->getNoEsq() != NULL) {
             noR = noR->getNoEsq();
         }
         return noR;
     } else {
         No * noP = no->getNoPai();
         while (noP != NULL && no == noP->getNoDir()) {
             no = noP;
             noP = no->getNoPai();
         }
         return noP;
     }
 }

/** REMOÇÃO **/

AVL::~AVL()
{
    //dtor
}
