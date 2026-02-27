#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/territory.h"
#include "../include/mission.h"
#include "../include/game_engine.h"
#include "../include/game.h"

// ── helpers ──────────────────────────────────────────────────────────────────
static int passed = 0;
static int failed = 0;

#define ASSERT(cond, msg) \
    do { \
        if (cond) { printf("  [OK] %s\n", msg); passed++; } \
        else       { printf("  [FAIL] %s\n", msg); failed++; } \
    } while (0)

// ── territory tests ───────────────────────────────────────────────────────────
static void test_territory() {
    printf("\n[TESTE] Territory\n");

    Territory *t = create_territory(1, "Brasil", 100, 1);
    ASSERT(t != NULL, "create_territory retorna ponteiro valido");
    ASSERT(t->id == 1, "id correto");
    ASSERT(strcmp(t->name, "Brasil") == 0, "nome correto");
    ASSERT(t->army_count == 100, "exercito correto");
    ASSERT(t->owner == 1, "dono correto");

    Territory *defender = create_territory(2, "Argentina", 10, 2);
    int result = attack_territory(t, defender);
    ASSERT(result == 1, "ataque bem-sucedido quando atacante tem tropas suficientes");
    ASSERT(defender->owner == 1, "dono do territorio atualizado apos conquista");

    free_territory(t);
    free_territory(defender);
}

// ── mission tests ─────────────────────────────────────────────────────────────
static void test_mission() {
    printf("\n[TESTE] Mission\n");

    Mission *m = mission_create(CONQUER, 3, "Conquistar 3 territorios");
    ASSERT(m != NULL, "mission_create retorna ponteiro valido");
    ASSERT(strcmp(mission_get_description(m), "Conquistar 3 territorios") == 0, "descricao correta");
    ASSERT(mission_get_target(m) == 3, "alvo correto");
    ASSERT(mission_is_completed(m) == 0, "missao inicia incompleta");

    mission_check_progress(m, 2);
    ASSERT(mission_is_completed(m) == 0, "missao incompleta com progresso parcial");

    mission_check_progress(m, 3);
    ASSERT(mission_is_completed(m) == 1, "missao completa ao atingir alvo");

    mission_free(m);
}

// ── game_engine tests ─────────────────────────────────────────────────────────
static int dummy_attack(Territory *a, Territory *d) {
    (void)a;
    d->army_count = 0;
    d->owner = a->owner;
    return 1;
}

static int dummy_victory(Mission *m) {
    return mission_is_completed(m);
}

static void test_engine() {
    printf("\n[TESTE] GameEngine\n");

    GameEngine *engine = engine_create(dummy_attack, dummy_victory);
    ASSERT(engine != NULL, "engine_create retorna ponteiro valido");

    Mission *m = mission_create(CONQUER, 1, "Conquistar 1 territorio");
    engine_add_mission(engine, m);

    Territory *a = create_territory(1, "Brasil",   100, 1);
    Territory *b = create_territory(2, "Uruguai",   30, 2);

    int result = engine_execute_attack(engine, a, b);
    ASSERT(result == 1, "engine_execute_attack retorna 1 na vitoria");

    int victory = engine_check_victory(engine);
    ASSERT(victory == 1, "engine_check_victory detecta missao completa");

    free_territory(a);
    free_territory(b);
    engine_free(engine);
}

// ── game struct tests ─────────────────────────────────────────────────────────
static void test_game() {
    printf("\n[TESTE] Game\n");

    Game *game = initialize_game();
    ASSERT(game != NULL, "initialize_game retorna ponteiro valido");
    ASSERT(game->num_territorios == 0, "num_territorios inicia em 0");

    // Adicionar territorios manualmente para testar atacar_territorio / verificar_vitoria
    game->num_territorios = 3;
    game->territorios = (Territorio*)malloc(3 * sizeof(Territorio));
    ASSERT(game->territorios != NULL, "alocacao de territorios bem-sucedida");

    strncpy(game->territorios[0].nome, "Brasil",    49); game->territorios[0].tropas = 100; game->territorios[0].jogador = 1;
    strncpy(game->territorios[1].nome, "Argentina", 49); game->territorios[1].tropas =  10; game->territorios[1].jogador = 2;
    strncpy(game->territorios[2].nome, "Uruguai",   49); game->territorios[2].tropas =   5; game->territorios[2].jogador = 2;

    int r = atacar_territorio(game, 0, 1);
    ASSERT(r == 1, "atacar_territorio retorna 1 na conquista");
    ASSERT(game->territorios[1].jogador == 1, "jogador atualizado apos conquista");

    r = atacar_territorio(game, 0, 2);
    ASSERT(r == 1, "segundo ataque bem-sucedido");

    verificar_vitoria(game);  // should print vitoria for jogador 1
    ASSERT(1, "verificar_vitoria executada sem crash");

    free_game(game);
}

// ── main ──────────────────────────────────────────────────────────────────────
int main() {
    printf("══════════════════════════════════\n");
    printf("  TESTES DO WAR GAME              \n");
    printf("══════════════════════════════════\n");

    test_territory();
    test_mission();
    test_engine();
    test_game();

    printf("\n══════════════════════════════════\n");
    printf("  Resultado: %d OK  |  %d FALHA   \n", passed, failed);
    printf("══════════════════════════════════\n\n");

    return (failed > 0) ? 1 : 0;
}
