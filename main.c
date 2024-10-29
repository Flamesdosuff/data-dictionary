#include "dictionary.h"

int main(int argc, char** argv) {
    char name[50];

    printf("Enter the name of the .txt file to process (utilizar gramatica1.txt para el ejemplo): ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    if (strstr(name, ".txt") == NULL) {
        printf("Error: The file must have a .txt extension.\n");
        return -1;
    }
    int result = initializeDataDictionary(name);
    
    if (result == -1) {
        return -1; 
    }

    return 0;
}
