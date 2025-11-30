#include <stdio.h>
#include "../include/game.h"

int main() {
    printf("=== Bem-vindo ao jogo War em C ===\n");
    printf("Projeto: Estruturas de Dados, Ponteiros e Alocação Dinâmica\n\n");
    
    // Inicialização do jogo
    Game *game = initialize_game();
    
    if (game == NULL) {
        printf("Erro ao inicializar o jogo!\n");
        return 1;
    }
    
    // Loop principal do jogo
    printf("Jogo iniciado com sucesso!\n");
    printf("Níveis: Novato | Aventureiro | Mestre\n");
    
    // Liberar memória
    free_game(game);
    
    printf("\nObrigado por jogar!\n");
    return 0;
}
