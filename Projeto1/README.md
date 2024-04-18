# Projeto 1 - Sistemas Operacionais
## Escada Rolante

### 1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?
R:
- Na abordagem de threads, nós fazemos a criação da thread que representa cada pessoa seguida da função join da biblioteca phthreads, que obriga que a thread do passageiro atual seja encerrada antes da criação do próximo, assim controlamos pela variaveis globais de tempoFinal e direção o andamento da escada, caso a escada esteja parada ou o passageiro atual siga na mesma direção aumentamos otempo em 10 e seguimos, agora caso siga numa direção contrária, criamos uma váriavel para representar uma fila de espera, que então espera chegar ao tempo final para mudar a direção e aumentar em 10 o tempo.

- Enquanto na abordagem de processos, utilizamos um semáforo, que também permite que apenas um processo modifique o atributo da struct na memoria compartilhada, ao ser bloquea-lo antes de acessar a região crítica e desbloqueá-lo após as alterações.

### 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?
R: Podemos garantir isso:
- Com threads, usamos a função join que espera a execução de uma thread para iniciar a proxima, mantendo a sequência, então verificamos qual a direção atual indicada pela variável global compartilhada entre as threads, caso seja igual a -1 ou a pessoa que está na escada, segue normalmente e apenas aumenta o tempo final, caso a direção seja diferente espera que todas as outras pessoas saiam da escada(ate o tempo final) para então mudar a direção da escada.
- Com processos, realizamos as mesmas ações, mas dessa vez utilizamos o bloqueio do semáforo para em cada processo verificar a direção atual no struct na região compartilhada de memória para fazer o cálculo.

### 3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.
R: Na implementação utilizando processos, por conta do espaço de endereçamento exclusivo, temos de utilizar mensagens para realizar a comunicação entre os processos, o que é custoso quando consideramos múltiplas trocas de informação durante a execução do programa. Por outro lado, quando implementamos por meio de threads, utilizamos o compartilhamento de memória, assim acessando o mesmo espaço de endereçamento varias vezes, o que facilita a comunição entre as threads e facilitando o controle da escada, além disso, a criação de cada thread é mais leve que a criação dos processos filhos, o que nos leva a concluir que para esse caso, em que a comunicação deve ser alta e a necessidade de paralelização baixa, a implementação com threads se mostra mais eficiente que a de processos.

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
