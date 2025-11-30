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

// Simular ataque entre territórios
int attack_territory(Territory* attacker, Territory* defender) {
    if (!attacker || !defender) return -1;
    if (attacker->army_count <= 0) return 0;  // Sem exército
    
    // Cálculo simples: ataque vs defesa
    int attacker_loss = attacker->army_count / 3;
    int defender_loss = defender->army_count / 2;
    
    attacker->army_count -= attacker_loss;
    defender->army_count -= defender_loss;
    
    if (defender->army_count <= 0) {
        defender->owner = attacker->owner;
        return 1;  // Vitória do atacante
    }
    return 0;  // Ataque falhou
}

// Liberar memória
void free_territory(Territory* territory) {
    if (territory) free(territory);
}
