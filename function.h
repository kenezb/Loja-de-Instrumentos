#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdio.h>


//DADOS DO USUÁRIO
typedef struct {
    int id;
    char cpf[12];
    char password[6];
    float balanceReal;
} User;

//INSTRUMENTOS E LIMPEZA
typedef struct {
    char name[50];
    float price;
} Instrument;


void buyInstrument(User *user);
void cleanInstrument(User *user);



//FUNCOES INTERFACE
void diviser();
void welcome();
void loginOrRegister(User *user);
void menu(int userId);

//FUNCOES REGISTRO E LOGIN
void loginUser(User *user);
void registerUser(User *user);

//FUNCAO CARTEIRA 
void depositReal(int userId);


#endif