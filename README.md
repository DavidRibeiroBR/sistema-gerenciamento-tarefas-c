# Sistema de Gerenciamento de Tarefas em C

> Projeto desenvolvido para a disciplina de Estruturas de Dados II, aplicando conceitos de programação em C, algoritmos de ordenação e manipulação de estruturas lineares.

---

## 🚀 Sobre o Projeto

Este programa simula um sistema completo de gerenciamento de tarefas via terminal. O diferencial da aplicação é a integração coesa entre diferentes estruturas de dados clássicas (`structs`, `Filas` e `Pilhas`) e algoritmos de ordenação eficientes para gerenciar o ciclo de vida das tarefas.

---

## ✨ Funcionalidades

1. **Cadastro de Tarefas:** Adicione tarefas informando ID, descrição, prioridade (de 1 a 10) e tempo estimado em minutos.
2. **Listagem:** Visualize todas as tarefas cadastradas em formato de tabela organizada.
3. **Ordenação de Tarefas:** Ordene a lista de tarefas utilizando os algoritmos:
   * **Bubble Sort**
   * **Insertion Sort**
   *(Podendo escolher entre o critério de **Prioridade** ou **Tempo Estimado**).*
4. **Fila de Execução (Queue):** Enfileire tarefas cadastradas para simular a ordem de processamento/execução (FIFO - *First In, First Out*).
5. **Execução de Tarefas:** Execute a próxima tarefa da fila.
6. **Histórico de Concluídas (Stack):** As tarefas executadas são automaticamente movidas para uma pilha de histórico, permitindo visualizá-las em ordem inversa de execução (LIFO - *Last In, First Out*).

---

## 🛠️ Tecnologias e Conceitos Utilizados

* **Linguagem C** (Padrão C99)
* **Alocação e Manipulação de Memória:** Estruturas (`struct`), typedefs e ponteiros.
* **Estruturas de Dados Lineares Estáticas:**
  * Fila Circular (`Queue`)
  * Pilha (`Stack`)
* **Algoritmos de Ordenação:** Bubble Sort e Insertion Sort adaptados para múltiplos critérios.
