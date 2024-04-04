#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
#include "funcoes.h"

//Observação: Para que as operações fiquem salvas é preciso clicar na opção 09 sair, para guardar o histórico.
int main(void) {

 
  Cliente clientes[MAX_CLIENTES]; //Cria variável do tipo Clientes
  int totalClientes = 0; 
  //Verifica se há espaço para cadastrar novos clientes.
  if(totalClientes >= MAX_CLIENTES){
    printf("Não há espaço para novos clientes.");
    return 1;
  }
 
   FILE *f = fopen("clientes", "rb");
    if(f != NULL){
    fread(clientes, sizeof(Cliente), MAX_CLIENTES, f);
    fclose(f);
}
  f = fopen("total", "rb");
  if(f !=NULL){
    fread(&totalClientes, sizeof(int), 1, f);
    fclose(f);
  }
  int operacao;
  do{
    printf("\nEscolha uma opção:\n ");
    printf("\n01 - Novo Cliente");
    printf("\n02 - Apagar Cliente.");
    printf("\n03 - Débito");
    printf("\n04 - Depósito");
    printf("\n05 - Extrato");
    printf("\n06 - Transferência Entre Contas");
    printf("\n07 - Empréstimo");
    printf("\n08 - Listar");
    printf("\n09 - Sair\n");
    
    scanf("%d", &operacao);
    switch(operacao){
      case 1:
        printf("Cadastro clientes\n");
        int r = novoCliente(clientes,&totalClientes); 
        if(r == 0){
          printf("Cliente cadastrado com sucesso.");
        }else if(r == 1){
          printf("Sem espaço para novos clientes.");
        }else if(r==2){
          printf("Cliente só cadastrado.");
        }else{
          printf("Outro erro: %d", r);
        }       
      break;
      
      case 2:
      printf("Apaga clientes\n");
      int s = apagaCliente(clientes,&totalClientes);
      if(s == 0){
        printf("Cliente apagado com sucesso");
      }else if(s==1){
        printf("Cliente não cadastrado");
      }else{
        printf("Outro erro: %d", s);
      }
      break;
      
      case 3:
      printf("Débitos\n");
      int a = debito(clientes, &totalClientes);
      if(a == -1){
        printf("Cliente não cadastrado.");
      }else if(a == 0){
        printf("Débito realizado com sucesso.");
      }else if(a == 1){
        printf("Senha incorreta.");
      }else if(a == 2){
        printf("Saldo insuficiente.");
      }else{
        printf("Outro erro: %d", a);
      }
      break;

      case 4:
      printf("Depósito\n");
      int b = deposito(clientes, &totalClientes);
      if(b == 1){
        printf("Cliente não cadastrado.");
      }else if(b == 0){
        printf("Depósito realizado com sucesso.");
      }else{
        printf("Outro erro: %d", b);
      }
      break;

      case 5:
      printf("Depósito\n");
      int re = extrato(clientes, &totalClientes);
        if(re == 1){
          printf("Senha incorreta.");
        }else if(re == 0){
          printf("Extrato impresso com sucesso.");
        }else{
          printf("Outro erro %d", re);
        }
        break;
      
      case 6:
      printf("Transferência\n");
      int c =transferenciaConta(clientes, &totalClientes);
      if(c == 1){
        printf("Cliente não cadastrado.");
      }else if(c == 0){
         printf("Transferência realizada com sucesso.");
      }else{
        printf("Outro erro: %d", b);
      }
      break;

      case 7:
      printf("Emprestimos\n");
      int res = emprestimo(clientes, &totalClientes);
      if(res ==0){
      printf("Empréstimo realizado com sucesso.");
      }else if(res == 1){
      printf("Empréstimo negado.");
      }
      break;
      
      case 8:
      imprimeCliente(clientes, totalClientes);
      break;
      
      default:
      printf("Obrigado!");
      
    }
  }while(operacao != 9);

  f = fopen("clientes", "wb");
  if(f == NULL){
    printf("Erro ao abir o arquivo de clientes para escrita");
    return 1;
  }
  fwrite(clientes, sizeof(Cliente), MAX_CLIENTES, f);
  fclose(f);

  f = fopen("total", "wb");
  if(f == NULL){
    printf("Erro ao salvar total de clientes. ");
    return 1;
  }
  fwrite(&totalClientes, sizeof(int), 1, f);
  fclose(f);
  return 0;
}