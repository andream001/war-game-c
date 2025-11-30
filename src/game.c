#include "../include/game.h"
#include <stdlib.h>
#include <stdio.h>

Game* initialize_game() {
    Game *game = (Game*) malloc(sizeof(Game));
    if (!game) return NULL;
    game->num_territorios = 0;
    game->num_jogadores = 0;
    game->jogador_atual = 0;
    printf("[JOGO] Inicializado com sucesso!\n");
    return game;
}

void free_game(Game *game) {
    if (game) {
        free(game);
        printf("[JOGO] Memoria liberada!\n");
    }
}
