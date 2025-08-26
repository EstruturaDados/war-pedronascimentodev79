#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];     // Nome do território
    char cor[10];      // Cor do exército associado ao território
    int tropas;        // Quantidade de tropas posicionadas
} Territorio;

int main() {
    Territorio territorios[5]; // Vetor para armazenar até 5 territórios
    int qtd = 0;               // Contador de quantos territórios foram cadastrados
    int opcao;                 // Armazena a escolha do usuário no menu

    do {
        // Exibição do menu
        printf("\n=== Menu Principal ===\n");
        printf("1 - Cadastrar Território\n");
        printf("2 - Ver lista de Territórios\n");
        printf("3 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (qtd < 5) {
                    printf("\n--- Cadastro do território %d ---\n", qtd + 1);

                    printf("Digite o nome do território: ");
                    scanf(" %[^\n]", territorios[qtd].nome);

                    printf("Digite a cor do exército: ");
                    scanf(" %[^\n]", territorios[qtd].cor);

                    printf("Digite a quantidade de tropas: ");
                    scanf("%d", &territorios[qtd].tropas);

                    qtd++; // Incrementa o contador de territórios cadastrados
                    printf("\n Território cadastrado com sucesso!\n");
                } else {
                    printf("\n Limite de 5 territórios atingido! Não é possível cadastrar mais.\n");
                }
                break;

            case 2:
                if (qtd == 0) {
                    printf("\n Nenhum território cadastrado ainda.\n");
                } else {
                    printf("\n=== Lista de Territórios ===\n");
                    for (int i = 0; i < qtd; i++) {
                        printf("Território %d:\n", i + 1);
                        printf("Nome: %s\n", territorios[i].nome);
                        printf("Cor do exército: %s\n", territorios[i].cor);
                        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
                        printf("-----------------------------\n");
                    }
                }
                break;

            case 3:
                printf("\n Saindo do sistema... Até logo!\n");
                break;

            default:
                printf("\n Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 3); // Repete até o usuário escolher "Sair"

    return 0;
}
