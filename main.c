#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int origemL, int origemC) {
    int deslocamento = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int destinoL = origemL + (i - deslocamento);
                int destinoC = origemC + (j - deslocamento);

                // Verificação de limites do tabuleiro
                if (destinoL >= 0 && destinoL < TAMANHO_TABULEIRO && destinoC >= 0 && destinoC < TAMANHO_TABULEIRO) {
                    tabuleiro[destinoL][destinoC] = 5;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Posicionamento de navios (representados pelo valor 3)
    tabuleiro[1][1] = 3;
    tabuleiro[1][2] = 3;
    tabuleiro[8][5] = 3;
    tabuleiro[9][5] = 3;

    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};

    // Construção dinâmica da habilidade em Cone
    // Lógica: Expande-se a partir do topo central para baixo
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= (TAMANHO_HABILIDADE / 2 - i) && j <= (TAMANHO_HABILIDADE / 2 + i)) {
                cone[i][j] = 1;
            }
        }
    }

    // Construção dinâmica da habilidade em Cruz
    // Lógica: Preenche a linha central e a coluna central
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2) {
                cruz[i][j] = 1;
            }
        }
    }

    // Construção dinâmica da habilidade em Octaedro (Losango)
    // Lógica: A soma das distâncias ao centro deve ser menor ou igual ao raio
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int distL = i > centro ? i - centro : centro - i;
            int distC = j > centro ? j - centro : centro - j;
            if (distL + distC <= centro) {
                octaedro[i][j] = 1;
            }
        }
    }

    // Aplicação das habilidades em pontos de origem distintos
    printf("Tabuleiro com Habilidade em Cone (Origem: 2, 5):\n");
    aplicarHabilidade(tabuleiro, cone, 2, 5);
    exibirTabuleiro(tabuleiro);

    printf("Tabuleiro com Habilidade em Cruz (Origem: 5, 2):\n");
    aplicarHabilidade(tabuleiro, cruz, 5, 2);
    exibirTabuleiro(tabuleiro);

    printf("Tabuleiro com Habilidade em Octaedro (Origem: 7, 7):\n");
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);
    exibirTabuleiro(tabuleiro);

    return 0;
}