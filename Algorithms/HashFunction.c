#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 256
#define TABLE_SIZE 10

// Structure for a node in the linked list
typedef struct Node {
    char *key;
    struct Node *next;
} Node;

//Hash Function
unsigned int hash(const char * key){
    unsigned int hashValue = 0;

    for(int i = 0; key[i] != '\0'; i++){
        hashValue = 31 * hashValue + key[i];
    }

    return hashValue % TABLE_SIZE; //Modulo to fit within hash table size
}

// Function to create a new node
Node *createNode(const char *key) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    new_node->key = strdup(key);
    new_node->next = NULL;
    return new_node;
}

// Function to insert a key into the hash table
void insert(Node *hash_table[], const char *key) {
    unsigned int index = hash(key);
    if (hash_table[index] == NULL) {
        // No collision, create a new node
        hash_table[index] = createNode(key);
    } else {
        // Collision occurred, add the new node to the linked list
        Node *current = hash_table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = createNode(key);
    }
}

// Function to print the hash table
void printHashTable(Node *hash_table[]) {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d:", i);
        Node *current = hash_table[i];
        while (current != NULL) {
            printf(" -> %s", current->key);
            current = current->next;
        }
        printf("\n");
    }
}

char * strdup(const char * str){
    size_t len = strlen(str) + 1;
    char * new_str = malloc(len);
    
    if(new_str == NULL){
        return NULL;
    }

    return strcpy(new_str, str);
}

int main(){
    //Initialize the hash table
    Node * hashTable[HASH_SIZE] = {NULL};

    //Insert keys into the hash table
    insert(hashTable, "apple");
    insert(hashTable, "banana");
    insert(hashTable, "orange");
    insert(hashTable, "grape");
    insert(hashTable, "kiwi");

    // Print the hash table
    printHashTable(hashTable);

    // Free memory
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = hashTable[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }

    return EXIT_SUCCESS;
}