#include <stdio.h>

#define TAMANHO 10 // Tamanho do tabuleiro 10x10
#define TAMANHO_NAVIO 3 // Tamanho fixo dos navios
#define TAMANHO_HABILIDADE 5 // Tamanho fixo das matrizes de habilidade

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0; // Inicializa com água (0)
        }
    }
}

int podePosicionar(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int horizontal, int diagonal, int reverso) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int x = linha + (diagonal ? (reverso ? -i : i) : (horizontal ? 0 : i));
        int y = coluna + (diagonal ? (reverso ? -i : i) : (horizontal ? i : 0));
        if (x < 0 || x >= TAMANHO || y < 0 || y >= TAMANHO || tabuleiro[x][y] != 0) {
            return 0; // Posição inválida ou já ocupada
        }
    }
    return 1; // Posição válida
}

void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int horizontal, int diagonal, int reverso) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int x = linha + (diagonal ? (reverso ? -i : i) : (horizontal ? 0 : i));
        int y = coluna + (diagonal ? (reverso ? -i : i) : (horizontal ? i : 0));
        tabuleiro[x][y] = 3; // Posiciona o navio
    }
}

void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int origemX, int origemY, int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int offset = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int x = origemX + i - offset;
            int y = origemY + j - offset;
            if (x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO && habilidade[i][j] == 1) {
                tabuleiro[x][y] = 5; // Marca a área afetada pela habilidade
            }
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro);
    
    // Definição das coordenadas dos navios
    int posicoes[4][4] = {
        {2, 3, 1, 0}, // Horizontal
        {5, 6, 0, 0}, // Vertical
        {1, 1, 2, 0}, // Diagonal principal
        {6, 8, 2, 1}  // Diagonal secundária
    };
    
    // Posicionando os navios
    for (int i = 0; i < 4; i++) {
        int linha = posicoes[i][0];
        int coluna = posicoes[i][1];
        int tipo = posicoes[i][2]; // 0: Vertical, 1: Horizontal, 2: Diagonal
        int reverso = posicoes[i][3]; // 0: Normal, 1: Reverso
        
        if (podePosicionar(tabuleiro, linha, coluna, tipo == 1, tipo == 2, reverso)) {
            posicionarNavio(tabuleiro, linha, coluna, tipo == 1, tipo == 2, reverso);
        }
    }
    
    // Definição das matrizes de habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0}
    };
    
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0}
    };
    
    // Aplicar habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, 4, 4, cone);    // Habilidade Cone no centro
    aplicarHabilidade(tabuleiro, 7, 7, cruz);    // Habilidade Cruz no canto inferior direito
    aplicarHabilidade(tabuleiro, 2, 7, octaedro); // Habilidade Octaedro no canto superior direito
    
    // Exibir o tabuleiro final
    exibirTabuleiro(tabuleiro);
    
    return 0;
}