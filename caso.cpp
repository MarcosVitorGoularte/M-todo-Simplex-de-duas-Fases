#include "caso.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>



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

bool Caso::getModoImpressao() const {
    return modoImpressao;
}

void Caso::setModoImpressao(bool modoImpressao){
    this->modoImpressao = modoImpressao;
}

#pragma endregion

std::string Caso::formatarNumerosImpressao(double valor, int casas){
    std::ostringstream saida;
    saida << std::fixed << std::setprecision(casas) << valor;
    std::string texto = saida.str();
    if(texto.size() > 1 && texto[0] == '-' && texto.find_first_not_of("-0.") == std::string::npos){
        texto.erase(0, 1);
    }
    return texto;
}

void Caso::imprimirEstadoAtual(const std::string& titulo) const {
    int colunas = totalColunasTableau;
    std::ios_base::fmtflags flagsAntigas = std::cout.flags();

    std::cout << "--- " << titulo << " ---\n\n";

    std::cout << std::left << std::setw(6) << "BASE" << std::right;
    for(int j = 0; j < colunas - 1; ++j){
        std::cout << ' ' << std::setw(10) << nomesVariaveisOrdem[j];
    }
    std::cout << ' ' << std::setw(10) << "RHS" << '\n';

    for(int i = 0; i <= restricoes; ++i){
        const std::string rotulo = (i < restricoes) ? nomesVariaveisOrdem[baseInicial[i]] : "Z";
        std::cout << std::left << std::setw(6) << rotulo << std::right;
        for(int j = 0; j < colunas; ++j){
            std::cout << ' ' << std::setw(10) << formatarNumerosImpressao(tableau[i * colunas + j], 4);
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    std::cout.flags(flagsAntigas);
}

void Caso::imprimirPivo(int linha, int coluna) const {
    std::cout << "Entra: " << nomesVariaveisOrdem[coluna]
    << " | Sai: " << nomesVariaveisOrdem[baseInicial[linha]]
    << " | Pivo: linha " << linha + 1 << ", coluna " << nomesVariaveisOrdem[coluna]
    << " (valor " << formatarNumerosImpressao(tableau[linha * totalColunasTableau + coluna], 4) << ")\n\n";
}

