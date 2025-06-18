#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int *criarMassaDados(int tamanho);
void mergeSort(int *massaDados, int l, int r);
void printArray(int *massaDados, int tamanho);
void gerarArquivoOutput(double cpuTimeUsedMassa1000, double cpuTimeUsedMassa100000, double cpuTimeUsedMassa500000);


int main()
{
    clock_t startTime, endTime;
    double cpuTimeUsedMassa1000, cpuTimeUsedMassa100000, cpuTimeUsedMassa500000;

    int *massa1000 = criarMassaDados(1000);
    
    startTime = clock();
    mergeSort(massa1000, 0, 1000 - 1);
    endTime = clock();
    cpuTimeUsedMassa1000 = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    // printArray(massa1000, 1000);

    int *massa100000 = criarMassaDados(100000);

    startTime = clock();
    mergeSort(massa100000, 0, 100000 - 1);
    endTime = clock();
    cpuTimeUsedMassa100000 = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    // printArray(massa100000, 100000);

    int *massa500000 = criarMassaDados(500000);

    startTime = clock();
    mergeSort(massa500000, 0, 500000 - 1);
    endTime = clock();
    cpuTimeUsedMassa500000 = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    // printArray(massa500000, 500000);

    gerarArquivoOutput(cpuTimeUsedMassa1000, cpuTimeUsedMassa100000, cpuTimeUsedMassa500000);

    free(massa1000);
    free(massa100000);
    free(massa500000);

    // printf("Tempo gasto massa 1000: %.6f segundos\n", cpuTimeUsedMassa1000);
    // printf("Tempo gasto massa 100000: %.6f segundos\n", cpuTimeUsedMassa100000);
    // printf("Tempo gasto massa 500000: %.6f segundos\n", cpuTimeUsedMassa500000);
    
    return 0;
}

int *criarMassaDados(int tamanho)
{
    srand(time(NULL));
    int *massaDados = (int *)calloc(tamanho, sizeof(int));
    int numeroAleatorio;
    for (int i = 0; i < tamanho; i++)
    {

        numeroAleatorio = rand();
        massaDados[i] = numeroAleatorio;
    }
    return massaDados;
}

void merge(int *massaDados, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)calloc(n1, sizeof(int));
    int *R = (int *)calloc(n2, sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = massaDados[l + i];
    for (j = 0; j < n2; j++)
        R[j] = massaDados[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            massaDados[k] = L[i];
            i++;
        }
        else
        {
            massaDados[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        massaDados[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        massaDados[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int *massaDados, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(massaDados, l, m);
        mergeSort(massaDados, m + 1, r);

        merge(massaDados, l, m, r);
    }
}

void gerarArquivoOutput(double cpuTimeUsedMassa1000, double cpuTimeUsedMassa100000, double cpuTimeUsedMassa500000){
    FILE *arquivo;
    char bufferMassa1000[100];
    char bufferMassa100000[100];
    char bufferMassa500000[100];
    char nomeArquivo[] = "Resultado Merge Sort.txt";
    char textoArquivo[200];

    arquivo = fopen(nomeArquivo, "w");

    sprintf(bufferMassa1000, "%.6f", cpuTimeUsedMassa1000);
    sprintf(bufferMassa100000, "%.6f", cpuTimeUsedMassa100000);
    sprintf(bufferMassa500000, "%.6f", cpuTimeUsedMassa500000);
    
    strcpy(textoArquivo, "Tempo de execução massa 1000: ");
    strcat(textoArquivo, bufferMassa1000);
    strcat(textoArquivo, " segundos ");
    strcat(textoArquivo, "| Status ordenação: Ordenado\n");

    strcat(textoArquivo, "Tempo de execução massa 100.000: ");
    strcat(textoArquivo, bufferMassa100000);
    strcat(textoArquivo, " segundos ");
    strcat(textoArquivo, "| Status ordenação: Ordenado\n");

    strcat(textoArquivo, "Tempo de execução massa 500.000: ");
    strcat(textoArquivo, bufferMassa500000);
    strcat(textoArquivo, " segundos ");
    strcat(textoArquivo, "| Status ordenação: Ordenado");

    fprintf(arquivo, "%s", textoArquivo);
    fclose(arquivo);
}

void printArray(int *massaDados, int tamanho)
{   
    for(int i = 0; i < tamanho; i++){
        printf("%d ", massaDados[i]);
    }
}