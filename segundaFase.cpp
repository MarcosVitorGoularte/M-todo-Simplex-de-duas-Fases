#include "segundaFase.hpp"
#include "caso.hpp"
#include <vector>
#include <iostream>

void SegundaFase::montarLinhaZFase2(Caso& caso){
    int variaveisDecisao = caso.getVariaveisDecisao();
    int restricoes = caso.getRestricoes();
    int totalColunas = caso.getTotalColunasTableau();
    const std::vector<double>& coeficientes = caso.getCoeficientesFuncaoObjetivo();
    std::vector<double>& tableau = caso.getTableauReferencia();
    int inicioZ = restricoes * totalColunas;

    for(int j = 0; j < totalColunas; ++j){
        tableau[inicioZ + j] = 0.0;
    }
    for(int j = 0; j < variaveisDecisao; ++j){
        tableau[inicioZ + j] = -coeficientes[j];
    }
}

void SegundaFase::canonicalizarLinhaZ(Caso& caso){
    int restricoes = caso.getRestricoes();
    int totalColunas = caso.getTotalColunasTableau();
    const std::vector<int>& base = caso.getBaseInicial();
    std::vector<double>& tableau = caso.getTableauReferencia();
    int inicioZ = restricoes * totalColunas;

    for(int i = 0; i < restricoes; ++i){
        int colunaBasica = base[i];
        double fator = tableau[inicioZ + colunaBasica];
        int inicioLinha = i * totalColunas;
        for(int j = 0; j < totalColunas; ++j){
            tableau[inicioZ + j] = tableau[inicioZ + j] - fator * tableau[inicioLinha + j];
        }
        tableau[inicioZ + colunaBasica] = 0.0;
    }
}

int SegundaFase::escolherVariavelEntraFase2(Caso& caso){
    int restricoes = caso.getRestricoes();
    int totalColunas = caso.getTotalColunasTableau();
    const std::vector<double>& tableau = caso.getTableau();
    int inicioZ = restricoes * totalColunas;
    int colunaEscolhida = -1;
    double menorValor = -EPS_COMPARACOES;

    for(int j = 0; j < totalColunas - 1; ++j){
        if(tableau[inicioZ + j] < menorValor){
            colunaEscolhida = j;
            menorValor = tableau[inicioZ + j];
        }
    }
    return colunaEscolhida;
}

int SegundaFase::escolherVariavelSaiFase2(Caso& caso, int colunaEscolhida){
    int restricoes = caso.getRestricoes();
    int totalColunas = caso.getTotalColunasTableau();
    const std::vector<double>& tableau = caso.getTableau();
    int linhaVariavelSai = -1;
    double menorRazao = 0.0;

    for(int i = 0; i < restricoes; ++i){
        double elemento = tableau[i * totalColunas + colunaEscolhida];
        if(elemento > EPS_COMPARACOES){
            double razao = tableau[i * totalColunas + totalColunas - 1] / elemento;
            if(linhaVariavelSai == -1 || razao < menorRazao){
                menorRazao = razao;
                linhaVariavelSai = i;
            }
        }
    }
    return linhaVariavelSai;
}

StatusFinalSegundaFase SegundaFase::pivoteamento(Caso& caso){
    std::vector<double>& tableau = caso.getTableauReferencia();
    std::vector<int>& base = caso.getBaseReferencia();
    int totalLinhas = caso.getRestricoes() + 1;
    int totalColunas = caso.getTotalColunasTableau();
    int limiteIteracoes = 100 * (caso.getVariaveisDecisao() + caso.getRestricoes());
    StatusFinalSegundaFase resultado;
    int contadorIteracoes = 0;

    while(true){
        int colunaEscolhida = escolherVariavelEntraFase2(caso);
        if(colunaEscolhida == -1){
            resultado.status = OTIMA;
            break;
        }

        int linhaEscolhida = escolherVariavelSaiFase2(caso, colunaEscolhida);
        if(linhaEscolhida == -1){
            resultado.status = ILIMITADA;
            break;
        }

        if(contadorIteracoes >= limiteIteracoes){
            std::cerr << "Limite de iteracoes da primeira fase atingido. Erro de implementacao ou ciclagem\n";
            resultado.status = LIMITE_ITERACOES;
            break;
        }

        int inicioLinhaPivo = linhaEscolhida * totalColunas;
        double elementoPivo = tableau[inicioLinhaPivo + colunaEscolhida];
        for(int j = 0; j < totalColunas; ++j){
            tableau[inicioLinhaPivo + j] = tableau[inicioLinhaPivo + j] / elementoPivo;
        }
        for(int i = 0; i < totalLinhas; ++i){
            if(i == linhaEscolhida){
                continue;
            }
            int inicioLinha = i * totalColunas;
            double multiplicador = tableau[inicioLinha + colunaEscolhida];
            for(int j = 0; j < totalColunas; ++j){
                tableau[inicioLinha + j] = tableau[inicioLinha + j] - multiplicador * tableau[inicioLinhaPivo + j];
            }
            tableau[inicioLinha + colunaEscolhida] = 0.0;
        }
        base[linhaEscolhida] = colunaEscolhida;
        ++contadorIteracoes;
    }

    resultado.iteracoes = contadorIteracoes;
    return resultado;
}

StatusFinalSegundaFase SegundaFase::executarSegundaFase(Caso& caso){
    montarLinhaZFase2(caso);
    canonicalizarLinhaZ(caso);
    return pivoteamento(caso);
}