//
// Created by ghopp on 02/04/2025.
//

#ifndef CSVSTRIP_H
#define CSVSTRIP_H

typedef struct {
    int id;
    char numero[24];
    char data_ajuizamento[50];
    int id_classe;
    char id_assunto[20];
    int ano_eleicao;

} Processo;

void stripCsv(char *filename);

int carregaProcessos(const char *nomeArquivo, Processo *processos, int maxProcessos );
int comparaIdCrescente(const void *a, const void *b);
int comparaDataDecrescente(const void *a, const void *b);
void salvaProcessosOrdenadosEmCSV(const char *nomeArquivo, Processo *processos, int numProcessos);
int contaPorIdClasse(Processo *processos, int numProcessos, int idClasse);
int contaIdAssuntosUnicos(Processo *processos, int numProcessos);
int contaMaisDeUm(Processo *processos, int numProcessos);
int calculaDiasEmTramitacao(const char *data_ajuizamento);


#endif //CSVSTRIP_H
