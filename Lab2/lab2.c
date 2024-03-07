#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

/*Programa feito para o Laboratório 2 de Sistemas Operacionais
em os processos pai e filho trocam algum tipo de mensagem.*/

int main() {
  pid_t pid;

  printf("Seu Adenor chega do trabalho e encontra seu filho João na sala:\n");
  printf("\n");

  pid = fork(); // cria um processo filho

  if (pid < 0) { // caso de erro na função fork
    fprintf(stderr, "ERRO! O fork falhou... \n");
    return 1;

  } else if (pid > 0) { // processo pai
    printf("Filho, aqui é o processo pai. Antes de mais nada...\n");
    printf("Você fez a sua tarefa de casa?\n");
    wait(NULL);

    printf("\n");
    printf("Que bom filho, o meu no caso é %d\n", pid);
    printf("Estou orgulhoso de você! Vamos jantar. \n");

  } else { // processo filho
    printf("\n");
    printf("Pai, aqui é o processo filho. \n");
    printf("Fiz minha tarefa e descobri que meu PID é %d\n", pid);
    printf("E isso ocorre por conta da função fork! \n");
  }
  return 0;
}
