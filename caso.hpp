#ifndef CASO_HPP
#define CASO_HPP

#include <vector>

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
    std::vector<double> matriz;
    std::vector<Operador> operadores;
    std::vector<double> ladosDireitos;
public:
    Caso() = default;
    Caso(long variaveisDecisao,long restricoes, Sentido sentido, const std::vector<double>& coeficientesFuncaoObjetivo, 
        const std::vector<double>& matriz, const std::vector<Operador>& operadores, const std::vector<double>& ladosDireitos);
    long getVariaveisDecisao() const;
    long getRestricoes() const;
    Sentido getSentido() const;
    const std::vector<double>& getCoeficientesFuncaoObjetivo() const;
    const std::vector<double>& getMatriz()const;
    const std::vector<Operador>& getOperadores()const;
    const std::vector<double>& getLadosDireitos() const;

    void setVariaveisDecisao(long variaveisDecisao);
    void setRestricoes(long restricoes);
    void setSentido(Sentido sentido);
    void setCoeficientesFuncaoObjetivo(const std::vector<double>& coeficientesFuncaoObjetivo);
    void setMatriz(const std::vector<double>& matriz);
    void setOperadores(const std::vector<Operador>& operadores);
    void setLadosDireitos(const std::vector<double>& ladosDireitos);

};



#endif