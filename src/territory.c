#include <stdlib.h>
#include <string.h>
#include "../include/territory.h"

// Criar novo território com malloc
Territory* create_territory(int id, const char* name, int army_count, int owner) {
    Territory* t = (Territory*)malloc(sizeof(Territory));
    if (t == NULL) return NULL;
    
    t->id = id;
    strncpy(t->name, name, 49);
    t->name[49] = '\0';
    t->army_count = army_count;
    t->owner = owner;
    
    return t;
}

// Simular ataque entre territórios (combate em múltiplas rodadas)
int attack_territory(Territory* attacker, Territory* defender) {
    if (!attacker || !defender) return -1;
    if (attacker->army_count <= 0) return 0;  // Sem exército

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
        return 1;  // Vitória do atacante
    }

    attacker->army_count = (troops_a > 0) ? troops_a : 0;
    return 0;  // Ataque falhou
}

// Liberar memória
void free_territory(Territory* territory) {
    if (territory) free(territory);
}
