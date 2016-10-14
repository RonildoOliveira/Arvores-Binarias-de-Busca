#ifndef AVL_H
#define AVL_H

#include "No.h"
#include "ArvoreBinaria.h"

class AVL:public ArvoreBinaria
{
    private:
        No * noRaiz;
        void inserirABAVL(No * aComparar, No * aInserir);

        No * sucessor(No *no);

        No * rotacaoEsquerda(No * inicial);
        No * rotacaoDireita(No * inicial);

        No * duplaRotacaoEsquerdaDireita(No * inicial);
        No * duplaRotacaoDireitaEsquerda(No *inicial);

        void removerABAVL(No * atual, int valor);
        void removerNoEncontrado(No * aRemover);

        void verificarBalanceamento(No *noAtual);
        void setBalanco(No * no);

    public:
        AVL(No * no);

        int altura(No * atual);

        void inserirAVL(int elem);

        void removerAVL(int valor);

        virtual ~AVL();

protected:

};

#endif // AVL_H
