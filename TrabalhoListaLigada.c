#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
    int id;
    char descricao[100];
    struct Node* proximo;
} Node;


Node* criarNo(int id, char descricao[]) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->id = id;
    strcpy(novo->descricao, descricao);
    novo->proximo = NULL;
    return novo;
}


void inserir(Node** cabeca, int id, char descricao[]) {
    Node* novo = criarNo(id, descricao);
    if (*cabeca == NULL) {
        *cabeca = novo;
    } else {
        Node* atual = *cabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
    printf("Tarefa inserida com sucesso!\n");
}


void exibir(Node* cabeca) {
    if (cabeca == NULL) {
        printf("Nenhuma tarefa encontrada.\n");
        return;
    }
    printf("\n=== LISTA DE TAREFAS ===\n");
    Node* atual = cabeca;
    while (atual != NULL) {
        printf("ID: %d | Descrição: %s\n", atual->id, atual->descricao);
        atual = atual->proximo;
    }
    printf("=========================\n");
}


void remover(Node** cabeca, int id) {
    Node* atual = *cabeca;
    Node* anterior = NULL;

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Tarefa com ID %d não encontrada.\n", id);
        return;
    }

    if (anterior == NULL) {
        *cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Tarefa removida com sucesso!\n");
}


void liberarLista(Node* cabeca) {
    Node* atual = cabeca;
    while (atual != NULL) {
        Node* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

int main() {
    Node* lista = NULL;
    int opcao, id;
    char descricao[100];

    do {
        printf("\n===== GERENCIAMENTO DE TAREFAS =====\n");
        printf("1. Inserir nova tarefa\n");
        printf("2. Exibir todas as tarefas\n");
        printf("3. Remover uma tarefa\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                printf("Digite o ID da tarefa: ");
                scanf("%d", &id);
                getchar();
                printf("Digite a descrição: ");
                fgets(descricao, 100, stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                inserir(&lista, id, descricao);
                break;
            case 2:
                exibir(lista);
                break;
            case 3:
                printf("Digite o ID da tarefa a remover: ");
                scanf("%d", &id);
                remover(&lista, id);
                break;
            case 0:
                liberarLista(lista);
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}