#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//FUNCOES DE INTERFACE
void menu(){
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