#include "dictionary.h"
#define MAX_PRODUCCION_LENGTH 100

void printNodes(Node *head) {
    Node *corre = head;
    int cont = 1;
    printf("Comprobación de que se hayan guardado los nodos. A continuación los nodos guardados:\n");
    
    while (corre != NULL) {
        printf("%d: ID = %s , Producción = %s\n", cont++, corre->ID, corre->Produccion);
        corre = corre->sig; 
    }
}

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

/*void PrintCicloNodes(Node *head) {
    Node *corre = head, *ori = head;

    while (ori != NULL) {
        printf("%s -> ", ori->ID);
        corre = ori;
        int firstProduction = 1;

        while (corre != NULL && strcmp(corre->ID, ori->ID) == 0) {
            char *produccion = corre->Produccion;
            int tieneID = 0;

            // Primer recorrido: buscar si hay coincidencia con el ID y, si hay, imprimir en llaves
            for (int i = 0; produccion[i] != '\0' && produccion[i] != '\r'; i++) {
                if (produccion[i] == ori->ID[0]) {
                    tieneID = 1;
                    if (!firstProduction) {
                        printf(" | ");
                    } else {
                        firstProduction = 0;
                    }
                    // Imprime con llaves la parte de la producción antes del ID
                    printf("{");
                    for (int j = 0; j < i; j++) {
                        putchar(produccion[j]);
                    }
                    printf("}");
                    break;
                }
            }

            // Segundo recorrido: imprime el resto normalmente si no contiene el ID
            if (!tieneID) {
                if (!firstProduction) {
                    printf(" | ");
                } else {
                    firstProduction = 0;
                }
                for (int i = 0; produccion[i] != '\0' && produccion[i] != '\r'; i++) {
                    putchar(produccion[i]);
                }
            } else {
                // Si ya imprimimos una parte entre llaves, imprime el resto de la producción después del ID
                for (int i = tieneID; produccion[i] != '\0' && produccion[i] != '\r'; i++) {
                    putchar(produccion[i]);
                }
            }
            corre = corre->sig;
        }
        printf("\n");
        ori = corre;
    }
}
*/
void PrintCicloNodes(Node *head) {
    Node *corre = head, *ori = head;

    while (ori != NULL) {
        printf("%s -> ", ori->ID);
        corre = ori;
        int firstProduction = 1;

        while (corre != NULL && strcmp(corre->ID, ori->ID) == 0) {
            char *produccion = corre->Produccion;
            int tieneID = 0;

            // Primer recorrido: buscar si hay coincidencia con el ID y, si hay, imprimir en llaves
            for (int i = 0; produccion[i] != '\0' && produccion[i] != '\r'; i++) {
                if (produccion[i] == ori->ID[0]) {
                    tieneID = 1;
                    if (!firstProduction) {
                        printf(" | ");
                    } else {
                        firstProduction = 0;
                    }
                    // Imprime con llaves la parte de la producción antes del ID
                    printf("{");
                    for (int j = 0; j < i; j++) {
                        putchar(produccion[j]);
                    }
                    printf("}");
                    break;
                }
            }
            if (!tieneID) {
                if (!firstProduction) {
                    printf(" | ");
                } else {
                    firstProduction = 0;
                }
                for (int i = 0; produccion[i] != '\0' && produccion[i] != '\r'; i++) {
                    putchar(produccion[i]);
                }
            } else {

                for (int i = tieneID+1; produccion[i] != '\0' && produccion[i] != '\r'; i++) {
                    putchar(produccion[i]);
                }
            }
            corre = corre->sig;
        }
        printf("\n");
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
    printNodes(cab);     
    PrintconsolidateNodes(cab); 
    PrintCicloNodes(cab);     
    return 1;
}
