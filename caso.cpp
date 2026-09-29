#include "caso.hpp"
#include <iostream>
#include <vector>
#include <string>


Caso::Caso(long variaveisDecisao,long restricoes, Sentido sentido, const std::vector<double>& coeficientesFuncaoObjetivo, 
        const std::vector<double>& matrizCoeficientesLadoEsquerdo,const std::vector<Operador>& operadores,
        const std::vector<double>& ladosDireitos,const std::vector<std::string>& nomesVariaveisOrdem)
        : variaveisDecisao(variaveisDecisao), restricoes(restricoes), sentido(sentido),coeficientesFuncaoObjetivo(coeficientesFuncaoObjetivo),
        matrizCoeficientesLadoEsquerdo(matrizCoeficientesLadoEsquerdo), operadores(operadores), 
        ladosDireitos(ladosDireitos), nomesVariaveisOrdem(nomesVariaveisOrdem){}

long Caso::getVariaveisDecisao() const {
    return variaveisDecisao;
}

long Caso::getRestricoes() const {
    return restricoes;
}

const std::vector<long>& Caso::getBaseInicial() const {
    return baseInicial;
}

Sentido Caso::getSentido() const {
    return sentido;
}

const std::vector<double>& Caso::getCoeficientesFuncaoObjetivo() const{
    return coeficientesFuncaoObjetivo;
}

const std::vector<double>& Caso::getMatrizCoeficientesLadoEsquerdo() const{
    return matrizCoeficientesLadoEsquerdo;
}

const std::vector<double>& Caso::getMatrizPadronizada() const{
    return matrizPadronizada;
}

const std::vector<Operador>& Caso::getOperadores()const{
    return operadores;
}

const std::vector<double>& Caso::getLadosDireitos()const {
    return ladosDireitos;
}
const std::vector<std::string>& Caso::getNomesVariaveisOrdem()const {
    return nomesVariaveisOrdem;
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

void Caso::setBaseInicial(const std::vector<long>& baseInicial){
    this->baseInicial = baseInicial;
}

void Caso::setCoeficientesFuncaoObjetivo(const std::vector<double>& coeficientesFuncaoObjetivo){
    this->coeficientesFuncaoObjetivo = coeficientesFuncaoObjetivo;
}

void Caso::setMatrizCoeficientesLadoEsquerdo(const std::vector<double>& matrizCoeficientesLadoEsquerdo){
    this->matrizCoeficientesLadoEsquerdo = matrizCoeficientesLadoEsquerdo;
}
void Caso::setMatrizPadronizada(const std::vector<double>& matrizPadronizada){
    this->matrizPadronizada = matrizPadronizada;
}

void Caso::setOperadores(const std::vector<Operador>& operadores){
    this->operadores = operadores;
}
void Caso::setLadosDireitos(const std::vector<double>& ladosDireitos){
    this->ladosDireitos = ladosDireitos;
}
void Caso::setNomesVariaveisOrdem(const std::vector<std::string>& nomesVariaveisOrdem){
    this->nomesVariaveisOrdem = nomesVariaveisOrdem;
}