#ifndef IMPRESSAO_H
#define IMPRESSAO_H

#include"No.h"
#include <fstream>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

class Impressao
{
public:
    Impressao();
    void imprimeArvore(No * raiz, int nivel, int espacoIdentacao, ostream& tipoSaida);
    void imprimeFolhas(int espacoIdentacao, int nivel, int nosNesseNivel,
                       const deque<No*>& listaNos, ostream& tipoSaida);
    void imprimeNos(int larguraGalho, int espacoEntreNos, int larguraInicial, int nosNesseNivel,
                    const deque<No*>& listaNos, ostream& tipoSaida);
    void imprimeGalhos(int larguraGalho, int espacoEntreNos, int larguraInicial, int nosNesseNivel,
                       const deque<No*>& listaNos, ostream& tipoSaida);
    string intToString(int elem);
    int alturaMaxima(No * no);

    ~Impressao();
};

#endif // IMPRESSAO_H
