#include "preProcessamento.hpp"
#include "caso.hpp"
#include <vector>

void PreProcessamento::verificarDireitaNegativa(Caso& caso){
    long variaveis = caso.getVariaveisDecisao();
    long restricoes = caso.getRestricoes();
    std::vector<double> ladosDireitos = caso.getLadosDireitos();
    std::vector<double> matriz = caso.getMatriz();
    std::vector<Operador> operadores = caso.getOperadores();

    for(long i = 0; i < restricoes; ++i){
        if(ladosDireitos[i] < 0){
            for(long j = 0; j < variaveis; ++j){
                matriz[i * variaveis + j] *= -1;
            }
            operadores[i] = Operador(int(operadores[i]) * -1);
            ladosDireitos[i] *= -1;
        }
    }
    caso.setMatriz(matriz);
    caso.setLadosDireitos(ladosDireitos);
    caso.setOperadores(operadores);
}