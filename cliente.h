#ifndef CLIENTE_H
#define CLIENTE_H

struct Cliente {
    char cpf[12];
    char nome[50];
    float saldo;
    char senha[50];
    char tipo_conta[10];
};

void novo_cliente(struct Cliente *clientes, int *numClientes);
void apaga_cliente(struct Cliente *clientes, int *numClientes);
void listar_clientes(struct Cliente *clientes, int numClientes);

#endif