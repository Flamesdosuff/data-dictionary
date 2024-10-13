#include "dictionary.h"

// Función para imprimir los nodos de la lista
void printNodes(Node *head) {
    Node *corre = head;
    int cont = 1; 
    printf("comprobacion de que se haya guardado los nodos a continuacion los nodos guardados: \n");
    while (corre != NULL) {
        printf("nodo #%d: %s\n", cont++, corre->value);
        corre = corre->sig; 
    }
}

int initializeDataDictionary(const char* dictionaryName) {
    Node *cab = NULL; // Variable para la cabeza de la lista
    Node *fin = NULL; // Variable para el último nodo
    printf("Initializing Data Dictionary...\n");
    FILE *file = fopen(dictionaryName, "r");
    if (!file) {
        printf("Error to open file: %s\n", dictionaryName);
        return -1;
    }

    char line[MAX_LINE_LENGTH];  
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        Node *aux = malloc(sizeof(Node));
        if (aux == NULL) {
            printf("Error allocating memory for node\n");
            fclose(file);
            return -1;
        }
        aux->sig = NULL; 
        strncpy(aux->value, line, sizeof(aux->value) - 1);
        aux->value[sizeof(aux->value) - 1] = '\0'; 
        if (cab == NULL) {
            cab = aux; 
        } else {
            fin->sig = aux;
        }
        fin = aux; 
    }

    fclose(file);
    printNodes(cab);

    return 1;
}
