#include <stdio.h>
#include <string.h>
#include <time.h>
#include "cliente.h"

int main() {
    struct Cliente clientes[100]; 
    int numClientes = 0; 

    int opcao;
    while (1) { 
        printf("==== (¬‿¬) QuemPoupaTem Bank (¬‿¬) ====\n");
        printf("1. Novo Cliente\n");
        printf("2. Apagar Cliente\n");
        printf("3. Listar Clientes\n");
        printf("4. Realizar Débito\n");
        printf("5. Realizar Depósito\n");
        printf("6. Extrato\n");
        printf("7. Transferência\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                novo_cliente(clientes, &numClientes);
                break;
            case 2:
                apaga_cliente(clientes, &numClientes);
                break;
            case 3:
                listar_clientes(clientes, numClientes);
                break;
            case 4:
                debito(clientes, numClientes);
                break;
            case 5:
                deposito(clientes, numClientes);
                break;
            case 6:
                extrato(clientes, numClientes);
                break;
            case 7:
                transferencia(clientes, numClientes);
                break;
            case 8:
                return 0; 
            default:
                printf("Opção inválida, tente novamente.\n");
                break;
        }
    }

    return 0;
}
