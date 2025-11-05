#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 50
#define MAX_COR 20
#define NUM_TERRITORIOS 5

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Territorio* inicializarMapa() {
    Territorio* mapa = (Territorio*)calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    printf("=== Cadastro dos Territórios ===\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, MAX_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(mapa[i].cor, MAX_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();
    }

    return mapa;
}

void exibirMapa(Territorio* mapa) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do Exército: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
    }
}

void simularBatalha(Territorio* mapa) {
    int atacante, defensor;
    printf("\n=== Fase de Ataque ===\n");
    printf("Escolha o território atacante (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &atacante);
    printf("Escolha o território defensor (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &defensor);
    limparBuffer();

    atacante--; defensor--;

    if (atacante == defensor || mapa[atacante].tropas <= 0 || mapa[defensor].tropas <= 0) {
        printf("Ataque inválido.\n");
        return;
    }

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\nDados sorteados:\n");
    printf("  Ataque (%s): %d\n", mapa[atacante].nome, dadoAtaque);
    printf("  Defesa (%s): %d\n", mapa[defensor].nome, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        mapa[defensor].tropas--;
        printf("Resultado: O atacante venceu!\n");

        if (mapa[defensor].tropas <= 0) {
            printf("Território %s foi conquistado!\n", mapa[defensor].nome);
            strcpy(mapa[defensor].cor, mapa[atacante].cor);
            mapa[defensor].tropas = 1;
            mapa[atacante].tropas--;
        }
    } else {
        printf("Resultado: O defensor resistiu ao ataque.\n");
    }
}

int main() {
    srand(time(NULL)); // Inicializa aleatoriedade

    Territorio* mapa = inicializarMapa();
    exibirMapa(mapa);

    char continuar;
    do {
        simularBatalha(mapa);
        exibirMapa(mapa);
        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
        limparBuffer();
    } while (continuar == 's' || continuar == 'S');

    free(mapa);
    return 0;
}