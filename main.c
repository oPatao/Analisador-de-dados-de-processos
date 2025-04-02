#include "csvStrip.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Processo processos[18392];
  int numProcessos = carregaProcessos("processo_043_202409032338.csv", processos, 18392);

  if (numProcessos < 0) {
    return EXIT_FAILURE;
  }

  // Funcionalidade 1: Ordenar por id (crescente)
  qsort(processos, numProcessos, sizeof(Processo), comparaIdCrescente);
  printf("Processos ordenados por ID em ordem crescente.\n");

  salvaProcessosOrdenadosEmCSV("processos_ordenados_por_ID.csv", processos, numProcessos);

  // Funcionalidade 2: Ordenar por data_ajuizamento (decrescente)
  qsort(processos, numProcessos, sizeof(Processo), comparaDataDecrescente);
  printf("Processos ordenados por data de ajuizamento em ordem decrescente.\n");

  salvaProcessosOrdenadosEmCSV("processos_ordenados_por_data.csv", processos, numProcessos);


  // Funcionalidade 3: Contar por id_classe
  int idClasse = 12554; // Exemplo
  int quantidade = contaPorIdClasse(processos, numProcessos, idClasse);
  printf("Quantidade de processos com id_classe %d: %d\n", idClasse, quantidade);

  // Funcionalidade 4: Contar id_assuntos únicos
  int idAssuntosUnicos = contaIdAssuntosUnicos(processos, numProcessos);
  printf("Quantidade de id_assuntos unicos: %d\n", idAssuntosUnicos);

    // Funcionalidade 5: Listar processos com mais de um assunto
  int contador = contaMaisDeUm(processos, numProcessos);
  printf("Quantidade de processos com mais de um assunto: %d\n", contador);

  // Funcionalidade 6: Dias em tramitação
  for (int i = 0; i < numProcessos; i++) {
    int dias = calculaDiasEmTramitacao(processos[i].data_ajuizamento);
    printf("Processo ID %d está em tramitacao ha %d dias.\n", processos[i].id, dias);
  }

  return EXIT_SUCCESS;
}