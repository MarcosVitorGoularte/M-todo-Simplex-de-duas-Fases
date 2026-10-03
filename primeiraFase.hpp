#ifndef PRIMEIRAFASE_HPP
#define PRIMEIRAFASE_HPP

#include "caso.hpp"

constexpr double EPS_COMPARACOES = 1e-9;
constexpr double EPS_CLASSIFICACOES = 1e-7;

enum Status{
    INVIAVEL,
    ILIMITADA,
    OTIMA,
    SEM_ARTIFICIAL,
    LIMITE_ITERACOES
};

struct StatusFinalPrimeiraFase{
    Status status;
    int iteracoes;
};


class PrimeiraFase
{
private:

    static void montarLinhaZFase1(Caso& caso);
    static int escolherVariavelEntraFase1(Caso& caso);
    static int escolherVariavelSaiFase1(Caso& caso, int colunaEscolhida);
    static StatusFinalPrimeiraFase pivoteamento(Caso& caso);
    static void transicaoParaFase2(Caso& caso);
public:
    static StatusFinalPrimeiraFase executarPrimeiraFase(Caso &caso);
    
};

#endif
