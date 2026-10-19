CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra

ifeq ($(OS),Windows_NT)
    EXE    := .exe
    PYTHON ?= python
else
    EXE    :=
    PYTHON ?= python3
endif

ifeq ($(shell echo "ok"),"ok")
    ESTILO := cmd
else
    ESTILO := sh
endif

TARGET := simplex$(EXE)
SRCS   := $(wildcard *.cpp)
HDRS   := $(wildcard *.hpp)
ARGS   ?=
GRUPO  ?=
CASO   ?=

ifeq ($(ESTILO),cmd)
    APAGAR = if exist $(TARGET) del /Q /F $(TARGET)
else
    APAGAR = rm -f $(TARGET)
endif

ifneq ($(filter caso,$(MAKECMDGOALS)),)
ifeq ($(strip $(CASO)),)
$(error Informe o caso: make caso CASO=b01   ou   make caso CASO="b01 d03")
endif
endif

define TEXTO_AJUDA
Comandos:
  make                       compila (g++ -std=c++17 -O2 -Wall -Wextra)
  make run                   compila e roda toda a bateria de casos/ comparando com esperado/
  make caso CASO=b01         compila e roda um caso, mostrando a saida do programa
  make caso CASO="b01 d03"   idem, para varios casos
  make grandes               gera os casos g08..g13 (gerador_grandes.py)
  make clean                 apaga o executavel

Variaveis opcionais (valem para run e caso):
  ARGS=-t                    passo a passo. Nao escreva make run -t: o make le -t como --touch
  ARGS="-t --ate 200"        com -t, run pula casos com n+m > 100; --ate N muda o limite
  GRUPO=A                    run apenas do grupo A (A a G)
  ARGS=--verboso             mostra gabarito e saida lado a lado nas falhas
  PYTHON=py                  interpretador Python (padrao: python no Windows, python3 no Linux)
endef

.PHONY: all run caso grandes clean ajuda help mostrar_ajuda

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	$(PYTHON) rodar_testes.py $(TARGET) $(if $(GRUPO),--grupo $(GRUPO),) $(ARGS)

caso: $(TARGET)
	$(PYTHON) rodar_testes.py $(TARGET) --saida --verboso --caso $(CASO) $(ARGS)

grandes:
	$(PYTHON) gerador_grandes.py

clean:
	$(APAGAR)

ajuda help:
	@$(MAKE) --no-print-directory -s mostrar_ajuda

mostrar_ajuda:
	$(info $(TEXTO_AJUDA))
