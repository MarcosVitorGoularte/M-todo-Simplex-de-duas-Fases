#include "preProcessamento.hpp"
#include "caso.hpp"
#include <vector>
#include <string>

void PreProcessamento::verificarDireitaNegativa(Caso& caso){
    int variaveis = caso.getVariaveisDecisao();
    int restricoes = caso.getRestricoes();
    std::vector<double> ladosDireitos = caso.getLadosDireitos();
    std::vector<double> matriz = caso.getMatrizCoeficientesLadoEsquerdo();
    std::vector<Operador> operadores = caso.getOperadores();

    for(int i = 0; i < restricoes; ++i){
        if(ladosDireitos[i] < 0){
            for(int j = 0; j < variaveis; ++j){
                matriz[i * variaveis + j] = 0.0 - matriz[i * variaveis + j];
            }
            operadores[i] = Operador(int(operadores[i]) * -1);
            ladosDireitos[i] = 0.0 - ladosDireitos[i];
        }
    }
    caso.setMatrizCoeficientesLadoEsquerdo(matriz);
    caso.setLadosDireitos(ladosDireitos);
    caso.setOperadores(operadores);
}

void PreProcessamento::criarVariaveisAuxiliares(Caso& caso){
    int variaveisDecisao = caso.getVariaveisDecisao();
    int restricoes = caso.getRestricoes();
    const std::vector<double>& matriz = caso.getMatrizCoeficientesLadoEsquerdo();
    const std::vector<Operador>& operadores = caso.getOperadores();
    std::vector<std::string> nomesVariaveisOrdem = caso.getNomesVariaveisOrdem();
    std::vector<TipoVariavel> tiposVariaveis = caso.getTiposVariaveis();
    const std::vector<double>& ladosDireitos = caso.getLadosDireitos();

    std::vector<int> variaveisFolgaExcesso(restricoes, -1);
    std::vector<int> variaveisArtificiais(restricoes, -1);
    //A pos i do vetor indica a restricao atual e o valor que ela recebe
    //indica quantas colunas devemos andar quando estivermos montando
    //a matriz com as variaveis auxiliares
    
    //nomesVariaveisOrdem ja tem as variaveis x1 ate xn (Lidas no leitor)
    //Quando pegamos o seu tamanho, sabemos qual o indice da proxima coluna


    for(int i = 0; i < restricoes; ++i){
        if(operadores[i] == MENOR_IGUAL){
            variaveisFolgaExcesso[i] = int(nomesVariaveisOrdem.size());
            nomesVariaveisOrdem.push_back("s" + std::to_string(i + 1));
            tiposVariaveis.push_back(FOLGA);
        }
        else if(operadores[i] == MAIOR_IGUAL){
            variaveisFolgaExcesso[i] = int(nomesVariaveisOrdem.size());
            nomesVariaveisOrdem.push_back("e" + std::to_string(i + 1));   
            tiposVariaveis.push_back(EXCESSO);
        }
    }

    int inicioColunaArtificiais = int(tiposVariaveis.size());

    for(int i = 0; i < restricoes; ++i){
        if(operadores[i] != MENOR_IGUAL){
            variaveisArtificiais[i] = int(nomesVariaveisOrdem.size());
            nomesVariaveisOrdem.push_back("a" + std::to_string(i + 1));
            tiposVariaveis.push_back(ARTIFICIAL);
        }
    }

    int totalVariaveis = int(nomesVariaveisOrdem.size());
    std::vector<double> matrizPadronizada(restricoes*totalVariaveis, 0.0);

    for(int i = 0; i < restricoes; ++i){
        for (int j = 0; j < variaveisDecisao; j++)
        {
            matrizPadronizada[i * totalVariaveis  + j] = matriz[i * variaveisDecisao + j]; 
        }
        if(operadores[i] == MENOR_IGUAL){
            matrizPadronizada[i * totalVariaveis + variaveisFolgaExcesso[i]] = 1.0;
        }
        else if(operadores[i] == MAIOR_IGUAL){
            matrizPadronizada[i * totalVariaveis + variaveisFolgaExcesso[i]] = -1.0;
        }
        if(variaveisArtificiais[i] != -1){
            matrizPadronizada[i * totalVariaveis + variaveisArtificiais[i]] = 1.0;
        }
    }

    std::vector<int> baseInicial(restricoes, -1);
    bool temVariavelArtificial = false;
    for(int i = 0; i < restricoes; ++i){
        if(variaveisArtificiais[i] != -1){
            baseInicial[i] = variaveisArtificiais[i];
            temVariavelArtificial = true;
        }
        else{
            baseInicial[i] = variaveisFolgaExcesso[i];
        }
    }

    int totalColunas = totalVariaveis + 1;

    caso.setTemVariavelArtificial(temVariavelArtificial);
    caso.setNomesVariaveisOrdem(nomesVariaveisOrdem);
    caso.setTiposVariaveis(tiposVariaveis);
    caso.setBaseInicial(baseInicial);
    caso.setTotalColunasTableau(totalColunas);
    caso.setInicioColunasArtificiais(inicioColunaArtificiais);
    std::vector<double> tableau((restricoes + 1) * totalColunas, 0.0);
    for(int i = 0; i < restricoes; ++i){
        for(int j = 0; j<totalVariaveis; ++j){
            tableau[i * totalColunas + j] = matrizPadronizada[i * totalVariaveis + j];
        }
        tableau[i * totalColunas + totalVariaveis] = ladosDireitos[i];
    }
    caso.setTableau(tableau);
    
}

void PreProcessamento::ajustarSentido(Caso& caso){
    if(caso.getSentido() == MINIMIZAR){
        std::vector<double> coeficientesFuncaoObjetivo = caso.getCoeficientesFuncaoObjetivo();
        for(double& coeficiente : coeficientesFuncaoObjetivo){
            coeficiente = 0.0 - coeficiente;
        }
        caso.setCoeficientesFuncaoObjetivo(coeficientesFuncaoObjetivo);
    }
}
