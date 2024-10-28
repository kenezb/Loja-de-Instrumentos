#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    User user;
    welcome();
    diviser();
    //ESCOLHA CADASTRO OU LOGIN
    loginOrRegister(&user);
    //MENU
    int option;
    do {
        menu(user.id);  
        scanf("%i", &option);

        switch (option) {
            case 1:
                depositReal(user.id);
                break;
            case 2:
                buyInstrument(&user);
                break;
            case 3:
                diviser();
                printf("\nLimpeza de Instrumento\n");
                break;
            case 4:
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