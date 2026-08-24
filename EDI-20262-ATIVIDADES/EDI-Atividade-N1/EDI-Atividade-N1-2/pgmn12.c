#include <stdio.h>

#define TAMANHO_ESTOQUE 5
#define ESTOQUE_MINIMO 10 //estruturas simbolicas

int estoque[TAMANHO_ESTOQUE];//vetor global


void exibirCabecalho(void) {
    printf("loja construmais, controle de estoque\n");//cabecalho func. sem parametros
}

void preencherEstoque(void) {
    int *p = estoque; // ponteiro local p o vetor global 
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        printf("Quantidade do produto %d:\n ", i + 1);
        scanf("%d", (p + i));
    }
}

void exibirEstoque(int momento) {
    if (momento == 0) {
        printf("\nestoque inicial\n");
    } else {
        printf("\nEstoque final\n");
    }
    int *p = estoque; 
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        printf("Produto %d: %d\n", i + 1, *(p + i));// func. sem parametros - prenchimento por ponteiros. 
    }
}

float calcularMediaEstoque(void) {//func. c retorno. 
    int *p = estoque;
    int soma = 0;
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        soma += *(p + i);
    }
    return (float)soma / TAMANHO_ESTOQUE;
}


void simularReposicao(int quantidadeAtual, int reposicao) {
    int resultado = quantidadeAtual + reposicao;
    printf("\n--- Simulação de Reposição (primeiro produto) ---\n");
    printf("Quantidade atual: %d + Reposição: %d = %d\n", 
           quantidadeAtual, reposicao, resultado);
    printf("(Valor original do estoque permanece inalterado)\n");// func. com passagem de valor
}


void aplicarReposicaoGeral(int reposicao) {
    int *p = estoque;
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        *(p + i) += reposicao;//altera o valor do vetor lgobal por meio de um ponteiro interno
    }
}


void identificarEstoqueCritico(int minimo) {
    int *p = estoque;
    int encontrouCritico = 0; //func de analise
    
    printf("\n--- Análise de Estoque Crítico (abaixo de %d) ---\n", minimo);
    
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        if (*(p + i) < minimo) {
            printf("Produto %d está em nível crítico: %d unidades\n", i + 1, *(p + i));
            encontrouCritico = 1;
        }
    }
    
    if (!encontrouCritico) {
        printf("Nenhum produto em estado crítico. Estoque regularizado.\n");
    }
}


   int main(void) {
    int reposicao;
    
    exibirCabecalho();
    
    preencherEstoque();
    
    exibirEstoque(0);
    
    float media = calcularMediaEstoque();
    printf("\nMédia do estoque: %.2f\n", media);
    printf("\nQuantidade de reposicao a aplicar: ");
    scanf("%d", &reposicao);
    
    simularReposicao(estoque[0], reposicao);
    
    aplicarReposicaoGeral(reposicao);
    
    exibirEstoque(1);
    identificarEstoqueCritico(ESTOQUE_MINIMO);
    
    return 0;
}
