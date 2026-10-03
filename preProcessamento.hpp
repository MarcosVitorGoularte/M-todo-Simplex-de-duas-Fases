#ifndef PREPROCESSAMENTO_HPP
#define PREPROCESSAMENTO_HPP
#include "caso.hpp"

class PreProcessamento
{
private:
public:
    static void verificarDireitaNegativa(Caso& caso);
    static void criarVariaveisAuxiliares(Caso& caso);
    static void ajustarSentido(Caso& caso);
};

#endif