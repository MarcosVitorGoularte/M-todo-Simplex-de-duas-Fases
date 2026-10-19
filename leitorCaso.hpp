#ifndef LEITORCASO_HPP
#define LEITORCASO_HPP
#include "caso.hpp"
#include <string>

class LeitorCaso
{
private:
public:
    LeitorCaso() = delete;
    static bool interpretaSentido(const std::string& lerSentido, Sentido& sentido);
    static bool interpretaOperador(const std::string& lerOperador, Operador& operador);
    static bool lerCaso(std::istream& in, Caso& caso);
};

#endif