/* mestre.c
 * Nível Mestre - Missões e Modularização Total
 *
 * Funcionalidades:
 *  - Código modularizado em funções
 *  - Inicialização automática/por cadastro
 *  - Menu principal:
 *      1) Atacar
 *      2) Verificar Missão
 *      0) Sair
 *  - Missões aleatórias:
 *      a) Destruir o exército "Verde" (remover todos os territórios cuja cor é "Verde")
 *      b) Conquistar 3 territórios (tornar pertencentes à sua cor)
 *  - Uso de const correctness onde faz sentido
 *
 * Observação: implementação para um jogador (controla uma cor escolhida no início).
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

/* protótipos */
void strip_newline(char *s);
void inicializar_automatico(Territorio mapa[], int n);
void imprimir_mapa(const Territorio mapa[], int n);
int simular_ataque(Territorio mapa[], int atacante, int defensor);
int contar_territorios_por_cor(const Territorio mapa[], int n, const char *cor);
int verificar_missao(const Territorio mapa[], int n, int tipo_missao, const char *cor_do_jogador);
void menu_ataque(Territorio mapa[], int n, const char *cor_do_jogador);

/* remove newline do fgets */
void strip_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n') s[len-1] = '\0';
}

/* inicializa os territórios automaticamente (exemplo) */
void inicializar_automatico(Territorio mapa[], int n) {
    const char *nomes_default[N_TERRITORIOS] = {"Amazonas", "Cerrado", "Pantanal", "Caatinga", "Mata Atlântica"};
    const char *cors_default[N_TERRITORIOS] = {"Verde", "Vermelho", "Azul", "Verde", "Amarelo"};
    const int tropas_default[N_TERRITORIOS] = {5, 3, 4, 2, 6};

    for (int i = 0; i < n; ++i) {
        strncpy(mapa[i].nome, nomes_default[i], MAX_NOME);
        mapa[i].nome[MAX_NOME-1] = '\0';
        strncpy(mapa[i].cor, cors_default[i], MAX_COR);
        mapa[i].cor[MAX_COR-1] = '\0';
        mapa[i].tropas = tropas_default[i];
    }
}

/* imprime o mapa */
void imprimir_mapa(const Territorio mapa[], int n) {
    printf("=== MAPA ATUAL ===\n");
    for (int i = 0; i < n; ++i) {
        printf("%d) %s | Cor: %s | Tropas: %d\n", i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("=================\n");
}

/* simula ataque (mesma lógica do aventureiro, porém modularizada)
 * retorna 1 se houve conquista, 0 caso contrário
 */
int simular_ataque(Territorio mapa[], int atacante, int defensor) {
    int atk_roll = rand() % 6 + 1;
    int def_roll = rand() % 6 + 1;

    printf("Ataque: %s (%s, %d tropas) -> %s (%s, %d tropas)\n",
           mapa[atacante].nome, mapa[atacante].cor, mapa[atacante].tropas,
           mapa[defensor].nome, mapa[defensor].cor, mapa[defensor].tropas);
    printf("  Dados: Atacante=%d, Defensor=%d\n", atk_roll, def_roll);

    if (atk_roll >= def_roll) {
        mapa[defensor].tropas -= 1;
        if (mapa[defensor].tropas < 0) mapa[defensor].tropas = 0;
        printf("  Atacante vence -> defensor perde 1 tropa (restam %d)\n", mapa[defensor].tropas);
    } else {
        printf("  Defensor vence -> nenhum efeito (modelo simplificado)\n");
    }

    if (mapa[defensor].tropas == 0) {
        strncpy(mapa[defensor].cor, mapa[atacante].cor, MAX_COR);
        mapa[defensor].cor[MAX_COR-1] = '\0';
        mapa[defensor].tropas = 1;
        printf("  Território %s conquistado e atribuído à cor %s\n", mapa[defensor].nome, mapa[defensor].cor);
        return 1;
    }
    return 0;
}

/* conta quantos territórios pertencem a 'cor' */
int contar_territorios_por_cor(const Terrorio mapa[], int n, const char *cor) {
    int cont = 0;
    for (int i = 0; i < n; ++i) {
        if (strcasecmp(mapa[i].cor, cor) == 0) cont++;
    }
    return cont;
}int contar_territorios_por_cor(const Territorio mapa[], int n, const char *cor) {
    int cont = 0;
    for (int i = 0; i < n; ++i) {
        if (strcasecmp(mapa[i].cor, cor) == 0) cont++;
    }
    return cont;
}

/* verifica se a missão foi cumprida
 * tipo_missao:
 *   1 -> Destruir o exército "Verde" (ou cor alvo passada)
 *   2 -> Conquistar 3 territórios (o jogador vence se possuir >=3 territórios)
 */
int verificar_missao(const Territorio mapa[], int n, int tipo_missao, const char *cor_do_jogador) {
    if (tipo_missao == 1) {
        int verdes = contar_territorios_por_cor(mapa, n, "Verde");
        return (verdes == 0);
    } else if (tipo_missao == 2) {
        int meus = contar_territorios_por_cor(mapa, n, cor_do_jogador);
        return (meus >= 3);
    }
    return 0;
}

/* rotina para tratar o menu de ataque: pede índices e chama simular_ataque */
void menu_ataque(Territorio mapa[], int n, const char *cor_do_jogador) {
    int atk_idx, def_idx;
    printf("Escolha o atacante (1-%d): ", n);
    if (scanf("%d", &atk_idx) != 1) { int c; while ((c=getchar())!='\n' && c!=EOF){} printf("Entrada inválida.\n"); return; }
    printf("Escolha o defensor (1-%d): ", n);
    if (scanf("%d", &def_idx) != 1) { int c; while ((c=getchar())!='\n' && c!=EOF){} printf("Entrada inválida.\n"); return; }
    int c; while ((c=getchar())!='\n' && c!=EOF) {}

    if (atk_idx < 1 || atk_idx > n || def_idx < 1 || def_idx > n || atk_idx == def_idx) {
        printf("Índices inválidos. Operação abortada.\n");
        return;
    }

    if (mapa[atk_idx-1].tropas <= 0) {
        printf("Território atacante não possui tropas suficientes.\n");
        return;
    }

    simular_ataque(mapa, atk_idx-1, def_idx-1);
}

int main(void) {
    Territorio mapa[N_TERRITORIOS];
    srand((unsigned)time(NULL));

    printf("=== NÍVEL MESTRE: Missões e Modularização ===\n");

    /* inicialização automática para simplificar; poderia pedir cadastro ao usuário */
    inicializar_automatico(mapa, N_TERRITORIOS);

    /* jogador escolhe uma cor que vai controlar */
    char cor_do_jogador[MAX_COR];
    printf("Escolha a cor que você controlará (ex: Vermelho, Azul, Verde): ");
    if (fgets(cor_do_jogador, MAX_COR, stdin) == NULL) {
        strncpy(cor_do_jogador, "Vermelho", MAX_COR);
        cor_do_jogador[MAX_COR-1] = '\\0';
    } else strip_newline(cor_do_jogador);

    /* escolher aleatoriamente uma missão (1 ou 2) */
    int tipo_missao = (rand() % 2) + 1;
    if (tipo_missao == 1) {
        printf("Missão sorteada: DESTRUIR O EXÉRCITO VERDE (eliminar todos os territórios com cor 'Verde').\\n");
    } else {
        printf("Missão sorteada: CONQUISTAR 3 TERRITÓRIOS (pertencer a sua cor).\\n");
    }

    int opcao = -1;
    while (1) {
        imprimir_mapa(mapa, N_TERRITORIOS);
        printf("\\nMenu:\\n 1 - Atacar\\n 2 - Verificar Missão\\n 0 - Sair\\nEscolha: ");
        if (scanf("%d", &opcao) != 1) {
            int c; while ((c=getchar())!='\\n' && c!=EOF) {}
            printf("Entrada inválida.\\n");
            continue;
        }
        int c; while ((c=getchar())!='\\n' && c!=EOF) {}

        if (opcao == 0) break;
        if (opcao == 1) {
            menu_ataque(mapa, N_TERRITORIOS, cor_do_jogador);
        } else if (opcao == 2) {
            int cumpriu = verificar_missao(mapa, N_TERRITORIOS, tipo_missao, cor_do_jogador);
            if (cumpriu) {
                printf("Parabéns! Você cumpriu a missão!\\n");
            } else {
                printf("Missão ainda não cumprida. Continue jogando.\\n");
            }
        } else {
            printf("Opção desconhecida.\\n");
        }
    }

    printf("Encerrando Nível Mestre. Até breve!\\n");
    return 0;
}