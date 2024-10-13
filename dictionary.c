#include "dictionary.h"

int initializeDataDictionary(const char diccionaryName) {
    long mainHeader = Empty_Pointer;
    int stringsToSave = 0;


    printf("Initializing Data Dictionary...\n");

    FILE *dictionary = fopen("diccionario.dat","w+");

    fwrite(&mainHeader,sizeof(mainHeader),1,dictionary);

    printf("How many strings would you like to save?");
    scanf("%d",&stringsToSave);

    for(int i = 0; i<stringsToSave; i++)
    {
        Node currentNode;
        currentNode.next = Empty_Pointer;
        printf("Enter a value for node #%d",i);
        scanf("%s[^\n]",currentNode.value);
        fwrite(&currentNode,sizeof(currentNode),1,dictionary);
    }

    return 1;
}
