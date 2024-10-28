#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//FUNCOES DE INTERFACE
void menu(int userId){
  printf("\nEscolha uma opcao:\n");
  diviser();
  printf("1 - Carteira | Deposito\n");
  printf("2 - Comprar instrumento\n");
  printf("3 - Limpeza de instrumento\n");
  printf("4 - Sair\n");
  diviser();
}

void diviser() { printf("------------------------------\n"); }

void welcome() {
  printf("INSTRUMENTOS\n");
  diviser();
  printf("A Melhor loja para o seu instrumento!\n");
}

void loginOrRegister(User *user) {
  int option = 0;
  printf("Faca LOGIN ou CADASTRO:\n");
  printf("1 - CADASTRO\n");
  printf("2 - LOGIN\n");
  diviser();
  printf("Digite sua escolha: ");
  scanf("%i", &option);
  if (option == 1)
    registerUser(user);
  else if (option == 2)
    loginUser(user);
  else {
    diviser();
    printf("\nOpcao invalida\n");
    diviser();
    loginOrRegister(user);
  }
}

//LOGIN OU REGISTRO
void loginUser(User *user) {
  char cpf[12];
  char password[6];
  int isUser = 0;
  User tempUser;

  printf("\nLOGIN\n");
  diviser();
  printf("Digite seu CPF (apenas numeros): ");
  scanf("%11s", cpf);

  printf("Digite sua senha (maximo 5 digitos): ");
  scanf("%5s", password);

  FILE *file = fopen("users.dat", "rb");
  if (!file) {
    printf("Erro.\n");
    return;
  }
  // PROCURA UM USUÁRIO COM O CPF E SENHA 
  while (fread(&tempUser, sizeof(User), 1, file) == 1) {
          if (strcmp(tempUser.cpf, cpf) == 0 && strcmp(tempUser.password, password) == 0) {
              *user = tempUser; 
              isUser = 1;
              break;
          }
      }

      fclose(file);

      if (isUser) {
          diviser();
          printf("Bem Vindo!\n");
          diviser();
      } else {
          diviser();
          printf("CPF ou Senha incorretos.\n");
          diviser();
          loginOrRegister(user);
      }
}

void registerUser(User *user) {
    FILE *file = fopen("users.dat", "rb"); 
    if (!file) {
        file = fopen("users.dat", "wb");  
        if (!file) {
            printf("Erro.\n");
            return;
        }
    }

    int userCount = 0;
    User tempUser;

    while (fread(&tempUser, sizeof(User), 1, file) == 1) {
        userCount++;
    }
    fclose(file);

    user->id = 1; 
    file = fopen("users.dat", "rb");  
    if (file != NULL) {
        while (fread(&tempUser, sizeof(User), 1, file) == 1) {
            if (tempUser.id >= user->id) {
                user->id = tempUser.id + 1; 
            }
        }
        fclose(file);
    }

  
    printf("\nCADASTRO\n");
    diviser();
    printf("Digite seu CPF (apenas numeros): ");
    scanf("%11s", user->cpf);  

    printf("Digite sua senha (maximo 5 digitos): ");
    scanf("%5s", user->password);  

    user->balanceReal = 0.0;
  
    file = fopen("users.dat", "ab");
    if (!file) {
        printf("Erro.\n");
        return;
    }

    fwrite(user, sizeof(User), 1, file);
    fclose(file);

    printf("\nUsuario Registrado e Logado!\n");
    diviser();
}

//FUNCAO CARTEIRA
void depositReal(int userId) {
  User user;
  int found = 0;
  float amount = 0;
  
  FILE *file = fopen("users.dat", "r+b"); 
  if (file == NULL) {
      printf("Erro ao verificar saldo\n");
      return;
  }

  while (fread(&user, sizeof(User), 1, file) == 1) {
      if (user.id == userId) { 
          found = 1;
          break;
      }
  }
  if (!found) {
      printf("Usuario nao encontrado.\n");
      fclose(file);
      return;
  }
  diviser();
  printf("Saldo Atual: R$%.2f\n", user.balanceReal);
  
  
  printf("\nQual valor do deposito? | Digite 0 para cancelar.\n");
  diviser();
  printf("R$ ");
  scanf("%f", &amount);
  diviser();
  
  if (amount == 0){
    return;
  }
  if (amount < 0) {
      printf("Seu deposito nao pode menor ou igual a zero.\n");
      fclose(file);
      depositReal(userId); 
  } else {
      user.balanceReal += amount;
      //REESCREVE NO ARQUIVO
      fseek(file, -sizeof(User), SEEK_CUR);
      fwrite(&user, sizeof(User), 1, file);
      printf("Saldo Atualizado: R$ %.2f\n", user.balanceReal);
      diviser();
      
      fclose(file);
  }
}

//INSTRUMENTOS 
void buyInstrument(User *user) {
    float* Saldo = &user->balanceReal;

    //INSTRUMENTOS Á VENDA NA LOJA
    Instrument instruments[] = {
        {"Violao", 800.0},
        {"Guitarra", 1000.0},
        {"Piano", 1500.0},
        {"Bateria", 800.0},
        {"Flauta", 200.0},
        {"Violino", 1300.0},
        {"Cavaquinho", 600.0},
        {"Pandero", 300.0},
        
    };
    printf("Saldo Atual: R$%.2f\n", *Saldo);
    int numInstruments = sizeof(instruments) / sizeof(instruments[0]);

    printf("INSTRUMENTOS A VENDA:\n");
    for (int i = 0; i < numInstruments; i++) {
        printf("%d - %s - R$ %.2f\n", i + 1, instruments[i].name, instruments[i].price);
    }

    int choice;
    printf("Escolha seu instrumento (ou 0 para cancelar): ");
    diviser();
    scanf("%d", &choice);
    //CANCELA COMPRA
    if (choice == 0) {
        return; 
    }

    if (choice < 1 || choice > numInstruments) {
        printf("Escolha invalida!\n");
        return;
    }

    Instrument selectedInstrument = instruments[choice - 1];

    diviser();

    //MOVIMENTAÇÕES NO SALDO
    if (user->balanceReal >= selectedInstrument.price) {
        user->balanceReal -= selectedInstrument.price;
        //MOSTRA SUA COMPRA
        printf("Voce comprou %s por R$ %.2f!\n", selectedInstrument.name, selectedInstrument.price);
        //MOSTRA NOVO
        printf("Saldo restante: R$ %.2f\n", user->balanceReal);
        diviser();
        //ATUALIZA O SALDO
        FILE *file = fopen("users.dat", "r+b"); 
        if (file == NULL) {
            printf("Erro.\n");
            return;
        }

        User tempUser;
        int found = 0;

        //LOCALIZA USUARIO
        while (fread(&tempUser, sizeof(User), 1, file) == 1) {
            if (tempUser.id == user->id) { 
                found = 1;
                fseek(file, -sizeof(User), SEEK_CUR); 
                fwrite(user, sizeof(User), 1, file);
                break;
            }
        }
        if (found) {
            printf("");
        } else {
            printf("Usuário não encontrado.\n");
        }

        fclose(file);
    } else {
        printf("Saldo insuficiente para comprar %s. Saldo atual: R$ %.2f\n", selectedInstrument.name, user->balanceReal);
    }
}