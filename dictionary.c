#include "dictionary.h"
#define MAX_PRODUCCION_LENGTH 500
#define MAX_RECORDS 50
BufferRecord bufferRecords[MAX_BUFFERS];  
int bufferCount = 0;  

void printNodes(Node *head) {
    Node *corre = head;
    int cont = 1;
    printf("Comprobación de que se hayan guardado los nodos. A continuación los nodos guardados:\n");
    
    while (corre != NULL) {
        printf("%d: ID = %s , Producción = %s\n", cont++, corre->ID, corre->Produccion);
        corre = corre->sig; 
    }
}
int recordCount = 0; 

void processNodes(Node *head) {
    Node *current = head;
    while (current != NULL) {
        const char *delimiter = strstr(current->Linea, "->");
        if (delimiter != NULL) {
            size_t idLength = (size_t)(delimiter - current->Linea);  
            strncpy(current->ID, current->Linea, idLength);
            current->ID[idLength] = '\0';                 
            strncpy(current->Produccion, delimiter + 2, sizeof(current->Produccion) - 1);
            current->Produccion[sizeof(current->Produccion) - 1] = '\0'; 
        } else {
            strcpy(current->ID, "NULL");
            strcpy(current->Produccion, "NULL");
        }
        current = current->sig;
    }
}




void PrintconsolidateNodes(Node *head) {
    Node *corre = head, *ori = head;
    while (ori != NULL) {
        printf("%s -> ", ori->ID); 
        corre = ori;  
        int firstProduction = 1;  
        while (corre != NULL && strcmp(corre->ID, ori->ID) == 0) {
            char *produccion = corre->Produccion;
            if (!firstProduction) {
                printf(" | "); 
            } else {
                firstProduction = 0;
            }
            for (int i = 0; produccion[i] != '\0' && produccion[i] != '\r'; i++) {
                if (produccion[i] == '\n') {
                    break;  
                }
                putchar(produccion[i]);  
            }
            corre = corre->sig;  
        }
        printf("\n");  
        ori = corre;
    }
}

void GuardarStrings(char *ID, char *buffer) {
        if (ID == NULL || buffer == NULL) {
        printf("Error: ID o buffer son nulos\n");
        return;
    }
    if (bufferCount < MAX_BUFFERS) {  // Verifica que hay espacio para un nuevo buffer
        strncpy(bufferRecords[bufferCount].ID, ID, sizeof(bufferRecords[bufferCount].ID) - 1);
        bufferRecords[bufferCount].ID[sizeof(bufferRecords[bufferCount].ID) - 1] = '\0'; // Para evitar overflow
        strncpy(bufferRecords[bufferCount].buffer, buffer, BUFFER_SIZE - 1);
        bufferRecords[bufferCount].buffer[BUFFER_SIZE - 1] = '\0';
        bufferCount++;
    } else {
        printf("No hay espacio para almacenar más buffers.\n");
    }
}


int checaRecursividad(Node *head, char *id, char *cadena) {
    Node *corre = head;
    int cont = 0;
    char buffer[BUFFER_SIZE] = ""; 
    printf("\n");

    if (corre == NULL) {
        return cont; // Retorna 0 si la lista está vacía
    }

    printf("%s -> ", corre->ID);
    int firstProduction = 1;

    while (corre != NULL) {
        int foundID = 0;

        if (!firstProduction) {
            printf(" | ");
            strcat(buffer, " | "); 
        } else {
            firstProduction = 0;
        }

        for (int j = 0; corre->Produccion[j] != '\0' && corre->Produccion[j] != '\r'; j++) {
            if (corre->Produccion[j] == id[0]) {
                foundID = 10; 
                cont = 10;
                printf(" %s", cadena);
                strcat(buffer, cadena); 
            }
            if (!foundID) {
                putchar(corre->Produccion[j]);
                strncat(buffer, &corre->Produccion[j], 1); 
            }
        }

        corre = corre->sig; // Avanza al siguiente nodo
    }  
    if (head != NULL) { 
        GuardarStrings(head->ID, buffer);
        GuardarStrings(id, cadena);
    }

    return cont;
}


void PrintCicloabajoarriba(Node *head) {
    Node *corre = head;
    int count = 0; 
    while (corre != NULL) {
        corre = corre->sig;
        count++;
    }
    if (count < 2) {
        printf("No hay suficientes nodos para realizar la operación.\n");
        return;
    }
    corre = head;
    Node *nodos[count]; 
    int index = 0;

    while (corre != NULL) {
        nodos[index++] = corre;
        corre = corre->sig; 
    }

    for (int i = count - 1; i >= 0; i--) { 
        Node *currentNode = nodos[i];
        char buffer[BUFFER_SIZE] = ""; 
        int firstProduction = 1; 
        int idFound = 0; 

        for (int k = 0; k < bufferCount; k++) {
            if (strcmp(bufferRecords[k].ID, currentNode->ID) == 0) {
                idFound = 1; 
                break; 
            }
        }
        if (!idFound) {
            for (int j = 0; currentNode->Produccion[j] != '\0' && currentNode->Produccion[j] != '\r'; j++) {
                char currentChar = currentNode->Produccion[j]; 

                int isID = 0;

                for (int k = 0; k < bufferCount; k++) {
                    if (bufferRecords[k].ID[0] == currentChar) {
                        isID = 1; 
                        if (!firstProduction) {
                            strcat(buffer, " | "); 
                        } else {
                            firstProduction = 0;
                        }
                        strcat(buffer, "{"); 
                        strcat(buffer, bufferRecords[k].buffer); 
                        strcat(buffer, "}"); 
                        break; 
                    }
                }
                if (!isID) {
                    if (!firstProduction) {
                        strcat(buffer, " | "); 
                    } else {
                        firstProduction = 0; 
                    }
                    strncat(buffer, &currentChar, 1); 
                }
            }
            GuardarStrings(currentNode->ID, buffer);
        }
    }
}

void MostrarBuffers() {
    for (int i = 0; i < bufferCount; i++) {
        printf("%s -> %s\n", bufferRecords[i].ID, bufferRecords[i].buffer);
    }
}



void PrintCicloNodes(Node *head) {
    Node *corre = head, *ori = head;

    while (ori != NULL) {
        printf("%s -> ", ori->ID);
        char buffer[BUFFER_SIZE] = ""; 
        corre = ori;
        int firstProduction = 1;
        int tieneID = 0;

        while (corre != NULL && strcmp(corre->ID, ori->ID) == 0) {
            char *produccion = corre->Produccion;

            for (int i = 0; produccion[i] != '\0' && produccion[i] != '\r'; i++) {
                if (produccion[i] == ori->ID[0]) {
                    tieneID = 1;
                    if (!firstProduction) {
                        printf(" | ");
                        strcat(buffer, " | ");
                    } else {
                        firstProduction = 0;
                    }
                    printf("{");
                    strcat(buffer, "{");
                    for (int j = 0; j < i; j++) {
                        putchar(produccion[j]);
                        strncat(buffer, &produccion[j], 1);
                    }
                    printf("}");
                    strcat(buffer, "}");
                    break;
                }
            }

            if (!tieneID) {
                if (!firstProduction) {
                    printf(" | ");
                    strcat(buffer, " | ");
                } else {
                    firstProduction = 0;
                }
                for (int i = 0; produccion[i] != '\0' && produccion[i] != '\r'; i++) {
                    putchar(produccion[i]);
                    strncat(buffer, &produccion[i], 1);
                }
            } else {
                for (int i = tieneID + 1; produccion[i] != '\0' && produccion[i] != '\r'; i++) {
                    putchar(produccion[i]);
                    strncat(buffer, &produccion[i], 1);
                }
            }

            corre = corre->sig;
        }

        printf("\n");
        if (tieneID) {
            int cont = checaRecursividad(corre, ori->ID, buffer);
            while (corre != NULL && strcmp(corre->ID, corre->ID) == 0) {
                corre = corre->sig;
            }
        }

        ori = corre;
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
        printf("LECTURA DE ARCHIVO");     
    printNodes(cab); 
        printf("COCATENADO\n");    
    PrintconsolidateNodes(cab);  
        printf("ARRIBA PARA AVAJO\n");

          PrintCicloNodes(cab);  

        printf("ABAJO PARA ARRIBA\n");

    PrintCicloabajoarriba(cab);  
    MostrarBuffers();
    return 1;
}
