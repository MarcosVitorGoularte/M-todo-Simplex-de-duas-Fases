#include "caso.hpp"
#include "leitorCaso.hpp"
#include "preProcessamento.hpp"
#include "primeiraFase.hpp"
#include "segundaFase.hpp"
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

struct CasosEspeciais {
    bool degenerada;
    bool multiplas;
    bool alternativaIlimitada;
    vector<double> alternativa;
};

vector<double> extrairX(const vector<double>& tableau, const vector<int>& base,
                             int variaveisDecisao, int restricoes, int totalColunas){
    vector<double> x(variaveisDecisao, 0.0);
    for(int i = 0; i < restricoes; ++i){
        if(base[i] < variaveisDecisao){
            x[base[i]] = tableau[i * totalColunas + totalColunas - 1];
        }
    }
    return x;
}

bool ehDegenerada(const Caso& caso){
    int restricoes = caso.getRestricoes();
    int totalColunas = caso.getTotalColunasTableau();
    const vector<double>& tableau = caso.getTableau();

    for(int i = 0; i < restricoes; ++i){
        if(fabs(tableau[i * totalColunas + totalColunas - 1]) < EPS_CLASSIFICACOES){
            return true;
        }
    }
    return false;
}

int primeiraColunaNaoBasicaCustoNulo(const Caso& caso){
    int restricoes = caso.getRestricoes();
    int totalColunas = caso.getTotalColunasTableau();
    const vector<double>& tableau = caso.getTableau();
    const vector<int>& base = caso.getBaseInicial();
    int inicioZ = restricoes * totalColunas;

    vector<bool> ehBasica(totalColunas, false);
    for(int i = 0; i < restricoes; ++i){
        ehBasica[base[i]] = true;
    }
    for(int j = 0; j < totalColunas - 1; ++j){
        if(!ehBasica[j] && fabs(tableau[inicioZ + j]) < EPS_CLASSIFICACOES){
            return j;
        }
    }
    return -1;
}

int linhaDaRazaoMinima(const vector<double>& tableau, int restricoes, int totalColunas, int coluna){
    int linhaSai = -1;
    double menorRazao = 0.0;

    for(int i = 0; i < restricoes; ++i){
        double elemento = tableau[i * totalColunas + coluna];
        if(elemento > EPS_COMPARACOES){
            double razao = tableau[i * totalColunas + totalColunas - 1] / elemento;
            if(linhaSai == -1 || razao < menorRazao){
                menorRazao = razao;
                linhaSai = i;
            }
        }
    }
    return linhaSai;
}

void pivotearUmaVez(vector<double>& tableau, vector<int>& base,
                    int restricoes, int totalColunas, int linhaPivo, int colunaPivo){
    int inicioLinhaPivo = linhaPivo * totalColunas;
    double elementoPivo = tableau[inicioLinhaPivo + colunaPivo];

    for(int j = 0; j < totalColunas; ++j){
        tableau[inicioLinhaPivo + j] = tableau[inicioLinhaPivo + j] / elementoPivo;
    }
    for(int i = 0; i < restricoes + 1; ++i){
        if(i == linhaPivo){
            continue;
        }
        int inicioLinha = i * totalColunas;
        double multiplicador = tableau[inicioLinha + colunaPivo];
        for(int j = 0; j < totalColunas; ++j){
            tableau[inicioLinha + j] = tableau[inicioLinha + j] - multiplicador * tableau[inicioLinhaPivo + j];
        }
        tableau[inicioLinha + colunaPivo] = 0.0;
    }
    base[linhaPivo] = colunaPivo;
}

CasosEspeciais analisarCasosEspeciais(const Caso& caso){
    CasosEspeciais especiais;
    especiais.degenerada = ehDegenerada(caso);
    especiais.multiplas = false;
    especiais.alternativaIlimitada = false;

    int colunaEntra = primeiraColunaNaoBasicaCustoNulo(caso);
    if(colunaEntra == -1){
        return especiais;
    }
    especiais.multiplas = true;

    int restricoes = caso.getRestricoes();
    int totalColunas = caso.getTotalColunasTableau();
    vector<double> tableau = caso.getTableau();
    vector<int> base = caso.getBaseInicial();

    int linhaSai = linhaDaRazaoMinima(tableau, restricoes, totalColunas, colunaEntra);
    if(linhaSai == -1){
        especiais.alternativaIlimitada = true;
        return especiais;
    }
    pivotearUmaVez(tableau, base, restricoes, totalColunas, linhaSai, colunaEntra);
    especiais.alternativa = extrairX(tableau, base, caso.getVariaveisDecisao(), restricoes, totalColunas);
    return especiais;
}

void imprimirVetor(const vector<double>& v){
    for(size_t j = 0; j < v.size(); ++j){
        if(j > 0){
            cout << ' ';
        }
        cout << Caso::formatarNumerosImpressao(v[j], 6);
    }
    cout << '\n';
}

void imprimirResultadoOtimo(const Caso& caso, int iteracoesFase1, int iteracoesFase2, const CasosEspeciais& especiais){
    int restricoes = caso.getRestricoes();
    int totalColunas = caso.getTotalColunasTableau();
    const vector<double>& tableau = caso.getTableau();

    double z = tableau[restricoes * totalColunas + totalColunas - 1];
    if(caso.getSentido() == MINIMIZAR){
        z = -z;
    }
    vector<double> x = extrairX(tableau, caso.getBaseInicial(), caso.getVariaveisDecisao(), restricoes, totalColunas);

    cout << "STATUS: OTIMA\n";
    cout << "Z: " << Caso::formatarNumerosImpressao(z, 6) << '\n';
    cout << "X: ";
    imprimirVetor(x);
    cout << "MULTIPLAS: " << (especiais.multiplas ? "SIM" : "NAO") << '\n';
    cout << "DEGENERADA: " << (especiais.degenerada ? "SIM" : "NAO") << '\n';
    cout << "ITERACOES: " << iteracoesFase1 << ' ' << iteracoesFase2 << '\n';
    if(especiais.multiplas){
        if(especiais.alternativaIlimitada){
            cout << "ALTERNATIVA: RAIO\n";
        }
        else{
            cout << "ALTERNATIVA: ";
            imprimirVetor(especiais.alternativa);
        }
    }
}

int main(int argc, char** argv){
    bool modoImpressao = false;
    for(int i = 1; i < argc; ++i){
        if(strcmp(argv[i], "-t") == 0){
            modoImpressao = true;
        }
    }

    Caso caso;
    if(!LeitorCaso::lerCaso(cin, caso)){
        return 1;
    }
    caso.setModoImpressao(modoImpressao);
    
    PreProcessamento::verificarDireitaNegativa(caso);
    PreProcessamento::criarVariaveisAuxiliares(caso);
    PreProcessamento::ajustarSentido(caso);

    StatusFinalPrimeiraFase fase1 = PrimeiraFase::executarPrimeiraFase(caso);
    if(fase1.status == INVIAVEL){
        cout << "STATUS: INVIAVEL\n";
        return 0;
    }
    if(fase1.status != OTIMA && fase1.status != SEM_ARTIFICIAL){
        return 1;
    }

    StatusFinalSegundaFase fase2 = SegundaFase::executarSegundaFase(caso);
    if(fase2.status == ILIMITADA){
        cout << "STATUS: ILIMITADA\n";
        return 0;
    }
    if(fase2.status != OTIMA){
        return 1;
    }

    CasosEspeciais especiais = analisarCasosEspeciais(caso);
    imprimirResultadoOtimo(caso, fase1.iteracoes, fase2.iteracoes, especiais);
    return 0;
}