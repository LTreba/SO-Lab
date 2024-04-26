# Laboratório 4 - Sistemas Operacionais

## Multiplicação matriz-vetor

<img src="https://i.imgur.com/oOiz1Ji.png" alt="matriz-vetor">

Nesse laboratório desenvolvemos um programa que realizada a multiplicação matriz-vetor utilizando a biblioteca pthreads da linguagem C em sistema operacional Unix. Em nossa resolução, declaramos uma matriz e um vetor globais, para que todas as threads envolvidas tenham acesso pela memória compartilhada, então criamos uma thread para cada linha do vetor resultante da multiplicação, passando como parâmetro o numero da respectiva linha e a função threadLinha, que faz a soma dos produtos entre as respectivas posições de Matriz e Vetor, armazenando na posição correspondente do vetor resultado, que depois é impresso na main.
No geral o programa é simples e intuitivo, sendo a maior dificuldade gerir as posições de Vetor e Matriz em cada thread para realizar o cálculo

<img src="https://i.imgur.com/7PtFKXb.png" alt="resultado">
