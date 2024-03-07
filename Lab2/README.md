# Laboratório 02 - Sistemas Operacionais

**Neste laboratório, estudamos e analisamos codigos propostos e desenvolvemos um programa escrito na linguagem C baseado no conceito de processos do Sistema Operacional, 
focando principalmente nos comandos: fork(), que cria um novo processo que tem como pai o processo que o chamou;
wait(), que coloca o processo que o chamou em estado de espera até que o processo filho seja executado; e
exit(), que finaliza o processo que o chamou, retornando valor de saída exit. Esse processo auxiliou no entendimento de como o sistema operacional é requisitado 
e executa as tarefas informadas pelos usuários.**

## Questão A

A partir do momento que a instrução fork() é chamada ela cria o processo filho mas segue executando o processo  pai, que por apresentar um pid difente de 0 cai na
condição do else, executando as instruções "printf("I am the parent %d\n",pid);" e "wait(NULL);" que então o colocam em estado de espera e chamam o processo filho, que por ter pid igual a 0 cai na condição do else if e executa as instruções "printf("I am the child %d\n",pid);" "execlp("/bin/ls","ls",NULL);"(que chama a função ls do terminal para listar os arquivos do diretório) e quando então finalizado, retornamos ao processo pai, que então imprime por fim a instrução "printf("Child Complete\n");" retornado e finalizando main

## Questão B

No exemplo citado, são criados 8 processos no total, descobrimos isso pois o número total de processos criados é igual a 2^n sendo n o número de instruções fork, (cada chamada dessa instrução duplica o número atual de processos) que nesse caso é igual a 3.

## Exercício

Nosso programa é uma simples troca de mensagens que usa a criação de dois processos, um pai e um filho através da função fork() da lib sys.types. A execução do programa segue a seguinte ordem: depois de criado em fork(), o processo pai é executado na verificação if(pid>0) até o final. A  execução do programa é retomada após o fork(), porém agora será executada a sessão em que o pid é igual 0 até o final do programa. 
Para comunicação entre os dois processos foi necessários o uso de pipe, que consiste na criação de um espaço de memória compartilhado, onde apenas um processo escreve na memória e outro só pode ler. Definimos com a função write() que iriamos escrever na memória uma string no processo pai e fechamos a leitura para esse com close(), já no processo filho, a escrita ficará bloqueada e leitura liberada. Desse modo foi possível estabelecer comunicação entre esses dois espaços de memória. 
 
## Console da AWS rodando o programa:
<img src="https://i.imgur.com/9dKYAtG.png" alt="Print AWS">
