#ifndef CASO_HPP
#define CASO_HPP

#include <vector>
#include <string>

enum Sentido {
    MAXIMIZAR, MINIMIZAR
};
enum Operador {
    MENOR_IGUAL = -1, 
    IGUAL = 0,
    MAIOR_IGUAL = 1 
};

class Caso
{
private:
    long variaveisDecisao;
    long restricoes;
    Sentido sentido;
    std::vector<double> coeficientesFuncaoObjetivo;
    std::vector<double> matrizCoeficientesLadoEsquerdo;
    std::vector<Operador> operadores;
    std::vector<double> ladosDireitos;
    std::vector<std::string> nomesVariaveisOrdem; 
    std::vector<double> matrizPadronizada;
    std::vector<long> baseInicial;

public:

    Caso() = default;
    Caso(long variaveisDecisao,long restricoes, Sentido sentido, const std::vector<double>& coeficientesFuncaoObjetivo, 
        const std::vector<double>& matrizCoeficientesLadoEsquerdo, const std::vector<Operador>& operadores, 
        const std::vector<double>& ladosDireitos, const std::vector<std::string>& nomesVariaveisOrdem);
    long getVariaveisDecisao() const;
    long getRestricoes() const;
    const std::vector<long>& getBaseInicial() const;
    Sentido getSentido() const;
    const std::vector<double>& getCoeficientesFuncaoObjetivo() const;
    const std::vector<double>& getMatrizCoeficientesLadoEsquerdo()const;
    const std::vector<double>& getMatrizPadronizada()const;
    const std::vector<Operador>& getOperadores()const;
    const std::vector<double>& getLadosDireitos() const;
    const std::vector<std::string>& getNomesVariaveisOrdem() const;

    void setVariaveisDecisao(long variaveisDecisao);
    void setRestricoes(long restricoes);
    void setBaseInicial(const std::vector<long>& baseInicial);
    void setSentido(Sentido sentido);
    void setCoeficientesFuncaoObjetivo(const std::vector<double>& coeficientesFuncaoObjetivo);
    void setMatrizCoeficientesLadoEsquerdo(const std::vector<double>& matrizCoeficientesLadoEsquerdo);
    void setMatrizPadronizada(const std::vector<double>& matrizPadronizada);
    void setOperadores(const std::vector<Operador>& operadores);
    void setLadosDireitos(const std::vector<double>& ladosDireitos);
    void setNomesVariaveisOrdem(const std::vector<std::string>& nomesVariaveisOrdem);
};



#endif