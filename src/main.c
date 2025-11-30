#include <stdio.h>
#include <stdlib.h>
#include "../include/territory.h"

int main() {
    printf("\n");
    printf("═════════════════════════════════════\n");
    printf("        GUERRA ESTRATÉGICA v2.0      \n");
    printf("═════════════════════════════════════\n\n");
    
    // Criar dois territórios
    Territory* brasil = create_territory(1, "Brasil", 100, 1);
    Territory* argentina = create_territory(2, "Argentina", 50, 2);
    
    if (!brasil || !argentina) {
        printf("[ERRO] Falha ao alocar memória!\n");
        return 1;
    }
    
    printf("[INÍCIO] Territórios criados com malloc\n");
    printf("  %s (Jogador): %d exércitos\n", brasil->name, brasil->army_count);
    printf("  %s (Inimigo): %d exércitos\n\n", argentina->name, argentina->army_count);
    
    // Simular ataque
    printf("[ATAQUE] %s atacando %s...\n\n", brasil->name, argentina->name);
    int resultado = attack_territory(brasil, argentina);
    
    printf("  Resultado do ataque:\n");
    printf("  %s: %d exércitos restantes\n", brasil->name, brasil->army_count);
    printf("  %s: %d exércitos restantes\n", argentina->name, argentina->army_count);
    
    if (resultado == 1) {
        printf("\n  ✓ %s conquistou %s!\n", brasil->name, argentina->name);
    } else if (resultado == 0) {
        printf("\n  ✗ %s resistiu ao ataque!\n", argentina->name);
    }
    
    // Liberar memória com free
    printf("\n[LIMPEZA] Liberando memória com free...\n");
    free_territory(brasil);
    free_territory(argentina);
    
    printf("\n═════════════════════════════════════\n");
    printf("     Jogo finalizado com sucesso!    \n");
    printf("═════════════════════════════════════\n\n");
    
    return 0;
}
