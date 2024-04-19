#include <fcntl.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>
#define _GNU_SOURCE

typedef struct {
  int tempo, direcao;
} Passageiro;

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

int ultimoMomentoEscada(Passageiro *passageiros, int numPassageiros) {
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

int main() {
  Passageiro passageiros[10000];
  int numPassageiros;

  lerPassageiros("./input/E_5", passageiros, &numPassageiros);

  int fd[2];

  if (pipe(fd) == -1) {
    perror("Erro ao criar pipe");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();

  if (pid == -1) {
    perror("Erro ao criar processo filho");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    close(fd[0]);
    int tempoFinal = ultimoMomentoEscada(passageiros, numPassageiros);
    write(fd[1], &tempoFinal, sizeof(int));
    close(fd[1]);
    exit(EXIT_SUCCESS);
  } else {
    close(fd[1]);
    int resultado;
    wait(NULL);
    read(fd[0], &resultado, sizeof(int));
    close(fd[0]);

  printf("O momento final da escada rolante eh %d ", resultado);

  return 0;
}
}
