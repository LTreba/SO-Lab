#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define FIBER_STACK (1024*64)

struct c {
    int saldo;
};
typedef struct c conta;

conta from, to;
int valor;
int valor1;
int total_transferencias = -1; 

sem_t semaforo;

void* transferenciaFromTo(void *arg) {
    sem_wait(&semaforo);
    total_transferencias++;
    if (from.saldo >= valor) {
        from.saldo -= valor;
        to.saldo += valor;
        printf("Transferência %d concluída from->to.\n", total_transferencias + 1);
        printf("Saldo de from: %d\n", from.saldo);
        printf("Saldo de to: %d\n", to.saldo);
    } else {
        printf("Transferência %d falhou: saldo insuficiente em 'from'.\n", total_transferencias );
    }
    
    sem_post(&semaforo);

    pthread_exit(NULL);
}

void* transferenciaToFrom(void *arg) {
    sem_wait(&semaforo);
    total_transferencias++;
    if (to.saldo >= valor1) {
        to.saldo -= valor1;
        from.saldo += valor1;
        printf("Transferência %d concluída to->from.\n", total_transferencias + 1);
        printf("Saldo de to: %d\n", to.saldo);
        printf("Saldo de from: %d\n", from.saldo);
    } else {
        printf("Transferência %d falhou: saldo insuficiente em 'to'.\n", total_transferencias);
    }

    sem_post(&semaforo);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[100];
    int i;

    sem_init(&semaforo, 0, 1);

    from.saldo = 100;
    to.saldo = 100;
    valor = 0;
    valor1 = 100;

    for (i = 0; i < 50; i++) {
        if (pthread_create(&threads[i], NULL, transferenciaFromTo, NULL)) {
            perror("pthread_create");
            exit(1);
        }
        if (pthread_create(&threads[i+50], NULL, transferenciaToFrom, NULL)) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (i = 0; i < 100; i++) {
        if (pthread_join(threads[i], NULL)) {
            perror("pthread_join");
            exit(1);
        }
    }

    sem_destroy(&semaforo);

    printf("Transferências concluídas e memória liberada.\n");
    printf("Saldo final de from: %d\n", from.saldo);
    printf("Saldo final de to: %d\n", to.saldo);

    return 0;
}

