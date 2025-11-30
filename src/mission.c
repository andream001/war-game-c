#include <stdlib.h>
#include <string.h>
#include "../include/mission.h"

// Estrutura privada - Encapsulamento
struct Mission {
    MissionType type;
    int target;
    int progress;
    char description[100];
    int completed;
};

// CRIAR MISSÃO - Aloca com malloc
Mission* mission_create(MissionType type, int target, const char* description) {
    Mission* m = (Mission*)malloc(sizeof(Mission));
    if (!m) return NULL;
    
    m->type = type;
    m->target = target;
    m->progress = 0;
    m->completed = 0;
    strncpy(m->description, description, 99);
    m->description[99] = '\0';
    
    return m;
}

// LIBERAR MISSÃO
void mission_free(Mission* mission) {
    if (mission) free(mission);
}

// VERIFICAR PROGRESSO - Passagem por referência
int mission_check_progress(Mission* mission, int current_progress) {
    if (!mission) return 0;
    
    mission->progress = current_progress;
    
    if (mission->progress >= mission->target && !mission->completed) {
        mission->completed = 1;
        return 1;  // Completada
    }
    return 0;  // Não completada
}

// VERIFICAR SE ESTÁ COMPLETA - const correctness
int mission_is_completed(const Mission* mission) {
    if (!mission) return 0;
    return mission->completed;
}

// GETTERS - ENCAPSULAMENTO - const correctness
const char* mission_get_description(const Mission* mission) {
    return mission ? mission->description : "";
}

int mission_get_target(const Mission* mission) {
    return mission ? mission->target : 0;
}

MissionType mission_get_type(const Mission* mission) {
    return mission ? mission->type : CONQUER;
}
