#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

struct Node {
    int vertex;
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
};

void BFS(struct Graph * graph, int startVertex);
void addEdge(struct Graph* graph, int src, int dest);
struct Graph* createGraph(int numVertices);
bool isEmpty(struct Queue * queue);
int dequeue(struct Queue * queue);
void enqueue(struct Queue * queue, int v);
struct Queue * createQueue();
struct Node* createNode(int v);

int main(void){
    struct Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);

    printf("Starting vertex: 0\n");
    BFS(graph, 0);
}

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Queue * createQueue(){
    struct Queue * queue = (struct Queue * )malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(struct Queue * queue, int v){
    struct Node * newNode = createNode(v);
    if(queue->rear == NULL){
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

int dequeue(struct Queue * queue){
    if(queue->front == NULL) return -1;
    struct Node * temp = queue->front;
    int vertex = temp->vertex;
    queue->front = queue->front->next;

    if(queue->front == NULL){
        queue->rear = NULL;
    }

    free(temp);
    return vertex;
}

bool isEmpty(struct Queue * queue){
    return queue->front == NULL;
}

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (struct Node**)malloc(numVertices * sizeof(struct Node*));
    for (int i = 0; i < numVertices; ++i) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // For undirected graph, add an edge from dest to src as well
    // newNode = createNode(src);
    // newNode->next = graph->adjLists[dest];
    // graph->adjLists[dest] = newNode;
}

void BFS(struct Graph * graph, int startVertex){
    //Array of Boolean values
    bool * visited = (bool *)malloc(graph->numVertices * sizeof(bool));

    //Set each entry to false
    for(int i = 0; i < graph->numVertices; i++){
        visited[i] = false;
    }

    //Create Queue and add starting vertex to queue
    //Mark it as visited
    struct Queue * queue = createQueue();
    visited[startVertex] = true;
    enqueue(queue, startVertex);

    //Traverse all unvisited vertices
    printf("Breadth-First Search Traversal Order Result: ");
    while(!isEmpty(queue)){
        //1. Pop a vertex from queue
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        //2. add unvisted neigbor vertices of the current node, mark them visited
        struct Node* temp = graph->adjLists[currentVertex];
        while(temp != NULL){
            int adjVertex = temp->vertex;
            if(!visited[adjVertex]){
                visited[adjVertex] = true;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }

    printf("\n");

    free(visited);
    free(queue);
}