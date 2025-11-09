#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição da struct Item
#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Declaração das funções
void inicializarMochila(Item mochila[], int *quantidade);
void inserirItem(Item mochila[], int *quantidade);
void removerItem(Item mochila[], int *quantidade);
void listarItens(const Item mochila[], int quantidade);
void limparBuffer();

int main() {
    Item mochila[MAX_ITENS];
    int quantidadeItens = 0;
    int opcao;
    
    inicializarMochila(mochila, &quantidadeItens);
    
    do {
        printf("===========================================\n");
        printf(" MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("===========================================\n");
        printf("Itens na Mochila: %d/10\n\n", quantidadeItens);
        
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Sair\n\n");
        
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                inserirItem(mochila, &quantidadeItens);
                break;
            case 2:
                removerItem(mochila, &quantidadeItens);
                break;
            case 3:
                listarItens(mochila, quantidadeItens);
                break;
            case 4:
                printf("Saindo do sistema... Boa sorte na sobrevivencia!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        printf("\n");
    } while (opcao != 4);
    
    return 0;
}

// inicia a mochila vazia 
void inicializarMochila(Item mochila[], int *quantidade) {
    *quantidade = 0;
    for (int i = 0; i < MAX_ITENS; i++) {
        strcpy(mochila[i].nome, "");
        strcpy(mochila[i].tipo, "");
        mochila[i].quantidade = 0;
    }
}

// Insere um novo item na mochila
void inserirItem(Item mochila[], int *quantidade) {
    if (*quantidade >= MAX_ITENS) {
        printf("Erro: Mochila cheia! Capacidade maxima de 10 itens atingida.\n");
        return;
    }
    
    printf("\n--- Adicionar Novo Item ---\n");
    
    printf("Nome do item: ");
    fgets(mochila[*quantidade].nome, TAM_NOME, stdin);
    mochila[*quantidade].nome[strcspn(mochila[*quantidade].nome, "\n")] = '\0';
    
    printf("Tipo do item (arma, municao, cura, etc.): ");
    fgets(mochila[*quantidade].tipo, TAM_TIPO, stdin);
    mochila[*quantidade].tipo[strcspn(mochila[*quantidade].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &mochila[*quantidade].quantidade);
    limparBuffer();
    
    (*quantidade)++;
    printf("\nItem '%s' adicionado com sucesso!\n", mochila[*quantidade - 1].nome);
    
    // Mostra a lista atualizada após adicionar
    printf("\n \n");
    listarItens(mochila, *quantidade);
}

// Remove um item da mochila pelo nome
void removerItem(Item mochila[], int *quantidade) {
    if (*quantidade == 0) {
        printf("A mochila esta vazia! Nada para remover.\n");
        return;
    }
    
    printf("\n--- Remover Item ---\n");
    char nomeBusca[TAM_NOME];
    printf("Nome do item a ser removido: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca um item pelo nome
    int posicao = -1;
    for (int i = 0; i < *quantidade; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            posicao = i;
            break;
        }
    }
    
    if (posicao == -1) {
        printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
        return;
    }
    
    // Remove o item deslocando os elementos posteriores
    printf("Item '%s' removido com sucesso!\n", mochila[posicao].nome);
    for (int i = posicao; i < *quantidade - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    
    // Limpa o último elemento
    strcpy(mochila[*quantidade - 1].nome, "");
    strcpy(mochila[*quantidade - 1].tipo, "");
    mochila[*quantidade - 1].quantidade = 0;
    
    (*quantidade)--;
    
    // Mostra a lista atualizada depois de remover
    printf("\n----\n");
    listarItens(mochila, *quantidade);
}

// Lista os itens da mochila
void listarItens(const Item mochila[], int quantidade) {
    printf("--- ITENS NA MOCHILA --- (%d/10)\n", quantidade);
    printf("|----------------------|-----------------|------------|\n");
    
    if (quantidade == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }
    
    printf("| %-20s | %-15s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("|----------------------|-----------------|------------|\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("| %-20s | %-15s | %-10d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
}

// Auto explicativo né?
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}