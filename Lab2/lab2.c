#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define BUFFER 256

int main() {
  int fd[2];
  pid_t pid;

  // Criar o pipe
  if (pipe(fd) == -1) {
    perror("Erro ao criar o pipe");
    exit(EXIT_FAILURE);
  }

  pid = fork(); // cria um processo filho

  if (pid < 0) { // caso de erro na função fork
    fprintf(stderr, "ERRO! O fork falhou... \n");
    return 1;

  } else if (pid > 0) { // processo pai
    close(fd[0]); // Fechar a extremidade de leitura do pipe no processo pai

    char str[BUFFER] = "Ola, filho! Esta é uma mensagem de seu pai enviada pelo pipe!\n";
    
    printf("Mensagem enviada para filho com sucesso!\n");
    
    write(fd[1], str, sizeof(str)); // Escrever no pipe

    close(fd[1]); // Fechar a extremidade de escrita do pipe no processo pai
    wait(NULL);   // Aguardar o término do processo filho
    
  } else {// processo filho
    char str_received[BUFFER];

    close(fd[1]); // Fechar a extremidade de escrita do pipe no processo filho

    read(fd[0], str_received, sizeof(str_received)); // Ler do pipe

    printf("Pai, recebi a mensagem: \n%s\n", str_received);
    printf("De filho, finalizando...\n");
    
    close(fd[0]); // Fechar a extremidade de leitura do pipe no processo filho
    exit(0);
  }
  return 0;
}
