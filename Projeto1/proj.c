#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#define _GNU_SOURCE

typedef struct {
    int tempo, direcao;
} Passageiro;

int ultimoMomentoEscada(Passageiro* passageiros, int numPassageiros) {
    int momento = 0;
    int indicePassageiro = 0;
    int previsao = 0;
    int direcao = -1;

    while (indicePassageiro < numPassageiros) {
        Passageiro passageiroAtual = passageiros[indicePassageiro];

        if (direcao == -1) {
            momento = passageiroAtual.tempo < momento ? momento : passageiroAtual.tempo;
            direcao = passageiroAtual.direcao;
        }
        previsao = momento + 10;
        if (passageiroAtual.direcao == direcao) {
            momento = passageiroAtual.tempo;
            previsao = momento + 10;
            indicePassageiro++;
        } else {
            if (passageiros[indicePassageiro + 1].tempo <= previsao) {
                momento = previsao;
            } else {
                direcao = -1;
                indicePassageiro++;
            }
        }
    }

    momento += 10;
    return momento;
}

void lerPassageiros(char* caminhoArquivo, Passageiro* passageiros, int* numPassageiros) {
    FILE* arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    fscanf(arquivo, "%d", numPassageiros);
    for (int i = 0; i < *numPassageiros; i++) {
        fscanf(arquivo, "%d %d", &passageiros[i].tempo, &passageiros[i].direcao);
    }
    fclose(arquivo);
}

int main() {
    Passageiro passageiros[10000];
    int numPassageiros;

    lerPassageiros("./entrada.txt", passageiros, &numPassageiros);
    int tempoFinal = ultimoMomentoEscada(passageiros, numPassageiros);

    printf("O momento final de parada da escala rolante é %d\n", tempoFinal);
    return 0;
}
