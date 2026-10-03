#include "caso.hpp"
#include "leitorCaso.hpp"
#include "preProcessamento.hpp"
#include "primeiraFase.hpp"
#include "segundaFase.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void detectarCasosEspeciais(){
    return;
}

int main(){
    Caso caso;
    bool tentativaLeitura = LeitorCaso::lerCaso(cin, caso);
    return tentativaLeitura;
}
