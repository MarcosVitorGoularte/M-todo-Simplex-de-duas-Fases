#include "caso.hpp"
#include <iostream>
#include <vector>
#include <string>



Caso::Caso(int variaveisDecisao,int restricoes, Sentido sentido, const std::vector<double>& coeficientesFuncaoObjetivo, 
        const std::vector<double>& matrizCoeficientesLadoEsquerdo,const std::vector<Operador>& operadores,
        const std::vector<double>& ladosDireitos,const std::vector<std::string>& nomesVariaveisOrdem, const std::vector<TipoVariavel>& tiposVariaveis)
        : variaveisDecisao(variaveisDecisao), restricoes(restricoes), sentido(sentido),coeficientesFuncaoObjetivo(coeficientesFuncaoObjetivo),
        matrizCoeficientesLadoEsquerdo(matrizCoeficientesLadoEsquerdo), operadores(operadores), 
        ladosDireitos(ladosDireitos), nomesVariaveisOrdem(nomesVariaveisOrdem), tiposVariaveis(tiposVariaveis){}


#pragma region Getters e Setters

int Caso::getVariaveisDecisao() const {
    return variaveisDecisao;
}

int Caso::getRestricoes() const {
    return restricoes;
}

bool Caso::getTemVariavelArtificial() const {
    return temVariavelArtificial;
}

const std::vector<int>& Caso::getBaseInicial() const {
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

const std::vector<Operador>& Caso::getOperadores()const{
    return operadores;
}

const std::vector<double>& Caso::getLadosDireitos()const {
    return ladosDireitos;
}
const std::vector<std::string>& Caso::getNomesVariaveisOrdem()const {
    return nomesVariaveisOrdem;
}

const std::vector<TipoVariavel>& Caso::getTiposVariaveis() const{
    return tiposVariaveis;
}

int Caso::getTotalColunasTableau() const {
    return totalColunasTableau;
}

const std::vector<double>& Caso::getTableau() const {
    return tableau;
}

int Caso::getInicioColunasArtificiais() const{
    return inicioColunasArtificiais;
}

std::vector<double>& Caso::getTableauReferencia(){
    return tableau; 
}
std::vector<int>& Caso::getBaseReferencia(){
    return baseInicial;
}

void Caso::setVariaveisDecisao(int variaveisDecisao){
    this->variaveisDecisao = variaveisDecisao;
}

void Caso::setRestricoes(int restricoes){
    this->restricoes = restricoes;
}

void Caso::setTemVariavelArtificial(bool temVariavelArtificial){
    this->temVariavelArtificial = temVariavelArtificial;
}


void Caso::setSentido(Sentido sentido){
    this->sentido = sentido;
}

void Caso::setBaseInicial(const std::vector<int>& baseInicial){
    this->baseInicial = baseInicial;
}

void Caso::setCoeficientesFuncaoObjetivo(const std::vector<double>& coeficientesFuncaoObjetivo){
    this->coeficientesFuncaoObjetivo = coeficientesFuncaoObjetivo;
}

void Caso::setMatrizCoeficientesLadoEsquerdo(const std::vector<double>& matrizCoeficientesLadoEsquerdo){
    this->matrizCoeficientesLadoEsquerdo = matrizCoeficientesLadoEsquerdo;
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

void Caso::setTiposVariaveis(const std::vector<TipoVariavel>& tiposVariaveis){
    this->tiposVariaveis = tiposVariaveis;
}

void Caso::setTotalColunasTableau(int totalColunasTableau){
    this->totalColunasTableau = totalColunasTableau;
}

void Caso::setTableau(const std::vector<double>& tableau){
    this->tableau = tableau;
}


void Caso::setInicioColunasArtificiais(int inicioColunasArtificiais){
    this->inicioColunasArtificiais = inicioColunasArtificiais;
}

#pragma endregion

