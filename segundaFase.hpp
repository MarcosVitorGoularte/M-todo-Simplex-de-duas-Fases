#ifndef SEGUNDAFASE_HPP
#define SEGUNDAFASE_HPP

#include "caso.hpp"
#include "primeiraFase.hpp"

struct StatusFinalSegundaFase {
    Status status;
    int iteracoes;
};

class SegundaFase
{
private:
    static void montarLinhaZFase2(Caso& caso);
    static void canonicalizarLinhaZ(Caso& caso);
    static int escolherVariavelEntraFase2(Caso& caso);
    static int escolherVariavelSaiFase2(Caso& caso, int colunaEscolhida);
    static StatusFinalSegundaFase pivoteamento(Caso& caso);
public:
    static StatusFinalSegundaFase executarSegundaFase(Caso& caso);
};

#endif