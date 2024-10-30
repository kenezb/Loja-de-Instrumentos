#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    User user;
    welcome();
    diviser();
    loginOrRegister(&user);

    int option;
    do {
        if (user.userType == 1) {
            adminMenu();
            scanf("%i", &option);
           switch (option) {
            case 1:
                addInstrument();
                break;
            case 2:
                addCleaningPrice();
                break;
            case 3:
                removeInstrument();
                break;
            case 4:
                listUsers();
                break;
            case 5:
                resetUserInfo(user.cpf);
                break;
            case 6:
                deleteAllInstruments();
                break;
            case 9:
                printf("Encerrando Sessao...\n");
                break;
            default:
                diviser();
                printf("Opcao invalida. Tente novamente.\n");
                diviser();
                break;
                }
        } else { 
            userMenu();
            scanf("%i", &option);
            switch (option) {
                case 1:
                    depositReal(user.id);
                    break;
                case 2:
                    buyInstrument(&user);
                    break;
                case 3:
                    cleanInstrument(&user);
                    break;
                case 9:
                    printf("Encerrando Sessao...\n");
                    break; 
                default:
                    diviser();
                    printf("Opcao invalida. Tente novamente.\n");
                    diviser();
                    break;
            }
        }
    } while (option != 9 && option != 10); 

    return 0;
}