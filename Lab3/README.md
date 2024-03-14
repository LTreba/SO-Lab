# Laboratório 3 - Sistemas Operacionais

## Exercício

Neste laboratório, é alocada memória dinamicamente com a função malloc, criamos uma variável value na main antes de chamada na função clone() que cria uma thread, e nela passamos como parâmetro o ponteiro da função criada para mudar o valor, a memória alocada e o endereço da variavel, executando assim a Thread. Durante a execução da função alteramos o resultado de value e verificamos quando voltamos ao processo pai se o valor se refletiu na main com uma impressão, provando que o processo pai e a thread compartilhando o espaço de endereçamento de memória.
<img src="https://i.imgur.com/eZfVlzX.jpeg" alt="Console AWS">
