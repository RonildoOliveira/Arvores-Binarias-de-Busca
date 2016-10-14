#include <iostream>
#include <cstdlib>
#include <ctime>

#include "No.h"
#include "ArvoreBinaria.h"
#include "AVL.h"
#include "ArvoreRN.h"

#include "Impressao.h"

/***************************************************

         UNIVERSIDADE FEDERAL DO CEARÁ
               Campus de Quixadá
 
    QXD0115 - Estruturas de Dados Avançadas
 Ronildo Oliveira da Silva - Ciência da Computação

***************************************************/


using namespace std;

int main()
{
    srand(time(0));

    int elemAB, elemAVL, elemRN;
    int numBusca = rand()%100+1;
    int numRemove = rand()%100+1;

    Impressao * Hp = new Impressao();

    ArvoreBinaria * arvB = new ArvoreBinaria(NULL);
    AVL * arvAVL = new AVL(NULL);
    ArvoreRN * arvRN = new ArvoreRN(NULL);

    for (int var = 0; var < 16; ++var) {
        elemAB = rand()%100+1;
        elemAVL = rand()%100+1;
        elemRN = rand()%100+1;

        arvB->inserirAB(elemAB);
        arvAVL->inserirAVL(elemAVL);
        arvRN->inserirRN(elemRN);
    }

/*
    cout << "######### ARVORE BINARIA #########" << endl;
    cout << "NUMERO DE NOS: " << arvB->totalNos(arvB->getRaiz()) << endl;
    cout << "ALTURA: " << arvB->altura(arvB->getRaiz()) << endl;
    cout << "MAXIMO: " << arvB->maximo(arvB->getRaiz()) << endl;
    cout << "MINIMO: " << arvB->minimo(arvB->getRaiz()) << endl;
    cout << "RAIZ: " << arvB->getRaiz()->getElemNo() << endl;
    cout << "BUSCA : " <<  numBusca << " [" << arvB->buscar(arvB->getRaiz(),numBusca)->getElemNo() << "] " << endl;
    cout << "REMOVER: " << numRemove << " [" << arvB->removerNo(arvB->getRaiz(), numRemove) << "] " << endl;
    cout << "POS ORDEM: "; arvB->posOrdem(arvB->getRaiz()); cout << "" << endl;

    Hp->imprimeArvore(arvB->getRaiz(),1,0,cout);
    cout << "\n --- " << endl;
    cout << "\n" << endl;
*/


    cout << "######### ARVORE AVL #########" << endl;
    cout << "NUMERO DE NOS: " << arvAVL->totalNos(arvAVL->getRaiz()) << endl;
    cout << "ALTURA: " << arvAVL->altura(arvAVL->getRaiz()) << endl;
    cout << "MAXIMO: " << arvAVL->maximo(arvAVL->getRaiz()) << endl;
    cout << "MINIMO: " << arvAVL->minimo(arvAVL->getRaiz()) << endl;
    cout << "RAIZ: " << arvAVL->getRaiz()->getElemNo() << endl;
    cout << "BUSCA : " <<  numBusca << " [" << arvAVL->buscar(arvAVL->getRaiz(),numBusca)->getElemNo() << "] " << endl;
    cout << "POS ORDEM: "; arvAVL->posOrdem(arvAVL->getRaiz()); cout << "" << endl;
    arvAVL->removerAVL(numRemove);
    cout << "REMOVER: " << " [" << numRemove << "] " << endl;
    cout << "POS ORDEM: "; arvAVL->posOrdem(arvAVL->getRaiz()); cout << "" << endl;

    Hp->imprimeArvore(arvAVL->getRaiz(),1,0,cout);
    cout << "\n --- " << endl;
    cout << "\n" << endl;

/*
    cout << "######### ARVORE RUBRO NEGRA #########" << endl;
    cout << "NUMERO DE NOS: " << arvRN->totalNos(arvRN->getRaiz()) << endl;
    cout << "ALTURA: " << arvRN->altura(arvRN->getRaiz()) << endl;
    cout << "MAXIMO: " << arvRN->maximo(arvRN->getRaiz()) << endl;
    cout << "MINIMO: " << arvRN->minimo(arvRN->getRaiz()) << endl;
    cout << "RAIZ: " << arvRN->getRaiz()->getElemNo() << endl;
    cout << "BUSCA : " <<  numBusca << " [" << arvRN->buscar(arvRN->getRaiz(),numBusca)->getElemNo() << "] " << endl;
    cout << "POS ORDEM: "; arvRN->posOrdemColorido(arvRN->getRaiz()); cout << "" << endl;
    arvRN->removerRN(numRemove);
    cout << "REMOVER: " << " [" << numRemove << "] " << endl;
    cout << "POS ORDEM: "; arvRN->posOrdemColorido(arvRN->getRaiz()); cout << "" << endl;

    Hp->imprimeArvore(arvRN->getRaiz(),1,0,cout);
    cout << "\n" << endl;

*/

    return (0);
}
