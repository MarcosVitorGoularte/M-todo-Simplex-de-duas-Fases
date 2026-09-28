#include "caso.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool interpretaSentido(const string& lerSentido, Sentido& sentido){
    if(lerSentido == "MAX"){
        sentido = MAXIMIZAR;
        return true;
    }
    if(lerSentido == "MIN"){
        sentido = MINIMIZAR;
        return true;
    }
    return false;
}

bool interpretaOperador(const string& lerOperador, Operador& operador){
    if(lerOperador == "<="){
        operador = MENOR_IGUAL;
        return true;
    }
    if(lerOperador == "=="){
        operador = IGUAL;
        return true;
    }
    if(lerOperador == ">="){
        operador = MAIOR_IGUAL;
        return true;
    }
    return false;
}


bool lerCaso(istream& in, Caso& caso){
    unsigned long n;
    long m;

    if(!(in >> n >> m)){
        cerr << "Erro em ler as variaveis ou restricoes\n";
        return false;
    }
    if(n <= 0 || m <=0){
        cerr << "A quantidade de restricoes e variaveis deve ser positiva\n";
        return false;
    }
    Sentido sentido;
    string lerSentido;
    if(!(in >> lerSentido) || !interpretaSentido(lerSentido, sentido)){
        cerr << "Erro na leitura do sentido da funcao objetivo";
        return false;
    }

    vector<double> coeficientesFuncaoObjetivo, ladosDireitos, matriz;
    vector<Operador> operadores;

    for(unsigned long j = 0; j < n; ++j){
        double coeficiente;
        if(!(in >> coeficiente)){
            cerr << "Erro na leitura do coeficiente["<<j<<"] da funcao objetivo\n";
            return false;
        }
        coeficientesFuncaoObjetivo.push_back(coeficiente);
    }

    for(unsigned long i = 0; i < m; ++i){
        for(unsigned long j = 0; j < n; j++){
            double coeficienteRestricao;
            if(!(in >> coeficienteRestricao)){
                cerr << "Erro ao ler A[" << i <<"][" << j << "]\n";
                return false;
            }
            matriz.push_back(coeficienteRestricao);
        }
    

        Operador operador;
        string lerOperador;
        if(!(in >> lerOperador) || !interpretaOperador(lerOperador, operador)){
            cerr << "Erro ao ler operador\n";
            return false;
        }
        operadores.push_back(operador);

        double ladoDireito;
        if(!(in >> ladoDireito)){
            cerr << "Erro ao ler lado direito\n";
            return false;
        }
        ladosDireitos.push_back(ladoDireito);
    }
    caso = Caso(n, m, sentido, coeficientesFuncaoObjetivo, matriz, operadores, ladosDireitos);
    return true;
}

int main(){
    Caso caso;
    bool tentativaLeitura = lerCaso(cin, caso);
    return 0;
}
