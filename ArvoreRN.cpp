#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "No.h"
#include "ArvoreRN.h"

using namespace std;

/** FUNCAO PARA COLORIR NÓS **/
/** DISPONÍVEL EM: http://stackoverflow.com/questions/9943187/colour-output-of-program-run-under-bash **/
enum Color
{
    NONE = 0,
    BLACK, RED, GREEN,
    YELLOW, BLUE, MAGENTA,
    CYAN, WHITE
};

static std::string set_color(Color foreground = NONE, Color background = NONE)
{
    std::stringstream s;
    s << "\033[";
    if (!foreground && ! background){
        s << "0";
    }
    if (foreground) {
        s << 29 + foreground;
        if (background) s << ";";
    }
    if (background) {
        s << 39 + background;
    }
    s << "m";
    return s.str();
}

/** FUNCAO PARA COLORIR NÓS **/

ArvoreRN::ArvoreRN(No *no):ArvoreBinaria(no)
{
    this->noRaiz = no;
}

void ArvoreRN::inserirRN(int elem)
{
    if(this->buscar(this->getRaiz(),elem)== NULL){
        inserirABRN(elem, this->getRaiz());
    }else{
        return;
    }
}


void ArvoreRN::inserirABRN(int elem, No *no)
{
    if(this->getRaiz()==NULL)
        this->setRaiz(new No(elem));
    else{
        if(elem >no->getElemNo()){
            if(no->getNoDir() == NULL){
                No * noDir = new No(elem);
                noDir->setNoPai(no);
                noDir->setVermelho(true);

                no->setNoDir(noDir);
                balanco(no->getNoDir());

            }else
                inserirABRN(elem,no->getNoDir());
        }else{
            if(no->getNoEsq() == NULL){
                No * noEsq = new No(elem);
                noEsq->setNoPai(no);
                noEsq->setVermelho(true);

                no->setNoEsq(noEsq);

                balanco(no->getNoEsq());
            }else
                inserirABRN(elem, no->getNoEsq());
        }
    }
}

void ArvoreRN::balanco(No * no)
{
    if (no->getNoPai() == NULL ||
        no->getNoPai()->getNoPai() == NULL ||
        !(no->getNoPai()->ehVermelho() == true
        && no->ehVermelho() == true)) {
        return;
    }
            No * y;
            No * z;

            y=no->getNoPai();
            z=no->getNoPai()->getNoPai();

            if(z->getNoEsq()==y){
                if(y->getNoEsq()==no){
                    if(z->getNoDir()==NULL || z->getNoDir()->ehVermelho()==false){

                        rotacaoDireita(y,z);

                        z->setVermelho(true);
                        y->setVermelho(false);

                    }else{
                        z->setVermelho(true);
                        y->setVermelho(false);
                        z->getNoDir()->setVermelho(false);
                        if(z==this->getRaiz()){
                            z->setVermelho(false);
                        }
                        else{
                            balanco(z);
                        }
                    }
                }else{

                    rotacaoEsquerda(no,y);

                    if(z->getNoDir()==NULL || z->getNoDir()->ehVermelho()==false){

                        rotacaoDireita(no,z);

                        z->setVermelho(true);
                        no->setVermelho(false);
                    }else{
                        z->setVermelho(true);
                        no->setVermelho(false);
                        z->getNoDir()->setVermelho(false);
                        if(z==this->getRaiz())
                            z->setVermelho(false);
                        else
                            balanco(z);
                    }
                }
            }else{
                if(y->getNoDir()==no){
                    if(z->getNoEsq()==NULL || z->getNoEsq()->ehVermelho()==false){

                        rotacaoEsquerda(y,z);

                        z->setVermelho(true);
                        y->setVermelho(false);
                    }else{
                        z->setVermelho(true);
                        y->setVermelho(false);
                        z->getNoEsq()->setVermelho(false);
                        if(z==this->getRaiz())
                            z->setVermelho(false);
                        else
                            balanco(z);
                    }
                }else{

                    rotacaoDireita(no,y);

                    if(z->getNoEsq() == NULL || z->getNoEsq()->ehVermelho()==false){

                        rotacaoEsquerda(no,z);

                        z->setVermelho(true);
                        no->setVermelho(false);
                    }else{
                        z->setVermelho(true);
                        no->setVermelho(false);
                        z->getNoEsq()->setVermelho(false);
                        if(z==this->getRaiz()){
                            z->setVermelho(false);
                        }
                        else{
                            balanco(z);
                        }
                    }
                }
            }
}

void ArvoreRN::rotacaoDireita(No *no1, No *no2)
{
    no1->setNoPai(no2->getNoPai());
    if(no1->getNoPai()== NULL)
        this->setRaiz(no1);
    else if(no1->getNoPai()->getNoEsq() == no2)
        no1->getNoPai()->setNoEsq(no1);
    else
        no1->getNoPai()->setNoDir(no1);

    no2->setNoEsq(no1->getNoDir());

    if(no2->getNoEsq() != NULL)
        no2->getNoEsq()->setNoPai(no2);

    no1->setNoDir(no2);

    no2->setNoPai(no1);
}

void ArvoreRN::rotacaoEsquerda(No *no1, No *no2)
{
    no1->setNoPai(no2->getNoPai());
    if(no2->getNoPai() == NULL)
        this->setRaiz(no1);
    else if(no2->getNoPai()->getNoEsq()==no2)
        no1->getNoPai()->setNoEsq(no1);
    else
        no1->getNoPai()->setNoDir(no1);

    no2->setNoDir(no1->getNoEsq());

    if(no2->getNoDir() != NULL)
        no2->getNoDir()->setNoPai(no2);

    no1->setNoEsq(no2);

    no2->setNoPai(no1);
}

void ArvoreRN::removerABRN(No * no)
{
    if(no==this->getRaiz() && no->getNoEsq() == NULL && no->getNoDir() == NULL){
        this->setRaiz(NULL);
        return;
    }
    No * y;
    No * z;

    bool unicoFilho = false;

    if(no->getNoEsq() == NULL || no->getNoDir() == NULL){	//atleast one child
        y = no;
        unicoFilho = true;
    }else{
        No * noTemp = no->getNoDir();
        for(y=noTemp; y->getNoEsq()!=NULL;y = y->getNoEsq());
    }

    bool estaNaEsquerda = false;

    if(y->getNoEsq() != NULL)
        z = y->getNoEsq();
    else
        z = y->getNoDir();
    if(z != NULL)
        z->setNoPai(y->getNoPai());
    if(y->getNoPai() == NULL)
        this->setRaiz(z);
    else{
        if(y == y->getNoPai()->getNoEsq()){
            y->getNoPai()->setNoEsq(z);
            estaNaEsquerda = false;
        }else{
            estaNaEsquerda = true;
            y->getNoPai()->setNoDir(z);
        }
    }
    no->setElemNo(y->getElemNo());

    No * a;
    No * b;
    No * c;
    No * d;

    int caso;

    No * irmaoNo;
    int i = 0;
    do{
        i++;

        if(y->getNoPai() == NULL){
            this->setRaiz(y);
            y->setVermelho(false);
            return;
        }

        caso = 0;
        bool ehVermelho = false;

        if(y->getNoPai()->ehVermelho()){
            if(estaNaEsquerda == false)
                irmaoNo = y->getNoPai()->getNoDir();
            else
                irmaoNo = y->getNoPai()->getNoEsq();
            ehVermelho = false;

            if(irmaoNo != NULL){
                if(irmaoNo->getNoEsq() != NULL){
                    ehVermelho = irmaoNo->getNoEsq()->ehVermelho();
                    c = irmaoNo->getNoEsq();
                }else if(irmaoNo->getNoDir() != NULL){
                    ehVermelho = (ehVermelho || irmaoNo->getNoDir()->ehVermelho());
                    c = irmaoNo->getNoDir();
                }
            }

            if(irmaoNo->ehVermelho() == false && ehVermelho == true)
                caso = 1;
            else if(irmaoNo->ehVermelho() == false)
                caso = 2;
        }else{
            if(estaNaEsquerda == false){
                irmaoNo = y->getNoPai()->getNoDir();
            }else{
                irmaoNo = y->getNoPai()->getNoEsq();
            }
            ehVermelho = false;

            if(irmaoNo != NULL){
                if(irmaoNo->ehVermelho() == true){
                    if(estaNaEsquerda && irmaoNo->getNoDir() != NULL){
                        c = irmaoNo->getNoDir();
                        if(irmaoNo->getNoDir()->getNoEsq() != NULL){
                            ehVermelho = irmaoNo->getNoDir()->ehVermelho();
                            d = irmaoNo->getNoDir()->getNoEsq();
                        }if(ehVermelho)
                            caso = 3;
                    }else if(ehVermelho != true && irmaoNo->getNoEsq() != NULL){
                        c = irmaoNo->getNoEsq();
                        if(irmaoNo->getNoEsq()->getNoDir() != NULL){
                            ehVermelho = irmaoNo->getNoEsq()->getNoDir()->ehVermelho();
                            d = irmaoNo->getNoEsq()->getNoDir();
                        }if(ehVermelho)
                            caso = 4;
                    }
                    if(ehVermelho == false)
                        caso = 5;
                }else{
                    bool continuaVermelho = false;
                    if(irmaoNo->getNoEsq() != NULL){
                        ehVermelho = irmaoNo->getNoEsq()->ehVermelho();
                    }
                    if(irmaoNo->getNoDir() != NULL){
                        continuaVermelho = irmaoNo->getNoDir()->ehVermelho();
                    }
                    if(continuaVermelho  || ehVermelho ){
                        caso = 6;
                        if(ehVermelho)
                            c = irmaoNo->getNoEsq();
                        else
                            c = irmaoNo->getNoDir();
                            cout << c->getElemNo() << endl;
                    }else
                        caso = 7;
                }
            }
        }

        b = irmaoNo;

        switch(caso){
        case 1:
            a = y->getNoPai();
            b = irmaoNo;
            b->setNoPai(a);
            c->setNoPai(b);
            if(a->getNoEsq() == b){
                if(b->getNoEsq() == c){
                    rotacaoDireita(b,a);
                }else{
                    rotacaoEsquerda(c,b);
                    rotacaoDireita(c,a);
                }
            }else{
                if(b->getNoDir() == c){
                    rotacaoEsquerda(b,a);
                }else{
                    rotacaoDireita(c,b);
                    rotacaoEsquerda(c,a);
                }
            }
            break;
        case 2:
            a = y->getNoPai();
            b->setNoPai(a);
            a->setVermelho(false);
            b->setVermelho(true);
            break;
        case 3:
            a = y->getNoPai();
            b->setNoPai(a);
            c->setNoPai(b);
            d->setNoPai(c);
            if(a->getNoEsq() == b){
                rotacaoDireita(b,a);
                d->setVermelho(false);
                c->setVermelho(true);
                b->setVermelho(false);
            }else{
                rotacaoEsquerda(b,a);
                rotacaoDireita(a,b);
                d->setVermelho(false);
                c->setVermelho(true);
                b->setVermelho(false);
            }
            break;
        case 4:
            a = y->getNoPai();
            b->setNoPai(a);
            c->setNoPai(b);
            d->setNoPai(c);
            if(a->getNoEsq() == b){
                rotacaoEsquerda(c,b);
                rotacaoDireita(c,a);
                d->setVermelho(false);
            }else{
                rotacaoEsquerda(b,a);
                b->setVermelho(false);
                c->setVermelho(true);
                d->setVermelho(false);
            }
            break;
        case 5:
            a = y->getNoPai();
            b->setNoPai(a);
            c->setNoPai(b);

            if(a->getNoEsq() == b){
                rotacaoDireita(b,a);
                b->setVermelho(false);
                c->setVermelho(true);
            }else{
                rotacaoEsquerda(b,a);
                b->setVermelho(false);
                c->setVermelho(true);
            }
            break;
        case 6:
            a = y->getNoPai();
            b->setNoPai(a);
            c->setNoPai(b);

            if(a->getNoEsq() == b){
                if(b->getNoEsq() == c){
                    rotacaoDireita(b,a);
                    b->setVermelho(false);
                    c->setVermelho(false);
                    a->setVermelho(false);
                }else{
                    rotacaoEsquerda(c,b);
                    rotacaoDireita(c,a);
                    c->setVermelho(false);
                }
            }else{
                if(b->getNoDir() == c){
                    rotacaoEsquerda(b,a);
                    b->setVermelho(false);
                    c->setVermelho(false);
                    a->setVermelho(false);
                }else{
                    rotacaoDireita(c,b);
                    rotacaoEsquerda(c,a);
                    c->setVermelho(false);
                }
            }
            break;
        case 7:
            a = y->getNoPai();
            b->setNoPai(a);
            b->setVermelho(true);
            y = a;
            if(y->getNoPai() == y)
                estaNaEsquerda = false;
            else
                estaNaEsquerda = true;
            break;
        }
    }while(caso == 7);

}

void ArvoreRN::removerRN(int elem)
{
    if(this->buscar(this->getRaiz(), elem)!= NULL){
        No * aRemover = buscar(this->getRaiz(), elem);
        removerABRN(aRemover);
    }else{
        return;
    }

}

void ArvoreRN::posOrdemColorido(No *no)
{
    if (no != NULL) {
        posOrdemColorido(no->getNoEsq());
        posOrdemColorido(no->getNoDir());
        if (no->ehVermelho()) {
            cout << set_color(RED) << " " << no->getElemNo() << " " << set_color(NONE);
        }else{
            cout << set_color(BLUE) << " " << no->getElemNo() << " " << set_color(NONE);
        }

    }
}

ArvoreRN::~ArvoreRN()
{

}
