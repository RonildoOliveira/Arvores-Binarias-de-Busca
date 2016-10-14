#include <fstream>
#include <cmath>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>

#include "Impressao.h"
#include "ArvoreBinaria.h"


Impressao::Impressao()
{

}

int Impressao::alturaMaxima(No * no) {
  if (!no) return 0;
  int alturaEsquerda = alturaMaxima(no->getNoEsq());
  int alturaDireita = alturaMaxima(no->getNoDir());
  return (alturaEsquerda > alturaDireita) ? alturaEsquerda + 1: alturaDireita + 1;
}

string Impressao::intToString(int elem){
  ostringstream ss;
  ss << elem;
  return ss.str();
}

void Impressao::imprimeGalhos(int larguraGalho, int espacoEntreNos, int larguraInicial,
                              int nosNesseNivel, const deque<No *> &listaNos, ostream& tipoSaida){
  deque<No*>::const_iterator iterador = listaNos.begin();
  //std::vector<No *>::iterator iterador = listaNos->begin();
  for (int i = 0; i < nosNesseNivel / 2; i++) {
    tipoSaida << ((i == 0) ? setw(larguraInicial-1) : setw(espacoEntreNos-2)) << "" << ((*iterador++) ? "/" : " ");
    tipoSaida << setw(2*larguraGalho+2) << "" << ((*iterador++) ? "\\" : " ");
  }
  tipoSaida << endl;
}


 void Impressao::imprimeNos(int larguraGalho, int espacoEntreNos, int larguraInicial, int nosNesseNivel,
                    const deque<No*>& listaNos, ostream& tipoSaida){
  deque<No*>::const_iterator iter = listaNos.begin();
  for (int i = 0; i < nosNesseNivel; i++, iter++) {
    tipoSaida << ((i == 0) ? setw(larguraInicial) : setw(espacoEntreNos)) << "" << ((*iter && (*iter)->getNoEsq()) ? setfill('_') : setfill(' '));
    tipoSaida << setw(larguraGalho+2) << ((*iter) ? intToString((*iter)->getElemNo()) : "");
    tipoSaida << ((*iter && (*iter)->getNoDir()) ? setfill('_') : setfill(' ')) << setw(larguraGalho) << "" << setfill(' ');
  }
  tipoSaida << endl;
}


void Impressao::imprimeFolhas(int espacoIdentacao, int nivel, int nosNesseNivel,
                       const deque<No*>& listaNos, ostream& tipoSaida){
  deque<No*>::const_iterator iter = listaNos.begin();
  for (int i = 0; i < nosNesseNivel; i++, iter++) {
    tipoSaida << ((i == 0) ? setw(espacoIdentacao+2) : setw(2*nivel+2)) << ((*iter) ? intToString((*iter)->getElemNo()) : "");
  }
  tipoSaida << endl;
}


void Impressao::imprimeArvore(No * raiz, int nivel, int espacoIdentacao, ostream& tipoSaida){
  int h = alturaMaxima(raiz);
  int nosNesseNivel = 1;

  int larguraGalho = 2*((int)pow(2.0,h)-1) - (3-nivel)*(int)pow(2.0,h-1);  // eq of the length of branch for each node of each level
  int espacoEntreNos = 2 + (nivel+1)*(int)pow(2.0,h);  // distance between left neighbor node's right arm and right neighbor node's left arm
  int larguraInicial = larguraGalho + (3-nivel) + espacoIdentacao;  // starting space to the first node to print of each level (for the left most node of each level only)

  deque<No*> listaNos;
  listaNos.push_back(raiz);
  for (int r = 1; r < h; r++) {
    imprimeGalhos(larguraGalho, espacoEntreNos,larguraInicial,nosNesseNivel,listaNos,tipoSaida);
    larguraGalho = larguraGalho/2 - 1;
    espacoEntreNos = espacoEntreNos/2 + 1;
    larguraInicial = larguraGalho + (3-nivel) + espacoIdentacao;
    imprimeNos(larguraGalho,espacoEntreNos,larguraInicial,nosNesseNivel,listaNos,tipoSaida);

    for (int i = 0; i < nosNesseNivel; i++) {
      No * noAtual = listaNos.front();
      listaNos.pop_front();
      if (noAtual) {
          listaNos.push_back(noAtual->getNoEsq());
          listaNos.push_back(noAtual->getNoDir());
      } else {
        listaNos.push_back(NULL);
        listaNos.push_back(NULL);
      }
    }
    nosNesseNivel *= 2;
  }
  imprimeGalhos(larguraGalho,espacoEntreNos,larguraInicial,nosNesseNivel,listaNos,tipoSaida);
  imprimeFolhas(espacoIdentacao,nivel,nosNesseNivel,listaNos,tipoSaida);
}


Impressao::~Impressao()
{

}

