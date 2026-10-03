#include "primeiraFase.hpp"
#include "caso.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstddef>

void PrimeiraFase::montarLinhaZFase1(Caso& caso){
    int restricoes = caso.getRestricoes();
    int totalColunas = caso.getTotalColunasTableau();
    const std::vector<int>& baseInicial = caso.getBaseInicial(); 
    const std::vector<TipoVariavel>& tiposVariaveis = caso.getTiposVariaveis();
    std::vector<double>& tableau = caso.getTableauReferencia();
  
    int colunaInicioArtificiais = caso.getInicioColunasArtificiais();
    int inicioZ = restricoes * totalColunas;

    for(int i = 0; i < totalColunas; ++i){
        tableau[inicioZ + i] = 0.0;        
    }

    for(int i = 0; i < restricoes; ++i){
        if(tiposVariaveis[baseInicial[i]] != ARTIFICIAL){
            continue;
        }
        int inicioLinha = i*totalColunas;
        for(int j = 0; j < totalColunas; ++j){
            tableau[inicioZ + j] -= tableau[inicioLinha + j];
        }
    }

    for(int j = colunaInicioArtificiais; j <totalColunas-1;++j){
        tableau[inicioZ + j] = 0.0;
    }
}

int PrimeiraFase::escolherVariavelEntraFase1(Caso& caso){
    int totalColunas = caso.getTotalColunasTableau();
    int restricoes = caso.getRestricoes();
    const std::vector<double>& tableau = caso.getTableau();
    int colunaInicioArtificiais = caso.getInicioColunasArtificiais();
    int inicioZ = restricoes * totalColunas;
    int colunaEscolhida = -1;
    double menorValor = -EPS_COMPARACOES;
    for(int j = 0; j<colunaInicioArtificiais; ++j){
        if(tableau[inicioZ + j] < menorValor){
            colunaEscolhida = j;
            menorValor = tableau[inicioZ + j];
        }
    }
    return colunaEscolhida;
}

int PrimeiraFase::escolherVariavelSaiFase1(Caso& caso, int colunaEscolhida){
    int restricoes = caso.getRestricoes();
    const std::vector<double>& tableau = caso.getTableau();
    int totalColunas = caso.getTotalColunasTableau();
    int linhaVariavelSai = -1;
    double menorRazao = 0.0;

    for(int i = 0; i<restricoes;++i){
        double elemento = tableau[i * totalColunas + colunaEscolhida];
        if(elemento > EPS_COMPARACOES){
            double razao = tableau[i*totalColunas + totalColunas-1]/elemento;
            if(razao < menorRazao  || linhaVariavelSai == -1){
                menorRazao = razao;
                linhaVariavelSai = i;
            }
        }
    }

    return linhaVariavelSai;
}

StatusFinalPrimeiraFase PrimeiraFase::pivoteamento(Caso& caso){
    StatusFinalPrimeiraFase resultadoPrimeiraFase;
    std::vector<double>& tableau = caso.getTableauReferencia();
    int totalLinhas = caso.getRestricoes() + 1;
    int totalColunas = caso.getTotalColunasTableau();
    std::vector<int>& baseInicial = caso.getBaseReferencia();
    int contadorIteracoes = 0;
    int limiteIteracoes = 100 * (caso.getVariaveisDecisao() + caso.getRestricoes());
    while(true){
        int colunaEscolhida = escolherVariavelEntraFase1(caso);
        if(colunaEscolhida == -1){
            break;
        }

        int linhaEscolhida = escolherVariavelSaiFase1(caso, colunaEscolhida);
        if(linhaEscolhida == -1){
            resultadoPrimeiraFase.status = ILIMITADA;
            resultadoPrimeiraFase.iteracoes = contadorIteracoes;
            return resultadoPrimeiraFase;
        }

        if(contadorIteracoes >= limiteIteracoes){
            std::cerr << "Limite de iteracoes da primeira fase atingido. Erro de implementacao ou ciclagem\n";
            resultadoPrimeiraFase.status = LIMITE_ITERACOES;
            break;
        }
        
        double elementoPivo = tableau[linhaEscolhida*totalColunas + colunaEscolhida];
        int i,j;
        for(j = 0; j < totalColunas; ++j){
            tableau[linhaEscolhida*totalColunas + j] = tableau[linhaEscolhida*totalColunas+j]/elementoPivo;
        }
        for(i = 0; i<totalLinhas;++i){
            if(i == linhaEscolhida){
                continue;
            }
            double multiplicador = tableau[i*totalColunas + colunaEscolhida];
            for(j = 0; j < totalColunas; ++j){
                tableau[i*totalColunas + j] = tableau[i*totalColunas + j] - (multiplicador*tableau[linhaEscolhida*totalColunas+j]);
            }
            tableau[i*totalColunas + colunaEscolhida] = 0.0;
        }
        baseInicial[linhaEscolhida] = colunaEscolhida;
        contadorIteracoes++;
    }

    int linhaZ = caso.getRestricoes();
    double valorW = -tableau[linhaZ * totalColunas + totalColunas - 1];
    if(valorW > EPS_CLASSIFICACOES){
        resultadoPrimeiraFase.status = INVIAVEL;
        resultadoPrimeiraFase.iteracoes = contadorIteracoes;
        return resultadoPrimeiraFase;
    }

    resultadoPrimeiraFase.status = OTIMA;
    resultadoPrimeiraFase.iteracoes = contadorIteracoes;
    return resultadoPrimeiraFase;
}


void PrimeiraFase::transicaoParaFase2(Caso& caso){
    int restricoes = caso.getRestricoes();
    int totalColunas = caso.getTotalColunasTableau();
    std::vector<TipoVariavel> tiposVariaveis = caso.getTiposVariaveis();
    std::vector<std::string> nomesVariaveis = caso.getNomesVariaveisOrdem();
    std::vector<int> baseInicial = caso.getBaseInicial();
    std::vector<double>& tableau = caso.getTableauReferencia();
    int inicioColunaArtificiais = caso.getInicioColunasArtificiais();

    for(int i = 0; i < restricoes;){
        if(tiposVariaveis[baseInicial[i]] != ARTIFICIAL){
                ++i;
                continue;
        }
        int colunaPivo = -1;
        for(int j = 0; j <inicioColunaArtificiais; ++j){
            if(std::fabs(tableau[i*totalColunas+j]) > EPS_COMPARACOES){
                colunaPivo = j;
                break;
            }
        }
        if(colunaPivo!=-1){
            int inicioLinhaPivo = i * totalColunas;
            double elementoPivo = tableau[inicioLinhaPivo + colunaPivo];

            for(int j = 0; j < totalColunas; ++j){
                tableau[inicioLinhaPivo + j] = tableau[inicioLinhaPivo + j] / elementoPivo;
            }
            for(int k = 0; k < restricoes+1; ++k){
                if(i == k){
                    continue;
                }
                int inicioOutraLinha = k * totalColunas;
                double multiplicador = tableau[inicioOutraLinha + colunaPivo];
                for(int j = 0; j < totalColunas; ++j){
                    tableau[inicioOutraLinha + j] = tableau[inicioOutraLinha +j] - multiplicador * tableau[inicioLinhaPivo + j];
                }
                tableau[inicioOutraLinha + colunaPivo] = 0.0;
            }
            baseInicial[i] = colunaPivo;
            ++i;
        }
        else{
            auto inicioLinha = tableau.begin() + i*totalColunas;
            tableau.erase(inicioLinha, inicioLinha + totalColunas);
            baseInicial.erase(baseInicial.begin() + i);
            --restricoes;
        }
    }
    int novasColunas = inicioColunaArtificiais + 1;
    std::vector<double> novoTableau((restricoes +1)*novasColunas, 0.0);
    for(int i = 0;i<restricoes+1;++i){
        for(int j = 0;j<inicioColunaArtificiais;++j){
            novoTableau[i*novasColunas+j] = tableau[i*totalColunas+j];
        }
        novoTableau[i*novasColunas+inicioColunaArtificiais] = tableau[i*totalColunas+totalColunas-1];
    }
    tiposVariaveis.resize(inicioColunaArtificiais);
    nomesVariaveis.resize(inicioColunaArtificiais);
    
    caso.setRestricoes(restricoes);
    caso.setBaseInicial(baseInicial);
    caso.setTiposVariaveis(tiposVariaveis);
    caso.setNomesVariaveisOrdem(nomesVariaveis);
    caso.setTotalColunasTableau(novasColunas);
    caso.setTemVariavelArtificial(false);
}

StatusFinalPrimeiraFase PrimeiraFase::executarPrimeiraFase(Caso &caso){
    StatusFinalPrimeiraFase resultadoPrimeiraFase;
    bool temVariavelArtificial = caso.getTemVariavelArtificial();
    if (!temVariavelArtificial){
        std::cerr << "Base Inicial sem variaveis artificiais\n";
        resultadoPrimeiraFase.iteracoes = 0;
        resultadoPrimeiraFase.status = SEM_ARTIFICIAL;
        return resultadoPrimeiraFase;
    }

    montarLinhaZFase1(caso);
    resultadoPrimeiraFase = pivoteamento(caso);

    if(resultadoPrimeiraFase.status != OTIMA){
        return resultadoPrimeiraFase;
    }

    transicaoParaFase2(caso);
    return resultadoPrimeiraFase;

}