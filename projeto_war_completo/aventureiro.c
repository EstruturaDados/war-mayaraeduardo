/* aventureiro.c
 * Nível Aventureiro - Batalhas Estratégicas
 *
 * Funcionalidades principais:
 *  - Alocação dinâmica de N_TERRITORIOS com calloc
 *  - Cadastro dos territórios (nome, cor, tropas)
 *  - Função que simula uma batalha entre atacante e defensor usando rand()
 *  - Lógica: se atacante vence -> defensor perde 1 tropa; empates favorecem atacante
 *  - Quando um território perde todas as tropas, é conquistado (muda cor e recebe 1 tropa)
 *
 * Comentários explicativos foram adicionados.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_TERRITORIOS 5
#define MAX_NOME 64
#define MAX_COR 32

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

/* removes newline from a string */
void strip_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n') s[len-1] = '\0';
}

/* imprime o estado do mapa */
void imprimir_mapa(const Territorio *mapa, int n) {
    printf("=== MAPA ===\n");
    for (int i = 0; i < n; ++i) {
        printf("%d) %s | Cor: %s | Tropas: %d\n", i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("===========\n");
}

/* simula um ataque entre os índices atacante_idx e defensor_idx
 * O atacante rola um valor 1..6, defensor também. Se atacante >= defensor -> defensor perde 1 tropa
 * empate favorece atacante (condição >=)
 * retorna 1 se o defensor foi conquistado (tropas chegaram a 0), 0 caso contrário.
 */
int simular_ataque(Territorio *mapa, int atacante_idx, int defensor_idx) {
    int atk_roll = rand() % 6 + 1;
    int def_roll = rand() % 6 + 1;

    printf("Ataque: %s (tropas %d) -> %s (tropas %d)\n",
           mapa[atacante_idx].nome, mapa[atacante_idx].tropas,
           mapa[defensor_idx].nome, mapa[defensor_idx].tropas);

    printf("  Dados: Atacante=%d, Defensor=%d\n", atk_roll, def_roll);

    if (atk_roll >= def_roll) {
        /* atacante vence (empate favorece atacante) */
        mapa[defensor_idx].tropas -= 1;
        if (mapa[defensor_idx].tropas < 0) mapa[defensor_idx].tropas = 0;
        printf("  Resultado: atacante vence -> defensor perde 1 tropa (restam %d)\n",
               mapa[defensor_idx].tropas);
    } else {
        /* defensor vence: nada acontece neste modelo (poderia reduzir tropas do atacante) */
        printf("  Resultado: defensor defende com sucesso (nenhuma tropa perdida neste modelo)\n");
    }

    if (mapa[defensor_idx].tropas == 0) {
        /* conquista: defensor muda de cor para a do atacante e recebe 1 tropa */
        strncpy(mapa[defensor_idx].cor, mapa[atacante_idx].cor, MAX_COR);
        mapa[defensor_idx].cor[MAX_COR-1] = '\0';
        mapa[defensor_idx].tropas = 1;
        printf("  Território %s conquistado! Agora pertence à cor %s e tem 1 tropa.\n",
               mapa[defensor_idx].nome, mapa[defensor_idx].cor);
        return 1;
    }
    return 0;
}

int main(void) {
    Territorio *mapa = calloc(N_TERRITORIOS, sizeof(Territorio));
    if (!mapa) {
        fprintf(stderr, "Erro de alocação\n");
        return 1;
    }

    printf("=== NÍVEL AVENTUREIRO: Cadastro Dinâmico e Batalhas ===\n\n");
    /* leitura dos territórios */
    for (int i = 0; i < N_TERRITORIOS; ++i) {
        printf("Território %d - Nome: ", i+1);
        if (fgets(mapa[i].nome, MAX_NOME, stdin) == NULL) {
            strncpy(mapa[i].nome, "SemNome", MAX_NOME);
            mapa[i].nome[MAX_NOME-1] = '\0';
        } else strip_newline(mapa[i].nome);

        printf("  Cor do exército: ");
        if (fgets(mapa[i].cor, MAX_COR, stdin) == NULL) {
            strncpy(mapa[i].cor, "Neutro", MAX_COR);
            mapa[i].cor[MAX_COR-1] = '\0';
        } else strip_newline(mapa[i].cor);

        printf("  Número de tropas: ");
        while (scanf("%d", &mapa[i].tropas) != 1) {
            int c; printf("  Entrada inválida. Digite um inteiro: ");
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
        int c; while ((c = getchar()) != '\n' && c != EOF) { }
        printf("\n");
    }

    /* inicializa gerador de números aleatórios */
    srand((unsigned) time(NULL));

    /* loop interativo de batalhas */
    int escolha = -1;
    while (1) {
        imprimir_mapa(mapa, N_TERRITORIOS);
        printf("Opções:\n 1 - Atacar\n 0 - Sair\nEscolha: ");
        if (scanf("%d", &escolha) != 1) {
            int ch; while ((ch = getchar()) != '\n' && ch != EOF) { }
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }
        int ch; while ((ch = getchar()) != '\n' && ch != EOF) { }

        if (escolha == 0) break;
        if (escolha == 1) {
            int atk, def;
            printf("Escolha o atacante (1-%d): ", N_TERRITORIOS);
            if (scanf("%d", &atk) != 1) { while ((ch = getchar()) != '\n' && ch != EOF) { } printf("Entrada inválida.\n"); continue; }
            printf("Escolha o defensor (1-%d): ", N_TERRITORIOS);
            if (scanf("%d", &def) != 1) { while ((ch = getchar()) != '\n' && ch != EOF) { } printf("Entrada inválida.\n"); continue; }
            while ((ch = getchar()) != '\n' && ch != EOF) { }

            if (atk < 1 || atk > N_TERRITORIOS || def < 1 || def > N_TERRITORIOS || atk == def) {
                printf("Escolhas inválidas. Atacante e defensor devem ser índices válidos e diferentes.\n");
                continue;
            }
            simular_ataque(mapa, atk-1, def-1);
        } else {
            printf("Opção desconhecida.\n");
        }
    }

    free(mapa);
    printf("Saindo do modo Aventureiro. Até mais!\n");
    return 0;
}