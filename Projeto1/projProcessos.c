#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#define _GNU_SOURCE

typedef struct {
    int tempo, direcao;
}Passageiro;

void calculaTempoPassageiro(int chegada,int dir,Passageiro *passageiro,sem_t *semaforo);

int criarProcessosFilhos(FILE *arquivo,int numPassageiros,Passageiro *passageiro,sem_t *semaforo);

int main(){
    int numPassageiros;
    FILE* arquivo = fopen("./input/E_5", "r");
    if(arquivo==NULL){
        printf("Erro ao abrir arquivo!");
        exit(1);
    }
    fscanf(arquivo, "%d", &numPassageiros);
    int shm = shm_open("/shm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm, sizeof(Passageiro));
    Passageiro* passageiro = (Passageiro*)mmap(0,sizeof(Passageiro),PROT_READ|PROT_WRITE, MAP_SHARED,shm,0);
    passageiro->direcao = -1;passageiro->tempo = 0;
    close(shm);

    sem_t* semaforo = sem_open("/semaforo", O_CREAT, 0666, 1);

    criarProcessosFilhos(arquivo,numPassageiros,passageiro,semaforo);

    printf("O momento final de parada da escada rolante é %d\n",passageiro->tempo);

    fclose(arquivo);
    shm_unlink("/shm");
    munmap(passageiro, sizeof(Passageiro));
    close(shm);
    sem_close(semaforo);
    sem_unlink("/semaforo");
    return 0;
}

int criarProcessosFilhos(FILE *arquivo,int numPassageiros,Passageiro *passageiro,sem_t *semaforo){
    pid_t pid;
    pid_t* child_pids = malloc(numPassageiros*sizeof(pid_t));

    for(int i=0;i<numPassageiros;i++){
        int tempoChegada,direcao;
        fscanf(arquivo, "%d %d", &tempoChegada, &direcao);
        pid = fork();
        if(pid == 0){
            calculaTempoPassageiro(tempoChegada,direcao,passageiro,semaforo);
            exit(0);
        }else if(pid<0) {
            printf("Erro ao criar processo filho.\n");
            exit(1);
        }else{
            child_pids[i] = pid;
        }
    }

    for(int i=0;i<numPassageiros;i++){
      waitpid(child_pids[i], NULL, 0);
    }

    free(child_pids);
    return 0;
}

void calculaTempoPassageiro(int chegada,int dir,Passageiro *passageiro,sem_t *semaforo){
    sleep(chegada);

    sem_wait(semaforo);
    if(passageiro->direcao == -1||passageiro->direcao == dir){
        passageiro->direcao = dir;passageiro->tempo = chegada + 10;
    }else{
      sem_post(semaforo);
      sleep(passageiro->tempo-chegada);
      sem_wait(semaforo);
      passageiro->direcao = dir;
      passageiro->tempo = chegada + 10;
    }
    sem_post(semaforo);
}
