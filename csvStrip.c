#include "csvStrip.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int carregaProcessos(const char *nomeArquivo, Processo *processos, int maxProcessos) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    char linha[512];
    int i = 0;

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) && i < maxProcessos) {
        sscanf(linha, "%d,%[^,],%[^,],{%d},%s,%d",
             &processos[i].id,
             processos[i].numero,
             processos[i].data_ajuizamento,
             &processos[i].id_classe,
             processos[i].id_assunto,
             &processos[i].ano_eleicao);
        i++;
    }

    fclose(arquivo);
    return i;
}

int comparaIdCrescente(const void *a, const void *b) {
    Processo *p1 = (Processo *)a;
    Processo *p2 = (Processo *)b;
    return (p1->id - p2->id);
}

int comparaDataDecrescente(const void *a, const void *b) {
    Processo *p1 = (Processo *)a;
    Processo *p2 = (Processo *)b;
    return strcmp(p2->data_ajuizamento, p1->data_ajuizamento);
}

void salvaProcessosOrdenadosEmCSV(const char *nomeArquivo, Processo *processos, int numProcessos) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        perror("Erro ao criar o arquivo CSV");
        return;
    }

    fprintf(arquivo, "id,numero,data_ajuizamento,id_classe,id_assunto,ano_eleicao\n");

    for (int i = 0; i < numProcessos; i++) {
        fprintf(arquivo,
                "%d,%s,%s,%d,%s,%d\n",
                processos[i].id,
                processos[i].numero,
                processos[i].data_ajuizamento,
                processos[i].id_classe,
                processos[i].id_assunto,
                processos[i].ano_eleicao);
    }

    fclose(arquivo);
    printf("Processos ordenados salvos no arquivo: %s\n", nomeArquivo);
}


int contaPorIdClasse(Processo *processos, int numProcessos, int idClasse) {
    int contador = 0;
    for (int i = 0; i < numProcessos; i++) {
        if (processos[i].id_classe == idClasse) {
            contador++;
        }
    }
    return contador;
}

int contaIdAssuntosUnicos(Processo *processos, int numProcessos) {
    int unicos[1000] = {0};
    int uniqueCount = 0;

    for (int i = 0; i < numProcessos; i++) {
        char idCopia[50]; 
        strcpy(idCopia, processos[i].id_assunto); 
        
        char *token = strtok(idCopia, ",{}");

        while (token != NULL) {
            int idAtual = atoi(token);

            if (unicos[idAtual] == 0) {
                unicos[idAtual] = 1;
                uniqueCount++;
            }

            token = strtok(NULL, ",{}");
        }
    }

    return uniqueCount;
}

int contaMaisDeUm(Processo *processos, int numProcessos) {
    int contador = 0;


    for (int i = 0; i < numProcessos; i++) {
        if (strchr(processos[i].id_assunto, ',') != NULL) {
            contador++;

        }
    }

    return contador;
}



int calculaDiasEmTramitacao(const char *dataAjuizamento) {
    struct tm tmAjuizamento = {0};
    time_t agora = time(NULL);
    time_t ajuizamento;

    sscanf(dataAjuizamento, "%d-%d-%d",
           &tmAjuizamento.tm_year,
           &tmAjuizamento.tm_mon,
           &tmAjuizamento.tm_mday);

    tmAjuizamento.tm_year -= 1900;
    tmAjuizamento.tm_mon -= 1;

    ajuizamento = mktime(&tmAjuizamento);

    return (int)difftime(agora, ajuizamento) / (60 * 60 * 24);
}
