#include "leitorCaso.hpp"
#include "caso.hpp"
#include <string>
#include <vector>
#include <iostream>

bool LeitorCaso::interpretaSentido(const std::string& lerSentido, Sentido& sentido){
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

bool LeitorCaso::interpretaOperador(const std::string& lerOperador, Operador& operador){
    if(lerOperador == "<="){
        operador = MENOR_IGUAL;
        return true;
    }
    if(lerOperador == "="){
        operador = IGUAL;
        return true;
    }
    if(lerOperador == ">="){
        operador = MAIOR_IGUAL;
        return true;
    }
    return false;
}


bool LeitorCaso::lerCaso(std::istream& in, Caso& caso){
    int n;
    int m;

    if(!(in >> n >> m)){
        std::cerr << "Erro em ler as variaveis ou restricoes\n";
        return false;
    }
    if(n <= 0 || m <=0){
        std::cerr << "A quantidade de restricoes e variaveis deve ser positiva\n";
        return false;
    }
    Sentido sentido;
    std::string lerSentido;
    if(!(in >> lerSentido) || !interpretaSentido(lerSentido, sentido)){
        std::cerr << "Erro na leitura do sentido da funcao objetivo";
        return false;
    }

    std::vector<double> coeficientesFuncaoObjetivo, ladosDireitos, matriz;
    std::vector<Operador> operadores;
    std::vector<std::string> nomesVariaveisOrdem;
    std::vector<TipoVariavel> tiposVariaveis;

    for(int j = 0; j < n; ++j){
        double coeficiente;
        if(!(in >> coeficiente)){
            std::cerr << "Erro na leitura do coeficiente["<<j<<"] da funcao objetivo\n";
            return false;
        }
        coeficientesFuncaoObjetivo.push_back(coeficiente);
        nomesVariaveisOrdem.push_back("x" + std::to_string(j+1));
        tiposVariaveis.push_back(DECISAO);
    }

    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; j++){
            double coeficienteRestricao;
            if(!(in >> coeficienteRestricao)){
                std::cerr << "Erro ao ler A[" << i <<"][" << j << "]\n";
                return false;
            }
            matriz.push_back(coeficienteRestricao);
        }
    
        Operador operador;
        std::string lerOperador;
        if(!(in >> lerOperador) || !interpretaOperador(lerOperador, operador)){
            std::cerr << "Erro ao ler operador\n";
            return false;
        }
        operadores.push_back(operador);

        double ladoDireito;
        if(!(in >> ladoDireito)){
            std::cerr << "Erro ao ler lado direito\n";
            return false;
        }
        ladosDireitos.push_back(ladoDireito);
    }
    caso = Caso(n, m, sentido, coeficientesFuncaoObjetivo, matriz, operadores, ladosDireitos, nomesVariaveisOrdem, tiposVariaveis);
    return true;
}