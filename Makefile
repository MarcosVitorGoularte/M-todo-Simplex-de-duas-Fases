# Makefile -- Simplex de Duas Fases (Trabalho 1)
#
#   make                  compila o executavel ./simplex
#   make test             roda a bateria inteira (verificar.py)
#   make test GRUPO=A     roda so um grupo (A..G)
#   make grandes          gera os casos g08..g13 (gerador_grandes.py)
#   make debug            compila com -g e sanitizers (ASan/UBSan)
#   make clean            apaga objetos e o executavel
#
# A bateria (casos/, esperado/, verificar.py) precisa estar na pasta apontada por
# BATERIA. Por padrao e a pasta atual; se ela estiver em outro lugar:
#   make test BATERIA=../PesquisaOperacional

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra
TARGET   := simplex
BUILD    := build
BATERIA  ?= .
GRUPO    ?=

SRCS := main.cpp modelo.cpp tableau.cpp regras.cpp fases.cpp \
        especiais.cpp saida.cpp solver.cpp
OBJS := $(SRCS:%.cpp=$(BUILD)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all test grandes debug clean

all: $(TARGET)

# Ligacao: junta todos os .o no executavel.
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compilacao: cada .cpp vira um .o. -MMD -MP gera os .d com as dependencias de
# cabecalhos, entao mexer num .hpp recompila so quem o inclui.
$(BUILD)/%.o: %.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

-include $(DEPS)

test: $(TARGET)
	cd $(BATERIA) && python3 verificar.py $(abspath $(TARGET)) $(if $(GRUPO),--grupo $(GRUPO),)

grandes:
	cd $(BATERIA) && python3 gerador_grandes.py

debug: CXXFLAGS = -std=c++17 -O0 -g -Wall -Wextra -fsanitize=address,undefined
debug: clean $(TARGET)

clean:
	rm -rf $(BUILD) $(TARGET)