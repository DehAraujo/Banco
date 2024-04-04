#include <stdio.h>
#include <time.h>
#define MAX_CLIENTES 100

typedef struct{
  char data[11];
  float valor;
  float taxa;
  float saldo;
}Operacao;

typedef struct{
  char nome[50];
  int cpf;
  char tipoConta[50];
  float valor;
  int senha;
  Operacao operacoes[1000];
  int posOp;
}Cliente; 



