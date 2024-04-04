#include <stdio.h>
#include "structs.h"


int buscaCliente(int cpf, Cliente clientes[], int total);
int debitar(Cliente *clientes, float valor, int senha);
int novoCliente(Cliente clientes[], int *total);
int apagaCliente(Cliente clientes[], int *total);
int debito(Cliente clientes[], int *total);
int deposito(Cliente clientes[], int *total);
int transferenciaConta(Cliente clientes[], int *total);
int emprestimo(Cliente clientes[], int *total);
void imprimeCliente(Cliente clientes[], int total);
void cadastraOperacoes( Cliente c[], float valores, float taxas, float saldos);
int extrato(Cliente *clientes, int *total);