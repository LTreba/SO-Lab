# Projeto 2 - Sistemas Operacionais
## Tranferência de fundos entre duas contas

Neste projeto, desenvolvemos um programa que realiza a transferência de fundos entre duas contas: To (destino) e From (origem). Essa tarefa é implementada declarando as duas contas globalmente e utilizando threads da biblioteca Pthreads do Linux. Cada thread tem acesso às contas através da memória compartilhada e representa uma transferência realizada entre elas. As transferências são feitas de forma concorrente apenas quando há saldo suficiente na conta de envio, permitindo que ocorram mais de uma transferência ao mesmo tempo. Para solucionar a condição de corrida gerada pela solução concorrente, utilizamos um mutex também da biblioteca Pthreads, que impede que mais de uma thread tenha acesso à região crítica de memória (o valor presente na conta de envio), além de não ultrapassar o número máximo de 100 transferências totais. Nosso programa ainda permite que o dinheiro seja enviado da conta To durante a execução, obedecendo às regras impostas anteriormente.

Para realizar os testes, usamos duas abordagens, a primeira ambas as direções de transferência enviam o mesmo valor(100), e na segunda valores diferentes(100 e 0).

### Para compilar o programa: 
Abrimos e editamos os programas com o vim:
```bash
vim proj2.c
```
Instalamos o compilador gcc:
```bash
sudo dnf install gcc
```
E então compilamos ambos os arquivos .c
```bash
gcc proj2.c -o projeto2
```

### Para executar o programa:
```bash
./projeto2
```
### Comprovar que os resultados propostos foram alcançados:

- A conta to pode receber mais de uma transferência simultânea;
- A conta from pode enviar mais de uma transferência simultânea;

<img src="https://i.imgur.com/3RZm2oE.png" alt="Prova1">
<img src="https://i.imgur.com/Si5SOh7.png" alt="Prova1">
As transferências simultâneas entre as duas contas são possíveis pois criamos todos as 100 threads(50 from->to e 50 to->from) de uma vez, e só então chamamos a função join que aguarda a execução de todas, ou seja ao implementarmos a solução concorrente, permitimos envio e recebimento de diversas tranferências ao mesmo tempo.
  
- A conta from não pode enviar dinheiro se não tiver mais saldo;
<img src="https://i.imgur.com/YZUKvWC.png" alt="Prova2">
<img src=" https://i.imgur.com/AW8Yxnf.png" alt="Prova2">
Nosso programa impede isso ao verificar o valor de tranferência da conta que envia com um if, e so permitir a transferência caso tenha saldo maior igual ao valor passado.
  
- A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode
receber e a conta que recebia pode enviar;
<img src="https://i.imgur.com/3RZm2oE.png" alt="Prova3">
<img src="https://i.imgur.com/Si5SOh7.png" alt="Prova3">
Declaramos as threads de ambas as direções juntas, o que faz com que a ordem possa ser trocada durante a execução.

- Poderão ser realizadas até 100 transações simultâneas de transferência
<img src="https://i.imgur.com/16JuIwX.png" alt="prova4">
<img src="https://i.imgur.com/wlGxEHT.png" alt="prova4">
Criamos todos no maximo 100 threads(50 from->to e 50 to->from), o que limita a 100 tranferências totais

## Execução do programa
### Caso 1: Duas contas transferindo o mesmo valor entre si
<img src="https://i.imgur.com/wlGxEHT.png" alt="execucaocaso1FromToAWS">

### Caso 2: Conta To enviando todo o dinheiro para From
<img src="https://i.imgur.com/7OI4xQP.png" alt="execucaoToFromAWS">

*resultado depende do valor que é transferido de to para from e de from para to*
