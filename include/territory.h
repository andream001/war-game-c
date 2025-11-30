#ifndef TERRITORY_H
#define TERRITORY_H

typedef struct {
    int id;
    char name[50];
    int army_count;
    int owner;  // 1 = player, 2 = enemy
} Territory;

// Funções
Territory* create_territory(int id, const char* name, int army_count, int owner);
int attack_territory(Territory* attacker, Territory* defender);
void free_territory(Territory* territory);

#endif
