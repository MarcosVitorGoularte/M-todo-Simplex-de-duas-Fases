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
            resultadoPrimeiraFase.iteracoes = contadorIteracoes;
            return resultadoPrimeiraFase;
        }
        
        if(caso.getModoImpressao()){
            caso.imprimirPivo(linhaEscolhida, colunaEscolhida);
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
        if(caso.getModoImpressao()){
            caso.imprimirEstadoAtual("Tableau apos iteracao " + std::to_string(contadorIteracoes) + " (Fase 1)");
        }
    }

    int linhaZ = caso.getRestricoes();
    double valorW = -tableau[linhaZ * totalColunas + totalColunas - 1];
    if(caso.getModoImpressao()){
        std::cout << "Fase 1 concluida: w = " << Caso::formatarNumerosImpressao(valorW, 6);
        if(valorW > EPS_CLASSIFICACOES){
            std::cout << "  (w > 0: problema INVIAVEL)";
        }
        std::cout << "\n\n";
    }
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
    bool modoImpressao = caso.getModoImpressao();
    bool houveAjuste = false;
    int removidas = 0;

    if(modoImpressao){
        std::cout << "--- Transicao Fase 1 -> Fase 2 ---\n\n";
    }

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

            if(modoImpressao){
                std::cout << "Linha " << i + removidas + 1 << ": artificial " << nomesVariaveis[baseInicial[i]]
                << " basica em zero -> pivo na coluna " << nomesVariaveis[colunaPivo]
                << " (valor " << Caso::formatarNumerosImpressao(elementoPivo, 4) << ")\n";
                houveAjuste = true;
            }

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
            if(modoImpressao){
                std::cout << "Linha " << i + removidas + 1 << ": artificial " << nomesVariaveis[baseInicial[i]]
                << " basica em zero e linha nula fora das artificiais -> restricao redundante, linha removida\n";
                houveAjuste = true;
            }
            auto inicioLinha = tableau.begin() + i*totalColunas;
            tableau.erase(inicioLinha, inicioLinha + totalColunas);
            baseInicial.erase(baseInicial.begin() + i);
            --restricoes;
            ++removidas;
        }
    }
    if(modoImpressao){
        if(!houveAjuste){
            std::cout << "Nenhuma variavel artificial permaneceu na base.\n";
        }
        std::cout << "Colunas artificiais descartadas.\n\n";
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
    
    caso.setTableau(novoTableau);
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
        if(caso.getModoImpressao()){
            std::cout << "=== FASE 1 ===\n\nFase 1 dispensada: nenhuma variavel artificial (0 iteracoes)\n\n";
        }
        resultadoPrimeiraFase.iteracoes = 0;
        resultadoPrimeiraFase.status = SEM_ARTIFICIAL;
        return resultadoPrimeiraFase;
    }

    montarLinhaZFase1(caso);
    if(caso.getModoImpressao()){
        std::cout << "=== FASE 1 ===\n\n";
        caso.imprimirEstadoAtual("Tableau inicial (Fase 1)");
    }
    resultadoPrimeiraFase = pivoteamento(caso);

    if(resultadoPrimeiraFase.status != OTIMA){
        return resultadoPrimeiraFase;
    }

    transicaoParaFase2(caso);
    return resultadoPrimeiraFase;

}