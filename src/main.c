#include <stdio.h>
#include <stdlib.h>
#include "../include/territory.h"
#include "../include/mission.h"
#include "../include/game_engine.h"

// Callback: Função de ataque personalizada (combate em múltiplas rodadas)
int custom_attack(Territory* attacker, Territory* defender) {
    if (!attacker || !defender) return 0;

    int troops_a = attacker->army_count;
    int troops_d = defender->army_count;

    while (troops_a > 0 && troops_d > 0) {
        int loss_a = troops_a / 3 + 1;
        int loss_d = troops_d / 2 + 1;
        troops_a -= loss_a;
        troops_d -= loss_d;
    }

    if (troops_d <= 0 && troops_a > 0) {
        attacker->army_count = troops_a;
        defender->army_count = 1;
        defender->owner = attacker->owner;
        return 1;
    }

    attacker->army_count = (troops_a > 0) ? troops_a : 0;
    return 0;
}

// Callback: Função de vitória
int check_mission_victory(Mission* mission) {
    return mission_is_completed(mission);
}

int main() {
    printf("\n");
    printf("═══════════════════════════════\n");
    printf(" GUERRA ESTRATÉGICA v3.0 - Com Missoes  \n");
    printf("═══════════════════════════════\n\n");
    
    // 1. Criar engine com callbacks
    GameEngine* engine = engine_create(custom_attack, check_mission_victory);
    if (!engine) {
        printf("[ERRO] Falha ao criar engine!\n");
        return 1;
    }
    printf("[LOG] Engine criada com sucesso\n");
    printf("Status: %s\n\n", engine_get_status(engine));
    
    // 2. Criar missão estratégica
    Mission* mission = mission_create(CONQUER, 2, "Conquistar 2 territórios");
    if (!mission) {
        printf("[ERRO] Falha ao criar missão!\n");
        engine_free(engine);
        return 1;
    }
    printf("[LOG] Missão criada: %s\n", mission_get_description(mission));
    printf("Alvo: %d territórios\n\n", mission_get_target(mission));
    
    // 3. Adicionar missão à engine
    engine_add_mission(engine, mission);
    printf("Status: %s\n\n", engine_get_status(engine));
    
    // 4. Criar territórios
    Territory* brasil = create_territory(1, "Brasil", 200, 1);
    Territory* argentina = create_territory(2, "Argentina", 50, 2);
    Territory* uruguai = create_territory(3, "Uruguai", 40, 2);
    
    printf("[TERRITÓRIOS]\n");
    printf("  %s (Jogador): %d exércitos\n", brasil->name, brasil->army_count);
    printf("  %s (Inimigo): %d exércitos\n", argentina->name, argentina->army_count);
    printf("  %s (Inimigo): %d exércitos\n\n", uruguai->name, uruguai->army_count);
    
    // 5. Executar ataques via engine
    printf("[ATAQUE]\n");
    int attack1 = engine_execute_attack(engine, brasil, argentina);
    printf("  Ataque 1: %s\n", attack1 ? "VENCEU!" : "Falhou");
    printf("  Status: %s\n\n", engine_get_status(engine));
    
    int attack2 = engine_execute_attack(engine, brasil, uruguai);
    printf("  Ataque 2: %s\n", attack2 ? "VENCEU!" : "Falhou");
    printf("  Status: %s\n\n", engine_get_status(engine));
    
    // 6. Verificar vitória
    printf("[VERIFICANDO VITÓRIA]\n");
    int victory = engine_check_victory(engine);
    printf("  Missão completa: %s\n", victory ? "SIM!" : "Não");
    printf("  Status: %s\n\n", engine_get_status(engine));
    
    // 7. Liberar memória (game_engine já libera mission)
    printf("[LIMPEZA]\n");
    free_territory(brasil);
    free_territory(argentina);
    free_territory(uruguai);
    engine_free(engine);
    printf("Memória liberada com sucesso!\n\n");
    
    printf("═══════════════════════════════\n");
    printf(" Versão 3.0 finalizada com sucesso!    \n");
    printf("═══════════════════════════════\n\n");
    
    return 0;
}
