#include "main.h"
#include <string.h>

int main(int argc, char** argv) {
    char name[50];

    printf("Enter the name of the .txt file to process (utilizar gramatica1.txt para el ejemplo): ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';

    if (strstr(name, ".txt") == NULL) {
        printf("Error: The file must have a .txt extension.\n");
        return -1;
    }
    initializeDataDictionary(name);

    /*funciones que hay que implementear al proyecto para perfeccionar el git
    
    void appendNode(Node **head, const char *line)
    {
        Node *newNode = createNode(line);
        if(*head == NULL)
    }

    Node* createNode(cnst char *line)
    {
        Node *newNode = (node*)malloc (sizeof(node));
        newNode -> 
    }
    void freelinkedlink(Node *head)
    Node createlinkedlink(FILE *file)

    */

    return 0;
}






