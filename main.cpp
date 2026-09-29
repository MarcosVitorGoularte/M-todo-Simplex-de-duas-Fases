#include "caso.hpp"
#include "leitorCaso.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    Caso caso;
    bool tentativaLeitura = LeitorCaso::lerCaso(cin, caso);
    return 0;
}
