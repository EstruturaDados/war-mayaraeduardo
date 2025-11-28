# Projeto WAR - Níveis Novato, Aventureiro e Mestre

Este repositório contém implementações em C para três níveis do desafio: **Novato**, **Aventureiro** e **Mestre**.
Todos os arquivos estão comentados em Português para demonstrar entendimento do código.

## Estrutura
- `novato.c`       : Nível Novato — vetor estático de territórios (5), leitura simples e exibição.
- `aventureiro.c`  : Nível Aventureiro — alocação dinâmica, simulação de ataques entre territórios.
- `mestre.c`       : Nível Mestre — modularização, menu, missões aleatórias e verificação de objetivos.
- `Makefile`       : Facilita a compilação dos três programas.

## Como compilar
No terminal (Linux / macOS / Codespaces):
```bash
make
```

## Como executar
Após compilar:
- `./novato`       # Executa o nível Novato
- `./aventureiro`  # Executa o nível Aventureiro
- `./mestre`       # Executa o nível Mestre

Cada programa usa leitura via terminal (stdin). Siga as instruções exibidas no terminal para cadastrar territórios e simular ataques.

## Passo-a-passo para entrega (SAVA)
1. Acesse o GitHub Classroom e abra o repositório do desafio.
2. Faça upload dos arquivos deste projeto (`novato.c`, `aventureiro.c`, `mestre.c`, `Makefile`, `README.md`) no repositório — você pode usar Codespaces ou git local.
3. Compile e teste usando `make`.
4. Commit e push para o repositório principal:
```bash
git add novato.c aventureiro.c mestre.c Makefile README.md
git commit -m "Implementação completa: níveis Novato, Aventureiro e Mestre"
git push origin main
```
5. Envie o link do repositório no SAVA.

## Observações
- Todos os arquivos possuem comentários explicando estruturas, funções e lógica principal — isso ajuda na correção.
- Se quiser, altere `N_TERRITORIOS` para testar com mais territórios (algumas funções assumem 5 inicialmente).
- Em Codespaces, crie um novo Codespace pelo botão **Code → Codespaces → Create codespace on main**.
