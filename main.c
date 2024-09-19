#include "main.h"

int main(int argc, char** argv) {

    initializeDataDictionary();
    FILE *dictionary = fopen("diccionario.dat","w+");
    
    return 0;
}
