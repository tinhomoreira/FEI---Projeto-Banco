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

void debito(struct Cliente *clientes, int numClientes) {
    char cpf[12];
    printf("CPF do cliente: ");
    scanf("%s", cpf);

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {  
            char senha[50];
            printf("Senha: ");
            scanf("%s", senha);

            if (strcmp(clientes[i].senha, senha) == 0) {  
                float valor;
                printf("Valor do débito: ");
                scanf("%f", &valor);

                if (valor > clientes[i].saldo) {
                    printf("Saldo insuficiente.\n");  
                } else {
                    char tipo_conta[10];
                    strcpy(tipo_conta, clientes[i].tipo_conta);

                    float saldo_atual = clientes[i].saldo;

                    if (strcmp(tipo_conta, "Plus") == 0) {
                        if (saldo_atual - valor < -5000) {
                            printf("Limite de saldo negativo excedido.\n");  
                        } else {
                            float taxa = valor * 0.03;
                            clientes[i].saldo = saldo_atual - valor - taxa;  
                            printf("Débito realizado com sucesso!\n");
                        }
                    } else if (strcmp(tipo_conta, "Comum") == 0) {
                        if (saldo_atual - valor < -1000) {
                            printf("Limite de saldo negativo excedido.\n"); 
                        } else {
                            float taxa = valor * 0.05;
                            clientes[i].saldo = saldo_atual - valor - taxa;  
                            printf("Débito realizado com sucesso!\n");
                        }
                    }
                }
                return;
            } else {
                printf("Senha incorreta.\n");  
                return;
            }
        }
    }
    printf("CPF não encontrado.\n");  
}

void deposito(struct Cliente *clientes, int numClientes) {
    char cpf[12];
    printf("CPF do cliente: ");
    scanf("%s", cpf);

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {  
            char senha[50];
            printf("Senha: ");
            scanf("%s", senha);

            if (strcmp(clientes[i].senha, senha) == 0) {  
                float valor;
                printf("Valor do depósito: ");
                scanf("%f", &valor);

                clientes[i].saldo += valor;  
                printf("Depósito realizado com sucesso!\n");
                return;
            } else {
                printf("Senha incorreta.\n");
                return;
            }
        }
    }
    printf("CPF não encontrado.\n");

}


void extrato(struct Cliente *clientes, int numClientes) {
    char cpf[12];
    float valor;  
    printf("CPF do cliente: ");
    scanf("%s", cpf);

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {  
            char senha[50];
            printf("Senha: ");
            scanf("%s", senha);

            if (strcmp(clientes[i].senha, senha) == 0) {  
                printf("Extrato do cliente %s:\n", clientes[i].nome);
                printf("Saldo: R$%.2f\n", clientes[i].saldo);
                printf("Histórico de Operações:\n");
                for (int j = 0; j < numClientes; j++) {
                    char data[100];
                    time_t t = time(NULL);
                    struct tm tm = *localtime(&t);
                    sprintf(data, "%02d/%02d/%04d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
                            tm.tm_hour, tm.tm_min, tm.tm_sec);

                    char tipo_operacao[20];
                    char valor_operacao[20];

                    if (strcmp(clientes[i].tipo_conta, "Plus") == 0) {
                        sprintf(tipo_operacao, "Débito");
                        sprintf(valor_operacao, "%.2f", valor);  
                    } else if (strcmp(clientes[i].tipo_conta, "Comum") == 0) {
                        sprintf(tipo_operacao, "Débito");
                        sprintf(valor_operacao, "%.2f", valor);  
                    }

                    printf("%s - %s - Valor: R$%s\n", data, tipo_operacao, valor_operacao);  
                }
                printf("==== Opções do Extrato ====\n");
                printf("1. Extrato da Conta Poupança\n");
                printf("2. Voltar\n");
                int opcao;
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);
                if (opcao == 1) {
                    printf("Extrato da Conta Poupança do cliente %s:\n", clientes[i].nome);
                    for (int j = 0; j < numClientes; j++) {
                        char data[100];
                        time_t t = time(NULL);
                        struct tm tm = *localtime(&t);
                        sprintf(data, "%02d/%02d/%04d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
                                tm.tm_hour, tm.tm_min, tm.tm_sec);

                        char tipo_operacao[20];
                        char valor_operacao[20];

                        if (strcmp(clientes[i].tipo_conta, "Plus") == 0) {
                            sprintf(tipo_operacao, "Débito");
                            sprintf(valor_operacao, "%.2f", valor);  
                        } else if (strcmp(clientes[i].tipo_conta, "Comum") == 0) {
                            sprintf(tipo_operacao, "Débito");
                            sprintf(valor_operacao, "%.2f", valor);  
                        }

                        printf("%s - %s - Valor: R$%s\n", data, tipo_operacao, valor_operacao);  
                    }
                }
                return;
            } else {
                printf("Senha incorreta.\n");
                return;
            }
        }
    }
    printf("CPF não encontrado.\n");
}


void transferencia(struct Cliente *clientes, int numClientes) {
    char cpf_origem[12];
    printf("CPF do cliente que deseja transferir: ");
    scanf("%s", cpf_origem);

    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf_origem) == 0) {  
            char cpf_destino[12];
            printf("CPF do cliente que irá receber a transferência: ");
            scanf("%s", cpf_destino);

            for (int j = 0; j < numClientes; j++) {
                if (strcmp(clientes[j].cpf, cpf_destino) == 0) {  
                    char senha[50];
                    printf("Senha: ");
                    scanf("%s", senha);

                    if (strcmp(clientes[i].senha, senha) == 0) {  
                        float valor;  
                        printf("Valor da transferência: ");
                        scanf("%f", &valor);

                        if (valor > clientes[i].saldo) {
                            printf("Saldo insuficiente.\n");
                        } else {
                            char tipo_conta_origem[10];
                            strcpy(tipo_conta_origem, clientes[i].tipo_conta);

                            float saldo_atual_origem = clientes[i].saldo;

                            if (strcmp(tipo_conta_origem, "Plus") == 0) {
                                if (saldo_atual_origem - valor < -5000) {
                                    printf("Limite de saldo negativo excedido.\n");
                                } else {
                                    float taxa = valor * 0.03;
                                    clientes[i].saldo = saldo_atual_origem - valor - taxa;  
                                    clientes[j].saldo += valor;  
                                    printf("Transferência realizada com sucesso!\n");
                                }
                            } else if (strcmp(tipo_conta_origem, "Comum") == 0) {
                                if (saldo_atual_origem - valor < -1000) {
                                    printf("Limite de saldo negativo excedido.\n");
                                } else {
                                    float taxa = valor * 0.05;
                                    clientes[i].saldo = saldo_atual_origem - valor - taxa;  
                                    clientes[j].saldo += valor;  
                                    printf("Transferência realizada com sucesso!\n");
                                }
                            }
                        }
                        return;
                    } else {
                        printf("Senha incorreta.\n");
                        return;
                    }
                }
            }
            printf("CPF de destino não encontrado.\n");
            return;
        }
    }
    printf("CPF de origem não encontrado.\n");
}