#include <fcntl.h>
#include <malloc.h>
#include <sched.h>
#include <semaphore.h>
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
  int filaEsperando = 0;
  int tempoFinal = 0;
  int direcao = -1;
  int i;

  for (i = 0; i < numPassageiros; i++) {
    if (direcao == -1) {
      direcao = passageiros[i].direcao;
      tempoFinal = passageiros[i].tempo + 10;

    } else if (passageiros[i].direcao == direcao) {
      if (filaEsperando > 0 && passageiros[i].tempo > tempoFinal) {
        filaEsperando = 1;
        tempoFinal += 10;
        direcao = passageiros[i].direcao * (-1);
      } else {
        direcao = passageiros[i].direcao;
        tempoFinal = passageiros[i].tempo + 10;
      }
    } else {
      if (passageiros[i].tempo > tempoFinal) {
        if (filaEsperando > 0) {
          tempoFinal += 10;
          filaEsperando = 1;
        } else {
          tempoFinal = passageiros[i].tempo + 10;
        }
      } else {
        filaEsperando++;
      }
    }
  }
  while (filaEsperando > 0) {
    tempoFinal += 10;
    filaEsperando--;
  }

  return tempoFinal;
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
