#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int matriz[3][3] = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
int vetor[3] = {1, 2, 3};
int resultado[3];

int linhas[3];

void *threadLinha(void *arg){
    int *nLinhas = (int *)arg;
    int linha = *nLinhas;
    resultado[linha] =0;
    for(int j=0;j<3;j++) {
        resultado[linha]+=matriz[linha][j]*vetor[j];
    }
  return NULL;
}

int main(){
    pthread_t threads[3];
    for(int i=0; i<3;i++){
        linhas[i]=i;
        pthread_create(&threads[i], NULL, threadLinha, (void *)&linhas[i]);
    }
    for(int i=0;i<3;i++){
        pthread_join(threads[i], NULL);
    }
    printf("Resultado: \n");
    for(int i=0; i<3;i++){
        printf("%d ", resultado[i]);
    }
    printf("\n");
    return 0;
}
