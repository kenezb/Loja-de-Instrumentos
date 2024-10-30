#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdio.h>

// DADOS DO USUÁRIO
typedef struct {
    int id;
    char cpf[12];
    char password[6];
    float balanceReal;
    int userType; 
} User;

// INSTRUMENTOS E LIMPEZA
typedef struct {
    char name[50];
    float price;
} Instrument;

void buyInstrument(User *user);
void cleanInstrument(User *user);

// FUNÇÕES INTERFACE
void diviser();
void welcome();
void loginOrRegister(User *user);
void userMenu();
void adminMenu(); 

// FUNÇÕES REGISTRO E LOGIN
void loginUser(User *user);
void registerUser(User *user);

// FUNÇÃO CARTEIRA 
void depositReal(int userId);

// FUNÇÕES ADMINISTRATIVAS
void addInstrument();
void addCleaningPrice();
void removeInstrument();
void listUsers();
void resetUserInfo(char *currentCpf); 
void deleteAllInstruments(); 

#endif
