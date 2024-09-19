#include "main.h"

int main(int argc, char** argv) {
    char name[50];

    printf("Enter a name of dictionary name")
    gets(name);   
    initializeDataDictionary(name);    
    return 0;
}
