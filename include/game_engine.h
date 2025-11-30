#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "territory.h"
#include "mission.h"

// Ponteiros para funções - MODULARIZAÇÃO
typedef int (*AttackCallback)(Territory* attacker, Territory* defender);
typedef int (*VictoryCallback)(Mission* mission);

// TAD GameEngine
typedef struct GameEngine GameEngine;

// Criar/destruir engine
GameEngine* engine_create(AttackCallback attack_fn, VictoryCallback victory_fn);
void engine_free(GameEngine* engine);

// Adicionar missão
void engine_add_mission(GameEngine* engine, Mission* mission);

// Verificar vitória
int engine_check_victory(GameEngine* engine);

// Executar ataque por referência
int engine_execute_attack(GameEngine* engine, Territory* attacker, Territory* defender);

// Obter status
const char* engine_get_status(const GameEngine* engine);

#endif
