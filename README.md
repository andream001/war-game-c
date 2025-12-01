# War Game (C)

**Guerra Estratégica** - Jogo War implementado em C com foco em estruturas de dados, ponteiros e alocação dinâmica de memória. Projeto desafiador com 3 níveis de implementação: Novato, Aventureiro e Mestre.

## Badges

![Linguagem C](https://img.shields.io/badge/Linguagem-C-blue)
![GCC](https://img.shields.io/badge/Compilador-GCC-green)

## Características

- **TAD (Tipo Abstrato de Dados)**: Encapsulamento completo com estruturas opacas
- **Ponteiros para Funções**: Callbacks customizáveis para ataques e verificação de vitória
- **Alocação Dinâmica**: Uso de malloc/calloc com liberação correta de memória
- **Modularização**: Código organizado em módulos separados (Territory, Mission, GameEngine)
- **Passagem por Referência**: Manipulação eficiente de estruturas

## Pré-requisitos

- GCC (ou outro compilador C compatível com C99)
- make
- valgrind (opcional, para verificação de memória)

## Compilação

Este projeto usa Makefile para compilação. Os comandos disponíveis são:

```bash
# Compilar o projeto
make build

# Ou simplesmente:
make
```

### Flags de compilação utilizadas

O Makefile usa as seguintes flags recomendadas:
- `-Wall -Wextra`: Avisos extras para código mais seguro
- `-std=c99`: Padrão C99
- `-g`: Símbolos de debug
- `-O2`: Otimização de nível 2

## Execução

Após compilar, execute o jogo:

```bash
# Compilar e executar
make run

# Ou executar diretamente o binário
./build/war-game
```

### Exemplo de saída

```
═══════════════════════════════
 GUERRA ESTRATÉGICA v3.0 - Com Missoes  
═══════════════════════════════

[LOG] Engine criada com sucesso
Status: Aguardando missão

[LOG] Missão criada: Conquistar 2 territórios
Alvo: 2 territórios

[TERRITÓRIOS]
  Brasil (Jogador): 100 exércitos
  Argentina (Inimigo): 50 exércitos
  Uruguai (Inimigo): 40 exércitos
```

### Comandos Make disponíveis

| Comando | Descrição |
|---------|-----------|
| `make build` | Compilar o projeto |
| `make run` | Compilar e executar |
| `make valgrind` | Testar vazamentos de memória |
| `make clean` | Limpar artefatos de build |
| `make help` | Exibir ajuda |

## Estrutura do projeto

```
war-game-c/
├── src/                    # Código-fonte (.c)
│   ├── main.c              # Ponto de entrada do programa
│   ├── game.c              # Lógica principal do jogo
│   ├── game_engine.c       # Engine com callbacks
│   ├── territory.c         # TAD Território
│   └── mission.c           # TAD Missão
├── include/                # Cabeçalhos (.h)
│   ├── game.h              # Interface do jogo
│   ├── game_engine.h       # Interface da engine
│   ├── territory.h         # Interface de território
│   └── mission.h           # Interface de missão
├── build/                  # Binários gerados (ignorado no VCS)
├── Makefile                # Script de compilação
├── CONTRIBUTING.md         # Guia de contribuição
└── README.md               # Este arquivo
```

## Níveis de Implementação

### Nível 1: Novato
- Estruturas básicas de territórios
- Leitura/escrita simples

### Nível 2: Aventureiro
- Ponteiros para funções
- Alocação dinâmica com malloc/calloc
- Lógica de ataque

### Nível 3: Mestre
- Modularização completa
- Passagem por referência
- Sistema de missões com TAD

## Como contribuir

1. Abra uma issue descrevendo sua proposta ou bug
2. Faça um fork e crie uma branch com um nome descritivo
3. Envie um pull request com descrição clara das mudanças

### Boas práticas

- Mantenha o código limpo e bem comentado
- Use nomes descritivos para variáveis e funções
- Libere memória corretamente (use `valgrind` para verificar)
- Teste seus commits antes de fazer push

Para mais detalhes, consulte o arquivo [CONTRIBUTING.md](CONTRIBUTING.md).

## Licença

Este projeto ainda não possui uma licença definida. Considere usar MIT. Confirme qual licença deseja usar.

## Autor

- [@andream001](https://github.com/andream001)

---

Desenvolvido como projeto educacional para prática de C com estruturas de dados avançadas.
