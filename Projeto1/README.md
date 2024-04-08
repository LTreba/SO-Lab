# Projeto 1 - Sistemas Operacionais
## Escada Rolante

### 1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?
R:
- Na abordagem de threads, nós utilizamos um mutex da biblioteca phthreads para evitar que duas pessoas acessem a escada rolante ao mesmo tempo, fazemos isso bloqueando o mutex antes de acessar as váriaveis compartilhadas de tempo e direção, permitindo apenas que a thread atual as altere.

- Enquanto na abordagem de processos, utilizamos um semáforo, que também permite que apenas um processo modifique o atributo da struct na memoria compartilhada, ao ser bloquea-lo antes de acessar a região crítica e desbloqueá-lo após as alterações.

### 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?
R: Podemos garantir isso:
- Com threads, por meio do bloqueio do mutex, verificamos qual a direção atual indicada pela variável global compartilhada entre as threads, caso seja igual a -1 ou a pessoa que está na escada, soma 10 segundos ao momento em que a pessoa atual tenha chegado, caso contrário espera a pessoa que ocupa a escada terminar sua travessia, e então troca o sinal (direção) da escada e soma 10 ao tempo resultante da travessia ate o momento.
- Com processos, realizamos as mesmas ações, mas dessa vez utilizamos o bloqueio do semáforo para em cada processo verificar a direção atual no struct na região compartilhada de memória para fazer o cálculo.

### 3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.
R: Na implementação utilizando processos, por conta do espaço de endereçamento exclusivo, temos de criar uma região de memória compartilhada (shm) para realizar a comunicação entre os processos, o que é custoso quando consideramos múltiplas trocas de informação durante a execução do programa. Por outro lado, quando implementamos por meio de threads, o compartilhamento de memoria já é nativa entre as threads, o que exige menos da máquina, além disso, a criação de cada thread é mais leve que a criação dos processos filhos, o que nos leva a concluir que para esse caso, em que a comunicação deve ser alta e a necessidade de paralelização baixa, a implementação com threads se mostra mais eficiente que a de processos.

## Execução com thread (E_1)

3
5 0
8 0
13 0

<img src="https://i.imgur.com/jcAMdMj.png" alt="execucaoThread">

## Execução com processo (E_1)
3
5 0
8 0
13 0
<img src="https://i.imgur.com/N3FgKEn.png" alt="execucaoProcesso">

## Execução com thread (E_4)
5
2 0
8 1
16 0
17 1
32 0
<img src="https://i.imgur.com/1agLIsj.png" alt="execucaoThread">


## Execução com processo (E_4)
5
2 0
8 1
16 0
17 1
32 0

## Execução com thread (E_5)
5
5 0
7 1
10 0
13 1
25 1
<img src="https://i.imgur.com/REkxMyx.png" alt="execucaoThread">

## Execução com processo (E_5)
5
5 0
7 1
10 0
13 1
25 1
