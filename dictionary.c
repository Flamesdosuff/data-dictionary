#include "dictionary.h"
void printNodes(Node *head) {
    Node *corre = head;
    int cont = 1; 
    printf("Comprobación de que se hayan guardado los nodos. A continuación los nodos guardados:\n");
    while (corre != NULL) {
        printf("Nodo #%d: %s\n", cont++, corre->Linea);
        corre = corre->sig; 
    }
}

void processNodes(Node *head) {
    Node *current = head;
    while (current != NULL) {
        const char *delimiter = strstr(current->Linea, "->");
        if (delimiter != NULL) {
            size_t idLength = delimiter - current->Linea;  
            strncpy(current->ID, current->Linea, idLength);
            current->ID[idLength] = '\0';                 
            strncpy(current->Produccion, delimiter + 2, sizeof(current->Produccion) - 1);
            current->Produccion[sizeof(current->Produccion) - 1] = '\0'; 
        } else {
            strcpy(current->ID, "N/A");
            strcpy(current->Produccion, "N/A");
        }
        printf("Nodo procesado: ID = %s, Producción = %s\n", current->ID, current->Produccion);
        current = current->sig;
    }
}


int initializeDataDictionary(const char* dictionaryName) {
    Node *cab = NULL; 
    Node *fin = NULL; 
    printf("Initializing Data Dictionary...\n");
    
    FILE *file = fopen(dictionaryName, "r");
    if (!file) {
        printf("Error opening file: %s\n", dictionaryName);
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
        strncpy(aux->Linea, line, sizeof(aux->Linea) - 1);
        aux->Linea[sizeof(aux->Linea) - 1] = '\0'; 

        if (cab == NULL) {
            cab = aux; 
        } else {
            fin->sig = aux;
        }
        fin = aux; 
    }

    fclose(file); 
    processNodes(cab);      
    printNodes(cab);     
    return 1;
}