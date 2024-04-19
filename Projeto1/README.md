# Projeto 1 - Sistemas Operacionais
## Escada Rolante

Nesse projeto, implementamos um esquema de escada rolante dupla que funciona da seguinte maneira: quando a escada está parada e alguém entra por uma das extremidades, ela automaticamente se liga e começa a se mover na direção desejada pela pessoa. Se alguém chegar à escada rolante dupla e ela já estiver se movendo na direção desejada pela pessoa, essa pessoa pode entrar imediatamente. No entanto, se a escada rolante estiver se movendo na direção oposta, a pessoa terá que esperar até que a escada pare antes de poder entrar. A escada rolante dupla é tão larga que pode acomodar várias pessoas entrando ao mesmo tempo, e incrivelmente nenhuma pessoa vai chega na escada rolante no momento exato em que ela vai prestes a parar.
Nossa implementação se dividiu em duas frentes, resolvemos o problema usando Threads (projThreads.c), em que cada thread da biblioteca Phtread, representa uma pessoa e a partir da memória compartilhada entre todas elas, controla a direção da escada e calcula o tempo final de parada; e também utilizamos Processos (projProcessos.c), em que usamos a função  fork para criar um processo filho que implemente a lógica da escada em loop e através de um pipe manda o ultimo momento de uso da escada.

### Para compilar o programa: 
Abrimos e editamos os programas com o vim:
```bash
vim projThreads.c
vim projProcessos.c
```
Instalamos o compilador gcc:
```bash
sudo dnf install gcc
```
E então compilamos ambos os arquivos .c
```bash
gcc projThreads.c -o threads
gcc projProcessos.c -o processos
```

### Para executar o programa:
```bash
./threads
./processos
```
### Comprovar que os resultados propostos foram alcançados:

Basta e executar o programa e comparar com o resultado do input correspondente na pasta Output presente no diretório.

## Perguntas

### 1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?
R:
- Na abordagem de threads, nós fazemos a criação da thread que representa cada pessoa seguida da função join da biblioteca phthreads, que obriga que a thread do passageiro atual seja encerrada antes da criação do próximo, assim controlamos pela variaveis globais de tempoFinal e direção o andamento da escada, caso a escada esteja parada ou o passageiro atual siga na mesma direção aumentamos o tempo em 10 e seguimos, agora caso siga numa direção contrária, criamos uma váriavel para representar uma fila de espera, que então espera chegar ao tempo final para mudar a direção e aumentar em 10 o tempo.

- Enquanto na abordagem de processos, o loop for implementado dentro do processo filho responsavel por fazer a conta do tempo da escada, faz a analise dos dados de cada pessoa por vez, e então permite apenas que ela use a escada no instante de chegada quando esta esta parada ou seguindo na mesma direção prévia, caso contrário permite o uso apenas quando todas as pessoas que iam naquela direção tenham saído da escada

### 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?
R: Podemos garantir isso:
- Com threads, usamos a função join que espera a execução de uma thread para iniciar a proxima, mantendo a sequência, então verificamos qual a direção atual indicada pela variável global compartilhada entre as threads, caso seja igual a -1 ou a pessoa que está na escada, segue normalmente e apenas aumenta o tempo final, caso a direção seja diferente criamos uma váriavel para representar uma fila de espera, que então espera que todas as outras pessoas saiam da escada(ate o tempo final) para então mudar a direção da escada.
- Com processos, o loop for do processo executada uma pessoa de cada vez e a análise da direção da pessoa anterior, presente na memória do processo filho, que recebe o ponteiro dos vetores de struct que representam as pessoas, troca a direção apenas após todas as pessoas tenham concluido sua trajetória.

### 3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.
R: Na implementação utilizando processos, por conta do espaço de endereçamento exclusivo, temos de utilizar mensagens para realizar a comunicação entre os processos pai e filho, além de enviar o ponteiro do vetor de passageiros, o que é custoso quando consideramos grandes trocas de informação durante a execução do programa. Por outro lado, quando implementamos por meio de threads, utilizamos o compartilhamento de memória, assim acessando o mesmo espaço de endereçamento varias vezes, o que facilita a comunição entre as threads e facilitando o controle da escada, além disso, a criação de cada thread é mais leve que a criação dos processos filhos, o que nos leva a concluir que para esse caso, em que a comunicação deve ser alta e a necessidade de paralelização baixa, a implementação com threads se mostra mais eficiente que a de processos.

## Execução com thread (E_1)

<img src="https://i.imgur.com/jcAMdMj.png" alt="execucaoThread">

## Execução com processo (E_1)

<img src="https://i.imgur.com/N3FgKEn.png" alt="execucaoProcesso">

## Execução com thread (E_4)

<img src="https://i.imgur.com/1agLIsj.png" alt="execucaoThread">

## Execução com processo (E_4)
<img src="https://i.imgur.com/lgNLYaL.png" alt="execucaoProcesso">

## Execução com thread (E_5)

<img src="https://i.imgur.com/REkxMyx.png" alt="execucaoThread">

## Execução com processo (E_5)

<img src="https://i.imgur.com/iPJUDlv.png" alt="execucaoProcesso">
