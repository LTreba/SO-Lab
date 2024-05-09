#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <semaphore.h>

#define FIBER_STACK 1024*64

struct c {
    int saldo;
};
typedef struct c conta;

conta from, to;
int valor;
int total_transferencias = 0; 

sem_t semaforo_from;
sem_t semaforo_to;

void* transferenciaFromTo(void *arg) {

  sem_wait(&semaforo_from);
  sem_wait(&semaforo_to);

  if (from.saldo >= valor) {
      from.saldo -= valor;
      to.saldo += valor;
      printf("Transferência %d concluída.\n", total_transferencias + 1);
      printf("Saldo de from: %d\n", from.saldo);
      printf("Saldo de to: %d\n", to.saldo);
      total_transferencias++;
  }

  sem_post(&semaforo_to);
  sem_post(&semaforo_from);

  return NULL;
}

void* transferenciaToFrom(void *arg) {

  sem_wait(&semaforo_to);
  sem_wait(&semaforo_from);

  if (to.saldo >= valor) {
      to.saldo -= valor;
      from.saldo += valor;
      printf("Transferência %d concluída.\n", total_transferencias + 1);
      printf("Saldo de to: %d\n", to.saldo);
      printf("Saldo de from: %d\n", from.saldo);
      total_transferencias++;
  }

  sem_post(&semaforo_from);
  sem_post(&semaforo_to);

  return NULL;
}

int main() {
  void *stack;
  pid_t pid;
  int i;
  int option;

  sem_init(&semaforo_from, 0, 1);
  sem_init(&semaforo_to, 0, 1);

  from.saldo = 100;
  to.saldo = 100;

  printf("Escolha uma opção(0= From -> To, 1= To -> From):\n");
  scanf("%d",&option);

  printf("Transferindo 10 entre as contas from e to\n");
  valor = 10;

  if(option == 0){

    for (i = 0; i < 100; i++) {
        stack = malloc(FIBER_STACK);
        if (stack == 0) {
            perror("malloc: could not allocate stack");
            exit(1);
        }

        pid = clone((void*) &transferenciaFromTo, (char *)stack + FIBER_STACK, SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, NULL);
        if (pid == -1) {
            perror("clone");
            exit(2);
        }
    }
  }else{
    for (i = 0; i < 100; i++) {
        stack = malloc(FIBER_STACK);
        if (stack == 0) {
            perror("malloc: could not allocate stack");
            exit(1);
        }

        pid = clone((void*) &transferenciaToFrom, (char *)stack + FIBER_STACK, SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, NULL);
        if (pid == -1) {
            perror("clone");
            exit(2);
        }
    }
  }

  for (i = 0; i < 10; i++) {
        wait(NULL);
  }

  free(stack);

  sem_destroy(&semaforo_from);
  sem_destroy(&semaforo_to);

  printf("Transferências concluídas e memória liberada.\n");
  printf("Saldo final de from: %d\n", from.saldo);
  printf("Saldo final de to: %d\n", to.saldo);

  return 0;
}
