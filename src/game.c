#include "../include/game.h"
#include <stdlib.h>
#include <stdio.h>

Game* initialize_game() {
    Game *game = (Game*) malloc(sizeof(Game));
    if (!game) return NULL;
    game->territorios = NULL;
    game->num_territorios = 0;
    game->num_jogadores = 0;
    game->jogador_atual = 0;
    printf("[JOGO] Inicializado com sucesso!\n");
    return game;
}

void free_game(Game *game) {
    if (game) {
        free(game->territorios);
        free(game);
        printf("[JOGO] Memoria liberada!\n");
    }
}

void exibir_mapa(Game *game) {
    if (!game || !game->territorios) return;
    printf("\n[MAPA]\n");
    for (int i = 0; i < game->num_territorios; i++) {
        printf("  [%d] %s - Tropas: %d - Jogador: %d\n",
               i + 1,
               game->territorios[i].nome,
               game->territorios[i].tropas,
               game->territorios[i].jogador);
    }
    printf("\n");
}

int atacar_territorio(Game *game, int territorio_ataque, int territorio_defesa) {
    if (!game || !game->territorios) return -1;
    if (territorio_ataque < 0 || territorio_ataque >= game->num_territorios) return -1;
    if (territorio_defesa < 0 || territorio_defesa >= game->num_territorios) return -1;

    Territorio *atacante = &game->territorios[territorio_ataque];
    Territorio *defensor  = &game->territorios[territorio_defesa];

    if (atacante->tropas <= 0) return 0;

    // Combate em multiplas rodadas ate um lado ser eliminado
    int tropas_a = atacante->tropas;
    int tropas_d = defensor->tropas;

    while (tropas_a > 0 && tropas_d > 0) {
        int perda_a = tropas_a / 3 + 1;
        int perda_d = tropas_d / 2 + 1;
        tropas_a -= perda_a;
        tropas_d -= perda_d;
    }

    if (tropas_d <= 0 && tropas_a > 0) {
        // Atacante vence: retém seus exércitos, defensor recebe guarnição mínima
        atacante->tropas  = tropas_a;
        defensor->tropas  = 1;
        defensor->jogador = atacante->jogador;
        return 1;
    }

    // Defensor resistiu
    atacante->tropas = (tropas_a > 0) ? tropas_a : 0;
    return 0;
}

void verificar_vitoria(Game *game) {
    if (!game || !game->territorios || game->num_territorios == 0) return;

    int jogador_dono = game->territorios[0].jogador;
    for (int i = 1; i < game->num_territorios; i++) {
        if (game->territorios[i].jogador != jogador_dono) {
            printf("[VITORIA] Nenhum jogador conquistou todos os territorios ainda.\n");
            return;
        }
    }
    printf("[VITORIA] Jogador %d conquistou todos os territorios!\n", jogador_dono);
}
