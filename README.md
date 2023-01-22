# sudoku_validator_c

## Sobre
Este é um código em C que resolve um sudoku. Ele usa threads para verificar se as linhas, 
colunas e regiões 3x3 do tabuleiro contêm os números de 1 a 9, sem repetições. O programa 
lê os valores do tabuleiro de um arquivo. Em seguida, o programa cria 27 threads (uma para cada linha, 
coluna e região 3x3) e as inicia. Depois que todas as threads terminarem, o programa verifica os resultados
e imprime "Tabuleiro válido!" se todas as threads retornarem com sucesso, ou "Tabuleiro inválido!" caso contrário. 

## Pré-requisitos
- Compilador ([gcc](https://gcc.gnu.org/), **[MinGW](https://pt.wikipedia.org/wiki/MinGW "w:MinGW")**, outros);

## Para compilar o programa: 
- Abrir o terminal do Windows ou Linux
```sh
gcc -o main main.c -lpthread 
```

## Para rodar os casos de teste
```bash
./main puzzle.txt 
```
