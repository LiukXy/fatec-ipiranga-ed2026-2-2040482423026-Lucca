/*
 * Disciplina: Estrutura de Dados
 * Prof. Veríssimo
 * Objetivo do Programa: Sistema de Atendimento - Lava-Rápido Brilho Total
 *                        Alocação dinâmica de memória e recursividade
 * Data - 31/08/2026
 * Autor: Lucca Rangel Rodrigues
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALOR_PREMIUM 100.0

// struct veiculo
typedef struct {
    char placa[8]; 
    float valor;
} Veiculo;

//Funções
void exibirCabecalho(void);
void preencherFrota(Veiculo *frota, int quantidade);
void exibirFrotaRecursivo(Veiculo *frota, int indice, int quantidade);
float calcularValorTotalRecursivo(Veiculo *frota, int indice, int quantidade);
int buscarVeiculoRecursivo(Veiculo *frota, int indice, int quantidade, char placa[8]);
int contarPremiumRecursivo(Veiculo *frota, int indice, int quantidade);

int main() {
    int quantidade;
    Veiculo *frota;

    //cabeçalho do sistema 
    exibirCabecalho();

    //quantidade de veículos
    printf("quantos veiculos serao atendidos hoje? ");
    scanf("%d", &quantidade);

    //alocação dinamica do vetor com maloc
    frota = (Veiculo *)malloc(quantidade * sizeof(Veiculo));

    //se o malloc foi bem-sucedido
    if (frota == NULL) {
        printf("erro: memoria insuficiente para alocar a frota.\n");
        return 1;
    }

    //preenchimento de vetor (única função com laço)
    preencherFrota(frota, quantidade);

    //recursividade na exibição da frota
    printf("\nveiculos atendidos hojen");
    exibirFrotaRecursivo(frota, 0, quantidade);

    //busca recursiva por placa
    char placaBusca[8];
    printf("\n busca por placa\n");
    printf("placa a ser pesquisada: ");
    scanf("%s", placaBusca);

    int posicao = buscarVeiculoRecursivo(frota, 0, quantidade, placaBusca);
    if (posicao != -1) {
        printf("veiculo encontrado na posicao %d! placa: %s | valor: R$ %.2f\n",
               posicao + 1, frota[posicao].placa, frota[posicao].valor);
    } else {
        printf("veiculo nao encontrado na frota.\n");
    }

    float totalArrecadado = calcularValorTotalRecursivo(frota, 0, quantidade);
    int totalPremium = contarPremiumRecursivo(frota, 0, quantidade);//resumo

    printf("resumo do dia\n");
    printf("total de veiculos atendidos: %d\n", quantidade);
    printf("servicos premium (>= R$ 100.00): %d\n", totalPremium);
    printf("valor total arrecadado: R$ %.2f\n", totalArrecadado);

    //liberar da memória alocada
    free(frota);
    frota = NULL;

    printf("Memoria da frota liberada com sucesso. Sistema encerrado.\n");

    return 0;
}

void exibirCabecalho(void) {
    printf("LAVA -RAPIDO BRILHO TOTAL - FILA DE ATENDIMENTO\n");
}


void preencherFrota(Veiculo *frota, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Placa do veiculo %d: ", i + 1);
        scanf("%s", (frota + i)->placa); 

        printf("Valor do servicio (R$): ");
        scanf("%f", &(frota + i)->valor); 
    }
}


void exibirFrotaRecursivo(Veiculo *frota, int indice, int quantidade) {
    //se atingir o fim do vetor, retorna
    if (indice == quantidade) {
        return;
    }

    printf("%d) Placa: %s | Valor: R$ %.2f\n",
           indice + 1, frota[indice].placa, frota[indice].valor);

    //continua recursivamente para o próximo elemento
    exibirFrotaRecursivo(frota, indice + 1, quantidade);
}


float calcularValorTotalRecursivo(Veiculo *frota, int indice, int quantidade) {
    //se atingiu o fim do vetor, retorna 0
    if (indice == quantidade) {
        return 0.0f;
    }

    //soma o valor atual com a soma do restante
    return frota[indice].valor + calcularValorTotalRecursivo(frota, indice + 1, quantidade);
}


int buscarVeiculoRecursivo(Veiculo *frota, int indice, int quantidade, char placa[8]) {
    //se atingiu o fim do vetor, o veiculo não foi encontrado
    if (indice == quantidade) {
        return -1;
    }

    //caso encontrou a placa, retorna o índice atual
    if (strcmp(frota[indice].placa, placa) == 0) {
        return indice;
    }

    //continua a busca para o prox objeto
    return buscarVeiculoRecursivo(frota, indice + 1, quantidade, placa);
}


int contarPremiumRecursivo(Veiculo *frota, int indice, int quantidade) {
    //se atingiu o fim do vetor, retorna 0
    if (indice == quantidade) {
        return 0;
    }

    //verifica se o valor atual é premium e soma
    int contagemAtual = (frota[indice].valor >= VALOR_PREMIUM) ? 1 : 0;
    return contagemAtual + contarPremiumRecursivo(frota, indice + 1, quantidade);
}
