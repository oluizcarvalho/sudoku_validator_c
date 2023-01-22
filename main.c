#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 27
#define TAMANHO 9

int validaThreads[NUM_THREADS] = {0};

typedef struct
{
    int linha;
    int coluna;
    int (*tabuleiro)[TAMANHO];
} parametros;

void *validaColuna(void *param);
void *validaLinha(void *param);
void *valida3x3(void *param);

int main(int argc, char *argv[])
{

    pthread_t threads[NUM_THREADS];
    FILE *fp = fopen(argv[1], "r");
    int tabuleiro[TAMANHO][TAMANHO];

    if (fp == NULL)
    {
        printf("Falha ao abrir o arquivo!\n");
        exit(1);
    }
    else
    {
        for (int coluna = 0; coluna < TAMANHO; coluna++)
        {
            for (int linha = 0; linha < TAMANHO; linha++)
            {
                fscanf(fp, "%d", &tabuleiro[coluna][linha]);
            }
        }
    }

    fclose(fp);

    printf("\nTABULEIRO AVALIADO\n\n");

    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int totalThreads = 0;
    int i, j;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (i % 3 == 0 && j % 3 == 0)
            {
                parametros *data = (parametros *)malloc(sizeof(parametros));
                data->linha = i;
                data->coluna = j;
                data->tabuleiro = tabuleiro;
                pthread_create(&threads[totalThreads++], NULL, valida3x3, data);
            }
            if (i == 0)
            {
                parametros *colunaData = (parametros *)malloc(sizeof(parametros));
                colunaData->linha = i;
                colunaData->coluna = j;
                colunaData->tabuleiro = tabuleiro;
                pthread_create(&threads[totalThreads++], NULL, validaColuna, colunaData);
            }
            if (j == 0)
            {
                parametros *linhaData = (parametros *)malloc(sizeof(parametros));
                linhaData->linha = i;
                linhaData->coluna = j;
                linhaData->tabuleiro = tabuleiro;
                pthread_create(&threads[totalThreads++], NULL, validaLinha, linhaData);
            }
        }
    }

    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    for (i = 0; i < NUM_THREADS; i++)
    {
        if (validaThreads[i] == 0)
        {
            printf("Tabuleiro invalido!\n");
            return 0;
        }
    }
    printf("Tabuleiro valido!\n");
    return 0;
}

void *validaColuna(void *param)
{
    parametros *data = (parametros *)param;
    int linha = data->linha;
    int coluna = data->coluna;

    int numerosLidos[9] = {0};
    int i;
    for (i = 0; i < 9; i++)
    {
        int num = data->tabuleiro[i][coluna];
        if (num < 1 || num > 9 || numerosLidos[num - 1] == 1)
        {
            pthread_exit(NULL);
        }
        else
        {
            numerosLidos[num - 1] = 1;
        }
    }

    validaThreads[18 + coluna] = 1;
    pthread_exit(NULL);
}

void *validaLinha(void *param)
{
    parametros *data = (parametros *)param;
    int linha = data->linha;
    int coluna = data->coluna;

    int numeroLidos[9] = {0};
    int i;
    for (i = 0; i < 9; i++)
    {
        int num = data->tabuleiro[linha][i];
        if (num < 1 || num > 9 || numeroLidos[num - 1] == 1)
        {
            pthread_exit(NULL);
        }
        else
        {
            numeroLidos[num - 1] = 1;
        }
    }

    validaThreads[9 + linha] = 1;
    pthread_exit(NULL);
}

void *valida3x3(void *param)
{
    parametros *data = (parametros *)param;
    int linha = data->linha;
    int coluna = data->coluna;

    int numeroLidos[9] = {0};
    int i, j;
    for (i = linha; i < linha + 3; i++)
    {
        for (j = coluna; j < coluna + 3; j++)
        {
            int num = data->tabuleiro[i][j];
            if (num < 1 || num > 9 || numeroLidos[num - 1] == 1)
            {
                pthread_exit(NULL);
            }
            else
            {
                numeroLidos[num - 1] = 1;
            }
        }
    }

    validaThreads[linha + coluna / 3] = 1;
    pthread_exit(NULL);
}