#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/game_engine.h"

// TAD GameEngine privado
struct GameEngine {
    Mission* mission;
    AttackCallback attack_fn;
    VictoryCallback victory_fn;
    char status[100];
    int territories_conquered;
};

// CRIAR ENGINE - Recebe ponteiros para funções (callbacks)
GameEngine* engine_create(AttackCallback attack_fn, VictoryCallback victory_fn) {
    GameEngine* engine = (GameEngine*)malloc(sizeof(GameEngine));
    if (!engine) return NULL;
    
    engine->attack_fn = attack_fn;
    engine->victory_fn = victory_fn;
    engine->mission = NULL;
    engine->territories_conquered = 0;
    strcpy(engine->status, "[INICIADO] Aguardando missão...");
    
    return engine;
}

// LIBERAR ENGINE
void engine_free(GameEngine* engine) {
    if (!engine) return;
    if (engine->mission) mission_free(engine->mission);
    free(engine);
}

// ADICIONAR MISSÃO - Passagem por referência
void engine_add_mission(GameEngine* engine, Mission* mission) {
    if (!engine || !mission) return;
    engine->mission = mission;
    sprintf(engine->status, "[MISSÃO] %s", mission_get_description(mission));
}

// EXECUTAR ATAQUE - Usando callback
int engine_execute_attack(GameEngine* engine, Territory* attacker, Territory* defender) {
    if (!engine || !engine->attack_fn) return 0;
    
    int result = engine->attack_fn(attacker, defender);
    
    if (result == 1) {
        engine->territories_conquered++;
        strcpy(engine->status, "[VENCEU] Território conquistado!");
    }
    
    return result;
}

// VERIFICAR VITÓRIA - Usando callback de vitória
int engine_check_victory(GameEngine* engine) {
    if (!engine || !engine->mission || !engine->victory_fn) return 0;
    
    // Atualizar progresso da missão
    mission_check_progress(engine->mission, engine->territories_conquered);
    
    // Chamar callback de vitória
    int victory = engine->victory_fn(engine->mission);
    
    if (victory) {
        strcpy(engine->status, "[VICTÓRIA GERAL] Missão completada!");
    }
    
    return victory;
}

// OBTER STATUS - const correctness
const char* engine_get_status(const GameEngine* engine) {
    return engine ? engine->status : "";
}
