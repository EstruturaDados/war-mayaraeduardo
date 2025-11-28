/* novato.c
 * Nível Novato - Cadastro Inicial dos Territórios
 *
 * Funcionalidade:
 *  - Define uma struct Territorio
 *  - Usa vetor ESTÁTICO de 5 elementos
 *  - Lê nome (fgets), cor (fgets) e número de tropas (scanf)
 *  - Exibe o mapa ao final
 *
 * Comentários detalhados foram adicionados para explicar cada parte.
 */

#include <stdio.h>
#include <string.h>

#define N_TERRITORIOS 5
#define MAX_NOME 64
#define MAX_COR 32

/* Estrutura que representa um território */
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];   /* cor do exército dominante (ex: "Vermelho", "Azul", "Verde") */
    int tropas;          /* número de tropas */
} Territorio;

/* Função para limpar o \\n deixado por fgets, se presente */
void strip_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\\n') s[len-1] = '\\0';
}

int main(void) {
    Territorio mapa[N_TERRITORIOS]; /* vetor estático de 5 territórios */
    printf("=== NÍVEL NOVATO: Cadastro de Territórios ===\\n\\n");

    for (int i = 0; i < N_TERRITORIOS; ++i) {
        printf("Território %d:\\n", i + 1);
        printf("  Nome: ");
        if (fgets(mapa[i].nome, MAX_NOME, stdin) == NULL) {
            /* Em caso de EOF, definimos um nome padrão */
            strncpy(mapa[i].nome, "SemNome", MAX_NOME);
            mapa[i].nome[MAX_NOME-1] = '\\0';
        } else {
            strip_newline(mapa[i].nome);
        }

        printf("  Cor do exército: ");
        if (fgets(mapa[i].cor, MAX_COR, stdin) == NULL) {
            strncpy(mapa[i].cor, "Neutro", MAX_COR);
            mapa[i].cor[MAX_COR-1] = '\\0';
        } else {
            strip_newline(mapa[i].cor);
        }

        printf("  Número de tropas: ");
        while (scanf("%d", &mapa[i].tropas) != 1) {
            /* Limpa entrada inválida */
            int c;
            printf("  Entrada inválida. Digite um número inteiro para tropas: ");
            while ((c = getchar()) != '\\n' && c != EOF) { }
        }
        int c; while ((c = getchar()) != '\\n' && c != EOF) { } /* limpar resto da linha */

        printf("\\n");
    }

    /* Exibição organizada do mapa */
    printf("=== Estado atual do mapa ===\\n");
    for (int i = 0; i < N_TERRITORIOS; ++i) {
        printf("Território %d: %s | Cor: %s | Tropas: %d\\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    return 0;
}