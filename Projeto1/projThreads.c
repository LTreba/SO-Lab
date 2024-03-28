#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <semaphore.h>
#include <pthread.h>
#define _GNU_SOURCE

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//sem_t semaforo;
int direcao = -1;
int tempoFinal = 0;

typedef struct {
    int tempo, direcao;
} Passageiro;

void *calculaTempoPassageiro(void *passageiro){
  Passageiro *passageiroAtual = (Passageiro *)passageiro;
  sleep(passageiroAtual->tempo);
  pthread_mutex_lock(&mutex);
  if(direcao==-1 || passageiroAtual->direcao==direcao){
    direcao = passageiroAtual->direcao;
    tempoFinal = passageiroAtual->tempo+10;
  }
  pthread_mutex_unlock(&mutex);
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
  pthread_t threads[10000];
  int numPassageiros;

  lerPassageiros("./input/E_1", passageiros, &numPassageiros);

  //sem_init(&semaforo, 0, 1);

  for(int i = 0; i < numPassageiros; i++){
    pthread_create(&threads[i], NULL, calculaTempoPassageiro, (void *)&passageiros[i]);
  }

  // Esperando as threads terminarem
  for(int i = 0; i < numPassageiros; i++){
    pthread_join(threads[i], NULL);
  }

  printf("O momento final de parada da escada rolante é %d\n", tempoFinal);

  return 0;
}
