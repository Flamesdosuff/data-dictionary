#include "dictionary.h"

void initializeDataDictionary(const char "diccionaryName") {
    long mainHeader = -1;
    printf("Initializing Data Dictionary...\n");
    FILE *dictionary = fopen("diccionario.dat","w+");
    fwrite(&mainHeader,sizeof(mainHeader),1,dictionary);
    long currentDir = ftell(dictionary);
    
    
}
