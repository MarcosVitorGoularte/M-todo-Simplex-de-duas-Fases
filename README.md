## 1. Como compilar e executar

Requisitos: `g++` com suporte a C++17, `make` e Python 3 (este só para rodar a bateria de testes).

```bash
make # g++ -std=c++17 -O2 -Wall -Wextra -> simplex (simplex.exe no Windows)
./simplex < casos/caso01.txt # apenas o resultado
./simplex -t < casos/caso01.txt # passo a passo + resultado
```
Comandos do `make` para a bateria de testes:

| comando | efeito |
|---|---|
| `make run` | compila e roda **todos** os casos de `casos/`, comparando com `esperado/` |
| `make run GRUPO=A` | roda só um grupo (a letra é a primeira do nome do caso) |
| `make caso CASO=caso01` ou `CASO="caso01 meucaso02"` | roda casos específicos e mostra a saída do programa |
| `make caso CASO=caso01 ARGS=-t` | roda casos específicos e mostra a saída do programa, com o passo a passo |
| `make run ARGS=--verboso` | nas falhas, mostra gabarito e saída lado a lado |
| `make grandes` | gera os casos grandes `g08`…`g13` (`gerador_grandes.py`) |
| `make clean` | apaga o executável |

> **Atenção: o `make` só encontra os testes se estiverem nas pastas certas.** Os casos de entrada devem ficar em
> **`casos/`** (`<nome>.txt`) e os resultados esperados em **`esperado/`** (`<nome>.out`), ao lado do `Makefile`
> e do `verificar.py`. O verificador monta a lista de casos a partir dos arquivos de `esperado/` e procura a
> entrada de mesmo nome em `casos/`; sem o par `casos/X.txt` + `esperado/X.out` o caso não roda (um `.txt` sem
> `.out` é ignorado em silêncio; um `.out` sem `.txt` aparece como `PULADO`). É por isso que `caso01`–`caso11`
> e `meucaso01`–`meucaso02` estão nessas duas pastas.

## 2. Principais decisões de implementação

```
main.cpp            chama: ler -> padronizar -> Fase 1 -> Fase 2 -> casos especiais (no próprio main) -> saída
caso.hpp/.cpp       classe Caso: dados do modelo, tableau, base e impressão do modo -t
leitorCaso.*        leitura da entrada (tokens separados por espaço ou quebra de linha)
preProcessamento.*  b < 0, variáveis de folga/excesso/artificiais, MIN -> MAX
primeiraFase.*      linha Z da Fase 1, pivoteamento, inviabilidade e transição para a Fase 2
segundaFase.*       linha Z original, canonicalização, pivoteamento e ilimitação
```

- **Bônus da Seção 12:** não implementados.

### Transição entre as fases

A Fase 1 só roda se houver artificial; caso contrário `ITERACOES` começa com `0` e vai-se direto à Fase 2. Na
Fase 1 a linha Z nasce zerada, subtrai-se dela cada linha cuja base é artificial e zeram-se as colunas
artificiais; *w* = −RHS(Z). Se *w\** > 1e-7, imprime-se `STATUS: INVIAVEL` e o programa encerra.

Se *w\** ≈ 0, `transicaoParaFase2` percorre as linhas **de cima para baixo** e, para cada artificial ainda básica
(valendo 0):

1. Se existe coluna **não artificial** com `|a_ij| > 1e-9`, pivoteia na menor delas. Isso troca a artificial por
   uma variável legítima sem alterar a solução. O pivô costuma ser **negativo** (no fim da Fase 1 a soma das
   linhas com artificial básica é ≤ 0 em cada coluna), o que é aceitável porque o RHS da linha é 0
   (`caso10`: pivô −1; `meucaso02`: pivô −2).
2. Se todos os coeficientes não artificiais são nulos, a restrição é **redundante**: a linha é apagada do tableau
   e da base e o índice da linha **não avança**, pois a seguinte desliza para a mesma posição.

A ordem importa: uma linha só se revela nula depois dos pivôs das anteriores (em `meucaso02`, a linha de `a3` só
fica nula depois do pivô de `a2`). Os pivôs da transição não entram em `ITERACOES`. Em seguida as colunas
artificiais são descartadas (novo tableau só com as colunas legítimas e o RHS).

Na Fase 2 a linha Z é **reconstruída** do objetivo original (`Z_j = -c_j` nas variáveis de decisão, 0 nas demais)
e **canonicalizada**: para cada linha `i`, `Z ← Z − Z[base(i)] · linha_i`, zerando a linha Z em todas as colunas
básicas. Sem esse passo a Fase 2 parte de custos reduzidos errados, mesmo com a base viável herdada da Fase 1.

### Casos especiais

- **INVIAVEL:** *w\** > 1e-7 ao fim da Fase 1; imprime só o `STATUS` e a Fase 2 não roda.
- **ILIMITADA:** a coluna escolhida não tem nenhum `a_ip > 1e-9`; imprime só o `STATUS`. Só ocorre na Fase 2 (na
  Fase 1, *w* ≥ 0 limita o objetivo).
- **MULTIPLAS:** na tabela ótima, existe coluna **não básica** (decisão, folga ou excesso) com `|Z_j| < 1e-7`.
- **ALTERNATIVA:** o pivô extra é feito numa **cópia** da tabela ótima (a original continua intacta para imprimir
  `Z`, `X` e `DEGENERADA`), trazendo a primeira coluna de custo nulo, com a razão mínima usual. Sem linha elegível,
  imprime `ALTERNATIVA: RAIO`. Esse pivô não conta em `ITERACOES`.
- **DEGENERADA:** alguma variável básica com `|RHS| < 1e-7` na tabela ótima (linhas redundantes já removidas não
  entram na conta).

## 3. Casos de teste

- `casos/caso01.txt`…`caso11.txt` e `esperado/caso01.out`…`caso11.out`: os 11 casos da Seção 7 do enunciado.
  A saída do programa é idêntica ao gabarito do enunciado nos 11.
- Casos próprios (a explicação fica aqui porque o leitor só aceita números e palavras-chave, sem comentários):

| arquivo | modelo | o que exercita |
|---|---|---|
| `meucaso01` | MIN `2x1+3x2+x3` s.a. `x1+x2+x3=6`, `2x1+2x2+2x3=12`, `3x1+3x2+3x3=18`, `x1<=4`, `x2>=1` | Duas restrições redundantes **consecutivas e no meio** do tableau (as duas últimas igualdades são múltiplos da primeira), seguidas de uma `<=` e de uma `>=`: a transição remove as duas linhas sem desalinhar as seguintes e a Fase 1 resolve empates de coluna e de linha. Ótimo único: Z = 8, X = (0, 1, 5), `ITERACOES: 3 1`. |
| `meucaso02` | MAX `2x1+3x2+x3` s.a. `x1+x2+x3=4`, `x1+x2-x3=4`, `2x1+2x2=8` | Transição com os dois ramos juntos: `a2` fica básica em zero e é trocada por `x3` num pivô de valor **−2**, e só depois desse pivô a linha de `a3` (soma das duas primeiras) se mostra nula e é removida. Ótimo único e degenerado (`x3` básica valendo 0): Z = 12, X = (0, 4, 0), `ITERACOES: 1 1`. |

## 4. Resultado da bateria (`verificar.py`)

Resumo final do `verificar.py` sobre os 107 casos da bateria original, testado em Windows 10 com Ryzen 5 5500U
(frequência base de 2,1 GHz):

```
--------------------------------------------------------------
  grupo A: 11/11 ok
  grupo B: 7/7 ok
  grupo C: 6/6 ok
  grupo D: 7/7 ok
  grupo E: 22/22 ok
  grupo F: 41/41 ok
  grupo G: 13/13 ok
--------------------------------------------------------------
107 casos executados | 107 ok | 0 com aviso | 0 falhas | 0 pulados | 175.0s
```

**Casos que ainda falham: nenhum** (0 falhas, 0 avisos).

## 5. Por que Duas Fases e não Big-M?

O Big-M resolve tudo numa só passada, mas penaliza cada artificial com um coeficiente −M no objetivo, e M precisa
ser "grande o bastante" em relação aos dados do problema, o que não se sabe de antemão. Se M é pequeno demais,
uma artificial pode continuar positiva no resultado final de um problema viável, levando a declarar inviabilidade
ou a devolver um ponto que viola as restrições originais. Se é grande demais, a linha Z passa a misturar números
da ordem de M com números da ordem de 1 e o `double` (53 bits, cerca de 16 dígitos) perde precisão por
cancelamento: com M = 1e9, o espaçamento entre dois `double` vizinhos perto de M já é cerca de 1,2e-7, bem maior
que o `EPS = 1e-9` das comparações. Custos reduzidos que deveriam ser 0 aparecem como ±1e-7, o teste "mais
negativo" pode escolher a coluna errada e o critério de inviabilidade ("alguma artificial > 0 no final") deixa de
ser confiável. Nas Duas Fases não há constante arbitrária: a Fase 1 minimiza a soma das artificiais, com números
da própria estrutura do problema, e termina num teste limpo (*w\** ≈ 0 é viável, *w\** > 0 é inviável); a Fase 2
usa o objetivo original, sem nenhuma contaminação. O preço é tratar a transição (artificial básica em zero,
restrição redundante) e, às vezes, fazer alguns pivôs a mais, mas isso é lógica determinística, enquanto escolher
M é um palpite que depende do problema. (Dá para manter M simbólico, como um par `a·M + b`, mas isso dobra a linha
Z e complica todas as comparações.)

## 6. Degenerescência × múltiplas soluções (Seção 3.6)

O critério exigido, `MULTIPLAS: SIM` quando alguma variável não básica tem custo reduzido nulo na tabela ótima, é
**necessário** para haver mais de um ótimo (se todos os custos reduzidos das não básicas forem estritamente
positivos, o ótimo é único), mas só é **suficiente** quando não há degenerescência. Sem degenerescência, trazer a
coluna de custo nulo para a base tem razão mínima positiva: o ponto se move para outro vértice com o mesmo Z (ou
revela um raio, se nenhuma linha qualifica). Com uma variável básica valendo 0 a razão mínima pode ser 0, e o pivô
só troca a base sem mover o ponto, de modo que `ALTERNATIVA` sai igual a `X`.

O caso `e17` da bateria mostra isso: três retas passam pelo vértice ótimo (2, 2), a folga `s2` é básica valendo 0
e `s3` é não básica com custo reduzido 0. O programa imprime `MULTIPLAS: SIM` e `ALTERNATIVA: 2.000000 2.000000`,
embora o ótimo seja **único** (o `scipy` confirma): é um falso positivo do critério algébrico. Já em `caso10`,
`e18` e `f14`, também degenerados, a alternativa difere de `X` e o critério acerta.

Duas consequências práticas: (i) com `DEGENERADA: SIM`, um `MULTIPLAS: SIM` significa apenas "talvez" e só se
confirma quando `ALTERNATIVA ≠ X`; (ii) como só a primeira coluna de custo nulo é testada, o programa pode, em
princípio, devolver o mesmo ponto mesmo havendo outra coluna de custo nulo que levaria a um vértice ótimo
diferente. Decidir de forma confiável exigiria testar as demais colunas de custo nulo, ou resolver o PL com a
restrição `c·x = Z*` e minimizar/maximizar cada variável, o que está fora do escopo da tarefa.

## 7. Uso de assistentes de IA

Nesta entrega, houve uso de IA para: ajudar na criação do makefile e auxilío na identificação de problemas de implementação e, em alguns casos, ajudar em sua correção.

## 8. Material complementar

- [Simplex — Duas Fases](https://pt.scribd.com/presentation/717470414/PPT-simplex-duas-fases)
- [Simplex — Duas Fases](https://pt.scribd.com/document/718282848/DOC-simplex-duas-fases)
- [Método de Gauss](https://pt.scribd.com/document/249621942/Metodo-de-Gauss)
