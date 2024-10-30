#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void diviser() { printf("------------------------------\n"); }

void adminMenu() {
    printf("\nMenu do Administrador:\n");
    diviser();
    printf("1 - Adicionar Instrumento\n");
    printf("2 - Adicionar Preco de Limpeza\n");
    printf("3 - Remover Instrumento\n");
    printf("4 - Listar Usuarios\n");
    printf("5 - Remover Todos os Usuarios\n");
    printf("6 - Remover Todos os Intrumentos\n");
    printf("\n");
    printf("9 - Sair\n");
    diviser();
}

void userMenu() {
    printf("\nMenu do Usuario:\n");
    diviser();
    printf("1 - Carteira | Deposito\n");
    printf("2 - Comprar instrumento\n");
    printf("3 - Limpeza de instrumento\n");
    printf("\n");
    printf("9 - Sair\n");
    diviser();
}
void welcome() {
  printf("INSTRUMENTOS\n");
  diviser();
  printf("A Melhor loja para o seu instrumento!\n");
}

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
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

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
        if (user->userType == 1) {
            printf("Bem-vindo, Administrador!\n");
        } else {
            printf("Bem-vindo, Usuario!\n");
        }
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
            printf("Erro ao abrir o arquivo.\n");
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

    printf("Digite sua senha (maximo 5 digitos):");
    scanf("%5s", user->password);

    printf("\nDigite o tipo de usuario\n");
    diviser();
    printf("0 para comum\n1 para administrador\n");
    scanf("%d", &user->userType);

    user->balanceReal = 0.0;

    file = fopen("users.dat", "ab");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fwrite(user, sizeof(User), 1, file);
    fclose(file);

    printf("\nUsuario Registrado e Logado!\n");
    diviser();
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

void buyInstrument(User *user) {
    float* Saldo = &user->balanceReal;

    Instrument instruments[100];
    int numInstruments = 0;

    FILE *file = fopen("instruments.dat", "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo de instrumentos.\n");
        return;
    }

    while (fread(&instruments[numInstruments], sizeof(Instrument), 1, file) == 1) {
        numInstruments++;
    }
    fclose(file);

    printf("Saldo Atual: R$%.2f\n", *Saldo);

    if (numInstruments == 0) {
        printf("Não há instrumentos disponíveis para venda.\n");
        return;
    }

    printf("INSTRUMENTOS A VENDA:\n");
    for (int i = 0; i < numInstruments; i++) {
        printf("%d - %s - R$ %.2f\n", i + 1, instruments[i].name, instruments[i].price);
    }

    int choice;
    printf("Escolha seu instrumento (ou 0 para cancelar):\n");
    diviser();
    scanf("%d", &choice);

    // CANCELA COMPRA
    if (choice == 0) {
        return; 
    }

    if (choice < 1 || choice > numInstruments) {
        printf("Escolha inválida!\n");
        return;
    }

    Instrument selectedInstrument = instruments[choice - 1];

    diviser();

    // MOVIMENTAÇÕES NO SALDO
    if (user->balanceReal >= selectedInstrument.price) {
        user->balanceReal -= selectedInstrument.price;

        // MOSTRA SUA COMPRA
        printf("Você comprou %s por R$ %.2f!\n", selectedInstrument.name, selectedInstrument.price);
        // MOSTRA NOVO SALDO
        printf("Saldo restante: R$ %.2f\n", user->balanceReal);
        diviser();
        // ATUALIZA O SALDO
        file = fopen("users.dat", "r+b"); 
        if (file == NULL) {
            printf("Erro ao abrir o arquivo de Usuarios.\n");
            return;
        }

        User tempUser;
        int found = 0;

        // LOCALIZA Usuario
        while (fread(&tempUser, sizeof(User), 1, file) == 1) {
            if (tempUser.id == user->id) { 
                found = 1;
                fseek(file, -sizeof(User), SEEK_CUR); 
                fwrite(user, sizeof(User), 1, file);
                break;
            }
        }
        if (found) {
            printf("Saldo atualizado com sucesso!\n");
        } else {
            printf("Usuario não encontrado.\n");
        }

        fclose(file);
    } else {
        printf("Saldo insuficiente para comprar %s.\nSaldo atual: R$ %.2f\n", selectedInstrument.name, user->balanceReal);
    }
}
void addInstrument() {
    Instrument newInstrument;
    printf("Digite o nome do instrumento: ");
    scanf("%49s", newInstrument.name);  // Limite de 49 caracteres + '\0'
    
    printf("Digite o preço do instrumento: ");
    scanf("%f", &newInstrument.price);

    // Adiciona o instrumento ao arquivo
    FILE *file = fopen("instruments.dat", "ab"); // Abre para adicionar no final
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fwrite(&newInstrument, sizeof(Instrument), 1, file);
    fclose(file);

    printf("Instrumento adicionado com sucesso!\n");
}

void cleanInstrument(User *user) {
    float* Saldo = &user->balanceReal;

    Instrument instruments[] = {
        {"Violao", 80.0},
        {"Guitarra", 100.0},
        {"Piano", 150.0},
        {"Bateria", 80.0},
        {"Flauta", 20.0},
        {"Violino", 130.0},
        {"Cavaquinho", 60.0},
        {"Pandero", 30.0},
        
    };
    printf("Saldo Atual: R$%.2f\n", *Saldo);
    int numInstruments = sizeof(instruments) / sizeof(instruments[0]);

    printf("PRECOS DA LIMPEZA:\n");
    for (int i = 0; i < numInstruments; i++) {
        printf("%d - %s - R$ %.2f\n", i + 1, instruments[i].name, instruments[i].price);
    }

    int choice;
    printf("Escolha seu instrumento a limpar (ou 0 para cancelar): ");
    diviser();
    scanf("%d", &choice);
    //CANCELA COMPRA DE LIMPEZA
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
            printf("Usuario não encontrado.\n");
        }

        fclose(file);
    } else {
        printf("Saldo insuficiente para limpar seu instrumento %s. Saldo atual: R$ %.2f\n", selectedInstrument.name, user->balanceReal);
    }
}

void addCleaningPrice() {
    printf("Adicionar preco de limpeza (Funcionalidade a ser implementada)\n");
}

void removeInstrument() {
    char name[50];
    printf("Digite o nome do instrumento que deseja remover: ");
    scanf("%49s", name);

    FILE *file = fopen("instruments.dat", "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Instrument tempInstruments[100]; 
    int count = 0;

    while (fread(&tempInstruments[count], sizeof(Instrument), 1, file) == 1) {
        count++;
    }
    fclose(file);

    file = fopen("instruments.dat", "wb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int removed = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(tempInstruments[i].name, name) != 0) {
            fwrite(&tempInstruments[i], sizeof(Instrument), 1, file);
        } else {
            removed = 1;
        }
    }
    fclose(file);

    if (removed) {
        printf("Instrumento removido com sucesso!\n");
    } else {
        printf("Instrumento não encontrado!\n");
    }
}

void listUsers() {
    FILE *file = fopen("users.dat", "rb"); 
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de Usuarios.\n");
        return;
    }

    printf("Lista de Usuarios:\n");
    printf("---------------------------------\n");

    User user;
    int userCount = 0;

    while (fread(&user, sizeof(User), 1, file) == 1) {
        printf("CPF: %s\n", user.cpf);
        printf("Tipo de Usuario: %s\n", user.userType ? "Administrador" : "Usuario Comum");
        printf("---------------------------------\n");
        userCount++;
    }

    if (userCount == 0) {
        printf("Nenhum Usuario encontrado.\n");
    }

    fclose(file);
}

void resetUserInfo(char *currentCpf) {
    FILE *file = fopen("users.dat", "rb+"); 
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file) == 1) {
    
        if (strcmp(user.cpf, currentCpf) != 0) {
            memset(&user, 0, sizeof(User));
            fseek(file, -sizeof(User), SEEK_CUR);
            fwrite(&user, sizeof(User), 1, file);
        }
    }

    fclose(file);
    printf("Informações de usuários (exceto do usuário atual) foram zeradas.\n");
}

// Função para apagar todos os dados dos instrumentos
void deleteAllInstruments() {
    FILE *file = fopen("instruments.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de instrumentos.\n");
        return;
    }

    fclose(file);
    printf("Todos os dados dos instrumentos foram apagados.\n");
}