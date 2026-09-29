#include "caso.hpp"
#include <iostream>

Caso::Caso(long variaveisDecisao,long restricoes, Sentido sentido, const std::vector<double>& coeficientesFuncaoObjetivo, 
        const std::vector<double>& matriz,const std::vector<Operador>& operadores,const std::vector<double>& ladosDireitos)
        : variaveisDecisao(variaveisDecisao), restricoes(restricoes), sentido(sentido), coeficientesFuncaoObjetivo(coeficientesFuncaoObjetivo),
          matriz(matriz), operadores(operadores), ladosDireitos(ladosDireitos){}

long Caso::getVariaveisDecisao() const {
    return variaveisDecisao;
}

long Caso::getRestricoes() const {
    return restricoes;
}

Sentido Caso::getSentido() const {
    return sentido;
}

const std::vector<double>& Caso::getCoeficientesFuncaoObjetivo() const{
    return coeficientesFuncaoObjetivo;
}

const std::vector<double>& Caso::getMatriz() const{
    return matriz;
}

const std::vector<Operador>& Caso::getOperadores()const{
    return operadores;
}

const std::vector<double>& Caso::getLadosDireitos()const {
    return ladosDireitos;
}

void Caso::setVariaveisDecisao(long variaveisDecisao){
    this->variaveisDecisao = variaveisDecisao;
}
void Caso::setRestricoes(long restricoes){
    this->restricoes = restricoes;
}
void Caso::setSentido(Sentido sentido){
    this->sentido = sentido;
}

void Caso::setCoeficientesFuncaoObjetivo(const std::vector<double>& coeficientesFuncaoObjetivo){
    this->coeficientesFuncaoObjetivo = coeficientesFuncaoObjetivo;
}
void Caso::setMatriz(const std::vector<double>& matriz){
    this->matriz = matriz;
}
void Caso::setOperadores(const std::vector<Operador>& operadores){
    this->operadores = operadores;
}
void Caso::setLadosDireitos(const std::vector<double>& ladosDireitos){
    this->ladosDireitos = ladosDireitos;
}