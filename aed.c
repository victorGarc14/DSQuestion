#include <stdio.h>
#include <stdlib.h>
//EQUIPE Cicero Victor de Oliveira Garcia e Francio Xavier

// Definição da estrutura de nó para a fila
typedef struct Node {
    int data; //info
    struct Node* next; //nó.prox
} Node;

// Definição da estrutura da fila
typedef struct {
    Node* front; //inicio da fila
    Node* rear; // fim da fila
    int size;   // quantidade de elementos da fila
    int capacity; // capacidade maxima
} Queue;

// Função para criar uma nova fila
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue)); // alocação de memória para a fila
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// Função para verificar se a fila está vazia
int isEmpty(Queue* queue) {
    return queue->size == 0;
}

// Função para verificar se a fila está cheia
int isFull(Queue* queue) {
    return queue->size == queue->capacity;
}

// Função para enfileirar um elemento na fila
void enqueue(Queue* queue, int data) {
    if (isFull(queue)) { //verifica se a fila está cheia e retorna erro
        printf("Fila cheia, não é possível adicionar mais carros.\n");
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node)); // adiciona novo nó
    newNode->data = data; //adiciona dados no novo nó
    newNode->next = NULL;
    if (isEmpty(queue)) {
        queue->front = newNode; //caso a fila esteja vazia, adiciona no inicio
    } else {
        queue->rear->next = newNode; //caso tenha alguem, adiciona ao próximo do final anterior
    }
    queue->rear = newNode; // transforma o final da fila no novo nó
    queue->size++; //aumenta o a quantidade de elementos na fila
}

// Função para desenfileirar um elemento da fila
int dequeue(Queue* queue) {
    if (isEmpty(queue)) { //verifica se a fila está vazia e retorna erro caso esteja
        printf("Fila vazia, não é possível remover carros.\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = queue->front; //pega o ponteiro inicial da fila
    int data = temp->data; //pega o valor do ponteiro temp
    queue->front = queue->front->next; //inicio da fila recebe inicio.prox
    free(temp);//limpa a memoria
    queue->size--; //diminui o tamanho da fila
    return data; //retorna valor de temp
}

// Função principal para calcular o número de carros lavados
int washedCars(int n, int k, int* V) {
    Queue* queue = createQueue(k + 1); // Capacidade aumentada para incluir o carro sendo lavado
    int washed = 0;// Iinicializa o valor de lavados
    int washTime = 0; // Contador para o tempo de lavagem do carro atual
    int cont = 0;//conotador para verificar o primeiro valor 1 da fila
    for (int i = 0; i < n; i++) {
        if (V[i] == 1) {//verifica o valor ja iniciando a lavagem e contando o tempo
            washTime = 3;
            break;
        }
        cont ++;//incremento do contador
    }

    for (cont; cont < n; cont++) {//comomeça a verificação do primeiro valor 1 da fila

        // Processa o carro atual que está sendo lavado
        if (washTime > 0) {
            washTime--;//decremento de tempo caso um carro esteja sendo lavado
            if (washTime == 0) {
                washed++;//incrementa o numero de lavados caso tenha terminado o tempo
                dequeue(queue);//retira o carro da fila
            }
        }

        // Verifica se há um novo cliente e espaço disponível na fila
        if (V[cont] == 1 && !isFull(queue)) {
            enqueue(queue, 1);//coloca na fila
        }

        // Verifica se há um carro para ser lavado e inicia o processo de lavagem
        if (!isEmpty(queue) && washTime == 0) {
            washTime = 3; // Define o tempo de lavagem para 3 minutos e ja inicia a lavagem
           washTime--;//decrementa o tempo pois ja iniciou a lavagem
        }
    }

    free(queue);//libera a memoria da fila
    return washed;//retorna lavados
}

int main() {
    int n, k;
    printf("Digite o número de minutos (n): ");
    scanf("%d", &n);
    printf("Digite a capacidade máxima de atendimento (k): ");
    scanf("%d", &k);

    int* V = (int*)malloc(n * sizeof(int));//alocando memória para o vetor
    printf("Digite o vetor binário V de tamanho %d: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &V[i]);
    }

    int washed = washedCars(n, k, V);
    printf("Número de carros lavados até o %d-ésimo minuto: %d\n", n, washed);

    free(V);//libera a memoria alocada para v
    return 0;
}
