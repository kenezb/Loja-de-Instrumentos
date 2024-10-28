#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdio.h>

//DADOS USUARIO 
typedef struct {
    int id;
    char cpf[12];
    char password[6];
    float balanceReal;
} User;

//FUNCOES DE INTERFACE
void diviser();
void welcome();
void menu(int userId);
void loginOrRegister(User *user);

//FUNCOES LOGIN E REGISTRO
void loginUser(User *user);
void registerUser(User *user);

#endif