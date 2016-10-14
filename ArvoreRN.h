#ifndef ARVORERN_H
#define ARVORERN_H

#include "No.h"
#include "ArvoreBinaria.h"

class ArvoreRN : public ArvoreBinaria
{
private:
    No * noRaiz;
    void inserirABRN(int elem, No *no);

    void balanco(No * no);
    void rotacaoDireita(No* no1, No * no2);
    void rotacaoEsquerda(No *no1, No *no2);

    void removerABRN(No * no);

public:
    ArvoreRN(No * no);

    void inserirRN(int elem);

    void removerRN(int elem);

    void posOrdemColorido(No * no);

    ~ArvoreRN();
};

#endif // ARVORERN_H
