#ifndef MISSION_H
#define MISSION_H

#include "territory.h"

// Tipo de missão
typedef enum {
    CONQUER,        // Conquistar N territórios
    ELIMINATE,      // Eliminar inimigo
    DEFEND          // Defender X turnos
} MissionType;

// TAD Mission - Encapsulamento completo
typedef struct Mission Mission;

// Criação e destruição
Mission* mission_create(MissionType type, int target, const char* description);
void mission_free(Mission* mission);

// Verificação de conclusão - PASSAGEM POR REFERÈNCIA
int mission_check_progress(Mission* mission, int current_progress);
int mission_is_completed(const Mission* mission);

// Getters - ENCAPSULAMENTO
const char* mission_get_description(const Mission* mission);
int mission_get_target(const Mission* mission);
MissionType mission_get_type(const Mission* mission);

#endif
