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

typedef enum {
    DESTRUIR_VERDE,
    CONQUISTAR_3,
    ALEATORIA
} TipoMissao;

typedef struct {
    TipoMissao tipo;
    int progresso;
    int concluida;
} Missao;

/* ---------- Funções utilitárias ---------- */

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ---------- Funções de inicialização ---------- */

void inicializarTerritorios(Territorio* mapa) {
    const char* nomes[NUM_TERRITORIOS] = {"Norte", "Sul", "Leste", "Oeste", "Centro"};
    const char* cores[NUM_TERRITORIOS] = {"Vermelho", "Azul", "Verde", "Amarelo", "Preto"};
    const int tropas_iniciais[NUM_TERRITORIOS] = {5, 5, 5, 5, 5};

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        strncpy(mapa[i].nome, nomes[i], MAX_NOME - 1);
        strncpy(mapa[i].cor, cores[i], MAX_COR - 1);
        mapa[i].tropas = tropas_iniciais[i];
    }
}

/* ---------- Exibição ---------- */

void exibirMapa(const Territorio* mapa) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do Exército: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
    }
}

/* ---------- Funções de Missão ---------- */

void atribuirMissao(Missao* missao) {
    int sorteio = rand() % 2;  // Apenas dois tipos de missão
    missao->tipo = sorteio == 0 ? DESTRUIR_VERDE : CONQUISTAR_3;
    missao->progresso = 0;
    missao->concluida = 0;

    printf("\n=== Missão Atribuída ===\n");
    if (missao->tipo == DESTRUIR_VERDE)
        printf("Missão: Destruir o exército Verde!\n");
    else if (missao->tipo == CONQUISTAR_3)
        printf("Missão: Conquistar 3 territórios!\n");
}

/* ---------- Batalhas ---------- */

void simularBatalha(Territorio* mapa, Missao* missao) {
    int atacante, defensor;

    printf("\n=== Fase de Ataque ===\n");
    printf("Escolha o território atacante (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &atacante);
    printf("Escolha o território defensor (1 a %d): ", NUM_TERRITORIOS);
    scanf("%d", &defensor);
    limparBuffer();

    atacante--; 
    defensor--;

    if (atacante == defensor || atacante < 0 || defensor < 0 || atacante >= NUM_TERRITORIOS || defensor >= NUM_TERRITORIOS) {
        printf("Ataque inválido.\n");
        return;
    }

    if (mapa[atacante].tropas <= 1) {
        printf("Território atacante não tem tropas suficientes.\n");
        return;
    }

    if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
        printf("Você não pode atacar um território aliado!\n");
        return;
    }

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\nDados sorteados:\n");
    printf("  Ataque (%s): %d\n", mapa[atacante].nome, dadoAtaque);
    printf("  Defesa (%s): %d\n", mapa[defensor].nome, dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        mapa[defensor].tropas--;
        printf("Resultado: O atacante venceu!\n");

        if (mapa[defensor].tropas <= 0) {
            printf("Território %s foi conquistado!\n", mapa[defensor].nome);
            strcpy(mapa[defensor].cor, mapa[atacante].cor);
            mapa[defensor].tropas = 1;
            mapa[atacante].tropas--;

            // Atualiza progresso da missão
            if (missao->tipo == CONQUISTAR_3)
                missao->progresso++;
        }
    } else {
        mapa[atacante].tropas--;
        printf("Resultado: O defensor resistiu ao ataque.\n");
    }
}

/* ---------- Verificação de Missão ---------- */

void verificarMissao(const Territorio* mapa, Missao* missao) {
    if (missao->concluida) {
        printf("\nVocê já completou sua missão!\n");
        return;
    }

    if (missao->tipo == DESTRUIR_VERDE) {
        int verde_existe = 0;
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0) {
                verde_existe = 1;
                break;
            }
        }
        if (!verde_existe) {
            printf("\n🎉 Missão cumprida: O exército Verde foi destruído!\n");
            missao->concluida = 1;
            return;
        } else {
            printf("\nMissão em andamento: Ainda existem territórios Verdes.\n");
        }
    } else if (missao->tipo == CONQUISTAR_3) {
        if (missao->progresso >= 3) {
            printf("\n🎉 Missão cumprida: Você conquistou 3 territórios!\n");
            missao->concluida = 1;
            return;
        } else {
            printf("\nMissão em andamento: %d/3 territórios conquistados.\n", missao->progresso);
        }
    }
}

/* ---------- Menu principal ---------- */

void menuPrincipal(Territorio* mapa, Missao* missao) {
    int opcao;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                simularBatalha(mapa, missao);
                exibirMapa(mapa);
                verificarMissao(mapa, missao);
                break;
            case 2:
                verificarMissao(mapa, missao);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0 && !missao->concluida);

    if (missao->concluida)
        printf("\n🏆 Parabéns! Você venceu o jogo!\n");
}

/* ---------- Função principal ---------- */

int main() {
    srand(time(NULL));

    Territorio mapa[NUM_TERRITORIOS];
    Missao missao;

    inicializarTerritorios(mapa);
    exibirMapa(mapa);
    atribuirMissao(&missao);
    menuPrincipal(mapa, &missao);

    return 0;
}
