#include "dictionary.h"

void printNodes(Node *head) {
    Node *corre = head;
    int cont = 1; 
    printf("comprobacion de que se haya guardado los nodos a continuacion los nodos guardados: \n");
    while (corre != NULL) {
        printf("nodo #%d: %s\n", cont++, corre->Linea);
        printf("el ID de el nodo #%d: es %s\n", cont, corre->ID);
        corre = corre->sig; 
    }
}

int initializeDataDictionary(const char* dictionaryName) {
    Node *cab = NULL; 
    Node *fin = NULL; 
    printf("Initializing Data Dictionary...\n");
    FILE *file = fopen(dictionaryName, "r");
    if (!file) {
        printf("Error to open file: %s\n", dictionaryName);
        return -1;
    }

    char line[MAX_LINE_LENGTH];  
    char ID[MAX_LINE_LENGTH]; 
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';        
        Node *aux = malloc(sizeof(Node));      
        if (aux == NULL) {
            printf("Error allocating memory for node\n");
            fclose(file);
            return -1;
        }
         //Separar el Id de todo el nodo
        fgets(ID,sizeof(line),file);
        ID[strcspn(ID, "-")] = '\0';  
        //
        aux->sig = NULL; 
        strncpy(aux->Linea, line, sizeof(aux->Linea) - 1);
        aux->Linea[sizeof(aux->Linea) - 1] = '\0'; 
        strncpy(aux->ID, ID, sizeof(aux->ID) - 1);
        aux->ID[sizeof(aux->ID) - 1] = '\0'; 
        if (cab == NULL) {
            cab = aux; 
        } else {
            fin->sig = aux;
        }
        fin = aux; 
    }
    // Separar los ID y los Produciones


    fclose(file);
    printNodes(cab);

    return 1;
}
//const char *delimiter = strstr(line,"->");
// ddespues para el otro seria
// strcpy(produccion, delimiter+2) se salta el "->"