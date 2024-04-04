#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Faz busca do cliente pelo cpf indicado.
int buscaCliente(int cpf, Cliente clientes[], int total) {
  for (int i = 0; i < total; i++) {
    if (clientes[i].cpf == cpf) {
      return i; //cpf encontrado
    }
  }
  return -1;
  printf("Cpf não encontrado"); // cliente não encontrado
}
//Função para guardar todas as transações feitas pelo cliente.
void cadastraOperacoes(float valores, float taxas, float saldos,
                       Cliente *cliente, char data[11]) {
  int pos = cliente->posOp;
  cliente->operacoes[pos].valor = valores;
  cliente->operacoes[pos].taxa = taxas;
  cliente->operacoes[pos].saldo = saldos;
  strcpy(cliente->operacoes[pos].data, data);
  cliente->posOp = cliente->posOp + 1;
}

// // Realiza a operação de depósito
int depositar(Cliente *cliente, float valor) {
  cliente->valor += valor; // cliente->valor = saldo

  Operacao *o = &cliente->operacoes[cliente->posOp];
  char data[11];
  float taxa = 0;
  
  o->taxa = taxa;
  o->valor = valor;
  o->saldo = cliente->valor;
  strcpy(o->data, data);
  cliente->posOp = cliente->posOp + 1;
  //Chama a função cadastraOperacoes para guardar os valores das transacoes.
  cadastraOperacoes(o->valor, o->taxa, o->saldo, cliente, o->data); 
  return 0; // debito realizado com sucesso
}
// Realiza a função de débito, verifica a senha e o tipo de conta comum ou plus para aplicação das taxas
int debitar(Cliente *clientes, int senha, float valor) {
  float taxa, limite;
  if (clientes->senha != senha) {
    printf("Clientes ->senha %d", clientes->senha);
    printf(" senha %d", senha);
    return 1; // senha incorreta
  }
  if (strcmp(clientes->tipoConta, "comum")) {
    taxa = 0.05;
    limite = -1000.0;
  } else { // se não for comum, deve ser do tipo plus
    taxa = 0.03;
    limite = -5000.0;
  }

  float valor_debitar = valor + valor * taxa;
  if (clientes->valor - valor_debitar < limite)
    return 2; // saldo insuficiente

  clientes->valor -= valor_debitar;

  Operacao *o = &clientes->operacoes[clientes->posOp];
  char data[11];

  printf("Informe a data no formato dd/mm/aaaa: ");
  scanf("%s", data); 
  strcpy(o->data, data); //Guarda a data da transação
  o->taxa = taxa;
  o->valor = valor;
  o->saldo = clientes->valor;
  clientes->posOp = clientes->posOp + 1;
  //Chama a função cadastraOperacoes para guardar os valores das transacoes.
  cadastraOperacoes(o->valor, o->taxa, o->saldo, clientes, o->data);
  return 0; // debito realizado com sucesso
}
// Função para listar os clientes
void imprimeCliente(Cliente clientes[], int total) {
  for (int i = 0; i < total; i++) {
    printf("Nome: %s\n", clientes[i].nome);
    printf("CPF: %d\n", clientes[i].cpf);
    printf("Tipo de conta: %s\n", clientes[i].tipoConta);
    printf("Valor Inicial: %.2f\n", clientes[i].valor);
    printf("Senha: %d\n", clientes[i].senha);
  }
}
// Função para cadastrar novo cliente
int novoCliente(Cliente clientes[], int *total) {
  if (*total >= MAX_CLIENTES) {
    return 1;
  }
  //Procura cliente pelo CPF para verificar se já é cadastrado.
  int cpf, busCpf;
  printf("Entre com o CPF: ");
  scanf("%d", &cpf);
  busCpf = buscaCliente(cpf, clientes, *total);
  if (busCpf >= 0) {
    printf("Cpf já cadastrado.");
    return 2;
  }
//Cadastra um novo cliente
  clientes[*total].cpf = cpf;
  char tmp;
  scanf("%c", &tmp);
  printf("Informe o nome completo: ");
  scanf("%[^\n]s", clientes[*total].nome);

  printf("Informe o tipo de conta: ");
  scanf("%s", clientes[*total].tipoConta);

  printf("Informe o valor: ");
  scanf("%f", &clientes[*total].valor);

  printf("Informe a senha: ");
  scanf("%d", &clientes[*total].senha);
  *total = *total + 1;
  imprimeCliente(clientes, *total);

  char data[11];
  printf("Informe a data no formato: dd/mm/aaaa: ");
  scanf("%s", data);
  //Chama a função cadastraOperacoes para guardar os valores das transacoes.
  cadastraOperacoes(clientes[*total].valor, 0, clientes[*total].valor,
                    &clientes[*total], data);
  return 0;
}
// Função para apagar cliente
int apagaCliente(Cliente clientes[], int *total) {

  int cpf, pos;
  printf("Informe o CPF: ");
  scanf("%d", &cpf);
//Procura cliente pelo CPF
  pos = buscaCliente(cpf, clientes, *total);
  printf("%d", pos);

  // Teste para verificar se CPF está cadastrado.
  if (pos == -1) {
    return 1; // Cliente nao encontrado.
  }

  // Apaga cliente do array
  for (int i = pos; i < *total - 1; i++) {

    clientes[i].cpf = clientes[i + 1].cpf;
    clientes[i].valor = clientes[i + 1].valor;
    clientes[i].senha = clientes[i + 1].senha;
    strcpy(clientes[i].nome, clientes[i + 1].nome);
    strcpy(clientes[i].tipoConta, clientes[i + 1].tipoConta);
  }
  // Limpa as informações do último cliente.
  clientes[*total].cpf = 0;
  clientes[*total].valor = 0;
  clientes[*total].senha = 0;
  strcpy(clientes[*total].nome, "\0");
  strcpy(clientes[*total].tipoConta, "\0");
  *total = *total - 1;
  imprimeCliente(clientes, *total);

  return 0; // Cliente apagado com sucesso
}
// Solicita dados do cliente para um possível débito.
int debito(Cliente clientes[], int *total) {
  int cpf, senha, pos;

  printf("Informe o CPF: ");
  scanf("%d", &cpf);

  printf("Informe sua senha: ");
  scanf("%d", &senha);
  // Recebe os dados se o cliente tem CPF cadastrado
  pos = buscaCliente(cpf, clientes, *total);

  if (pos < 0) {
    return -1; // cpf não encontrado
  }
// Cliente encontrado, pede se o valor e chama a função debitar para realizar a operacao caso os dados solicitados estejam corretos.
  float valor;
  printf("Entre com o valor: ");
  scanf("%f", &valor);
  return debitar(&clientes[pos], valor, senha);
}

// Solicita os dados do cliente para um possível depósito
int deposito(Cliente clientes[], int *total) {
  int cpf, pos;

  printf("Informe o CPF: ");
  scanf("%d", &cpf);
//Verifica se o CPF informado está cadastrado
  pos = buscaCliente(cpf, clientes, *total);
  if (pos < 0) {
    return 1; // Cliente não encontrado
  }
  // Cliente encontrado, pede se valor e chama a função depositar para realizar
  // a operação.
  float valor;
  printf("Entre com o valor: ");
  scanf("%f", &valor);
  return depositar(&clientes[pos], valor);
}

// Mostra todo histórico do cliente
int extrato(Cliente clientes[], int *total) {

  int cpf, pos, senha, res, i;

  printf("Informe o CPF: ");
  scanf("%d", &cpf);
  pos = buscaCliente(cpf, clientes, *total); // Busca cliente pelo CPF
  if (pos < 0) {
    printf("Cliente nao encontrado");
    return 1; // Cliente não encontrado
  } else {
    printf("Informe sua senha: ");
    scanf("%d", &senha);
    if (clientes[pos].senha != senha){ //Verifica se a senha está correta.
       return 2; // Senha incorreta
    } else{ //Imprime os dados do cliente.
      printf("Extrato do cliente: %s\n", clientes[pos].nome);
      printf("CPF: %d\n", clientes[pos].cpf);
      printf("Tipo de conta: %s\n", clientes[pos].tipoConta);
      printf("Saldo: %.2f\n", clientes[pos].valor);
      printf("Operações:\n");
       for (int i = 0; i < clientes[pos].posOp; i++) { //Imprime todas as operações
        Operacao operacao = clientes[pos].operacoes[i];
        printf("Data: %s\n", operacao.data);
        printf("Valor: %.2f\n", operacao.valor);
        printf("Taxa: %.2f\n", operacao.taxa);
        printf("Saldo: %.2f\n", operacao.saldo);
        printf("-------------------------\n");
      }
      return 0; //Cliente encontrado com sucesso
    }  
  }
}

// Realiza transferência de valores usando as funções depositar e debitar
int transferenciaConta(Cliente clientes[], int *total) {
  int cpfOrigem, cpfDestino, senha, posOrigem, posDestino;
  float valor;
//Pede os dados
  printf("Informe o CPF de Origem: ");
  scanf("%d", &cpfOrigem);
  printf("Informe o CPF de Destino: ");
  scanf("%d", &cpfDestino);
  printf("Informe a senha: ");
  scanf("%d", &senha);
//Verifica se os CPFs estão cadastrados
  posOrigem = buscaCliente(cpfOrigem, clientes, *total);
  posDestino = buscaCliente(cpfDestino, clientes, *total);

  if (posOrigem < 0) {
    return 1; // Cpf não encontrado
  }
  if (posDestino < 0) {
    return 2; // Cpf não encontrado
  }

  printf("Informe o valor: ");
  scanf("%f", &valor);
  int cliOrigem;
  //Chama a função para realizar o débito 
  cliOrigem = debitar(&clientes[posOrigem], senha, valor);
  if (cliOrigem > 0) {
    return cliOrigem; // Foi debitado com sucesso.
  }
  return depositar(&clientes[posDestino], valor); //O retorno chama a função depositar
}
// A função empréstimo solicita CPF e senha, localiza o cliente e verifica se a senha esta correta, caso todas as informações estejam corretas ela chama afunção depositar para realizar a transação.
int emprestimo(Cliente clientes[], int *total) {
  int cpf, senha, pos, dep;
  float valor;

  printf("Informe o CPF: ");
  scanf("%d", &cpf);
  // Procura pelo cpf cadastrado
  pos = buscaCliente(cpf, clientes, *total);
  if (pos < 0) {
    return -1; // cpf não encontrado
  }
  // Verifica a senha se está correta
  printf("Informe a senha cadastrada: ");
  scanf("%d", &senha);
  if (clientes->senha != senha) {
    return 1; // senha incorreta
  }
  printf("Informe o valor: ");
  scanf("%f", &valor);

  if (valor <= 1000) {
    dep = depositar(clientes, valor);
    return 0; // Emprestimo liberado com sucesso.
  } else {
    return 1; // Emprestimo negado.
  }
}
