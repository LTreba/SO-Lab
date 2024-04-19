#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>
#define _GNU_SOURCE

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int direcao = -1;
int tempoFinal = 0;
int filaEsperando = 0;

typedef struct {
  int tempo, direcao;
} Passageiro;

void *calculaTempoPassageiro(void *passageiro) {
  Passageiro *passageiroAtual = (Passageiro *)passageiro;
  if (direcao == -1){
    direcao = passageiroAtual->direcao;
    tempoFinal = passageiroAtual->tempo + 10;
  }
  else if (passageiroAtual->direcao == direcao) {
    if (filaEsperando > 0 && passageiroAtual->tempo > tempoFinal) {
      filaEsperando = 1;
      tempoFinal += 10;
      direcao = passageiroAtual->direcao * (-1);
    } else {
      direcao = passageiroAtual->direcao;
      tempoFinal = passageiroAtual->tempo + 10;
    }
  } else {
    if (passageiroAtual->tempo > tempoFinal) {
      if (filaEsperando > 0) {
        tempoFinal += 10;
        filaEsperando = 1;
      } else {
        tempoFinal = passageiroAtual->tempo + 10;
      }
    } else {
      filaEsperando++;
    }
  }
}

void lerPassageiros(char *caminhoArquivo, Passageiro *passageiros,
                    int *numPassageiros) {
  FILE *arquivo = fopen(caminhoArquivo, "r");
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
  pthread_t threads[10000];
  int numPassageiros;

  lerPassageiros("./input/E_5", passageiros, &numPassageiros);

  for (int i = 0; i < numPassageiros; i++) {
    pthread_create(&threads[i], NULL, calculaTempoPassageiro,
                   (void *)&passageiros[i]);
    pthread_join(threads[i], NULL);
  }

  while (filaEsperando > 0) {
    tempoFinal += 10;
    filaEsperando--;
  }

  printf("O momento final de parada da escada rolante é %d\n", tempoFinal);
  return 0;
}
