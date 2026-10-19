import os
import re
import subprocess
import sys

import verificar

LIMITE_COM_T = 100


def main():
    if len(sys.argv) < 2:
        print("uso: python rodar_testes.py <executavel> [-t] [--saida] [opcoes do verificar.py]")
        sys.exit(2)

    if os.name == "nt":
        os.system("")

    programa = os.path.abspath(sys.argv[1])
    argumentos = sys.argv[2:]
    modo_impressao = "-t" in argumentos
    mostrar_saida = "--saida" in argumentos
    repassar = [a for a in argumentos if a not in ("-t", "--saida")]

    if modo_impressao and "--caso" not in repassar and "--ate" not in repassar:
        repassar += ["--ate", str(LIMITE_COM_T)]
        print("Modo -t: casos com n+m > %d foram pulados, pois o passo a passo deles tem "
              "de dezenas de MB a GB." % LIMITE_COM_T)
        print("Use --caso para escolher casos ou --ate N para mudar o limite.\n")

    executar_original = subprocess.run

    def executar(comando, *args, **kwargs):
        if modo_impressao:
            comando = list(comando) + ["-t"]
        resultado = executar_original(comando, *args, **kwargs)
        if modo_impressao or mostrar_saida:
            saida = resultado.stdout
            print(saida, end="" if (not saida or saida.endswith("\n")) else "\n")
            if resultado.stderr:
                print(resultado.stderr, end="", file=sys.stderr)
            sys.stdout.flush()
        if modo_impressao:
            achado = re.search(r"^STATUS:", resultado.stdout, re.MULTILINE)
            if achado:
                resultado.stdout = resultado.stdout[achado.start():]
        return resultado

    subprocess.run = executar
    sys.argv = [sys.argv[0], programa] + repassar
    verificar.main()


if __name__ == "__main__":
    main()
