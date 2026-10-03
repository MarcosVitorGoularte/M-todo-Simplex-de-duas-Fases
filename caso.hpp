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
enum TipoVariavel{
    DECISAO,
    FOLGA,
    EXCESSO,
    ARTIFICIAL
};



class Caso
{
private:
    int variaveisDecisao;
    int restricoes;
    Sentido sentido;
    std::vector<double> coeficientesFuncaoObjetivo;
    std::vector<double> matrizCoeficientesLadoEsquerdo;
    std::vector<Operador> operadores;
    std::vector<double> ladosDireitos;
    std::vector<std::string> nomesVariaveisOrdem; 
    //Para o Tableau
    std::vector<int> baseInicial;
    bool temVariavelArtificial;
    std::vector<TipoVariavel> tiposVariaveis;
    int inicioColunasArtificiais;
    int totalColunasTableau;
    std::vector<double> tableau;
public:

    Caso() = default;
    Caso(int variaveisDecisao,int restricoes, Sentido sentido, const std::vector<double>& coeficientesFuncaoObjetivo, 
        const std::vector<double>& matrizCoeficientesLadoEsquerdo, const std::vector<Operador>& operadores, 
        const std::vector<double>& ladosDireitos, const std::vector<std::string>& nomesVariaveisOrdem,
        const std::vector<TipoVariavel>& tiposVariaveis);
    
    int getVariaveisDecisao() const;
    int getRestricoes() const;
    bool getTemVariavelArtificial() const;
    const std::vector<int>& getBaseInicial() const;
    Sentido getSentido() const;
    const std::vector<double>& getCoeficientesFuncaoObjetivo() const;
    const std::vector<double>& getMatrizCoeficientesLadoEsquerdo()const;
    const std::vector<Operador>& getOperadores()const;
    const std::vector<double>& getLadosDireitos() const;
    const std::vector<std::string>& getNomesVariaveisOrdem() const;
    const std::vector<TipoVariavel>& getTiposVariaveis()const;
    int getTotalColunasTableau() const;
    const std::vector<double>& getTableau() const;
    int getInicioColunasArtificiais() const;
    std::vector<double>& getTableauReferencia();
    std::vector<int>& getBaseReferencia();

    void setVariaveisDecisao(int variaveisDecisao);
    void setRestricoes(int restricoes);
    void setTemVariavelArtificial(bool temVariavelArtificial);
    void setBaseInicial(const std::vector<int>& baseInicial);
    void setSentido(Sentido sentido);
    void setCoeficientesFuncaoObjetivo(const std::vector<double>& coeficientesFuncaoObjetivo);
    void setMatrizCoeficientesLadoEsquerdo(const std::vector<double>& matrizCoeficientesLadoEsquerdo);
    void setOperadores(const std::vector<Operador>& operadores);
    void setLadosDireitos(const std::vector<double>& ladosDireitos);
    void setNomesVariaveisOrdem(const std::vector<std::string>& nomesVariaveisOrdem);
    void setTiposVariaveis(const std::vector<TipoVariavel>& tiposVariaveis);
    void setTotalColunasTableau(int totalColunasTableau);
    void setTableau(const std::vector<double>& tableau);
    void setInicioColunasArtificiais(int inicioColunasArtificiais);

};



#endif