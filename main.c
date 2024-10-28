#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    welcome();
    diviser();
    //MENU
    int option;
    do {
        menu();  
        scanf("%i", &option);

        switch (option) {
            case 1:
                diviser();
                printf("\nCarteira | Deposito\n");
                break;
            case 2:
                diviser();
                printf("\nComprar Instrumento\n");
                break;
            case 3:
                diviser();
                printf("\nLimpeza de Instrumento\n");
                break;
            case 4:
                diviser();
                printf("\nSair\n");
                break;
            default:
                diviser();
                printf("Opcaoo invalida. Tente novamente.\n");
                diviser();
                break;
        }
    } while (option != 4);

    return 0;
}