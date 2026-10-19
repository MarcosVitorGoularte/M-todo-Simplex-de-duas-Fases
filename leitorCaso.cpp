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
        return false;
    }
    if(n <= 0 || m <=0){
        return false;
    }
    Sentido sentido;
    std::string lerSentido;
    if(!(in >> lerSentido) || !interpretaSentido(lerSentido, sentido)){
        return false;
    }

    std::vector<double> coeficientesFuncaoObjetivo, ladosDireitos, matriz;
    std::vector<Operador> operadores;
    std::vector<std::string> nomesVariaveisOrdem;
    std::vector<TipoVariavel> tiposVariaveis;

    for(int j = 0; j < n; ++j){
        double coeficiente;
        if(!(in >> coeficiente)){
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
                return false;
            }
            matriz.push_back(coeficienteRestricao);
        }
    
        Operador operador;
        std::string lerOperador;
        if(!(in >> lerOperador) || !interpretaOperador(lerOperador, operador)){
            return false;
        }
        operadores.push_back(operador);

        double ladoDireito;
        if(!(in >> ladoDireito)){
            return false;
        }
        ladosDireitos.push_back(ladoDireito);
    }
    caso = Caso(n, m, sentido, coeficientesFuncaoObjetivo, matriz, operadores, ladosDireitos, nomesVariaveisOrdem, tiposVariaveis);
    return true;
}