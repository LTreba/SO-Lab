# Projeto 2 - Sistemas Operacionais
## Tranferência de fundos entre duas contas

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
- A conta to pode receber mais de uma transferência simultânea
  
- A conta from pode enviar mais de uma transferência simultânea;
  
- A conta from não pode enviar dinheiro se não tiver mais saldo;
  
- A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode
receber e a conta que recebia pode enviar;

- Poderão ser realizadas até 100 transações simultâneas de transferência

## Execução do programa
### Caso 1: Duas contas transferindo o mesmo valor entre si
<img src="https://i.imgur.com/wlGxEHT.png" alt="execucaocaso1FromToAWS">
### Caso 2: Conta To enviando todo o dinheiro para From
<img src="https://i.imgur.com/7OI4xQP.png" alt="execucaoToFromAWS">
**resultado depende do valor que é transferido de to para from e de from para to**
