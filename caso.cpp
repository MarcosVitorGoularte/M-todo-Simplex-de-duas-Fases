#include "caso.hpp"
#include <iostream>

Caso::Caso(unsigned long variaveisDecisao, long restricoes, Sentido sentido, std::vector<double>& coeficientesFuncaoObjetivo, 
        std::vector<double>& matriz, std::vector<Operador>& operadores, std::vector<double>& ladosDireitos)
        : variaveisDecisao(variaveisDecisao), restricoes(restricoes), sentido(sentido), coeficientesFuncaoObjetivo(coeficientesFuncaoObjetivo),
          matriz(matriz), operadores(operadores), ladosDireitos(ladosDireitos){}

unsigned long Caso::getVariaveisDecisao() {
    return variaveisDecisao;
}

long Caso::getRestricoes() {
    return restricoes;
}

Sentido Caso::getSentido() {
    return sentido;
}

std::vector<double>& Caso::getCoeficientesFuncaoObjetivo() {
    return coeficientesFuncaoObjetivo;
}

std::vector<double>& Caso::getMatriz() {
    return matriz;
}

std::vector<Operador>& Caso::getOperadores() {
    return operadores;
}

std::vector<double>& Caso::getladosDireitos() {
    return ladosDireitos;
}