#include "main.h"

int main(int argc, char** argv) {
    char name[50];

    printf("Enter a name of dictionary name");
    fgets(name,50);   
    initializeDataDictionary(name);    
    return 0;
}
