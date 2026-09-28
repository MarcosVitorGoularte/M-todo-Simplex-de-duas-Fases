#ifndef CASO_HPP
#define CASO_HPP

#include <vector>

enum Sentido {
    MAXIMIZAR, MINIMIZAR
};
enum Operador {
    MENOR_IGUAL, MAIOR_IGUAL, IGUAL
};

class Caso
{
private:
    unsigned long variaveisDecisao;
    long restricoes;
    Sentido sentido;
    std::vector<double> coeficientesFuncaoObjetivo;
    std::vector<double> matriz;          // matriz m x n, por linhas: A[i * n + j]
    std::vector<Operador> operadores;
    std::vector<double> ladosDireitos;
public:
    Caso() = default;
    Caso(unsigned long variaveisDecisao, long restricoes, Sentido sentido, std::vector<double>& coeficientesFuncaoObjetivo, 
        std::vector<double>& matriz, std::vector<Operador>& operadores, std::vector<double>& ladosDireitos);
    unsigned long getVariaveisDecisao();
    long getRestricoes();
    Sentido getSentido();
    std::vector<double>& getCoeficientesFuncaoObjetivo();
    std::vector<double>& getMatriz();
    std::vector<Operador>& getOperadores();
    std::vector<double>& getladosDireitos();
};



#endif