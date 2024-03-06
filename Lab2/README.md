#Laboratório 02 - Sistemas Operacionais

Neste laboratório, estudamos e analisamos codigos propostos e desenvolvemos um programa escrito na linguagem C baseado no conceito de processos do Sistema Operacional, 
focando principalmente nos comandos: fork(), que cria um novo processo que tem como pai o processo que o chamou;
wait(), que coloca o processo que o chamou em estado de espera até que o processo filho seja executado; e
exit(), que finaliza o processo que o chamou, retornando valor de saída exit. Esse processo auxiliou no entendimento de como o sistema operacional é requisitado 
e executa as tarefas informadas pelos usuários.

##Questão A

A partir do momento que a instrução fork() é chamada ela cria o processo filho mas segue executando o processo  pai, que por apresentar um pid difente de 0 cai na
condição do else, executando as instruções "printf("I am the parent %d\n",pid);" e "wait(NULL);" que então o colocam em estado de espera e chamam o processo filho, que por ter pid igual a 0 cai na condição do else if e executa as instruções "printf("I am the child %d\n",pid);" "execlp("/bin/ls","ls",NULL);"(que chama a função ls do terminal para listar os arquivos do diretório) e quando então finalizado, retornamos ao processo pai, que então imprime por fim a instrução "printf("Child Complete\n");" retornado e finalizando main

##Questão B

No exemplo citado, são criados 8 processos no total, descobrimos isso pois o número total de processos criados é igual a 2^n sendo n o número de instruções fork, (cada chamada dessa instrução duplica o número atual de processos) que nesse caso é igual a 3.

##Exercício

