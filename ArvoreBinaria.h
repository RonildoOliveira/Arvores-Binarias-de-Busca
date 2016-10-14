#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#include <vector>

#include "No.h"

class ArvoreBinaria
{
private:
    No * noRaiz;

    No * removeAtual(No* no);
public:
    ArvoreBinaria(No * no);

    No * getRaiz();
    void setRaiz(No *no);

    bool inserirAB (int elem);

    bool removerNo(No *no, int elem);

    No * buscar(No *no, int valor);

    int alturaArvore(No * no);
    int altura(No * no);

    int balanceamentoNo(No *no);

    int sucNo(No *no);
    int antNo(No *no);
    int totalNos(No * no);

    void emOrdem(No *no);
    void preOrdem(No *no);
    void posOrdem(No *no);
    std::vector<No> vetorPosOrdem(No * no);

    int minimo(No * no);
    int maximo(No * no);

    virtual ~ArvoreBinaria();
};

#endif // ARVOREBINARIA_H
