#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAREFAS 100

//  Estruturas de Dados (Corrigidas com typedef) 
typedef struct {
    int id;
    int prioridade;
    int tempoEstimado;
    char descricao[100];
} Tarefa;

typedef struct {
    Tarefa itens[TAREFAS];
    int inicio, fim, tamanho;
} Fila;

typedef struct {
    Tarefa itens[TAREFAS];
    int topo;
} Pilha;

// Declaração de funções
void inicializarFila(Fila *f);
int inserirFila(Fila *f, Tarefa t);
Tarefa removerFila(Fila *f);
void inicializarPilha(Pilha *p);
int pushPilha(Pilha *p, Tarefa t);
Tarefa popPilha(Pilha *p);
void ordenarBubbleSort(Tarefa vetor[], int numero, int criterio);
void ordenarInsertionSort(Tarefa vetor[], int numero, int criterio);
void cadastrarTarefa();
void listarTarefas();
void ordenarTarefas();
void adicionarNaFila(Fila *f);
void executarTarefa(Fila *f, Pilha *p);
void mostrarHistorico(Pilha *p);

// Variáveis Globais
Tarefa listaTarefas[TAREFAS];
int totalTarefas = 0;

int main() {
    Fila filaExecucao;
    Pilha historicoConcluidas;
    
    inicializarFila(&filaExecucao);
    inicializarPilha(&historicoConcluidas);

    int opcao;

    do {
        printf("\n Sistema de Gerenciamento de Tarefas \n");
        printf("1 - Cadastrar tarefa\n");
        printf("2 - Listar tarefas\n");
        printf("3 - Ordenar tarefas (prioridade ou tempo)\n");
        printf("4 - Adicionar tarefa a fila\n");
        printf("5 - Executar tarefa da fila\n");
        printf("6 - Mostrar historico (pilha)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarTarefa();
                break;
            case 2:
                listarTarefas();
                break;
            case 3:
                ordenarTarefas();
                break;
            case 4:
                adicionarNaFila(&filaExecucao);
                break;
            case 5:
                executarTarefa(&filaExecucao, &historicoConcluidas);
                break;
            case 6:
                mostrarHistorico(&historicoConcluidas);
                break;
            case 0:
                printf("Saindo do sistema\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

//  Funções da Fila 
void inicializarFila(Fila *f) {
    f[0].inicio = 0;
    f[0].fim = 0;
    f[0].tamanho = 0;
}

int inserirFila(Fila *f, Tarefa t) {
    if (f[0].tamanho == TAREFAS) {
        printf("Erro: Fila cheia!\n");
        return 0;
    }
    f[0].itens[f[0].fim] = t;
    f[0].fim = (f[0].fim + 1) % TAREFAS;
    f[0].tamanho++;
    return 1;
}

Tarefa removerFila(Fila *f) {
    Tarefa t;
    if (f[0].tamanho == 0) {
        printf("Erro: Fila vazia!\n");
        t.id = -1;
        return t;
    }
    t = f[0].itens[f[0].inicio];
    f[0].inicio = (f[0].inicio + 1) % TAREFAS;
    f[0].tamanho--;
    return t;
}

//  Funções da Pilha 
void inicializarPilha(Pilha *p) {
    p[0].topo = -1;
}

int pushPilha(Pilha *p, Tarefa t) {
    if (p[0].topo == TAREFAS - 1) {
        printf("Erro: Pilha cheia!\n");
        return 0;
    }
    p[0].topo++;
    p[0].itens[p[0].topo] = t;
    return 1;
}

Tarefa popPilha(Pilha *p) {
    Tarefa t;
    if (p[0].topo == -1) {
        printf("Erro: Pilha vazia!\n");
        t.id = -1;
        return t;
    }
    t = p[0].itens[p[0].topo];
    p[0].topo--;
    return t;
}

//  Algoritmos de Ordenação 
void ordenarBubbleSort(Tarefa vetor[], int numero, int criterio) {
    for (int i = 0; i < numero - 1; i++) {
        for (int j = 0; j < numero - i - 1; j++) {
            int trocar = 0;
            if (criterio == 1) {
                if (vetor[j].prioridade < vetor[j + 1].prioridade) trocar = 1;
            } else {
                if (vetor[j].tempoEstimado > vetor[j + 1].tempoEstimado) trocar = 1;
            }

            if (trocar) {
                Tarefa temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

void ordenarInsertionSort(Tarefa vetor[], int numero, int criterio) {
    for (int i = 1; i < numero; i++) {
        Tarefa chave = vetor[i];
        int j = i - 1;

        if (criterio == 1) {
            while (j >= 0 && vetor[j].prioridade < chave.prioridade) {
                vetor[j + 1] = vetor[j];
                j--;
            }
        } else {
            while (j >= 0 && vetor[j].tempoEstimado > chave.tempoEstimado) {
                vetor[j + 1] = vetor[j];
                j--;
            }
        }
        vetor[j + 1] = chave;
    }
}

//  Funções do Sistema 
void cadastrarTarefa() {
    if (totalTarefas >= TAREFAS) {
        printf("Limite de tarefas atingido!\n");
        return;
    }

    Tarefa t;
    printf("\n Cadastrar Tarefa \n");
    printf("ID: ");
    scanf("%d", &t.id);
    
    printf("Descricao: ");
    scanf("%99s", t.descricao); 
    
    do {
        printf("Prioridade (1-10): ");
        scanf("%d", &t.prioridade);
    } while (t.prioridade < 1 || t.prioridade > 10);

    printf("Tempo estimado (minutos): ");
    scanf("%d", &t.tempoEstimado);

    listaTarefas[totalTarefas] = t;
    totalTarefas++;
    printf("Tarefa cadastrada com sucesso!\n");
}

void listarTarefas() {
    if (totalTarefas == 0) {
        printf("\nNenhuma tarefa cadastrada.\n");
        return;
    }
    printf("\n Lista de Tarefas \n");
    printf("%-5s %-30s %-12s %-10s\n", "ID", "Descricao", "Prioridade", "Tempo(min)");
    for (int i = 0; i < totalTarefas; i++) {
        printf("%-5d %-30s %-12d %-10d\n", 
               listaTarefas[i].id, 
               listaTarefas[i].descricao, 
               listaTarefas[i].prioridade, 
               listaTarefas[i].tempoEstimado);
    }
}

void ordenarTarefas() {
    if (totalTarefas == 0) {
        printf("\nNenhuma tarefa para ordenar.\n");
        return;
    }

    int criterio, algoritmo;
    printf("\nOrdenar por:\n1 - Prioridade\n2 - Tempo Estimado\nEscolha: ");
    scanf("%d", &criterio);
    
    printf("Algoritmo:\n1 - Bubble Sort\n2 - Insertion Sort\nEscolha: ");
    scanf("%d", &algoritmo);

    if (algoritmo == 1) {
        ordenarBubbleSort(listaTarefas, totalTarefas, criterio);
        printf("Ordenado com Bubble Sort!\n");
    } else if (algoritmo == 2) {
        ordenarInsertionSort(listaTarefas, totalTarefas, criterio);
        printf("Ordenado com Insertion Sort!\n");
    } else {
        printf("Opcao invalida.\n");
    }
}

void adicionarNaFila(Fila *f) {
    if (totalTarefas == 0) {
        printf("\nNenhuma tarefa cadastrada.\n");
        return;
    }
    int id;
    printf("\nDigite o ID da tarefa para adicionar a fila: ");
    scanf("%d", &id);

    for (int i = 0; i < totalTarefas; i++) {
        if (listaTarefas[i].id == id) {
            if (inserirFila(f, listaTarefas[i])) {
                printf("Tarefa '%s' adicionada a fila de execucao.\n", listaTarefas[i].descricao);
            }
            return;
        }
    }
    printf("Tarefa com ID %d nao encontrada.\n", id);
}

void executarTarefa(Fila *f, Pilha *p) {
    Tarefa t = removerFila(f);
    if (t.id != -1) {
        printf("\nExecutando tarefa: %s (ID: %d)\n", t.descricao, t.id);
        printf("Tarefa concluida!\n");
        pushPilha(p, t);
    }
}

void mostrarHistorico(Pilha *p) {
    if (p[0].topo == -1) {
        printf("\nHistorico vazio.\n");
        return;
    }
    printf("\n Historico de Tarefas Concluidas (Ordem Inversa) \n");
    printf("%-5s %-30s %-12s %-10s\n", "ID", "Descricao", "Prioridade", "Tempo(min)");
    for (int i = p[0].topo; i >= 0; i--) {
        printf("%-5d %-30s %-12d %-10d\n", 
               p[0].itens[i].id, 
               p[0].itens[i].descricao, 
               p[0].itens[i].prioridade, 
               p[0].itens[i].tempoEstimado);
    }
}