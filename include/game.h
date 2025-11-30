#ifndef GAME_H
#define GAME_H

/* Estrutura de dados para representar um Territorio */
typedef struct {
    char nome[50];
    int tropas;
    int jogador;
} Territorio;

/* Estrutura principal do Jogo */
typedef struct {
    Territorio *territorios;
    int num_territorios;
    int num_jogadores;
    int jogador_atual;
} Game;

/* Funcoes disponiveis */
Game* initialize_game(void);
void free_game(Game *game);
void exibir_mapa(Game *game);
int atacar_territorio(Game *game, int territorio_ataque, int territorio_defesa);
void verificar_vitoria(Game *game);

#endif
