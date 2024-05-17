#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "cliente.h"  


void novo_cliente(struct Cliente *clientes, int *numClientes) {
    if (*numClientes < 100) {  
        struct Cliente novo;  
        printf("CPF: ");
        scanf("%s", novo.cpf);
        printf("Nome: ");
        scanf("%s", novo.nome);
        printf("Saldo inicial: ");
        scanf("%f", &novo.saldo);
        printf("Senha: ");
        scanf("%s", novo.senha);
        printf("Tipo de conta (Comum ou Plus): ");
        scanf("%s", novo.tipo_conta);

        clientes[*numClientes] = novo;  
        (*numClientes)++;  

        printf("Cliente cadastrado com sucesso!\n");
    } else {
        printf("Limite de clientes atingido.\n");  
    }
}

void apaga_cliente(struct Cliente *clientes, int *numClientes) {
    char cpf[12];
    printf("CPF do cliente a ser removido: ");
    scanf("%s", cpf);

    for (int i = 0; i < *numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {  
            for (int j = i; j < *numClientes - 1; j++) {
                clientes[j] = clientes[j + 1];  
            }
            (*numClientes)--;  
            printf("Cliente removido com sucesso!\n");
            return;
        }
    }
    printf("CPF não encontrado.\n");  
}

void listar_clientes(struct Cliente *clientes, int numClientes) {
    printf("Lista de clientes:\n");
    for (int i = 0; i < numClientes; i++) {
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Tipo de conta: %s\n", clientes[i].tipo_conta);
        printf("Saldo: R$ %.2f\n", clientes[i].saldo);
        printf("------------------\n");
    }
}