#ifndef NO_H
#define NO_H

class No
{
private:
    int elemento;
    int balanceamento;
    int altura;

    No * noDir;
    No * noEsq;
    No * noPai;

    bool vermelho;
public:

    No(int elem);

    No* getNo();
    void setNo(No *no);

    No* getNoDir();
    void setNoDir(No * no);

    No* getNoEsq();
    void setNoEsq(No * no);

    int getElemNo();
    void setElemNo(int novoElem);

    No* getNoPai();
    void setNoPai(No *no);

    int getBalanceamento();
    void setBalanceamento(int bal);

    int getAltura();
    void setAltura(int novaAltura);

    bool ehVermelho();
    void setVermelho(bool cor);

    virtual ~No();
};

#endif // NO_H
